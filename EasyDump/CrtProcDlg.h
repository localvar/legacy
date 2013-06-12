#pragma once


class CCreateProcessDialog : public CDialogImpl<CCreateProcessDialog>
{
public:
	TCHAR m_szAppPath[MAX_PATH];
	TCHAR m_szArg[MAX_ARGUMENT_LEN];
	TCHAR m_szWorkDir[MAX_PATH];

public:
	enum { IDD = IDD_CREATE_PROCESS };

	BEGIN_MSG_MAP( COptionDialog )
		COMMAND_ID_HANDLER( IDOK, OnOk )
		COMMAND_ID_HANDLER( IDCANCEL, OnCancel )
		COMMAND_ID_HANDLER( IDC_BROWSE_APPPATH, OnBrowseAppPath )
		COMMAND_ID_HANDLER( IDC_BROWSE_WORKDIR, OnBrowseWorkDir )
		MESSAGE_HANDLER( WM_INITDIALOG, OnInitDialog )
	END_MSG_MAP()

public:
	LRESULT OnInitDialog( UINT, WPARAM, LPARAM, BOOL& );
	LRESULT OnOk( WORD, WORD, HWND, BOOL& );
	LRESULT OnCancel( WORD, WORD, HWND, BOOL& );
	LRESULT OnBrowseAppPath( WORD, WORD, HWND, BOOL& );
	LRESULT OnBrowseWorkDir( WORD, WORD, HWND, BOOL& );
};
