// SetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winwq.h"
#include "SetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetDlg dialog


CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDlg::IDD, pParent)
{
	CWinApp* pApp=AfxGetApp();
	int panes=pApp->GetProfileInt("Settings","BoardPanes",19);
	panes=(panes-9)/2;
	//{{AFX_DATA_INIT(CSetDlg)
	m_nAllowOverTime = pApp->GetProfileInt("Settings","AllowOverTime",10);;
	m_nAllowOverTimeFast = pApp->GetProfileInt("Settings","AllowOverTimeFast",10);
	m_nBoardPanes = panes;
	m_bContextMenu = pApp->GetProfileInt("Settings","ContextMenu",1);
	m_MusicFileName = pApp->GetProfileString("Settings","MusicFileName","");
	m_bGiveAnswer = pApp->GetProfileInt("Settings","GiveAnswer",1);
	m_nAutoReplayDelayTime = pApp->GetProfileInt("Settings","AutoReplayDelayTime",5);
	m_bEditComment = pApp->GetProfileInt("Settings","AllowEditComment",0);
	m_nEntireGameTime = pApp->GetProfileInt("Settings","EntireGameTime",300);
	m_nEntireGameTimeFast = pApp->GetProfileInt("Settings","EntireGameTimeFast",90);
	m_nPrePutNumInGuess = pApp->GetProfileInt("Settings","PreputNumInGuess",5);
	m_nMaxBlock = pApp->GetProfileInt("Settings","MaxBlock",256);
	m_nMaxHand = pApp->GetProfileInt("Settings","MaxHand",360);
	m_nMaxKills = pApp->GetProfileInt("Settings","MaxKills",128);
	//}}AFX_DATA_INIT
}


void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetDlg)
	DDX_Text(pDX, IDC_ALLOW_OVERTIME, m_nAllowOverTime);
	DDV_MinMaxInt(pDX, m_nAllowOverTime, 0, 99);
	DDX_Text(pDX, IDC_ALLOW_OVERTIME_FAST, m_nAllowOverTimeFast);
	DDV_MinMaxInt(pDX, m_nAllowOverTimeFast, 0, 99);
	DDX_CBIndex(pDX, IDC_BOARD_PANES, m_nBoardPanes);
	DDX_Check(pDX, IDC_CONTEXT_MENU, m_bContextMenu);
	DDX_Text(pDX, IDC_MUSIC_FILE_NAME, m_MusicFileName);
	DDX_Radio(pDX, IDC_GIVE_ANSWER, m_bGiveAnswer);
	DDX_Text(pDX, IDC_AUTOREPLAY_DELAY_TIME, m_nAutoReplayDelayTime);
	DDV_MinMaxInt(pDX, m_nAutoReplayDelayTime, 1, 999);
	DDX_Check(pDX, IDC_EDIT_COMMENT, m_bEditComment);
	DDX_Text(pDX, IDC_ENTIRE_GAME_TIME, m_nEntireGameTime);
	DDV_MinMaxInt(pDX, m_nEntireGameTime, 0, 999);
	DDX_Text(pDX, IDC_ENTIRE_GAME_TIME2, m_nEntireGameTimeFast);
	DDV_MinMaxInt(pDX, m_nEntireGameTimeFast, 0, 999);
	DDX_Text(pDX, IDC_PREPUT_NUM_INGUESS, m_nPrePutNumInGuess);
	DDV_MinMaxInt(pDX, m_nPrePutNumInGuess, 0, 99);
	DDX_Text(pDX, IDC_MAXBLOCK, m_nMaxBlock);
	DDX_Text(pDX, IDC_MAXHAND, m_nMaxHand);
	DDX_Text(pDX, IDC_MAXKILLS, m_nMaxKills);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialog)
	//{{AFX_MSG_MAP(CSetDlg)
	ON_BN_CLICKED(IDC_BTN_MUSIC_FILE, OnBtnMusicFile)
	ON_BN_CLICKED(IDC_DEFAULT, OnDefault)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetDlg message handlers

void CSetDlg::OnOK() 
{
	if(!UpdateData()) return;

	if(m_nMaxBlock<30||m_nMaxBlock>360) m_nMaxBlock=256;
	if(m_nMaxBlock<300||m_nMaxBlock>999) m_nMaxBlock=360;
	if(m_nMaxBlock<20||m_nMaxBlock>999) m_nMaxBlock=128;
	
	int panes=m_nBoardPanes*2+9;
	CWinApp* pApp=AfxGetApp();
	pApp->WriteProfileInt("Settings","ContextMenu",m_bContextMenu);
	pApp->WriteProfileInt("Settings","BoardPanes",panes);
	pApp->WriteProfileInt("Settings","GiveAnswer",m_bGiveAnswer);
	pApp->WriteProfileString("Settings","MusicFileName",m_MusicFileName);
	pApp->WriteProfileInt("Settings","AllowOverTime",m_nAllowOverTime);
	pApp->WriteProfileInt("Settings","AllowOverTimeFast",m_nAllowOverTimeFast);
	pApp->WriteProfileInt("Settings","AutoReplayDelayTime",m_nAutoReplayDelayTime);
	pApp->WriteProfileInt("Settings","AllowEditComment",m_bEditComment);
	pApp->WriteProfileInt("Settings","EntireGameTime",m_nEntireGameTime);
	pApp->WriteProfileInt("Settings","EntireGameTimeFast",m_nEntireGameTimeFast);
	pApp->WriteProfileInt("Settings","PreputNumInGuess",m_nPrePutNumInGuess);
	pApp->WriteProfileInt("Settings","MaxBlock",m_nMaxBlock);
	pApp->WriteProfileInt("Settings","MaxHand",m_nMaxHand);
	pApp->WriteProfileInt("Settings","MaxKills",m_nMaxKills);

	CDialog::OnOK();
}

void CSetDlg::OnBtnMusicFile() 
{
	char szTitle[]="选择音乐文件";
	CFileDialog MusicFileDlg(true,"mid", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"音乐文件(*.mid)|*.mid|" ,this);	
	MusicFileDlg.m_ofn.lpstrTitle=szTitle;
	if(MusicFileDlg.DoModal()==IDOK)
	{
		m_MusicFileName=MusicFileDlg.GetPathName();
		GetDlgItem(IDC_MUSIC_FILE_NAME)->SetWindowText(m_MusicFileName);
	}	
}

BOOL CSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN1))->SetRange(0,99);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN2))->SetRange(1,999);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN4))->SetRange(0,99);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN5))->SetRange(0,99);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_ENTIRE_GAME))->SetRange(0,999);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_ENTIRE_GAME2))->SetRange(0,999);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPINMAXHAND))->SetRange(300,999);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPINMAXKILLS))->SetRange(20,999);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPINMAXBLOCK))->SetRange(30,360);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetDlg::OnDefault() 
{
	m_nMaxHand=360;
	m_nMaxKills=128;
	m_nMaxBlock=256;
	SetDlgItemInt(IDC_MAXHAND,360,FALSE);
	SetDlgItemInt(IDC_MAXKILLS,128,FALSE);
	SetDlgItemInt(IDC_MAXBLOCK,256,FALSE);
}
