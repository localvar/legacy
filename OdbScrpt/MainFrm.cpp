// MainFrm.cpp : implmentation of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OdbScrpt.h"

#include "MainFrm.h"
#include ".\mainfrm.h"



CMainFrame::CMainFrame()
{
	m_bFirstChange = true;
	m_rcMargin.bottom = m_rcMargin.left = m_rcMargin.right = m_rcMargin.top = 1000;
	m_printer.OpenDefaultPrinter();
	m_devmode.CopyFromPrinter( m_printer );
}



BOOL CMainFrame::PreTranslateMessage( MSG* pMsg )
{
	if( CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg) )
		return TRUE;
	return m_view.PreTranslateMessage( pMsg );
}



BOOL CMainFrame::OnIdle()
{
	UIEnable( ID_EDIT_PASTE, m_view.CanPaste() );
	UIEnable( ID_EDIT_COPY, m_view.CanCopy() );
	UIEnable( ID_EDIT_CUT, m_view.CanCut() );
	UIEnable( ID_EDIT_CLEAR, m_view.CanClear() );
	UIEnable( ID_EDIT_UNDO, m_view.CanUndo() );
	UIEnable( ID_EDIT_REDO, m_view.CanRedo() );

	bool bOn = ((GetKeyState(VK_NUMLOCK) & 1) == 1);
	m_wndStatus.SetPaneText( IDS_NUMLOCK_PANE, bOn ? m_szNumLockPane : _T("") );
	bOn = ((GetKeyState(VK_INSERT) & 1) == 1);
	m_wndStatus.SetPaneText( IDS_INSERT_PANE, bOn ? m_szInsertPane : _T("") );

	UIUpdateToolBar();
	return FALSE;
}



LRESULT CMainFrame::OnCreate( UINT, WPARAM, LPARAM, BOOL& )
{
	LoadConstantString();

	// create command bar window
	DWORD dwStyle = ATL_SIMPLE_CMDBAR_PANE_STYLE;
	HWND hWndCmdBar = m_CmdBar.Create( m_hWnd, rcDefault, NULL, dwStyle );

	m_CmdBar.AttachMenu( GetMenu() );		// attach menu
	m_CmdBar.LoadImages( IDR_MAINFRAME );	// load command bar images
	SetMenu( NULL );						// remove old menu

	dwStyle = ATL_SIMPLE_TOOLBAR_PANE_STYLE;
	HWND hWndToolBar = CreateSimpleToolBarCtrl( m_hWnd, IDR_MAINFRAME, FALSE, dwStyle );

	CreateSimpleReBar( ATL_SIMPLE_REBAR_NOBORDER_STYLE );
	AddSimpleReBarBand( hWndCmdBar );
	AddSimpleReBarBand( hWndToolBar, NULL, TRUE );

	CreateSimpleStatusBar();
	m_wndStatus.SubclassWindow( m_hWndStatusBar );
	int arrPane[] = { ID_DEFAULT_PANE, IDS_ROW_COL_PANE, IDS_NUMLOCK_PANE, IDS_INSERT_PANE };
	m_wndStatus.SetPanes( arrPane, DIMOF(arrPane), true );

	dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	m_hWndClient = m_splitter.Create( *this, rcDefault, NULL, dwStyle );

	dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	m_wndContainer.Create( m_splitter, IDS_FUNC_PANE_TITLE, dwStyle );
	m_wndContainer.EnableCloseButton( TRUE );

	dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS;
	m_lbFunc.Create( m_wndContainer, rcDefault, NULL, dwStyle, WS_EX_STATICEDGE );
	m_wndContainer.SetClient( m_lbFunc );

	dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS;
	dwStyle |= WS_HSCROLL | WS_VSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL;
	dwStyle |= ES_MULTILINE | ES_NOHIDESEL | ES_SAVESEL;
	m_view.Create( m_splitter, rcDefault, NULL, dwStyle, WS_EX_STATICEDGE );

	m_splitter.SetSplitterPanes( m_wndContainer, m_view );
	UpdateLayout();
	m_splitter.SetSplitterPos( 120 );
	m_splitter.SetActivePane( SPLIT_PANE_RIGHT );


	UIAddToolBar( hWndToolBar );
	UISetCheck( ID_VIEW_TOOLBAR, 1 );
	UISetCheck( ID_VIEW_STATUS_BAR, 1 );
	UISetCheck( ID_VIEW_FUNC_LIST, 1 );

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = theModule.GetMessageLoop();
	ATLASSERT( pLoop != NULL );
	pLoop->AddMessageFilter( this );
	pLoop->AddIdleHandler( this );

	return 0;
}



LRESULT CMainFrame::OnFileExit( WORD, WORD, HWND, BOOL& )
{
	PostMessage( WM_CLOSE );
	return 0;
}



LRESULT CMainFrame::OnViewToolBar( WORD, WORD, HWND, BOOL& )
{
	CReBarCtrl rebar = m_hWndToolBar;
	int nIndex = rebar.IdToIndex( ATL_IDW_BAND_FIRST + 1 );

	REBARBANDINFO rbbi;
	rbbi.cbSize = sizeof(rbbi);
	rbbi.fMask = RBBIM_STYLE;
	rebar.GetBandInfo( nIndex, &rbbi );
	bool bVisible = ((rbbi.fStyle & RBBS_HIDDEN) != 0);

	rebar.ShowBand( nIndex, bVisible );
	UISetCheck( ID_VIEW_TOOLBAR, bVisible );
	UpdateLayout();

	return 0;
}




LRESULT CMainFrame::OnViewStatusBar( WORD, WORD, HWND, BOOL& )
{
	bool bVisible = !::IsWindowVisible( m_hWndStatusBar );
	::ShowWindow( m_hWndStatusBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE );
	UISetCheck( ID_VIEW_STATUS_BAR, bVisible );
	UpdateLayout();
	return 0;
}




LRESULT CMainFrame::OnAppAbout( WORD, WORD, HWND, BOOL& )
{
	CSimpleDialog<IDD_ABOUTBOX> dlg;
	dlg.DoModal();
	return 0;
}



HRESULT CMainFrame::LoadFuncTable()
{
	CComPtr<IXMLDOMDocument2> spXmlDoc;
	spXmlDoc.CoCreateInstance( CLSID_DOMDocument40, NULL, CLSCTX_INPROC_SERVER );
	CComVariant varFile( L"c:/vpc/winxp.vmc" );
	VARIANT_BOOL bSucc;
	spXmlDoc->load( varFile, &bSucc );

	CComPtr<IXMLDOMElement> spRoot;
	spXmlDoc->get_documentElement( &spRoot );

	CComPtr<IXMLDOMNodeList> spNodeList;
	spRoot->get_childNodes( &spNodeList );

	CComPtr<IXMLDOMNode> spNode;
	while( spNodeList->nextNode(&spNode) == S_OK )
	{
		CComBSTR bstrName;
		spNode->get_nodeName( &bstrName );
		spNode.Release();
	}

	return 0;
}



LRESULT CMainFrame::OnViewFuncList( WORD, WORD, HWND, BOOL& )
{
	BOOL bVisible = m_wndContainer.IsWindowVisible();
	m_splitter.SetSinglePaneMode( bVisible ? SPLIT_PANE_RIGHT : SPLIT_PANE_NONE );
	UISetCheck( ID_VIEW_FUNC_LIST, !bVisible );
	return 0;
}



LRESULT CMainFrame::OnContextMenu( UINT, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	if( m_view.m_hWnd == reinterpret_cast<HWND>(wParam) )
	{
		CMenuHandle mnuCntxt( m_CmdBar.GetMenu().GetSubMenu(1) );
		UINT uFlag = TPM_LEFTBUTTON | TPM_RIGHTBUTTON | TPM_LEFTALIGN | TPM_TOPALIGN;
		m_CmdBar.TrackPopupMenu( mnuCntxt, uFlag, LOWORD(lParam), HIWORD(lParam) );
	}
	else
	{
		bHandled = FALSE;
	}

	return 0;
}


void CMainFrame::UndateRowCol( int row, int col )
{
	TCHAR szBuff[64];
	wsprintf( szBuff, m_szRowColPaneFmt, row, col );
	m_wndStatus.SetPaneText( IDS_ROW_COL_PANE, szBuff );
}


void CMainFrame::LoadConstantString()
{
	AtlLoadString( IDS_ROW_COL_PANE_FMT, m_szRowColPaneFmt, DIMOF(m_szRowColPaneFmt) );
	AtlLoadString( IDS_NUMLOCK_PANE, m_szNumLockPane, DIMOF(m_szNumLockPane) );
	AtlLoadString( IDS_INSERT_PANE, m_szInsertPane, DIMOF(m_szInsertPane) );
	AtlLoadString( IDR_MAINFRAME, m_szTitle, DIMOF(m_szTitle) );
}



LRESULT CMainFrame::OnFilePageSetup( WORD, WORD, HWND, BOOL& )
{
	CPageSetupDialog dlg;

	dlg.m_psd.hDevMode = m_devmode.CopyToHDEVMODE();
	dlg.m_psd.hDevNames = m_printer.CopyToHDEVNAMES();
	dlg.m_psd.rtMargin = m_rcMargin;

	if( dlg.DoModal() == IDOK )
	{
		m_devmode.CopyFromHDEVMODE( dlg.m_psd.hDevMode );
		m_printer.ClosePrinter();
		m_printer.OpenPrinter( dlg.m_psd.hDevNames, m_devmode.m_pDevMode );
		m_rcMargin = dlg.m_psd.rtMargin;
	}

	GlobalFree( dlg.m_psd.hDevMode );
	GlobalFree( dlg.m_psd.hDevNames );

	return 0;
}


LRESULT CMainFrame::OnFileNew( WORD, WORD, HWND, BOOL& )
{
	DoFileNew();
	return 0;
}


void CMainFrame::DoFileNew()
{
	if( m_view.QueryClose() )
	{
		m_view.SetWindowText( NULL );
		TCHAR szName[16];
		AtlLoadString( IDS_UNTITLED, szName, DIMOF(szName) );
		m_view.Init( _T(""), szName );
		UpdateTitle();
		m_bFirstChange = true;
	}
}


LRESULT CMainFrame::OnFileSaveAs( WORD, WORD, HWND, BOOL& )
{
	if( m_view.OnFileSaveAs() )
	{
		UpdateTitle();
		m_bFirstChange = true;
	}
	return 0;
}



LRESULT CMainFrame::OnFileSave( WORD, WORD, HWND, BOOL& )
{
	if( m_view.OnFileSave() )
	{
		UpdateTitle();
		m_bFirstChange = true;
	}

	return 0;
}



LRESULT CMainFrame::OnFileOpen( WORD, WORD, HWND, BOOL& )
{
	TCHAR szFilter[256];
	::ZeroMemory( szFilter, DIMOF(szFilter) );
	int nChar = AtlLoadString( IDS_FILE_FILTER, szFilter, DIMOF(szFilter) );

	DWORD dwFlags = OFN_ENABLESIZING | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	CFileDialog dlg( TRUE, NULL, _T(""), dwFlags, szFilter );
	if( dlg.DoModal() == IDOK )
	{
		ATLTRACE(_T("File path: %s\n"), dlg.m_ofn.lpstrFile);

		if( m_view.QueryClose() )
			DoFileOpen( dlg.m_szFileName, dlg.m_szFileTitle );
	}

	return 0;
}


bool CMainFrame::DoFileOpen( LPCTSTR szFilePath, LPCTSTR szFileName )
{
	bool bRet = m_view.LoadFile( szFilePath );
	if( bRet )
	{
		m_view.Init( szFilePath, szFileName );
		UpdateTitle();
	}
	else
	{
		AtlMessageBox( *this, IDS_READ_FILE_FAILED, IDR_MAINFRAME, MB_OK|MB_ICONERROR );
		DoFileNew();
	}

	m_bFirstChange = true;

	return bRet;
}


LRESULT CMainFrame::OnClose( UINT, WPARAM, LPARAM, BOOL& bHandled )
{
	bHandled = !m_view.QueryClose();
	return 0;
}


void CMainFrame::UpdateTitle()
{
	TCHAR szFullTitle[320];
	lstrcpy( szFullTitle, m_view.GetFileName() );
	if( m_view.GetModify() )
		lstrcat( szFullTitle, _T("*") );
	lstrcat( szFullTitle, _T(" - ") );
	lstrcat( szFullTitle, m_szTitle );
	SetWindowText( szFullTitle );
}


LRESULT CMainFrame::OnTextChange( WORD, WORD, HWND, BOOL& )
{
	if( m_bFirstChange )
	{
		UpdateTitle();
		m_bFirstChange = false;
	}
	return 0;
}