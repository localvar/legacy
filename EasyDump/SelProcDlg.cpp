#include "stdafx.h"
#include "EasyDump.h"
#include "SelProcDlg.h"


////////////////////////////////////////////////////////////////////////////////


LRESULT CSelProcDlg::OnInitDialog( UINT, WPARAM, LPARAM, BOOL& )
{
	m_hProc = NULL;

	DlgResize_Init( false );

	m_lst.SubclassWindow( GetDlgItem( IDC_PROCESS_LIST ) );
	DWORD dwStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	dwStyle |= LVS_EX_HEADERDRAGDROP;
	m_lst.SetExtendedListViewStyle( dwStyle );

	TCHAR szHeaders[128];
	AtlLoadString( IDS_PROCESS_LIST_HEADER, szHeaders, _countof(szHeaders) );

	RECT rect;
	m_lst.GetWindowRect( &rect );
	int nWidth = rect.right - rect.left;

	int nIndex = 0;
	LPCTSTR sz = _tcstok( szHeaders, _T("\n") );
	while( sz != NULL )
	{
		int w = _ttoi(_tcstok( NULL, _T("\n") )) * nWidth / 100;
		m_lst.InsertColumn( nIndex++, sz, LVCFMT_LEFT, w, 0 );
		sz = _tcstok( NULL, _T("\n") );
	}

	m_lst.SetColumnSortType( 0, LVCOLSORT_TEXTNOCASE );
	m_lst.SetColumnSortType( 1, LVCOLSORT_LONG );
	m_lst.SetColumnSortType( 2, LVCOLSORT_TEXTNOCASE );
	m_lst.SetSortColumn( 0 );

	RefreshProcessList();
	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////


void CSelProcDlg::RefreshProcessList()
{
	HANDLE hss = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	if( hss == INVALID_HANDLE_VALUE )
		return;

	PROCESSENTRY32 pe = { sizeof(PROCESSENTRY32) };
	if( !Process32First( hss, &pe ) )
	{
		CloseHandle( hss );
		return;
	}

	m_lst.SetRedraw( FALSE );
	m_lst.DeleteAllItems();

	do
	{
		int nIndex = m_lst.GetItemCount();
		DWORD pid = pe.th32ProcessID;
		if( pid == GetCurrentProcessId() )	// skip this process
			continue;

		m_lst.InsertItem( nIndex, pe.szExeFile );

		TCHAR buf[MAX_PATH];
		m_lst.SetItemText( nIndex, 1, _itot(pid, buf, 10) );

		if( pid == 0 ) // skip the "system process"
			continue;

		if( GetImagePathByPid( pid, buf, _countof(buf) ) )
			m_lst.SetItemText( nIndex, 2, buf );
	} while( Process32Next( hss, &pe ) );

	CloseHandle( hss );

	m_lst.SortItems(m_lst.GetSortColumn(), m_lst.IsSortDescending());
	m_lst.SetRedraw( TRUE );
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CSelProcDlg::OnCancel( WORD, WORD, HWND, BOOL& )
{
	EndDialog( IDCANCEL );
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CSelProcDlg::OnOk( WORD, WORD, HWND, BOOL& )
{
	int nIndex = m_lst.GetNextItem( -1, LVNI_SELECTED );

	TCHAR buf[16];
	m_lst.GetItemText( nIndex, 1, buf, _countof(buf) );
	m_dwPid = _tcstoul( buf, NULL, 0 );

	m_lst.GetItemText( nIndex, 2, m_szImagePath, _countof(m_szImagePath) );

	EndDialog( IDOK );
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CSelProcDlg::OnRefresh( WORD, WORD, HWND, BOOL& )
{
	RefreshProcessList();
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CSelProcDlg::OnLvnItemchangedProcessList( int, LPNMHDR pNMHDR, BOOL& )
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int nIndex = m_lst.GetNextItem( -1, LVNI_SELECTED );
	GetDlgItem( IDOK ).EnableWindow( nIndex >= 0 );
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CSelProcDlg::OnNMDblclkProcessList( int, LPNMHDR, BOOL& bHandled )
{
	if( m_lst.GetNextItem( -1, LVNI_SELECTED ) >= 0 )
		OnOk( 0, 0, NULL, bHandled );
	return 0;
}


////////////////////////////////////////////////////////////////////////////////