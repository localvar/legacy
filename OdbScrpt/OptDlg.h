#pragma once

class COptDlg : public CDialogImpl< COptDlg >
{
public:
	enum { IDD = IDD_OPT, FONT_SIZE_MIN = 6, FONT_SIZE_MAX = 32 };
	CFont m_font;
	UINT m_uTabWidth;
	TCHAR m_szPath[MAX_PATH];
	bool m_bViewNaviBar;


public:
	BEGIN_MSG_MAP( COptDlg )
		MESSAGE_HANDLER( WM_INITDIALOG, OnInitDialog )
		COMMAND_ID_HANDLER( IDCANCEL, OnCancel )
		COMMAND_HANDLER( IDC_BOLD, BN_CLICKED, OnFontChange )
		COMMAND_HANDLER( IDC_FONT_SIZE, CBN_SELCHANGE, OnFontChange )
		COMMAND_HANDLER( IDC_FONT_FACE, CBN_SELCHANGE, OnFontChange )
		COMMAND_HANDLER( IDC_ITALIC, BN_CLICKED, OnFontChange )
		COMMAND_HANDLER( IDOK, BN_CLICKED, OnOk )
		COMMAND_HANDLER( IDC_BROWSE, BN_CLICKED, OnBrowse )
	END_MSG_MAP()


public:
	COptDlg( HFONT hFont, UINT nTabWidth, LPCTSTR szPath, bool bViewNaviBar );
	UINT GetTabWidth();
	void GetLogFont( LOGFONT* pLogFont );
	LPCTSTR GetScriptPath();
	bool GetViewNaviBar();


protected:
	BOOL EnumFontCallBack( ENUMLOGFONTEX* lplf, NEWTEXTMETRICEX* lpntm, DWORD dwFontType );
	static BOOL CALLBACK EnumFontCallBackStub( ENUMLOGFONTEX* lplf, NEWTEXTMETRICEX* lpntm, DWORD dwFontType, LPARAM lParam );
	void PreviewFont();
	bool InitFontStyle();

// message handlers
public:
	LRESULT OnInitDialog( UINT, WPARAM, LPARAM, BOOL& );
	LRESULT OnCancel( WORD, WORD, HWND, BOOL& );
	LRESULT OnFontChange( WORD, WORD, HWND, BOOL& );
	LRESULT OnOk( WORD, WORD, HWND, BOOL& );
	LRESULT OnBrowse( WORD, WORD, HWND, BOOL& );
};
