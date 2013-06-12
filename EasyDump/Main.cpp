#include "stdafx.h"
#include "EasyDump.h"
#include "inirdwrt.h"
#include "MainDlg.h"


////////////////////////////////////////////////////////////////////////////////
// 全局变量

CAppModule _Module;
CSettings Settings;

static CAtlArray<CExceptionInfo> g_aException;
static CRITICAL_SECTION g_cs;

static CMainDlg* g_pMainWnd = NULL;


////////////////////////////////////////////////////////////////////////////////
// 通过PID得到映像名称

BOOL GetImageNameByPid( DWORD dwPid, LPTSTR szBuf, DWORD cbBuf )
{
	HANDLE hss = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, dwPid );
	if( hss == INVALID_HANDLE_VALUE )
		return FALSE;

	MODULEENTRY32 me = { sizeof(MODULEENTRY32) };
	if( Module32First( hss, &me ) )
	{
		_tcsncpy( szBuf, me.szModule, cbBuf );
		szBuf[cbBuf - 1] = 0;
		CloseHandle( hss );
		return TRUE;
	}

	CloseHandle( hss );
	return FALSE;
}


////////////////////////////////////////////////////////////////////////////////
// 通过PID得到映像路径

BOOL GetImagePathByPid( DWORD dwPid, LPTSTR szBuf, DWORD cbBuf )
{
	HANDLE hss = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, dwPid );
	if( hss == INVALID_HANDLE_VALUE )
		return FALSE;

	MODULEENTRY32 me = { sizeof(MODULEENTRY32) };
	if( Module32First( hss, &me ) )
	{
		_tcsncpy( szBuf, me.szExePath, cbBuf );
		szBuf[cbBuf - 1] = 0;
		CloseHandle( hss );
		return TRUE;
	}

	CloseHandle( hss );
	return FALSE;
}


////////////////////////////////////////////////////////////////////////////////
// 记录日志

void LogEvent( UINT uEventId, ... )
{
	if( g_pMainWnd == NULL )
		return;

	TCHAR fmt[256];
	if( AtlLoadString( uEventId, fmt, _countof(fmt) ) <= 0 )
	{
		ATLASSERT( FALSE );
		return;
	}

	LPTSTR log = NULL;
	va_list arg;
	va_start( arg, uEventId );
	FormatMessage(
		FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		fmt,
		0,
		0,
		reinterpret_cast<LPTSTR>( &log ),
		0,
		&arg
		);

	g_pMainWnd->PostMessage( WM_LOG_EVENT, reinterpret_cast<WPARAM>(log), 0 );
}


////////////////////////////////////////////////////////////////////////////////
// 消息框

int MessageBoxV( HWND hWnd, UINT uTextFmt, UINT uType, ... )
{
	TCHAR fmt[256], caption[32];
	if( AtlLoadString( uTextFmt, fmt, _countof(fmt) ) <= 0 )
	{
		ATLASSERT( FALSE );
		fmt[0] = 0;
	}

	LPTSTR text = NULL;
	va_list arg;
	va_start( arg, uType );
	FormatMessage(
		FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		fmt,
		0,
		0,
		reinterpret_cast<LPTSTR>( &text ),
		0,
		&arg
		);

	AtlLoadString( IDR_MAINFRAME, caption, _countof(caption) );

	int res = MessageBox( hWnd, text, caption, uType );
	LocalFree( text );
	return res;
}


////////////////////////////////////////////////////////////////////////////////


static CExceptionInfo* GetExceptionInfoByCode( DWORD dwExceptionCode )
{
	for( size_t i = 0; i < g_aException.GetCount(); ++i )
		if( g_aException[i].dwCode == dwExceptionCode )
			return &g_aException[i];
	return NULL;
}


////////////////////////////////////////////////////////////////////////////////
// 加载内部异常列表

static void LoadInternalExceptionList()
{
	g_aException.SetCount( 0, 32 );

	LPCTSTR rs = NULL;
	size_t len = AtlLoadString(
		IDS_INTERNAL_EXCEPTIONS,
		reinterpret_cast<LPTSTR>(&rs),
		0
		);

	LPTSTR buf = reinterpret_cast<LPTSTR>( malloc((len + 1) * sizeof(TCHAR)) );
	_tcsncpy( buf, rs, len );
	buf[len] = 0;

	LPCTSTR p = _tcstok( buf, _T("|") );
	while( p != NULL )
	{
		CExceptionInfo ei;
		ei.bUser = false;
		ei.bFiltered = false;
		ei.dwCode = _tcstoul( p, NULL, 0 );
		p = _tcstok( NULL, _T("|") );
		_tcsncpy( ei.szName, p, _countof(ei.szName) );
		ei.szName[_countof(ei.szName) - 1] = 0;
		g_aException.Add( ei );
		p = _tcstok( NULL, _T("|") );
	}

	free( buf );
}


////////////////////////////////////////////////////////////////////////////////
// 配置信息读取和保存

static LPCTSTR g_szGeneralSection = _T("General");
static LPCTSTR g_szDumpPath = _T("DumpPath");
static LPCTSTR g_szSnapshot = _T("Snapshot");

static LPCTSTR g_szCrashSection = _T("Crash");
static LPCTSTR g_szFirstChance = _T("FirstChance");
static LPCTSTR g_szSecondChance = _T("SecondChance");
static LPCTSTR g_szAutoDelete = _T("AutoDelete");

static LPCTSTR g_szUserExceptionSection = _T("UserException");
static LPCTSTR g_szFilterSection = _T("Filter");

//------------------------------------------------------------------------------

static void LoadSettings()
{
	CIniFile ini;
	ini.OpenDefault();

	Settings.lVersion = 0;

	// general section
	CIniSection* sctn = ini.GetSection( g_szGeneralSection );
	Settings.dwSnapshot = sctn->GetValueInt( g_szSnapshot, ED_MINI_DUMP );
	LPCTSTR str = sctn->GetValueString( g_szDumpPath, _T("") );
	_tcsncpy( Settings.szDumpPath, str, _countof(Settings.szDumpPath) );
	Settings.szDumpPath[_countof(Settings.szDumpPath) - 1] = 0;

	// crash section
	sctn = ini.GetSection( g_szCrashSection );
	Settings.dwFirstChance = sctn->GetValueInt( g_szFirstChance, ED_DONT_DUMP );
	Settings.dwSecondChance = sctn->GetValueInt(g_szSecondChance, ED_MINI_DUMP);
	Settings.bAutoDelete = sctn->GetValueBool( g_szAutoDelete, true );

	// user exception list
	sctn = ini.GetSection( g_szUserExceptionSection );
	size_t pos = sctn->GetFirstKeyPosition();
	while( pos != 0xffffffff )
	{
		CIniKey* key = sctn->GetNextKey( pos );

		CExceptionInfo ei;
		ei.bUser = true;
		ei.bFiltered = false;
		ei.dwCode = _tcstoul( key->GetName(), NULL, 0 );
		_tcsncpy( ei.szName, key->GetValueString(), _countof(ei.szName) );
		ei.szName[_countof(ei.szName) - 1] = 0;
		g_aException.Add( ei );
	}

	// filter section
	sctn = ini.GetSection( g_szFilterSection );
	pos = sctn->GetFirstKeyPosition();
	while( pos != 0xffffffff )
	{
		CIniKey* key = sctn->GetNextKey( pos );
		DWORD code = _tcstoul( key->GetName(), NULL, 0 );
		CExceptionInfo* pei = GetExceptionInfoByCode( code );
		if( pei != NULL )
			pei->bFiltered = key->GetValueBool();
	}
}

//------------------------------------------------------------------------------

static void SaveSettings()
{
	CIniFile ini;

	// general section
	CIniSection* sctn = ini.GetSection( g_szGeneralSection );
	sctn->SetValueInt( g_szSnapshot, Settings.dwSnapshot );
	sctn->SetValueString( g_szDumpPath, Settings.szDumpPath );

	// crash section
	sctn = ini.GetSection( g_szCrashSection );
	sctn->SetValueInt( g_szFirstChance, Settings.dwFirstChance );
	sctn->SetValueInt( g_szSecondChance, Settings.dwSecondChance );
	sctn->SetValueBool( g_szAutoDelete, !!Settings.bAutoDelete );

	// user exception list
	sctn = ini.GetSection( g_szUserExceptionSection );
	for( size_t i = 0; i < g_aException.GetCount(); ++i )
	{
		if( !g_aException[i].bUser )
			continue;
		TCHAR buf[16];
		_sntprintf( buf, _countof(buf), _T("0x%08X"), g_aException[i].dwCode );
		sctn->SetValueString( buf, g_aException[i].szName );
	}

	// filter section
	sctn = ini.GetSection( g_szFilterSection );
	for( size_t i = 0; i < g_aException.GetCount(); ++i )
	{
		TCHAR buf[16];
		_sntprintf( buf, _countof(buf), _T("0x%08X"), g_aException[i].dwCode );
		sctn->SetValueBool( buf, g_aException[i].bFiltered );
	}

	ini.SaveToDefault();
}

//------------------------------------------------------------------------------

LPTSTR GetDumpPath( LPTSTR szBuf, DWORD cbBuf )
{
	DWORD cb = _countof(Settings.szDumpPath);
	if( cb > cbBuf )
		cb = cbBuf;

	for( ; ; )
	{
		LONG lVer = Settings.lVersion;
		if( lVer % 2 != 0 )
		{
			Sleep( 0 );
			continue;
		}
		_tcsncpy( szBuf, Settings.szDumpPath, cb );
		szBuf[cb - 1] = 0;
		if( lVer == Settings.lVersion )
			break;
	}

	if( szBuf[0] == 0 )
	{
		GetModuleFileName( NULL, szBuf, cbBuf );
		LPTSTR p = _tcsrchr( szBuf, _T('\\') );
		if( p != NULL )
			*p = 0;
	}
	else
	{
		size_t len = _tcslen( szBuf ) - 1;
		if( szBuf[len] == _T('/') || szBuf[len] == _T('\\') )
			szBuf[len] = 0;
	}

	return szBuf;
}


////////////////////////////////////////////////////////////////////////////////
// 判断一个异常是否被过滤, 这点数据量不排序应该也没有太多效率问题

BOOL FilterException( DWORD dwExceptionCode )
{
	BOOL ret = FALSE;

	EnterCriticalSection( &g_cs );
	for( size_t i = 0; i < g_aException.GetCount(); ++i )
	{
		if( g_aException[i].dwCode == dwExceptionCode )
		{
			ret = g_aException[i].bFiltered;
			break;
		}
	}
	LeaveCriticalSection( &g_cs );
	return ret;
}


////////////////////////////////////////////////////////////////////////////////


const CAtlArray<CExceptionInfo>& GetExceptionList()
{
	return g_aException;
}


////////////////////////////////////////////////////////////////////////////////
// 更新异常列表

void UpdateExceptionList( CAtlArray<CExceptionInfo>& aException )
{
	EnterCriticalSection( &g_cs );
	g_aException.Copy( aException );
	LeaveCriticalSection( &g_cs );
}


////////////////////////////////////////////////////////////////////////////////
// 获得调试权限

static BOOL EnableDebugPrivilege()
{ 
	BOOL ok = FALSE;
	HANDLE tk; 
	TOKEN_PRIVILEGES tp; 

	if( !OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &tk) )
		return FALSE;

	tp.PrivilegeCount = 1; 
	LookupPrivilegeValue( NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid ); 
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	AdjustTokenPrivileges( tk, FALSE, &tp, sizeof(tp), NULL, NULL ); 
	ok = (GetLastError() == ERROR_SUCCESS); 
	CloseHandle( tk ); 

	return ok; 
} 


////////////////////////////////////////////////////////////////////////////////
// 处理命令行参数

static BOOL ProcessCommandLine()
{
	if( __argc == 1 )
		return FALSE;

	DWORD dwPid = 0;
	HANDLE hEvent = NULL;

	if( (__argc != 3) || (_stscanf( __targv[1], _T("-p:%d"), &dwPid ) != 1)
		|| (_stscanf( __targv[2], _T("-e:%d"), &hEvent ) != 1) )
	{
		MessageBoxV( NULL, IDS_CMDLINE_ERROR, MB_OK | MB_ICONHAND );
		return TRUE;
	}

	DumpAeDebug( dwPid, hEvent );
	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////
// 主函数

int WINAPI _tWinMain( HINSTANCE hInst, HINSTANCE, LPTSTR, int )
{
	_tsetlocale( LC_ALL, _T(".OCP") );

	ATLVERIFY( SUCCEEDED( _Module.Init( NULL, hInst ) ) );
	if( !EnableDebugPrivilege() )
	{
		MessageBoxV( NULL, IDS_NO_DEBUG_PRIVILEGE, MB_OK | MB_ICONHAND );
		return 0;
	}

	InitializeCriticalSection( &g_cs );
	LoadInternalExceptionList();
	LoadSettings();
	DumpInit();

	if( !ProcessCommandLine() )
	{
		AtlInitCommonControls( ICC_BAR_CLASSES );
		LoadLibrary( CRichEditCtrl::GetLibraryName() );

		CMainDlg dlgMain;
		g_pMainWnd = &dlgMain;
		int nRet = dlgMain.DoModal();
		g_pMainWnd = NULL;
	}

	DumpUninit();
	SaveSettings();
	DeleteCriticalSection( &g_cs );

	_Module.Term();
	return 0;
}


////////////////////////////////////////////////////////////////////////////////