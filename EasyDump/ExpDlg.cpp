#include "StdAfx.h"
#include "EasyDump.h"
#include "ExpDlg.h"


////////////////////////////////////////////////////////////////////////////////


CExceptionDialog::CExceptionDialog(
								   CAtlArray<CExceptionInfo>& aException,
								   int nIndex
								   )
								   : m_aException( aException )
								   , m_nIndex( nIndex )
{
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CExceptionDialog::OnInitDialog( UINT, WPARAM, LPARAM, BOOL& )
{
	int nLimit = _countof( m_aException[0].szName ) - 1;
	((CEdit)GetDlgItem( IDC_NAME )).LimitText( nLimit );

	if( m_nIndex != -1 )
	{
		TCHAR buf[16];
		CExceptionInfo& ei = m_aException[m_nIndex];
		_sntprintf( buf, _countof(buf), _T("0x%08X"), ei.dwCode );
		SetDlgItemText( IDC_CODE, buf );
		SetDlgItemText( IDC_NAME, ei.szName );
	}

	return 0;
}


////////////////////////////////////////////////////////////////////////////////


DWORD CExceptionDialog::GetExceptionCode( BOOL& bTrans )
{
	TCHAR szTxt[16];
	LPCTSTR szStart = szTxt;
	TCHAR* pEnd = NULL;

	if( GetDlgItemText( IDC_CODE, szTxt, _countof(szTxt) ) == 0 )
	{
		bTrans = FALSE;
		return 0;
	}

	// don't use _tcstol, if the number is large than 0x7fffffff,
	// it return 0x7fffffff
	DWORD dwRes = _tcstoul( szStart, &pEnd, 0 );
	if( (dwRes == 0 || dwRes == 0xffffffff) && (errno == ERANGE) )
	{
		bTrans = FALSE;
		return 0;
	}

	while( *pEnd != 0 )
	{
		if( *pEnd != _T(' ') && *pEnd != _T('\t') )
		{
			bTrans = FALSE;
			return 0;
		}
		++pEnd;
	}

	bTrans = TRUE;
	return dwRes;
}


////////////////////////////////////////////////////////////////////////////////


BOOL CExceptionDialog::IsExceptionCodeExist( DWORD dwCode )
{
	for( int i = 0; i < static_cast<int>(m_aException.GetCount()); ++i )
		if( m_aException[i].dwCode == dwCode && m_nIndex != i )
			return TRUE;
	return FALSE;
}


////////////////////////////////////////////////////////////////////////////////


BOOL CExceptionDialog::IsExceptionNameExist( LPCTSTR szName )
{
	for( int i = 0; i < static_cast<int>(m_aException.GetCount()); ++i )
		if( _tcsicmp( m_aException[i].szName, szName ) == 0 && m_nIndex != i )
			return TRUE;
	return FALSE;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CExceptionDialog::OnOk( WORD, WORD, HWND, BOOL& )
{
	BOOL bTrans = TRUE;
	DWORD dwCode = 0;
	TCHAR szName[_countof(m_aException[0].szName)];

	dwCode = GetExceptionCode( bTrans );
	if( !bTrans )
	{
		MessageBoxV( *this, IDS_INVALID_INPUT, MB_OK | MB_ICONHAND );
		GetDlgItem( IDC_CODE ).SetFocus();
		return 0;
	}

	if( GetDlgItemText( IDC_NAME, szName, _countof(szName) ) == 0 )
	{
		MessageBoxV( *this, IDS_INVALID_INPUT, MB_OK | MB_ICONHAND );
		GetDlgItem( IDC_NAME ).SetFocus();
		return 0;
	}

	if( IsExceptionCodeExist( dwCode ) )
	{
		MessageBoxV( *this, IDS_ALREADY_EXIST, MB_OK | MB_ICONHAND );
		GetDlgItem( IDC_CODE ).SetFocus();
		return 0;
	}

	if( IsExceptionNameExist( szName ) )
	{
		MessageBoxV( *this, IDS_ALREADY_EXIST, MB_OK | MB_ICONHAND );
		GetDlgItem( IDC_NAME ).SetFocus();
		return 0;
	}

	if( m_nIndex == -1 )
	{
		CExceptionInfo ei;
		ei.bFiltered = false;
		ei.bUser = true;
		ei.dwCode = dwCode;
		ei.Reserved = 0;
		_tcscpy( ei.szName, szName );
		m_aException.Add( ei );
	}
	else
	{
		m_aException[m_nIndex].dwCode = dwCode;
		_tcscpy( m_aException[m_nIndex].szName, szName );
	}

	EndDialog( IDOK );
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CExceptionDialog::OnCancel( WORD, WORD, HWND, BOOL& )
{
	EndDialog( IDCANCEL );
	return 0;
}


////////////////////////////////////////////////////////////////////////////////