#include "stdafx.h"
#include "EasyDump.h"
#include "CrtProcDlg.h"


////////////////////////////////////////////////////////////////////////////////


LRESULT CCreateProcessDialog::OnInitDialog( UINT, WPARAM, LPARAM, BOOL& )
{
	m_szAppPath[0] = 0;
	m_szArg[0] = 0;
	m_szWorkDir[0] = 0;

	CEdit edt = GetDlgItem( IDC_APPPATH );
	edt.LimitText( _countof(m_szAppPath) - 1 );

	edt = GetDlgItem( IDC_ARGUMENT );
	edt.LimitText( _countof(m_szArg) - 1 );

	edt = GetDlgItem( IDC_WORKDIR );
	edt.LimitText( _countof(m_szWorkDir) - 1 );

	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CCreateProcessDialog::OnOk( WORD, WORD, HWND, BOOL& )
{
	if( GetDlgItemText( IDC_APPPATH, m_szAppPath, _countof(m_szAppPath) ) == 0 )
	{
		MessageBoxV( *this, IDS_INVALID_APPPATH, MB_OK | MB_ICONHAND );
		return 0;
	}

	GetDlgItemText( IDC_ARGUMENT, m_szArg, _countof(m_szArg) );
	GetDlgItemText( IDC_WORKDIR, m_szWorkDir, _countof(m_szWorkDir) );
	EndDialog( IDOK );
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CCreateProcessDialog::OnCancel( WORD, WORD, HWND, BOOL& )
{
	EndDialog( IDCANCEL );
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CCreateProcessDialog::OnBrowseAppPath( WORD, WORD, HWND, BOOL& )
{
	DWORD dwFlag = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	TCHAR szFilter[64];
	AtlLoadString( IDS_APP_FILTER, szFilter, _countof(szFilter) );
	for( int i = 0; i < _countof(szFilter); ++i )
		if( szFilter[i] == _T('|') )
			szFilter[i] = 0;
	CFileDialog dlg( true, NULL, NULL, dwFlag, szFilter );
	if( dlg.DoModal() == IDOK )
		SetDlgItemText( IDC_APPPATH, dlg.m_szFileName );
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CCreateProcessDialog::OnBrowseWorkDir( WORD, WORD, HWND, BOOL& )
{
	TCHAR szTitle[32];
	AtlLoadString( IDS_BROWSE_WORKDIR, szTitle, _countof(szTitle) );

	CFolderDialog dlg( *this, szTitle );
	if( dlg.DoModal() == IDOK )
		SetDlgItemText( IDC_WORKDIR, dlg.m_szFolderPath );

	return 0;
}


////////////////////////////////////////////////////////////////////////////////