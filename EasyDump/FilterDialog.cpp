#include "StdAfx.h"
#include "EasyDump.h"
#include "FilterDialog.h"
#include "ExpDlg.h"


////////////////////////////////////////////////////////////////////////////////


CFilterDialog::CFilterDialog( CAtlArray<CExceptionInfo>& aException )
{
	m_aException.Copy( aException );
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CFilterDialog::OnInitDialog( UINT, WPARAM, LPARAM, BOOL& )
{
	CListViewCtrl list = GetDlgItem( IDC_EXCEPTION_LIST );
	list.SetExtendedListViewStyle( LVS_EX_CHECKBOXES | LVS_EX_INFOTIP );
	list.SetItemCount( m_aException.GetCount() );
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CFilterDialog::OnOk( WORD, WORD, HWND, BOOL& )
{
	EndDialog( IDOK );
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CFilterDialog::OnCancel( WORD, WORD, HWND, BOOL& )
{
	EndDialog( IDCANCEL );
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CFilterDialog::OnAdd( WORD, WORD, HWND, BOOL& )
{
	CExceptionDialog dlg( m_aException, -1 );
	if( dlg.DoModal() == IDOK )
	{
		CListViewCtrl list = GetDlgItem( IDC_EXCEPTION_LIST );
		list.SetItemCount( m_aException.GetCount() );
	}
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CFilterDialog::OnDelete( WORD, WORD, HWND, BOOL& )
{
	UINT uFlag = MB_YESNO | MB_ICONQUESTION;
	if( MessageBoxV( *this, IDS_CONFIRM_DELETE, uFlag ) == IDNO )
		return 0;

	CListViewCtrl list = GetDlgItem( IDC_EXCEPTION_LIST );
	for( int i = list.GetItemCount() - 1; i >= 0; --i )
	{
		if( !m_aException[i].bUser )
			continue;
		if( list.GetItemState( i, LVIS_SELECTED ) == LVIS_SELECTED )
			m_aException.RemoveAt( i);
	}

	list.SetItemCount( 0 );
	list.SetItemCount( m_aException.GetCount() );
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CFilterDialog::OnSelectAll( WORD, WORD, HWND, BOOL& )
{
	for( size_t i = 0; i < m_aException.GetCount(); ++i )
		m_aException[i].bFiltered = true;
	CListViewCtrl list = GetDlgItem( IDC_EXCEPTION_LIST );
	list.Invalidate();
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CFilterDialog::OnUnselectAll( WORD, WORD, HWND, BOOL& )
{
	for( size_t i = 0; i < m_aException.GetCount(); ++i )
		m_aException[i].bFiltered = false;
	CListViewCtrl list = GetDlgItem( IDC_EXCEPTION_LIST );
	list.Invalidate();
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CFilterDialog::OnGetTooltip( int, LPNMHDR pNMHDR, BOOL& )
{
	LPNMLVGETINFOTIP pGetInfoTip = reinterpret_cast<LPNMLVGETINFOTIP>(pNMHDR);

	CExceptionInfo& ei = m_aException[pGetInfoTip->iItem];
	_sntprintf(
		pGetInfoTip->pszText,
		pGetInfoTip->cchTextMax,
		_T("0x%08X\n%s"),
		ei.dwCode,
		ei.szName
		);
	pGetInfoTip->pszText[pGetInfoTip->cchTextMax - 1] = 0;
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CFilterDialog::OnGetDispInfo( int, LPNMHDR pNMHDR, BOOL& )
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	LPLVITEM pItem = &pDispInfo->item;
	CExceptionInfo& ei = m_aException[pItem->iItem];
	ATLASSERT( pItem->iSubItem == 0 );

	pItem->mask = LVIF_TEXT | LVIF_STATE;
	pItem->pszText = ei.szName;
	pItem->stateMask = LVIS_STATEIMAGEMASK;
	pItem->state = INDEXTOSTATEIMAGEMASK( ei.bFiltered ? 2 : 1 );

	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CFilterDialog::OnItemChanged( int, LPNMHDR, BOOL& )
{
	CListViewCtrl list = GetDlgItem( IDC_EXCEPTION_LIST );
	GetDlgItem( IDC_DELETE ).EnableWindow( list.GetSelectedCount() > 0 );
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CFilterDialog::OnListDblClk( int, LPNMHDR pNMHDR, BOOL& )
{
	LPNMITEMACTIVATE pNmItem = reinterpret_cast<LPNMITEMACTIVATE>( pNMHDR );
	if( pNmItem->iItem < 0 )
		return 0;

	CExceptionInfo& ei = m_aException[pNmItem->iItem];
	if( !ei.bUser )
		return 0;

	CExceptionDialog dlg( m_aException, pNmItem->iItem );
	if( dlg.DoModal() == IDOK )
	{
		CListViewCtrl list = GetDlgItem( IDC_EXCEPTION_LIST );
		list.Invalidate();
	}

	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CFilterDialog::OnListClick( int, LPNMHDR pNMHDR, BOOL& )
{
	LPNMITEMACTIVATE pNmItem = reinterpret_cast<LPNMITEMACTIVATE>( pNMHDR );
	if( pNmItem->iItem < 0 )
		return 0;

	CListViewCtrl list = GetDlgItem( IDC_EXCEPTION_LIST );
	UINT uFlags = 0;
	list.HitTest( pNmItem->ptAction, &uFlags );
	if( (uFlags == LVHT_ONITEMSTATEICON) )
	{
		CExceptionInfo& ei = m_aException[pNmItem->iItem];
		ei.bFiltered = !ei.bFiltered;
		RECT rect;
		list.GetItemRect( pNmItem->iItem, &rect, LVIR_BOUNDS );
		list.InvalidateRect( &rect );
	}

	return 0;
}


////////////////////////////////////////////////////////////////////////////////


LRESULT CFilterDialog::OnListKeyDown( int, LPNMHDR pNMHDR, BOOL& bHandled )
{
	LPNMLVKEYDOWN pKey = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);

	if( pKey->wVKey != VK_SPACE )
	{
		bHandled = FALSE;
		return 0;
	}

	CListViewCtrl list = GetDlgItem( IDC_EXCEPTION_LIST );
	int idx = list.GetNextItem( -1, LVNI_SELECTED );
	while( idx != -1 )
	{
		CExceptionInfo& ei = m_aException[idx];
		ei.bFiltered = !ei.bFiltered;
		RECT rect;
		list.GetItemRect( idx, &rect, LVIR_BOUNDS );
		list.InvalidateRect( &rect );
		idx = list.GetNextItem( idx, LVNI_SELECTED );
	}

	return 0;
}


////////////////////////////////////////////////////////////////////////////////