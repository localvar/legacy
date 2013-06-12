#pragma once

#include "resource.h"
#include "version.h"

////////////////////////////////////////////////////////////////////////////////
// 常量定义

// 转储类型
#define ED_DONT_DUMP			0
#define ED_MINI_DUMP			(MiniDumpNormal | MiniDumpWithHandleData)
#define ED_FULL_DUMP			(MiniDumpNormal | MiniDumpWithFullMemory \
	| MiniDumpWithHandleData | MiniDumpWithUnloadedModules \
	| MiniDumpWithThreadInfo | MiniDumpWithFullMemoryInfo)

// 创建进程时, 命令行参数的最大长度
#define MAX_ARGUMENT_LEN		1024

// 记录日志所用的消息
#define WM_LOG_EVENT			(WM_USER + 200)


////////////////////////////////////////////////////////////////////////////////
// 异常信息

struct CExceptionInfo
{
	DWORD dwCode;		// 异常代码
	bool bUser;			// 是否是用户定义的
	bool bFiltered;		// 是否被过滤掉了
	WORD Reserved;
	TCHAR szName[32];	// 异常名称
};


////////////////////////////////////////////////////////////////////////////////
// 系统配置选项

struct CSettings
{
	LONG volatile lVersion;		// 用于多线程同步
	bool volatile bKillOnExit;	// 退出时是否杀死进程
	bool bAutoDelete;
	WORD Reserved;
	DWORD dwSnapshot;
	DWORD dwFirstChance;
	DWORD dwSecondChance;
	TCHAR szDumpPath[MAX_PATH];
};

extern CSettings Settings;


////////////////////////////////////////////////////////////////////////////////
// 工具函数

BOOL GetImageNameByPid( DWORD dwPid, LPTSTR szBuf, DWORD cbBuf );
BOOL GetImagePathByPid( DWORD dwPid, LPTSTR szBuf, DWORD cbBuf );
void LogEvent( UINT uEventId, ... );
int MessageBoxV( HWND hWnd, UINT uTextFmt, UINT uType, ... );
LPTSTR GetDumpPath( LPTSTR szBuf, DWORD cbBuf );
BOOL FilterException( DWORD dwExceptionCode );
const CAtlArray<CExceptionInfo>& GetExceptionList();
void UpdateExceptionList( CAtlArray<CExceptionInfo>& aException );


////////////////////////////////////////////////////////////////////////////////
// 实际转储工作相关

BOOL DumpInit();
void DumpUninit();
BOOL DumpAeDebug( DWORD dwPid, HANDLE hEvent );
DWORD DumpStart( DWORD dwPid, LPCTSTR szImgPath );
DWORD DumpStart( LPCTSTR szImgPath, LPCTSTR szArg, LPCTSTR szWorkDir );
void DumpSnapshot();
void DumpStop();
BOOL IsDumping();
BOOL IsDetachSupported();


////////////////////////////////////////////////////////////////////////////////