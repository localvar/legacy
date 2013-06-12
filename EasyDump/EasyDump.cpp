#include "stdafx.h"
#include "EasyDump.h"


////////////////////////////////////////////////////////////////////////////////


struct CDumpThreadArgument
{
	BOOL bAttach;					// 附加到已有进程?
	DWORD dwPid;					// 进程PID, 仅在附加时有效
	TCHAR szImgPath[MAX_PATH];		// 进程路径
	TCHAR szArg[MAX_ARGUMENT_LEN];	// 进程启动参数, 仅在新建进程时有效
	TCHAR szWorkDir[MAX_PATH];		// 工作目录, 仅在新建进程时有效
};

typedef BOOL (WINAPI* FxDetachDebuggee)( DWORD );


////////////////////////////////////////////////////////////////////////////////


static FxDetachDebuggee g_fnDetachDebuggee = NULL;

static HANDLE g_hStopEvent = NULL;
static HANDLE g_hSnapshotEvent = NULL;
static HANDLE g_hNotifyEvent = NULL;
static HANDLE g_hThread = NULL;

static DWORD volatile g_dwPid = 0xffffffff;
static HANDLE g_hProc = NULL;
static DWORD g_dwDumpCounter = 0;
static BOOL g_bSeenInitialBP = FALSE;
static BOOL g_bAeDebug = FALSE;
static TCHAR g_szLastFirstChance[MAX_PATH];
static TCHAR g_szImgName[MAX_PATH];


////////////////////////////////////////////////////////////////////////////////


static BOOL DetachDebuggee( DWORD dwPid )
{
	if( g_fnDetachDebuggee != NULL )
		return (*g_fnDetachDebuggee)( dwPid );
	return FALSE;
}


////////////////////////////////////////////////////////////////////////////////


static BOOL DoDump(
				   LPCTSTR szFileName,
				   DWORD dwDumpType,
				   PMINIDUMP_EXCEPTION_INFORMATION pMEI
				   )
{
	HANDLE hFile = CreateFile(
		szFileName,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);
	if( hFile == INVALID_HANDLE_VALUE )
	{
		LogEvent( IDS_CREATE_FILE_FAILED, GetLastError() );
		return FALSE;
	}

	BOOL ok = MiniDumpWriteDump(
		g_hProc,
		g_dwPid,
		hFile,
		static_cast<MINIDUMP_TYPE>( dwDumpType ),
		pMEI,
		NULL,
		NULL
		);

	if( ok )
	{
		++g_dwDumpCounter;
		LogEvent( IDS_DUMP_SUCCEEDED, szFileName );
		CloseHandle( hFile );
	}
	else
	{
		LogEvent( IDS_DUMP_FAILED, GetLastError() );
		CloseHandle( hFile );
		DeleteFile( szFileName );
	}

	return ok;
}


////////////////////////////////////////////////////////////////////////////////


static BOOL DumpHang()
{
	TCHAR szFileName[MAX_PATH];
	GetDumpPath( szFileName, _countof(szFileName) );
	size_t len = _tcslen( szFileName );
	_sntprintf( szFileName + len, _countof(szFileName) - len,
		_T("\\%s_PID%d_hang_%04d.dmp"), g_szImgName, g_dwPid, g_dwDumpCounter );
	szFileName[_countof(szFileName) - 1] = 0;

	LogEvent( IDS_BEGIN_SNAPSHOT );

	BOOL ok = DoDump( szFileName, Settings.dwSnapshot, NULL );

	SetEvent( g_hNotifyEvent );
	return ok;
}


////////////////////////////////////////////////////////////////////////////////
// 附加或创建目标进程

static DWORD DoAttach( CDumpThreadArgument* arg )
{
	// 先检查目标进程是否确实是用户想附加的那个, 虽然这样仍有可能附加错误
	// 的进程, 但概率极低. 先附加后检查在win2k系统上可能会导致必须杀掉那个
	// 被错误附加的进程
	TCHAR szPath[MAX_PATH];
	if( !GetImagePathByPid( arg->dwPid, szPath, _countof(szPath) ) )
	{
		LogEvent( IDS_GET_IMAGE_PATH_FAILED );
		return 0xffffffff;
	}

	if( _tcsicmp( szPath, arg->szImgPath ) != 0 )
	{
		LogEvent( IDS_IMAGE_PATH_MISMATCH );
		return 0xffffffff;
	}

	if( !DebugActiveProcess( arg->dwPid ) )
	{
		LogEvent( IDS_ATTACH_PROCESS_FAILED, GetLastError() );
		return 0xffffffff;
	}

	GetImageNameByPid( arg->dwPid, g_szImgName, _countof(g_szImgName) );
	return arg->dwPid;
}

//------------------------------------------------------------------------------

static DWORD DoCreate( CDumpThreadArgument* arg )
{
	STARTUPINFO si = {};
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi = {};

	BOOL ok = CreateProcess( 
		arg->szImgPath,
		arg->szArg,
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE | DEBUG_ONLY_THIS_PROCESS,
		NULL,
		arg->szWorkDir[0] == 0 ? NULL : arg->szWorkDir,
		&si,
		&pi
		);

	if( !ok )
	{
		LogEvent( IDS_CREATE_PROCESS_FAILED, GetLastError() );
		return 0xffffffff;
	}

	GetFileTitle( arg->szImgPath, g_szImgName, _countof(g_szImgName) );
	return pi.dwProcessId;
}

//------------------------------------------------------------------------------

static BOOL AttachOrCreate( CDumpThreadArgument* arg )
{
	DWORD pid = 0xffffffff;

	if( arg->bAttach )
		pid = DoAttach( arg );
	else
		pid = DoCreate( arg );
	delete arg;

	if( pid != 0xffffffff )
	{
		g_dwPid = pid;
		SetEvent( g_hNotifyEvent );
		LogEvent( IDS_PROCESS_CREATE_OR_ATTACHED, pid );
		return TRUE;
	}

	return FALSE;
}


////////////////////////////////////////////////////////////////////////////////


static void GetThreadContext( DWORD dwTid, LPCONTEXT lpContext )
{
	DWORD dwFlag = THREAD_QUERY_INFORMATION | THREAD_GET_CONTEXT;
	HANDLE hThread = OpenThread( dwFlag, FALSE, dwTid );
	ATLASSERT( hThread != NULL );
	ATLVERIFY( GetThreadContext( hThread, lpContext ) );
	CloseHandle( hThread );
}


////////////////////////////////////////////////////////////////////////////////


static BOOL DumpCrash( LPDEBUG_EVENT pde, LPCTSTR szFileName, DWORD dwDumpType )
{
	CONTEXT Context;
	Context.ContextFlags = 0xffffffff;	// all field are needed
	GetThreadContext( pde->dwThreadId, &Context );

	EXCEPTION_POINTERS ep;
	ep.ExceptionRecord = &pde->u.Exception.ExceptionRecord;
	ep.ContextRecord = &Context;

	MINIDUMP_EXCEPTION_INFORMATION mei;
	mei.ThreadId = pde->dwThreadId;
	mei.ExceptionPointers = &ep;
	mei.ClientPointers = FALSE;

	return DoDump( szFileName, dwDumpType, &mei );
}


////////////////////////////////////////////////////////////////////////////////


static BOOL OnFirstChance( LPDEBUG_EVENT pde )
{
	if( g_szLastFirstChance[0] != 0 )
	{
		if( Settings.bAutoDelete )
			DeleteFile( g_szLastFirstChance );
		g_szLastFirstChance[0] = 0;
	}

	if( FilterException( pde->u.Exception.ExceptionRecord.ExceptionCode ) )
		return TRUE;

	LogEvent( IDS_FIRST_CHANCE,
		pde->u.Exception.ExceptionRecord.ExceptionAddress,
		pde->u.Exception.ExceptionRecord.ExceptionCode
		);

	if( Settings.dwFirstChance == ED_DONT_DUMP )
		return TRUE;

	TCHAR szFileName[MAX_PATH];
	GetDumpPath( szFileName, _countof(szFileName) );
	size_t len = _tcslen( szFileName );
	_sntprintf( szFileName + len,
		_countof(szFileName) - len,
		_T("\\%s_PID%d_1st_%04d.dmp"),
		g_szImgName,
		g_dwPid,
		g_dwDumpCounter
		);
	szFileName[_countof(szFileName) - 1] = 0;

	ATLASSERT( _countof(g_szLastFirstChance) == _countof(szFileName) );
	_tcscpy( g_szLastFirstChance, szFileName );

	return DumpCrash( pde, szFileName, Settings.dwFirstChance );
}


////////////////////////////////////////////////////////////////////////////////


static BOOL OnSecondChance( LPDEBUG_EVENT pde )
{
	g_szLastFirstChance[0] = 0;
	LogEvent( IDS_SECOND_CHANCE,
		pde->u.Exception.ExceptionRecord.ExceptionAddress,
		pde->u.Exception.ExceptionRecord.ExceptionCode
		);

	if( Settings.dwSecondChance == ED_DONT_DUMP )
		return TRUE;

	TCHAR szFileName[MAX_PATH];
	GetDumpPath( szFileName, _countof(szFileName) );
	size_t len = _tcslen( szFileName );
	_sntprintf(
		szFileName + len,
		_countof(szFileName) - len,
		_T("\\%s_PID%d_2nd_%04d.dmp"),
		g_szImgName,
		g_dwPid,
		g_dwDumpCounter
		);
	szFileName[_countof(szFileName) - 1] = 0;

	return DumpCrash( pde, szFileName, Settings.dwSecondChance );
}


////////////////////////////////////////////////////////////////////////////////


static BOOL OnExceptionEvent( LPDEBUG_EVENT pde )
{
	DWORD ExceptionCode = pde->u.Exception.ExceptionRecord.ExceptionCode;
	DWORD dwContinue = DBG_EXCEPTION_NOT_HANDLED;
	g_bAeDebug = FALSE;

	// 放过加载器设置的断点
	if( ExceptionCode == EXCEPTION_BREAKPOINT && g_bSeenInitialBP == FALSE )
	{
		g_bSeenInitialBP = TRUE;
		dwContinue = DBG_CONTINUE;
	}
	else if( pde->u.Exception.dwFirstChance != 0 )
	{
		OnFirstChance( pde );
	}
	else
	{
		OnSecondChance( pde );
	}

	ContinueDebugEvent( pde->dwProcessId, pde->dwThreadId, dwContinue );
	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////


static BOOL OnCreateProcessEvent( LPDEBUG_EVENT pde )
{
	g_hProc = pde->u.CreateProcessInfo.hProcess;
	if( pde->u.CreateProcessInfo.hFile != NULL )
		CloseHandle( pde->u.CreateProcessInfo.hFile );
	ContinueDebugEvent( pde->dwProcessId, pde->dwThreadId, DBG_CONTINUE );
	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////


static BOOL OnExitProcessEvent( LPDEBUG_EVENT pde )
{
	// AeDebug的情况下, 收不到C++异常事件, 所以在这里处理一下
	if( g_bAeDebug && Settings.dwSecondChance != ED_DONT_DUMP )
	{
		TCHAR szFileName[MAX_PATH];
		GetDumpPath( szFileName, _countof(szFileName) );
		size_t len = _tcslen( szFileName );
		_sntprintf(
			szFileName + len,
			_countof(szFileName) - len,
			_T("\\%s_PID%d_crash_%04d.dmp"),
			g_szImgName,
			g_dwPid,
			g_dwDumpCounter
			);
		szFileName[_countof(szFileName) - 1] = 0;
		DoDump( szFileName, Settings.dwSecondChance, NULL );
	}
	LogEvent( IDS_PROCESS_EXIT, pde->u.ExitProcess.dwExitCode );
	ContinueDebugEvent( pde->dwProcessId, pde->dwThreadId, DBG_CONTINUE );
	return FALSE;
}


////////////////////////////////////////////////////////////////////////////////


static BOOL OnLoadDllEvent( LPDEBUG_EVENT pde )
{
	if( pde->u.LoadDll.hFile != NULL )
		CloseHandle( pde->u.LoadDll.hFile );
	ContinueDebugEvent( pde->dwProcessId, pde->dwThreadId, DBG_CONTINUE );
	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////


static BOOL OnDebugEvent( LPDEBUG_EVENT pde )
{
	switch( pde->dwDebugEventCode )
	{
	case EXCEPTION_DEBUG_EVENT:
		return OnExceptionEvent( pde );
		break;

	case CREATE_PROCESS_DEBUG_EVENT:
		return OnCreateProcessEvent( pde );
		break;

	case EXIT_PROCESS_DEBUG_EVENT:
		return OnExitProcessEvent( pde );
		break;

	case LOAD_DLL_DEBUG_EVENT:
		return OnLoadDllEvent( pde );
		break;
/*
	case CREATE_THREAD_DEBUG_EVENT:
		ContinueDebugEvent( pde->dwProcessId, pde->dwThreadId, DBG_CONTINUE );
		break;

	case EXIT_THREAD_DEBUG_EVENT:
		ContinueDebugEvent( pde->dwProcessId, pde->dwThreadId, DBG_CONTINUE );
		break;

	case OUTPUT_DEBUG_STRING_EVENT:
		ContinueDebugEvent( pde->dwProcessId, pde->dwThreadId, DBG_CONTINUE );
		break;

	case RIP_EVENT:
		ContinueDebugEvent( pde->dwProcessId, pde->dwThreadId, DBG_CONTINUE );
		break;

	case UNLOAD_DLL_DEBUG_EVENT:
		ContinueDebugEvent( pde->dwProcessId, pde->dwThreadId, DBG_CONTINUE );
		break;
		*/
	default:
		ContinueDebugEvent( pde->dwProcessId, pde->dwThreadId, DBG_CONTINUE );
		break;
	}

	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////


static unsigned DumpThread( CDumpThreadArgument* arg )
{
	if( !AttachOrCreate( arg ) )
		return 0;

	g_dwDumpCounter = 0;
	g_bSeenInitialBP = FALSE;
	g_szLastFirstChance[0] = 0;

	BOOL bContinue = TRUE;
	HANDLE aEvent[] = { g_hStopEvent, g_hSnapshotEvent };

	while( bContinue )
	{
		// 处理调试事件
		DEBUG_EVENT de;
		while( WaitForDebugEvent( &de, 100 ) )
			bContinue = OnDebugEvent( &de );

		// 处理用户事件
		DWORD res = WaitForMultipleObjects(
			_countof(aEvent),
			aEvent,
			FALSE,
			0
			);

		if( res == WAIT_OBJECT_0 + 1 )	// 快照
		{
			DumpHang();
			continue;
		}

		if( res == WAIT_OBJECT_0 )		// 退出
		{
			bContinue = FALSE;
			if( !Settings.bKillOnExit )
				DetachDebuggee( g_dwPid );
		}
	}

	LogEvent( IDS_PROCESS_DETACHED );
	return 0;
}

//------------------------------------------------------------------------------

static unsigned __stdcall DumpThreadStub( void* arg )
{
	return DumpThread( reinterpret_cast<CDumpThreadArgument*>( arg ) );
}


////////////////////////////////////////////////////////////////////////////////


BOOL DumpAeDebug( DWORD dwPid, HANDLE hEvent )
{
	if( !DebugActiveProcess( dwPid ) )
		return FALSE;

	ATLVERIFY( GetImageNameByPid( dwPid, g_szImgName, _countof(g_szImgName) ) );
	g_dwPid = dwPid;

	ATLVERIFY( SetEvent( hEvent ) );

	g_dwDumpCounter = 0;
	g_bSeenInitialBP = FALSE;
	g_bAeDebug = TRUE;
	g_szLastFirstChance[0] = 0;

	DEBUG_EVENT de;
	while( WaitForDebugEvent( &de, 100 ) )
		OnDebugEvent( &de );

	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////


DWORD DumpStart( DWORD dwPid, LPCTSTR szImgPath )
{
	CDumpThreadArgument* arg = new CDumpThreadArgument();
	arg->bAttach = TRUE;
	arg->dwPid = dwPid;
	_tcsncpy( arg->szImgPath, szImgPath, _countof(arg->szImgPath) );
	arg->szImgPath[_countof(arg->szImgPath) - 1] = 0;
	arg->szArg[0] = 0;
	arg->szWorkDir[0] = 0;

	uintptr_t handle = ::_beginthreadex(
		NULL,
		0,
		DumpThreadStub,
		arg,
		0,
		NULL
		);

	if( handle == 0 )
	{
		delete arg;
		return 0xffffffff;
	}

	g_hThread = reinterpret_cast<HANDLE>( handle );
	HANDLE aHandle[] = { g_hNotifyEvent, g_hThread };
	WaitForMultipleObjects( _countof(aHandle), aHandle, FALSE, INFINITE );
	return g_dwPid;
}


////////////////////////////////////////////////////////////////////////////////


DWORD DumpStart( LPCTSTR szImgPath, LPCTSTR szArg, LPCTSTR szWorkDir )
{
	CDumpThreadArgument* arg = new CDumpThreadArgument();
	arg->bAttach = FALSE;
	arg->dwPid = 0;
	_tcsncpy( arg->szImgPath, szImgPath, _countof(arg->szImgPath) );
	arg->szImgPath[_countof(arg->szImgPath) - 1] = 0;
	_tcsncpy( arg->szArg, szArg, _countof(arg->szArg) );
	arg->szArg[_countof(arg->szArg) - 1] = 0;
	_tcsncpy( arg->szWorkDir, szWorkDir, _countof(arg->szWorkDir) );
	arg->szWorkDir[_countof(arg->szWorkDir) - 1] = 0;

	uintptr_t handle = ::_beginthreadex(
		NULL,
		0,
		DumpThreadStub,
		arg,
		0,
		NULL
		);

	if( handle == 0 )
	{
		delete arg;
		return 0xffffffff;
	}

	g_hThread = reinterpret_cast<HANDLE>( handle );
	HANDLE aHandle[] = { g_hNotifyEvent, g_hThread };
	WaitForMultipleObjects( _countof(aHandle), aHandle, FALSE, INFINITE );
	return g_dwPid;
}


////////////////////////////////////////////////////////////////////////////////


void DumpStop()
{
	if( g_hThread != NULL )
	{
		SetEvent( g_hStopEvent );
		WaitForSingleObject( g_hThread, INFINITE );
		CloseHandle( g_hThread );
		g_hThread = NULL;
	}

	// 这些事件可能没有被成功等待, 全部重置一下
	ResetEvent( g_hStopEvent );
	ResetEvent( g_hSnapshotEvent );
	ResetEvent( g_hNotifyEvent );
}


////////////////////////////////////////////////////////////////////////////////


void DumpSnapshot()
{
	SetEvent( g_hSnapshotEvent );

	// 同时等待通知事件和线程, 可能没有处理请求, 就退出了
	HANDLE aHandle[] = { g_hNotifyEvent, g_hThread };
	WaitForMultipleObjects( _countof(aHandle), aHandle, FALSE, INFINITE );
}


////////////////////////////////////////////////////////////////////////////////


BOOL IsDumping()
{
	if( g_hThread == NULL )
		return FALSE;
	if( WaitForSingleObject( g_hThread, 0 ) == WAIT_TIMEOUT )
		return TRUE;
	return FALSE;
}


////////////////////////////////////////////////////////////////////////////////


BOOL IsDetachSupported()
{
	return g_fnDetachDebuggee != NULL;
}


////////////////////////////////////////////////////////////////////////////////


BOOL DumpInit()
{
	HINSTANCE inst = GetModuleHandle( _T("Kernel32.dll") );
	FARPROC p = GetProcAddress( inst, "DebugActiveProcessStop" );
	g_fnDetachDebuggee = reinterpret_cast<FxDetachDebuggee>( p );

	g_hStopEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
	g_hSnapshotEvent = CreateEvent( NULL, FALSE,FALSE, NULL );
	g_hNotifyEvent = CreateEvent( NULL, FALSE,FALSE, NULL );
	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////


void DumpUninit()
{
	CloseHandle( g_hNotifyEvent );
	g_hNotifyEvent = NULL;
	CloseHandle( g_hSnapshotEvent );
	g_hSnapshotEvent = NULL;
	CloseHandle( g_hStopEvent );
	g_hStopEvent = NULL;
}


////////////////////////////////////////////////////////////////////////////////
