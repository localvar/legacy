// OdbScrptView.h : interface of the CScriptEditView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once


struct CFindReplaceOption
{
	TCHAR StrToFind[128];
	bool bMatchCase;
	bool bWholeWord;
	bool bFindOnly;
};


class CScriptEditView
	: public CWindowImpl<CScriptEditView, CRichEditCtrl>
	, public CRichEditCommands< CScriptEditView >
{
protected:
	CFont m_font;
	CFindReplaceDialog* m_pFindDlg;
	CFindReplaceOption m_fro;
	int m_nTabStop;
	TCHAR m_szFilePath[MAX_PATH];
	TCHAR m_szFileName[MAX_PATH];


public:
	DECLARE_WND_SUPERCLASS( NULL, CRichEditCtrl::GetWndClassName() )

	BEGIN_MSG_MAP( CScriptEditView )
		MESSAGE_HANDLER( WM_KEYDOWN, OnKey )
		MESSAGE_HANDLER( WM_KEYUP, OnKey )
		MESSAGE_HANDLER( WM_LBUTTONDOWN, OnKey )
		MESSAGE_HANDLER( WM_CONTEXTMENU, OnContextMenu )
		MESSAGE_HANDLER( CFindReplaceDialog::GetFindReplaceMsg(), OnFindReplaceCmd )
		MESSAGE_HANDLER( WM_CREATE, OnCreate )
		COMMAND_ID_HANDLER(ID_VIEW_OPTION, OnViewOption)
		ALT_MSG_MAP( 1 )
		COMMAND_ID_HANDLER( ID_VIEW_OPTION, OnViewOption )
		COMMAND_ID_HANDLER( ID_EDIT_FIND, OnEditFind )
		COMMAND_ID_HANDLER( ID_EDIT_REPEAT, OnEditFindNext )
		COMMAND_ID_HANDLER( ID_EDIT_REPLACE, OnEditReplace )
		CHAIN_MSG_MAP_ALT( CRichEditCommands< CScriptEditView >, 1 )
	END_MSG_MAP()


public:
	CScriptEditView();
	BOOL SetTabStopWidth();
	bool CreateFindReplaceDialog( bool bFindOnly );
	bool DoFindText( bool bNext = true );
	bool QueryClose();
	void Init( LPCTSTR szFilePath, LPCTSTR szFileName );
	bool OnFileSaveAs();
	bool DoFileSave();
	bool SaveFile( LPCTSTR szFilePath );
	bool OnFileSave();
	bool LoadFile( LPCTSTR szFilePath );
	static DWORD CALLBACK StreamWriteCallback( DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb );
	static DWORD CALLBACK StreamReadCallback( DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb );
	LPCTSTR GetFileName();


public:
	BOOL PreTranslateMessage( MSG* pMsg );
	LRESULT OnSetFont( WORD, WORD, HWND, BOOL& );
	LRESULT OnContextMenu( UINT, WPARAM, LPARAM, BOOL& );
	LRESULT OnKey( UINT, WPARAM, LPARAM, BOOL& );

	LRESULT OnEditFind( WORD, WORD, HWND, BOOL& );
	LRESULT OnEditFindNext( WORD, WORD, HWND, BOOL& );
	LRESULT OnEditReplace( WORD, WORD, HWND, BOOL& );
	LRESULT OnFindReplaceCmd( UINT, WPARAM, LPARAM, BOOL& );

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnViewOption(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
