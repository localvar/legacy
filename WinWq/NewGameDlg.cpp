// NewGameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinWq.h"
#include "NewGameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewGameDlg dialog


CNewGameDlg::CNewGameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewGameDlg::IDD, pParent)
{
	CWinApp* pApp=AfxGetApp();
	m_GameTime = CTime::GetCurrentTime();
	m_nYear=m_GameTime.GetYear();
	m_nMonth=m_GameTime.GetMonth();
	m_nDay=m_GameTime.GetDay();

	//{{AFX_DATA_INIT(CNewGameDlg)
	m_GameName = pApp->GetProfileString("Settings","GameName","春兰杯");
	m_WhiteName = pApp->GetProfileString("Settings","WhiteName","李昌镐");
	m_BlackName = pApp->GetProfileString("Settings","BlackName","ZBM");
	m_nBlackDegree = pApp->GetProfileInt("Settings","BlackDegree",0);
	m_nWhiteDegree = pApp->GetProfileInt("Settings","WhiteDegree",0);
	m_nBlackPrePut = pApp->GetProfileInt("Settings","BlackPrePut",0);
	m_nPlayMode = pApp->GetProfileInt("Settings","PlayMode",0);
	//}}AFX_DATA_INIT
	char *degree[]={
		"无",
		"业余初段",	"业余二段",	"业余三段",
		"业余四段",	"业余五段",	"业余六段",
		"初段",	"二段",	"三段",	"四段",	"五段",
		"六段",	"七段",	"八段",	"九段"
	};
	if(m_nBlackDegree<0||m_nBlackDegree>15)
		m_nBlackDegree=0;
	if(m_nWhiteDegree<0||m_nWhiteDegree>15)
		m_nWhiteDegree=0;
	m_BlackDegree=degree[m_nBlackDegree];
	m_WhiteDegree=degree[m_nWhiteDegree];
}


void CNewGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewGameDlg)
	DDX_CBString(pDX, IDC_GAME_NAME, m_GameName);
	DDX_DateTimeCtrl(pDX, IDC_GAMEDATE, m_GameTime);
	DDX_CBString(pDX, IDC_WHITE_NAME, m_WhiteName);
	DDX_CBString(pDX, IDC_BLACK_NAME, m_BlackName);
	DDX_CBIndex(pDX, IDC_BLACK_DEGREE, m_nBlackDegree);
	DDX_CBIndex(pDX, IDC_WHITE_DEGREE, m_nWhiteDegree);
	DDX_CBIndex(pDX, IDC_BLACK_PREPUT, m_nBlackPrePut);
	DDX_Radio(pDX, IDC_FREE, m_nPlayMode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewGameDlg, CDialog)
	//{{AFX_MSG_MAP(CNewGameDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewGameDlg message handlers

void CNewGameDlg::OnOK() 
{
	if(!UpdateData()) return;

	CWinApp* pApp=AfxGetApp();
	pApp->WriteProfileString("Settings","GameName",m_GameName);
	pApp->WriteProfileString("Settings","WhiteName",m_WhiteName);
	pApp->WriteProfileString("Settings","BlackName",m_BlackName);
	pApp->WriteProfileInt("Settings","BlackDegree",m_nBlackDegree);
	pApp->WriteProfileInt("Settings","WhiteDegree",m_nWhiteDegree);
	pApp->WriteProfileInt("Settings","BlackPrePut",m_nBlackPrePut);
	pApp->WriteProfileInt("Settings","PlayMode",m_nPlayMode);
	
	m_nYear=m_GameTime.GetYear();
	m_nMonth=m_GameTime.GetMonth();
	m_nDay=m_GameTime.GetDay();
	((CComboBox*)GetDlgItem(IDC_WHITE_DEGREE))->GetLBText(m_nWhiteDegree,m_WhiteDegree);
	((CComboBox*)GetDlgItem(IDC_BLACK_DEGREE))->GetLBText(m_nBlackDegree,m_BlackDegree);

	CDialog::OnOK();
}

BOOL CNewGameDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int panes=AfxGetApp()->GetProfileInt("Settings","BoardPanes",19);	
	if(panes!=19)
		GetDlgItem(IDC_BLACK_PREPUT)->ShowWindow(SW_HIDE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
