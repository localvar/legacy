#pragma once


class COptionDialog : public CDialogImpl<COptionDialog>
{
protected:
	BOOL m_bAeDebug;
	static LPCTSTR s_szAeDebug;
	static LPCTSTR s_szDebugger;
	static LPCTSTR s_szDebuggerBackup;
	CAtlArray<CExceptionInfo> m_aException;

public:
	enum { IDD = IDD_OPTION };

	BEGIN_MSG_MAP( COptionDialog )
		COMMAND_ID_HANDLER( IDOK, OnOk )
		COMMAND_ID_HANDLER( IDCANCEL, OnCancel )
		COMMAND_ID_HANDLER( IDC_BROWSE, OnBrowse )
		COMMAND_ID_HANDLER( IDC_FILTER, OnFilter )
		MESSAGE_HANDLER( WM_INITDIALOG, OnInitDialog )
	END_MSG_MAP()

protected:
	BOOL IsAeDebug();
	BOOL SetAeDebug();
	BOOL RestoreAeDebug();
	LPCTSTR GetDebuggerCommandLine( LPTSTR buf );
	BOOL CopyRegString( CRegKey& reg, LPCTSTR szSrc, LPCTSTR szDst );

public:
	LRESULT OnInitDialog( UINT, WPARAM, LPARAM, BOOL& );
	LRESULT OnOk( WORD, WORD, HWND, BOOL& );
	LRESULT OnCancel( WORD, WORD, HWND, BOOL& );
	LRESULT OnBrowse( WORD, WORD, HWND, BOOL& );
	LRESULT OnFilter( WORD, WORD, HWND, BOOL& );
};
