#pragma once

class CExceptionDialog : public CDialogImpl<CExceptionDialog>
{
public:
	CAtlArray<CExceptionInfo>& m_aException;
	int m_nIndex;

public:
	enum { IDD = IDD_EXCEPTION };

	BEGIN_MSG_MAP( CExceptionDialog )
		COMMAND_ID_HANDLER( IDOK, OnOk )
		COMMAND_ID_HANDLER( IDCANCEL, OnCancel )
		MESSAGE_HANDLER( WM_INITDIALOG, OnInitDialog )
	END_MSG_MAP()

public:
	DWORD GetExceptionCode( BOOL& bTrans );
	BOOL IsExceptionCodeExist( DWORD dwCode );
	BOOL IsExceptionNameExist( LPCTSTR szName );

public:
	CExceptionDialog( CAtlArray<CExceptionInfo>& aException, int nIndex );
	LRESULT OnInitDialog( UINT, WPARAM, LPARAM, BOOL& );
	LRESULT OnOk( WORD, WORD, HWND, BOOL& );
	LRESULT OnCancel( WORD, WORD, HWND, BOOL& );
};
