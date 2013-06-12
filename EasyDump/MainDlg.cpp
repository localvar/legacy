#include "stdafx.h"
#include "EasyDump.h"
#include "MainDlg.h"
#include "SelProcDlg.h"
#include "CrtProcDlg.h"
#include "OptDlg.h"


////////////////////////////////////////////////////////////////////////////////


#define IDT_TIMER		2


////////////////////////////////////////////////////////////////////////////////
// CAboutDialog

class CAboutDialog : public CDialogImpl<CAboutDialog>
{
public:
	CHyperLink m_wndLink;

public:
	enum { IDD = IDD_ABOUTBOX };

	BEGIN_MSG_MAP( CAboutDialog )
		MESSAGE_HANDLER( WM_INITDIALOG, OnInitDialog )
		COMMAND_ID_HANDLER( IDOK, OnClose )
		COMMAND_ID_HANDLER( IDCANCEL, OnClose )
	END_MSG_MAP()

public:
	LRESULT OnInitDialog( UINT, WPARAM, LPARAM, BOOL& )
	{
		m_wndLink.SubclassWindow( GetDlgItem( IDC_LINK ) );
		m_wndLink.SetHyperLink( _T("http://code.google.com/p/easytools/") );
		SetDlgItemText( IDC_VERSION, _T(ED_VER_STR) );
		return 0;
	}

	LRESULT OnClose( WORD, WORD, HWND, BOOL& )
	{
		EndDialog( IDCANCEL );
		return 0;
	}
};


////////////////////////////////////////////////////////////////////////////////


LRESULT CMainDlg::OnInitDialog( UINT, WPARAM, LPARAM, BOOL& )
{
	HINSTANCE inst = _Module.GetResourceInstance();
	HICON hIcon = LoadIcon( inst, MAKEINTRESOURCE(IDR_MAINFRAME) );
	SetIcon( hIcon, TRUE );
	SetIcon( hIcon, FALSE );
	DlgResize_Init( false );

	ATLASSERT( (ID_APP_ABOUT & 0xFFF0) == ID_APP_ABOUT);
	ATLASSERT( ID_APP_ABOUT < 0xF000);
	TCHAR szAbout[64];
	AtlLoadString( IDS_ABOUT, szAbout, _countof(szAbout) );
	CMenuHandle menu = GetSystemMenu( FALSE );
	menu.AppendMenu( MF_SEPARATOR );
	menu.AppendMenu( MF_STRING, ID_APP_ABOUT, szAbout );
	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CMainDlg::OnSysCommand( UINT, WPARAM wParam, LPARAM, BOOL& bHandled )
{
	if((wParam & 0xFFF0) == ID_APP_ABOUT )
	{
		CAboutDialog dlg;
		dlg.DoModal();
		return 0;
	}
	bHandled = FALSE;
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CMainDlg::OnCancel( WORD, WORD, HWND, BOOL& )
{
	if( IsDumping() )
		if( !DoDetach() )
			return 0;

	EndDialog( IDCANCEL );
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CMainDlg::OnTimer( UINT, WPARAM, LPARAM, BOOL& )
{
	if( !IsDumping() )
		StopDump();
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


void CMainDlg::StopDump()
{
	KillTimer( IDT_TIMER );
	DumpStop();
	UpdateUI( FALSE, 0, NULL );
}


////////////////////////////////////////////////////////////////////////////////


void CMainDlg::UpdateUI( BOOL bDumping, DWORD dwPid, LPCTSTR szImgPath )
{
	GetDlgItem( IDC_SELECT_PROCESS ).EnableWindow( !bDumping );
	GetDlgItem( IDC_CREATE_PROCESS ).EnableWindow( !bDumping );
	GetDlgItem( IDC_DETACH_PROCESS ).EnableWindow( bDumping );
	GetDlgItem( IDC_SNAPSHOT ).EnableWindow( bDumping );

	if( bDumping )
	{
		SetDlgItemInt( IDC_PID, dwPid, FALSE );
		SetDlgItemText( IDC_IMAGE_PATH, szImgPath );
	}
	else
	{
		SetDlgItemText( IDC_PID, _T("") );
		SetDlgItemText( IDC_IMAGE_PATH, _T("") );
	}
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CMainDlg::OnCreateProcess( WORD, WORD, HWND, BOOL& )
{
	ATLASSERT( !IsDumping() );

	CCreateProcessDialog dlg;
	if( dlg.DoModal() != IDOK )
		return 0;

	CWaitCursor wait;

	DWORD pid = DumpStart( dlg.m_szAppPath, dlg.m_szArg, dlg.m_szWorkDir );
	if( pid != 0xffffffff )
	{
		UpdateUI( TRUE, pid, dlg.m_szAppPath );
		SetTimer( IDT_TIMER, 500, NULL );
	}

	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CMainDlg::OnSelectProcess( WORD, WORD, HWND, BOOL& )
{
	ATLASSERT( !IsDumping() );

	CSelProcDlg dlg;
	if( dlg.DoModal() != IDOK )
		return 0;

	CWaitCursor wait;

	DWORD pid = DumpStart( dlg.m_dwPid, dlg.m_szImagePath );
	if( pid != 0xffffffff )
	{
		ATLASSERT( pid == dlg.m_dwPid );
		UpdateUI( TRUE, pid, dlg.m_szImagePath );
		SetTimer( IDT_TIMER, 500, NULL );
	}

	return 0;
}


////////////////////////////////////////////////////////////////////////////////


BOOL CMainDlg::DoDetach()
{
	Settings.bKillOnExit = true;

	if( IsDetachSupported() )
	{
		UINT uType = MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2;
		int res = MessageBoxV( *this, IDS_CONFIRM_DETACH, uType );
		if( res == IDCANCEL )
			return FALSE;
		if( res == IDNO )
			Settings.bKillOnExit = false;
	}
	else
	{
		UINT uType = MB_YESNO | MB_ICONQUESTION;
		int res = MessageBoxV( *this, IDS_CONFIRM_KILL, uType );
		if( res == IDNO )
			return FALSE;
	}

	StopDump();
	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CMainDlg::OnDetachProcess( WORD, WORD, HWND, BOOL& )
{
	DoDetach();
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CMainDlg::OnSnapshot( WORD, WORD, HWND, BOOL& )
{
	CWaitCursor wait;
	DumpSnapshot();
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CMainDlg::OnClearLog( WORD, WORD, HWND, BOOL& )
{
	SetDlgItemText( IDC_LOG, _T("") );
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CMainDlg::OnOption( WORD, WORD, HWND, BOOL& )
{
	COptionDialog dlg;
	dlg.DoModal();
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CMainDlg::OnLogEvent( UINT, WPARAM wParam, LPARAM, BOOL& )
{
	CRichEditCtrl log = GetDlgItem( IDC_LOG );
	LPTSTR szLog = reinterpret_cast<LPTSTR>( wParam );
	log.AppendText( szLog );
	LocalFree( szLog );
	return 0;
}


////////////////////////////////////////////////////////////////////////////////