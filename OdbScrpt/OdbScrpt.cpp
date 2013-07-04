// OdbScrpt.cpp : main source file for OdbScrpt.exe
//

#include "stdafx.h"
#include "OdbScrpt.h"
#include "MainFrm.h"



CAppModule theModule;
CMainFrame* g_pMainWnd = NULL;


CMainFrame& WtlGetMainWnd()
{
	ATLASSERT( g_pMainWnd != NULL );
	return *g_pMainWnd;
}


int Run( LPTSTR lpstrCmdLine, int nCmdShow = SW_SHOWDEFAULT )
{
	int nRet = 0;
	CMessageLoop theLoop;
	theModule.AddMessageLoop( &theLoop );

	g_pMainWnd = new CMainFrame;
	ATLASSERT( g_pMainWnd != NULL );

	if( g_pMainWnd->CreateEx() == NULL )
	{
		ATLTRACE( _T("Main window creation failed!\n") );
	}
	else
	{
		if( lpstrCmdLine[0] == 0 )
		{
			g_pMainWnd->DoFileNew();
		}
		else	// file name specified at the command line
		{
			// strip quotes (if any)
			LPTSTR lpstrCmd = lpstrCmdLine;
			if( lpstrCmd[0] == '"' )
			{
				lpstrCmd++;
				for( int i = 0; i < lstrlen(lpstrCmd); i++ )
				{
					if( lpstrCmd[i] == '"' )
					{
						lpstrCmd[i] = 0;
						break;
					}
				}
			}
			// get full path and file name
			TCHAR szPathName[MAX_PATH];
			LPTSTR lpstrFileName = NULL;
			::GetFullPathName( lpstrCmd, MAX_PATH, szPathName, &lpstrFileName );
			// open file
			g_pMainWnd->DoFileOpen( szPathName, lpstrFileName );
		}

		g_pMainWnd->ShowWindow( nCmdShow );
		nRet = theLoop.Run();
	}

	delete g_pMainWnd;
	g_pMainWnd = NULL;

	theModule.RemoveMessageLoop();

	return nRet;
}



int WINAPI _tWinMain( HINSTANCE hInstance, HINSTANCE, LPTSTR lpstrCmdLine, int nCmdShow )
{
	HRESULT hRes = ::CoInitializeEx( NULL, COINIT_APARTMENTTHREADED );
	ATLASSERT( SUCCEEDED(hRes) );

	// add flags to support other controls
	AtlInitCommonControls( ICC_COOL_CLASSES | ICC_BAR_CLASSES | ICC_TREEVIEW_CLASSES );

	hRes = theModule.Init( NULL, hInstance );
	ATLASSERT( SUCCEEDED(hRes) );

	HMODULE hInstRich = ::LoadLibrary(CRichEditCtrl::GetLibraryName());
	ATLASSERT(hInstRich != NULL);

	int nRet = Run( lpstrCmdLine, nCmdShow );

	::FreeLibrary( hInstRich );

	theModule.Term();
	::CoUninitialize();

	return nRet;
}
