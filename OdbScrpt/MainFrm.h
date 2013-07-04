// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "EditView.h"


class CMainFrame
	: public CFrameWindowImpl<CMainFrame>
	, public CUpdateUI<CMainFrame>
	, public CMessageFilter
	, public CIdleHandler
{
protected:
	TCHAR m_szRowColPaneFmt[32];
	TCHAR m_szNumLockPane[8];
	TCHAR m_szInsertPane[8];
	TCHAR m_szTitle[32];


protected:
	bool m_bFirstChange;
	CScriptEditView m_view;
	CPaneContainer m_wndContainer;
	CSplitterWindow m_splitter;
	CCommandBarCtrl m_CmdBar;
	CListBox m_lbFunc;
	CMultiPaneStatusBarCtrl m_wndStatus;

	CPrinterT<true> m_printer;
	CDevModeT<true> m_devmode;
	RECT m_rcMargin;


public:
	DECLARE_FRAME_WND_CLASS( NULL, IDR_MAINFRAME )

	BEGIN_UPDATE_UI_MAP( CMainFrame )
		UPDATE_ELEMENT( ID_EDIT_COPY, UPDUI_MENUPOPUP|UPDUI_TOOLBAR )
		UPDATE_ELEMENT( ID_EDIT_CUT, UPDUI_MENUPOPUP|UPDUI_TOOLBAR )
		UPDATE_ELEMENT( ID_EDIT_PASTE, UPDUI_MENUPOPUP|UPDUI_TOOLBAR )
		UPDATE_ELEMENT( ID_EDIT_UNDO, UPDUI_MENUPOPUP|UPDUI_TOOLBAR )
		UPDATE_ELEMENT( ID_EDIT_REDO, UPDUI_MENUPOPUP|UPDUI_TOOLBAR )
		UPDATE_ELEMENT( ID_EDIT_CLEAR, UPDUI_MENUPOPUP )
		UPDATE_ELEMENT( ID_VIEW_TOOLBAR, UPDUI_MENUPOPUP )
		UPDATE_ELEMENT( ID_VIEW_STATUS_BAR, UPDUI_MENUPOPUP )
		UPDATE_ELEMENT( ID_VIEW_FUNC_LIST, UPDUI_MENUPOPUP )
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP( CMainFrame )
		COMMAND_CODE_HANDLER( EN_CHANGE, OnTextChange )
		COMMAND_ID_HANDLER( ID_APP_EXIT, OnFileExit )
		COMMAND_ID_HANDLER( ID_FILE_NEW, OnFileNew )
		COMMAND_ID_HANDLER( ID_VIEW_TOOLBAR, OnViewToolBar )
		COMMAND_ID_HANDLER( ID_VIEW_STATUS_BAR, OnViewStatusBar )
		COMMAND_ID_HANDLER( ID_APP_ABOUT, OnAppAbout )
		COMMAND_ID_HANDLER( ID_VIEW_FUNC_LIST, OnViewFuncList )
		COMMAND_ID_HANDLER( ID_PANE_CLOSE, OnViewFuncList )
		COMMAND_ID_HANDLER( ID_FILE_PAGE_SETUP, OnFilePageSetup )
		MESSAGE_HANDLER( WM_CREATE, OnCreate )
		MESSAGE_HANDLER( WM_CONTEXTMENU, OnContextMenu )
		COMMAND_ID_HANDLER(ID_FILE_SAVE_AS, OnFileSaveAs)
		COMMAND_ID_HANDLER(ID_FILE_SAVE, OnFileSave)
		COMMAND_ID_HANDLER(ID_FILE_OPEN, OnFileOpen)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		CHAIN_MSG_MAP( CUpdateUI<CMainFrame> )
		CHAIN_MSG_MAP( CFrameWindowImpl<CMainFrame> )
		CHAIN_COMMANDS_ALT_MEMBER( m_view, 1 )
	END_MSG_MAP()


public:
	CMainFrame();
	HRESULT LoadFuncTable();
	void UndateRowCol( int row, int col );
	void LoadConstantString();
	void DoFileNew();
	bool DoFileOpen( LPCTSTR szFilePath, LPCTSTR szFileName );
	void UpdateTitle();


// overrides
public:
	virtual BOOL PreTranslateMessage( MSG* pMsg );
	virtual BOOL OnIdle();


// message handlers
public:
	LRESULT OnCreate( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ );
	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnContextMenu(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT OnFileExit( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnFileNew( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnViewToolBar( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnViewStatusBar( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnAppAbout( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnTextChange( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnViewFuncList(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFilePageSetup(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFileSaveAs(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFileSave(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFileOpen(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
