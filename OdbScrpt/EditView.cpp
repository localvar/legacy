// OdbScrptView.cpp : implementation of the CScriptEditView class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OdbScrpt.h"
#include "EditView.h"
#include "OptDlg.h"
#include "MainFrm.h"
#include ".\editview.h"



CScriptEditView::CScriptEditView()
	: m_pFindDlg( NULL )
	, m_nTabStop( 8 )
{
	m_szFileName[0] = m_szFilePath[0] = m_fro.StrToFind[0] = 0;
	m_fro.bMatchCase = m_fro.bWholeWord = m_fro.bFindOnly = true;
}


BOOL CScriptEditView::PreTranslateMessage( MSG* pMsg )
{
	if( m_pFindDlg != NULL )
	{
		ATLASSERT( ::IsWindow(m_pFindDlg->m_hWnd) );
		if( m_pFindDlg->IsDialogMessage(pMsg) )
			return TRUE;
	}

	return FALSE;
}



LRESULT CScriptEditView::OnSetFont( WORD, WORD, HWND, BOOL& )
{
	CFontDialog dlg( NULL, CF_EFFECTS | CF_SCREENFONTS | CF_NOVERTFONTS );
	m_font.GetLogFont( &dlg.m_lf );
	dlg.m_cf.Flags |= CF_INITTOLOGFONTSTRUCT;
	if (dlg.DoModal() == IDOK)
	{
		m_font.DeleteObject();
		m_font.CreateFontIndirect( &dlg.m_lf );
		SetFont( m_font );
		SetTabStopWidth();
	}
	return 0;
}



LRESULT CScriptEditView::OnContextMenu( UINT, WPARAM wParam, LPARAM lParam, BOOL& )
{
	return WtlGetMainWnd().SendMessage( WM_CONTEXTMENU, wParam, lParam );
}


LRESULT CScriptEditView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& )
{
	LRESULT lRet = DefWindowProc( uMsg, wParam, lParam );
	if( lRet != -1 )
	{
		m_font = AtlGetDefaultGuiFont();
		SetFont( m_font );
		SetOptions( ECOOP_OR, ECO_SELECTIONBAR );
		SetTabStopWidth();
		SetEventMask( GetEventMask() | ENM_CHANGE );
		SetModify( FALSE );
	}

	return lRet;
}



LRESULT CScriptEditView::OnKey( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& )
{
	LRESULT lRet = DefWindowProc( uMsg, wParam, lParam );

	//if( uMsg == WM_KEYDOWN && wParam == VK_INSERT )
	//{
	//	bool bOn = ((GetKeyState(VK_INSERT) & 1) == 1);
	//	if( bOn )
	//		CreateSolidCaret( 10, 10 );
	//	else
	//		CreateSolidCaret( 2, 10 );
	//}

	// calc caret position
	long nStartPos, nEndPos;
	GetSel( nStartPos, nEndPos );
	int nRow = LineFromChar( nEndPos );
	int nCol = 0;
	int nChar = nEndPos - LineIndex();
	if( nChar > 0 )
	{
		// min = WORD for length
		LPTSTR lpstrLine = (LPTSTR)_alloca( (nChar + 2) * sizeof(TCHAR) );
		nChar = GetLine( nRow, lpstrLine, nChar );
		for( int i = 0; i < nChar; i++ )
		{
			if(lpstrLine[i] == _T('\t'))
				nCol = ((nCol / m_nTabStop) + 1) * m_nTabStop;
			else
				nCol++;
		}
	}

	WtlGetMainWnd().UndateRowCol( nRow + 1, nCol + 1 );

	return lRet;
}



BOOL CScriptEditView::SetTabStopWidth()
{
	CClientDC dc( *this );
	HFONT hOldFont = dc.SelectFont(m_font);

	TEXTMETRIC tm;
	dc.GetTextMetrics( &tm );
	int nLogPix = dc.GetDeviceCaps( LOGPIXELSX );
	dc.SelectFont(hOldFont);

	// 1440 twips = 1 inch
	int cxTab = ::MulDiv( tm.tmAveCharWidth * m_nTabStop, 1440, nLogPix );
	if(cxTab != -1)
	{
		PARAFORMAT pf;
		pf.cbSize = sizeof( PARAFORMAT );
		pf.dwMask = PFM_TABSTOPS;
		pf.cTabCount = MAX_TAB_STOPS;
		for(int i = 0; i < MAX_TAB_STOPS; i++)
			pf.rgxTabs[i] = (i + 1) * cxTab;
		SetParaFormat( pf );
	}

	return TRUE;
}


bool CScriptEditView::CreateFindReplaceDialog( bool bFindOnly )
{
	if( m_pFindDlg != NULL )
	{
		if( m_fro.bFindOnly == bFindOnly )
		{
			ATLASSERT( ::IsWindow(m_pFindDlg->m_hWnd) );
			m_pFindDlg->SetFocus();
			return true;
		}
		else
		{
			// m_pFindDlg was deleted in OnFinalMessage
			m_pFindDlg->DestroyWindow();
			m_pFindDlg = NULL;
		}
	}

	m_pFindDlg = new CFindReplaceDialog;
	if(m_pFindDlg == NULL)
	{
		ATLASSERT( FALSE );
		return false;
	}

	m_fro.bFindOnly = bFindOnly;
	DWORD dwFlags = FR_HIDEUPDOWN;
	if( m_fro.bMatchCase )
		dwFlags |= FR_MATCHCASE;
	if( m_fro.bWholeWord )
		dwFlags |= FR_WHOLEWORD;

	if( !m_pFindDlg->Create( bFindOnly, m_fro.StrToFind, NULL, dwFlags, m_hWnd) )
	{
		delete m_pFindDlg;
		m_pFindDlg = NULL;
		return false;
	}

	m_pFindDlg->ShowWindow(SW_NORMAL);

	return true;
}


LRESULT CScriptEditView::OnEditFind( WORD, WORD, HWND, BOOL& )
{
	if( !CreateFindReplaceDialog(true) )
		::MessageBeep( (UINT)-1 );
	return 0;
}


LRESULT CScriptEditView::OnEditFindNext( WORD wNotifyCode, WORD wId, HWND hWndCtl, BOOL& bHandled )
{
	if( m_fro.StrToFind[0] == 0 )
		return OnEditFind( wNotifyCode, wId, hWndCtl, bHandled );

	if( !DoFindText() )
		::MessageBeep( (UINT)-1 );

	return 0;
}


LRESULT CScriptEditView::OnEditReplace( WORD, WORD, HWND, BOOL& )
{
	if( !CreateFindReplaceDialog(false) )
		::MessageBeep( (UINT)-1 );
	return 0;
}


LRESULT CScriptEditView::OnFindReplaceCmd( UINT, WPARAM, LPARAM lParam, BOOL& )
{
	CFindReplaceDialog* pDlg = CFindReplaceDialog::GetNotifier(lParam);
	if( pDlg == NULL )
	{
		::MessageBeep( (UINT)-1 );
		return 1;
	}
	ATLASSERT( pDlg == m_pFindDlg );

	if( pDlg->IsTerminating() )
	{
		m_pFindDlg = NULL;
		return 0;
	}

	lstrcpyn( m_fro.StrToFind, pDlg->m_fr.lpstrFindWhat, DIMOF(m_fro.StrToFind) );
	m_fro.bMatchCase = (pDlg->MatchCase() != FALSE);
	m_fro.bWholeWord = (pDlg->MatchWholeWord() != FALSE);

	if( pDlg->FindNext() )
	{
		if( !DoFindText() )
			::MessageBeep( (UINT)-1 );
	}
	else if( pDlg->ReplaceCurrent() )
	{
		long nStart, nEnd;
		GetSel( nStart, nEnd );

		if( nStart != nEnd )
		{
			LPTSTR szFind = (LPTSTR)_alloca( (nEnd - nStart + 1) * sizeof(TCHAR) );
			GetSelText( szFind );
			int nRet;
			if( m_fro.bMatchCase )
				nRet = lstrcmp( szFind, m_fro.StrToFind );
			else
				nRet = lstrcmpi( szFind, m_fro.StrToFind );
			if(nRet == 0)
				ReplaceSel( pDlg->GetReplaceString(), TRUE );
		}

		if( !DoFindText() )
			::MessageBeep( (UINT)-1 );

	}
	else if( pDlg->ReplaceAll() )
	{
		SetRedraw(FALSE);
		CWaitCursor wait;
		while( DoFindText(false) )
			ReplaceSel( pDlg->GetReplaceString(), TRUE );
		SetRedraw( TRUE );
		Invalidate();
		UpdateWindow();
	}

	return 0;
}


bool CScriptEditView::DoFindText( bool bNext )
{
	DWORD dwFlags = FR_DOWN;
	if( m_fro.bMatchCase )
		dwFlags |= FR_MATCHCASE;
	if( m_fro.bWholeWord )
		dwFlags |= FR_WHOLEWORD;

	long nStart, nEnd;
	GetSel( nStart, nEnd );

	FINDTEXTEX ft;
	ft.chrg.cpMin = bNext ? nEnd : nStart ;
	ft.chrg.cpMax = -1;
	ft.lpstrText = m_fro.StrToFind;

	if( FindText(dwFlags, ft) == -1 )
		return false;

	SetSel( ft.chrgText );

	return true;
}


bool CScriptEditView::QueryClose()
{
	if( !GetModify() )
		return true;

	TCHAR szFmt[32];
	AtlLoadString( IDS_SAVE_MODIFIED, szFmt, DIMOF(szFmt) );
	TCHAR szBuff[MAX_PATH + 40];
	wsprintf( szBuff, szFmt, m_szFileName );
	int nRet = AtlMessageBox(
		WtlGetMainWnd(),
		szBuff,
		IDR_MAINFRAME,
		MB_YESNOCANCEL | MB_ICONEXCLAMATION
		);

	if(nRet == IDCANCEL)
		return false;

	if(nRet == IDYES)
		return OnFileSave();

	return true;
}


void CScriptEditView::Init( LPCTSTR szFilePath, LPCTSTR szFileName )
{
	lstrcpy( m_szFilePath, szFilePath );
	lstrcpy( m_szFileName, szFileName );
	SetModify( FALSE );
}


bool CScriptEditView::OnFileSaveAs()
{
	bool bRet = false;

	TCHAR szFilter[256];
	::ZeroMemory( szFilter, DIMOF(szFilter) );
	int nChar = AtlLoadString( IDS_FILE_FILTER, szFilter, DIMOF(szFilter) );

	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog dlg( FALSE, _T("*.txt"), m_szFilePath, dwFlags, szFilter );
	if( dlg.DoModal() == IDOK )
	{
		ATLTRACE( _T("File path: %s\n"), dlg.m_ofn.lpstrFile );
		bRet = SaveFile( dlg.m_szFileName );
		if( bRet )
		{
			Init( dlg.m_szFileName, dlg.m_szFileTitle );
		}
		else
		{
			AtlMessageBox(
				WtlGetMainWnd(),
				IDS_WRITE_FILE_FAILED,
				IDR_MAINFRAME,
				MB_OK|MB_ICONERROR
				);
		}
	}

	return bRet;
}


bool CScriptEditView::DoFileSave()
{
	ATLASSERT( m_szFilePath[0] != 0 );

	if( !GetModify() )
		return true;

	bool bRet = SaveFile( m_szFilePath );
	if( bRet )
	{
		SetModify( FALSE );
	}
	else
	{
		AtlMessageBox(
			WtlGetMainWnd(),
			IDS_WRITE_FILE_FAILED,
			IDR_MAINFRAME,
			MB_OK|MB_ICONERROR
			);
	}

	return bRet;
}


DWORD CALLBACK CScriptEditView::StreamWriteCallback( DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb )
{
	ATLASSERT( dwCookie != 0 );
	ATLASSERT( pcb != NULL );

	HANDLE hFile = reinterpret_cast<HANDLE>(dwCookie);
	return !::WriteFile( hFile, pbBuff, cb, (LPDWORD)pcb, NULL );
}


bool CScriptEditView::SaveFile( LPCTSTR szFilePath )
{
	ATLASSERT( szFilePath != NULL && szFilePath[0] != 0 );

	DWORD dwFlag = FILE_ATTRIBUTE_ARCHIVE | FILE_FLAG_SEQUENTIAL_SCAN;
	HANDLE hFile = ::CreateFile( szFilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, dwFlag, NULL );
	if( hFile == INVALID_HANDLE_VALUE )
		return false;

	EDITSTREAM es;
	es.dwCookie = reinterpret_cast<DWORD_PTR>(hFile);
	es.dwError = 0;
	es.pfnCallback = StreamWriteCallback;
	StreamOut( SF_TEXT, es );

	::CloseHandle( hFile );

	return es.dwError == 0;
}


bool CScriptEditView::OnFileSave()
{
	return (m_szFilePath[0] == 0) ? OnFileSaveAs() : DoFileSave();
}


DWORD CALLBACK CScriptEditView::StreamReadCallback( DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb )
{
	ATLASSERT( dwCookie != 0 );
	ATLASSERT( pcb != NULL );

	HANDLE hFile = reinterpret_cast<HANDLE>(dwCookie);
	return !::ReadFile( hFile, pbBuff, cb, (LPDWORD)pcb, NULL );
}


bool CScriptEditView::LoadFile( LPCTSTR szFilePath )
{
	ATLASSERT( szFilePath != NULL && szFilePath[0] != 0 );

	DWORD dwFlag = FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN;
	HANDLE hFile = ::CreateFile( szFilePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, dwFlag, NULL );
	if( hFile == INVALID_HANDLE_VALUE )
		return false;

	EDITSTREAM es;
	es.dwCookie = reinterpret_cast<DWORD_PTR>(hFile);
	es.dwError = 0;
	es.pfnCallback = StreamReadCallback;
	StreamIn( SF_TEXT, es );

	::CloseHandle(hFile);

	return es.dwError == 0;
}



LPCTSTR CScriptEditView::GetFileName()
{
	return m_szFileName;
}



LRESULT CScriptEditView::OnViewOption( WORD, WORD, HWND, BOOL& )
{
	COptDlg dlg( m_font, 8, _T(""), true );
	if( dlg.DoModal() == IDOK )
	{
	}
	return 0;
}
