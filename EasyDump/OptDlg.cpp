#include "stdafx.h"
#include "EasyDump.h"
#include "OptDlg.h"
#include "FilterDialog.h"


////////////////////////////////////////////////////////////////////////////////


LRESULT COptionDialog::OnInitDialog( UINT, WPARAM, LPARAM, BOOL& )
{
	CEdit edt = GetDlgItem( IDC_DUMP_PATH );
	edt.LimitText( _countof(Settings.szDumpPath) - 1 );
	edt.SetWindowText( Settings.szDumpPath );

	if( Settings.dwSnapshot == ED_FULL_DUMP )
		CheckDlgButton( IDC_SNAPSHOT, BST_CHECKED );

	m_bAeDebug = IsAeDebug();
	if( m_bAeDebug )
		CheckDlgButton( IDC_AEDEBUG, BST_CHECKED );

	if( Settings.dwFirstChance == ED_DONT_DUMP )
		CheckDlgButton( IDC_FIRST_CHANCE, BST_CHECKED );
	else if( Settings.dwFirstChance == ED_MINI_DUMP )
		CheckDlgButton( IDC_FIRST_CHANCE + 1, BST_CHECKED );
	else if( Settings.dwFirstChance == ED_FULL_DUMP )
		CheckDlgButton( IDC_FIRST_CHANCE + 2, BST_CHECKED );

	if( Settings.dwSecondChance == ED_DONT_DUMP )
		CheckDlgButton( IDC_SECOND_CHANCE, BST_CHECKED );
	else if( Settings.dwSecondChance == ED_MINI_DUMP )
		CheckDlgButton( IDC_SECOND_CHANCE + 1, BST_CHECKED );
	else if( Settings.dwSecondChance == ED_FULL_DUMP )
		CheckDlgButton( IDC_SECOND_CHANCE + 2, BST_CHECKED );

	if( Settings.bAutoDelete )
		CheckDlgButton( IDC_AUTO_DELETE, BST_CHECKED );

	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT COptionDialog::OnOk( WORD, WORD, HWND, BOOL& )
{
	CSettings opt;

	GetDlgItemText( IDC_DUMP_PATH, opt.szDumpPath, _countof(opt.szDumpPath) );
	opt.szDumpPath[_countof(opt.szDumpPath) - 1] = 0;
	if( opt.szDumpPath[0] != 0 )
	{
		DWORD dwAttr = GetFileAttributes( opt.szDumpPath );
		if( dwAttr == INVALID_FILE_ATTRIBUTES
			|| (dwAttr & FILE_ATTRIBUTE_DIRECTORY) == 0 )
		{
			MessageBoxV( *this, IDS_DUMP_PATH_ERROR, MB_OK | MB_ICONHAND );
			GetDlgItem( IDC_DUMP_PATH ).SetFocus();
			return 0;
		}
	}

	opt.dwSnapshot = ED_MINI_DUMP;
	if( IsDlgButtonChecked( IDC_SNAPSHOT ) == BST_CHECKED )
		opt.dwSnapshot = ED_FULL_DUMP;

	if( IsDlgButtonChecked( IDC_FIRST_CHANCE ) == BST_CHECKED )
		opt.dwFirstChance = ED_DONT_DUMP;
	else if( IsDlgButtonChecked( IDC_FIRST_CHANCE + 1 ) == BST_CHECKED )
		opt.dwFirstChance = ED_MINI_DUMP;
	else if( IsDlgButtonChecked( IDC_FIRST_CHANCE + 2 ) == BST_CHECKED )
		opt.dwFirstChance = ED_FULL_DUMP;

	if( IsDlgButtonChecked( IDC_SECOND_CHANCE ) == BST_CHECKED )
		opt.dwSecondChance = ED_DONT_DUMP;
	else if( IsDlgButtonChecked( IDC_SECOND_CHANCE + 1 ) == BST_CHECKED )
		opt.dwSecondChance = ED_MINI_DUMP;
	else if( IsDlgButtonChecked( IDC_SECOND_CHANCE + 2 ) == BST_CHECKED )
		opt.dwSecondChance = ED_FULL_DUMP;

	opt.bAutoDelete = (IsDlgButtonChecked( IDC_AUTO_DELETE ) == BST_CHECKED);

	if( m_bAeDebug && IsDlgButtonChecked( IDC_AEDEBUG ) == BST_UNCHECKED )
		RestoreAeDebug();
	else if( !m_bAeDebug && IsDlgButtonChecked( IDC_AEDEBUG ) == BST_CHECKED )
		SetAeDebug();

	_InterlockedIncrement( &Settings.lVersion );

	Settings.dwSnapshot = opt.dwSnapshot;
	Settings.dwFirstChance = opt.dwFirstChance;
	Settings.dwSecondChance = opt.dwSecondChance;
	_tcscpy( Settings.szDumpPath, opt.szDumpPath );

	_InterlockedIncrement( &Settings.lVersion );

	if( m_aException.GetCount() != 0 )
		UpdateExceptionList( m_aException );

	EndDialog( IDOK );
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT COptionDialog::OnCancel( WORD, WORD, HWND, BOOL& )
{
	EndDialog( IDCANCEL );
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT COptionDialog::OnBrowse( WORD, WORD, HWND, BOOL& )
{
	TCHAR szTitle[32];
	AtlLoadString( IDS_BROWSE_DUMP_PATH, szTitle, _countof(szTitle) );

	CFolderDialog dlg( *this, szTitle );
	if( dlg.DoModal() == IDOK )
		SetDlgItemText( IDC_DUMP_PATH, dlg.m_szFolderPath );

	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT COptionDialog::OnFilter( WORD, WORD, HWND, BOOL& )
{
	if( m_aException.GetCount() == 0 )
		m_aException.Copy( GetExceptionList() );

	CFilterDialog dlg( m_aException );
	if( dlg.DoModal() == IDOK )
		m_aException.Copy( dlg.m_aException );

	return 0;
}


////////////////////////////////////////////////////////////////////////////////
// AeDebug

LPCTSTR COptionDialog::s_szAeDebug =
		_T("Software\\Microsoft\\Windows NT\\CurrentVersion\\AeDebug");
LPCTSTR COptionDialog::s_szDebugger = _T("Debugger");
LPCTSTR COptionDialog::s_szDebuggerBackup = _T("EasyDumpBackup");

//------------------------------------------------------------------------------

LPCTSTR COptionDialog::GetDebuggerCommandLine( LPTSTR buf )
{
	buf[0] = _T('"');
	DWORD len = GetModuleFileName( NULL, buf + 1, MAX_PATH );
	buf[len + 1] = _T('"');
	_tcscpy( buf + len + 2, _T(" -p:%ld -e:%ld") );
	return buf;
}

//------------------------------------------------------------------------------

BOOL COptionDialog::IsAeDebug()
{
	CRegKey reg;
	if( reg.Open( HKEY_LOCAL_MACHINE, s_szAeDebug, KEY_READ ) != ERROR_SUCCESS )
		return FALSE;

	TCHAR szValue[MAX_PATH + 64];
	ULONG lChars = _countof(szValue);
	if(reg.QueryStringValue( s_szDebugger, szValue, &lChars ) != ERROR_SUCCESS)
		return FALSE;
	szValue[_countof(szValue) - 1] = 0;

	TCHAR szCmdLine[MAX_PATH + 64];
	GetDebuggerCommandLine( szCmdLine );

	return _tcsicmp( szValue, szCmdLine ) == 0;
}

//------------------------------------------------------------------------------

BOOL COptionDialog::CopyRegString( CRegKey& reg, LPCTSTR szSrc, LPCTSTR szDst )
{
	TCHAR szValue[512];
	ULONG lChars = _countof(szValue);
	if( reg.QueryStringValue( szSrc, szValue, &lChars ) != ERROR_SUCCESS )
		return FALSE;
	szValue[_countof(szValue) - 1] = 0;
	if( reg.SetStringValue( szDst, szValue ) != ERROR_SUCCESS )
		return FALSE;
	return TRUE;
}

//------------------------------------------------------------------------------

BOOL COptionDialog::SetAeDebug()
{
	CRegKey reg;
	if( reg.Create( HKEY_LOCAL_MACHINE, s_szAeDebug ) != ERROR_SUCCESS )
		return FALSE;

	CopyRegString( reg, s_szDebugger, s_szDebuggerBackup );

	TCHAR szCmdLine[MAX_PATH + 64];
	GetDebuggerCommandLine( szCmdLine );
	if( reg.SetStringValue( s_szDebugger, szCmdLine ) != ERROR_SUCCESS )
		return FALSE;

	return TRUE;
}

//------------------------------------------------------------------------------

BOOL COptionDialog::RestoreAeDebug()
{
	CRegKey reg;
	if( reg.Create( HKEY_LOCAL_MACHINE, s_szAeDebug ) != ERROR_SUCCESS )
		return FALSE;
	CopyRegString( reg, s_szDebuggerBackup, s_szDebugger );
	reg.DeleteValue( s_szDebuggerBackup );
	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////