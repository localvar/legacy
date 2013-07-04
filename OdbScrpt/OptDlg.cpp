#include "StdAfx.h"
#include "OdbScrpt.h"
#include "OptDlg.h"



COptDlg::COptDlg( HFONT hFont, UINT uTabWidth, LPCTSTR szPath, bool bViewNaviBar )
	: m_font( hFont )
	, m_uTabWidth( uTabWidth )
	, m_bViewNaviBar( bViewNaviBar )
{
	ATLASSERT( szPath != NULL );

	lstrcpyn( m_szPath, szPath, DIMOF(m_szPath) );
	m_szPath[MAX_PATH] = 0;
}


LRESULT COptDlg::OnInitDialog( UINT, WPARAM, LPARAM, BOOL& )
{
	InitFontStyle();
	SetDlgItemText( IDC_PATH, m_szPath );
	SetDlgItemInt( IDC_TAB_WIDTH, m_uTabWidth );
	CheckDlgButton( IDC_NAVI_BAR, m_bViewNaviBar ? BST_CHECKED : BST_UNCHECKED );

	CEdit edt = GetDlgItem( IDC_PATH );
	edt.LimitText( MAX_PATH - 1 );

	edt = GetDlgItem( IDC_TAB_WIDTH );
	edt.LimitText( 2 );

	return TRUE;
}


bool COptDlg::InitFontStyle()
{
	LOGFONT lf = {0};
	CClientDC dc( *this );

	// fill the font face combo box
	lf.lfCharSet = DEFAULT_CHARSET;
	FONTENUMPROC proc = reinterpret_cast<FONTENUMPROC>( EnumFontCallBackStub );
	LPARAM param = reinterpret_cast<LPARAM>( this );
	EnumFontFamiliesEx( dc, &lf, proc, param, 0 );

	// fill the font size combo box
	CComboBox cb = GetDlgItem( IDC_FONT_SIZE );
	for( int i = FONT_SIZE_MIN; i <= FONT_SIZE_MAX; ++i )
	{
		TCHAR szText[8];
		_itot( i, szText, 10 );
		cb.AddString( szText );
	}

	// set the default selections
	m_font.GetLogFont( &lf );

	// font face
	cb = GetDlgItem( IDC_FONT_FACE );
	cb.SelectString( 0, lf.lfFaceName );

	// font size
	int nHeight = lf.lfHeight;
	if( nHeight < 0 )
	{
		POINT pt = { 0, 0 };
		dc.DPtoLP( &pt );
		pt.y = pt.y - nHeight;
		dc.LPtoDP( &pt );
		nHeight = ::MulDiv( pt.y, 720, dc.GetDeviceCaps(LOGPIXELSY) );
	}
	cb = GetDlgItem( IDC_FONT_SIZE );
	cb.SetCurSel( nHeight / 10 - FONT_SIZE_MIN );

	// bold and italic
	CheckDlgButton( IDC_BOLD, lf.lfWeight == FW_BOLD ? BST_CHECKED : BST_UNCHECKED );
	CheckDlgButton( IDC_ITALIC, lf.lfItalic ? BST_CHECKED : BST_UNCHECKED );

	// preview this font
	GetDlgItem( IDC_SAMPLE ).SetFont( m_font );

	return true;
}


LRESULT COptDlg::OnCancel( WORD, WORD, HWND, BOOL& )
{
	EndDialog( IDCANCEL );
	return 0;
}


void COptDlg::PreviewFont()
{
	CComboBox cb = GetDlgItem( IDC_FONT_SIZE );
	int nSize = (cb.GetCurSel() + FONT_SIZE_MIN) * 10;

	TCHAR szFace[LF_FACESIZE];
	GetDlgItem(IDC_FONT_FACE).GetWindowText( szFace, DIMOF(szFace) );

	bool bBold = IsDlgButtonChecked( IDC_BOLD ) == BST_CHECKED;
	bool bItalic = IsDlgButtonChecked( IDC_ITALIC ) == BST_CHECKED;

	m_font.DeleteObject();
	m_font.CreatePointFont( nSize, szFace, NULL, bBold, bItalic );

	GetDlgItem( IDC_SAMPLE ).SetFont( m_font );
}



LRESULT COptDlg::OnFontChange( WORD, WORD, HWND, BOOL& )
{
	PreviewFont();
	return 0;
}



LRESULT COptDlg::OnOk( WORD, WORD, HWND, BOOL& )
{
	m_uTabWidth = GetDlgItemInt(IDC_TAB_WIDTH);
	if( m_uTabWidth == 0 )
	{
		AtlMessageBox( *this,
			IDS_WRONG_TAB_WIDTH,
			IDR_MAINFRAME,
			MB_OK | MB_ICONERROR
			);
	}
	else
	{
		m_bViewNaviBar = (IsDlgButtonChecked( IDC_NAVI_BAR ) == BST_CHECKED);
		GetDlgItemText( IDC_PATH, m_szPath, DIMOF(m_szPath) );
		EndDialog( IDOK );
	}
	return 0;
}



BOOL COptDlg::EnumFontCallBack( ENUMLOGFONTEX* lplf, NEWTEXTMETRICEX* lpntm, DWORD dwFontType )
{
	CComboBox cb = GetDlgItem( IDC_FONT_FACE );

	BYTE byCharset = lplf->elfLogFont.lfCharSet;
	LPCTSTR szFace = lplf->elfLogFont.lfFaceName;
	if( (byCharset == ANSI_CHARSET || byCharset == GB2312_CHARSET)
		&& (szFace[0] != _T('@'))	// i don't want vert fonts
		&& (cb.FindString(0, szFace) == -1)
		)
	{
		cb.AddString( lplf->elfLogFont.lfFaceName );
	}
	return TRUE;
}



BOOL CALLBACK COptDlg::EnumFontCallBackStub(
	ENUMLOGFONTEX* lplf,
	NEWTEXTMETRICEX* lpntm,
	DWORD dwFontType,
	LPARAM lParam
	)
{
	COptDlg* pDlg = reinterpret_cast<COptDlg*>( lParam );
	return pDlg->EnumFontCallBack( lplf, lpntm, dwFontType );
}



LRESULT COptDlg::OnBrowse( WORD, WORD, HWND, BOOL& )
{
	CFolderDialog dlg( *this, NULL, BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE );
	if( dlg.DoModal() == IDOK )
		SetDlgItemText( IDC_PATH, dlg.m_szFolderPath );

	return 0;
}


UINT COptDlg::GetTabWidth()
{
	return m_uTabWidth;
}


void COptDlg::GetLogFont( LOGFONT* pLogFont )
{
	m_font.GetLogFont( pLogFont );
}


LPCTSTR COptDlg::GetScriptPath()
{
	return m_szPath;
}


bool COptDlg::GetViewNaviBar()
{
	return m_bViewNaviBar;
}
