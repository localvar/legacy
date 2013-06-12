// MRegretDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winwq.h"
#include "MRegretDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMRegretDlg dialog


CMRegretDlg::CMRegretDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMRegretDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMRegretDlg)
	m_nToHand = 0;
	//}}AFX_DATA_INIT
}


void CMRegretDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMRegretDlg)
	DDX_Text(pDX, IDC_EDIT_HAND, m_nToHand);
	DDV_MinMaxInt(pDX, m_nToHand, 0, m_nMaxHand);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMRegretDlg, CDialog)
	//{{AFX_MSG_MAP(CMRegretDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMRegretDlg message handlers

BOOL CMRegretDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString abc;
	abc.Format("这一盘棋共有%d手",m_nMaxHand);
	GetDlgItem(IDC_TOTAL_IN_GAME)->SetWindowText(abc);
	abc.Format("当前是第%d手",m_nCurrentHand);
	GetDlgItem(IDC_CURRENT_IN_GAME)->SetWindowText(abc);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN1))->SetRange(0,m_nMaxHand);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
