// EndGameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winwq.h"
#include "EndGameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEndGameDlg dialog


CEndGameDlg::CEndGameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEndGameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEndGameDlg)
	m_BlackTimeUsed = 0;
	m_nGuanZi = 0;
	m_nMiddle = 0;
	m_WhiteTimeUsed = 0;
	m_WinLost = _T("");
	m_MaxHand = _T("");
	//}}AFX_DATA_INIT
}


void CEndGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEndGameDlg)
	DDX_DateTimeCtrl(pDX, IDC_BLACK_TIMEUSED, m_BlackTimeUsed);
	DDX_Text(pDX, IDC_MIDDLEGAME, m_nMiddle);
	DDV_MinMaxInt(pDX, m_nMiddle, 0, nMaxHand);
	DDX_Text(pDX, IDC_GUANZI, m_nGuanZi);
	DDV_MinMaxInt(pDX, m_nGuanZi, m_nMiddle, nMaxHand);
	DDX_DateTimeCtrl(pDX, IDC_WHITE_TIMEUSED, m_WhiteTimeUsed);
	DDX_Text(pDX, IDC_WINLOST, m_WinLost);
	DDX_Text(pDX, IDC_MAXHAND, m_MaxHand);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEndGameDlg, CDialog)
	//{{AFX_MSG_MAP(CEndGameDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEndGameDlg message Secondlers

BOOL CEndGameDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_MaxHand.Format("这盘棋共有%d手",nMaxHand);
	m_nMiddle=nMaxHand/10;
	m_nGuanZi=nMaxHand-m_nMiddle;

	int hour,minute,second;

	hour=m_nBlackSecond/3600;
	minute=(m_nBlackSecond-hour*3600)/60;
	second=m_nBlackSecond%60;
	m_BlackTimeUsed=CTime(2000,1,1,hour,minute,second,1);

	hour=m_nWhiteSecond/3600;
	minute=(m_nWhiteSecond-hour*3600)/60;
	second=m_nWhiteSecond%60;
	m_WhiteTimeUsed=CTime(2000,1,1,hour,minute,second,1);
	
	GetDlgItem(IDC_WINLOST)->EnableWindow(false);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN1))->SetRange(0,nMaxHand);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN2))->SetRange(0,nMaxHand);

	switch(nEndType)
	{
	case 0:	GetDlgItem(IDC_WINLOST)->EnableWindow(true);
		break;
	case 1:m_WinLost="黑中盘胜";
		break;
	case 2:m_WinLost="白中盘胜";
		break;
	case 3:m_WinLost="黑超时负";
		break;
	case 4:m_WinLost="白超时负";
		break;
	}

	if(PlayMode!=RECORD)
	{
		GetDlgItem(IDC_BLACK_TIMEUSED)->EnableWindow(false);
		GetDlgItem(IDC_WHITE_TIMEUSED)->EnableWindow(false);
	}
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEndGameDlg::OnOK() 
{
	if(!UpdateData()) return;
	m_nBlackSecond=m_BlackTimeUsed.GetHour()*3600;
	m_nBlackSecond+=m_BlackTimeUsed.GetMinute()*60;
	m_nBlackSecond+=m_BlackTimeUsed.GetSecond();
	m_nWhiteSecond=m_WhiteTimeUsed.GetHour()*3600;
	m_nWhiteSecond+=m_WhiteTimeUsed.GetMinute()*60;
	m_nWhiteSecond+=m_WhiteTimeUsed.GetSecond();
	CDialog::OnOK();
}

void CEndGameDlg::OnCancel() 
{
	if(nEndType==3||nEndType==4)
	{
		MessageBox("您被超时判负,不能选择取消","比赛结束",MB_ICONERROR|MB_OK);
		return;
	}
	CDialog::OnCancel();
}
