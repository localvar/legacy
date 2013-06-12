// FindPieceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winwq.h"
#include "FindPieceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindPieceDlg dialog


CFindPieceDlg::CFindPieceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindPieceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindPieceDlg)
	m_MaxHand = _T("");
	m_nPieceToFind = 1;
	//}}AFX_DATA_INIT
}


void CFindPieceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindPieceDlg)
	DDX_Text(pDX, IDC_MAXHAND, m_MaxHand);
	DDX_Text(pDX, IDC_PIECE_TO_FIND, m_nPieceToFind);
	DDV_MinMaxInt(pDX, m_nPieceToFind, 1, nMaxHand);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindPieceDlg, CDialog)
	//{{AFX_MSG_MAP(CFindPieceDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindPieceDlg message handlers

BOOL CFindPieceDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_MaxHand.Format("这盘棋共有%d手",nMaxHand);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN1))->SetRange(1,nMaxHand);
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
