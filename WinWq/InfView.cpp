// InfView.cpp : implementation file
//

#include "stdafx.h"
#include "WinWq.h"
#include "InfView.h"
#include "CBoard.h"

#include "DirectSound.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfView

extern CDirectSound SoundEffect;

IMPLEMENT_DYNCREATE(CInfView, CFormView)

CInfView::CInfView(): CFormView(CInfView::IDD)
{
	//{{AFX_DATA_INIT(CInfView)
	m_BlackName = _T("");
	m_GameName = _T("");
	m_WhiteName = _T("");
	//}}AFX_DATA_INIT
	m_bHasTimer=false;
}

CInfView::~CInfView()
{
}

void CInfView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfView)
	DDX_Control(pDX, IDC_STAT_LIST, m_StatList);
	DDX_Control(pDX, IDC_WHITE_KILLS, m_WhiteKills);
	DDX_Control(pDX, IDC_BLACK_KILLS, m_BlackKills);
	DDX_Control(pDX, IDC_DISCRIBE, m_Discribe);
	DDX_Text(pDX, IDC_BLACKNAME, m_BlackName);
	DDX_Text(pDX, IDC_GAMENAME, m_GameName);
	DDX_Text(pDX, IDC_WHITENAME, m_WhiteName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInfView, CFormView)
	//{{AFX_MSG_MAP(CInfView)
	ON_EN_KILLFOCUS(IDC_DISCRIBE, OnKillfocusDiscribe)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_PUT_BLACK, OnPutBlack)
	ON_BN_CLICKED(IDC_PUT_WHITE, OnPutWhite)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_INVERT_COLOR, OnInvertColor)
	ON_BN_CLICKED(IDC_REGRET, OnRegret)
	ON_BN_CLICKED(IDC_REPUT, OnReput)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_REGRET_TO_START, OnRegretToStart)
	ON_BN_CLICKED(IDC_REPUT_TO_END, OnReputToEnd)
	ON_BN_CLICKED(IDC_CURRENT_SERNUM, OnCurrentSernum)
	ON_BN_CLICKED(IDC_CURRENT_POSITION, OnCurrentPosition)
	ON_BN_CLICKED(IDC_GIVE_IN, OnGiveIn)
	ON_BN_CLICKED(IDC_GIVE_UP, OnGiveUp)
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(BN_CLICKED,IDC_BLACK_TIME,IDC_WHITE_TIME,OnTimerClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfView diagnostics

#ifdef _DEBUG
void CInfView::AssertValid() const
{
	CFormView::AssertValid();
}

void CInfView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInfView message handlers
void CInfView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CBoard* pDoc=(CBoard*)GetDocument();
	int nPanes;
	CPoint pt;
	switch(lHint)
	{
	case 0://document restart
		NewDocUpdate();
		PlayModeChgUpdate();
		nPanes=pDoc->GetPanes();
		m_nRow=nPanes/2+1;
		m_nCol=m_nRow;
		PutPieceUpdate();
		CaretMoveUpdate();
		break;
	case 1: //put,delete a piece
		PutPieceUpdate();
	case 2:	//caret move
		m_nRow=((CPoint*)pHint)->x;
		m_nCol=((CPoint*)pHint)->y;
		CaretMoveUpdate();
		break;
	case 3://play mode change
		PlayModeChgUpdate();
		PutPieceUpdate();
		break;
	case 4://game over
		PutPieceUpdate();
		if(m_bHasTimer)
		{
			KillTimer(3);
			m_bHasTimer=false;
		}
		GetDlgItem(IDC_GIVE_IN)->EnableWindow(false);
		GetDlgItem(IDC_GIVE_UP)->EnableWindow(false);
		break;
	}
}

void CInfView::OnKillfocusDiscribe() 
{
	CBoard* pDoc=(CBoard*)GetDocument();
	CString abc;
	m_Discribe.GetWindowText(abc);
	pDoc->SetPieceDiscribe(m_nRow,m_nCol,abc);
}

HBRUSH CInfView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	switch(pWnd->GetDlgCtrlID())
	{
	case IDC_GAMENAME:
		pDC->SetTextColor(RGB(255,0,0));
		break;
	case IDC_WHITENAME:
	case IDC_WHITE_KILLS:
		pDC->SetTextColor(RGB(255,255,255));
		break;
	case IDC_WHITE_TIME:
		switch(m_Timer[1].mode)
		{
		case 1:
			pDC->SetTextColor(RGB(255,255,255));
			break;
		case 2:
			pDC->SetTextColor(RGB(255,0,0));
			break;
		case 3:
			pDC->SetTextColor(RGB(0,255,0));
			break;
		case 4:
			pDC->SetTextColor(RGB(0,0,255));
			break;
		}
		break;
	case IDC_BLACK_TIME:
		switch(m_Timer[0].mode)
		{
		case 1:
			pDC->SetTextColor(RGB(0,0,0));
			break;
		case 2:
			pDC->SetTextColor(RGB(255,0,0));
			break;
		case 3:
			pDC->SetTextColor(RGB(0,255,0));
			break;
		case 4:
			pDC->SetTextColor(RGB(0,0,255));
			break;
		}
		break;
	}

	return hbr;
}

void CInfView::OnInitialUpdate() 
{
	//do not call default because already call
	//CFormView::OnInitialUpdate();
}

void CInfView::OnButton1() 
{
	((CFrameWnd*)AfxGetMainWnd())->SetActiveView(m_pBuddy);
}

void CInfView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	if(m_Discribe.IsWindowEnabled()&&bActivate)
		m_Discribe.SetFocus();
	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CInfView::OnPutBlack() 
{
	m_pBuddy->PostMessage(WM_COMMAND,ID_PUT_BLACK);	
}

void CInfView::OnPutWhite() 
{
	m_pBuddy->PostMessage(WM_COMMAND,ID_PUT_WHITE);		
}

void CInfView::OnInvertColor() 
{
	m_pBuddy->PostMessage(WM_COMMAND,ID_EDIT_INVERT);		
}

void CInfView::OnRegret() 
{
	m_pBuddy->PostMessage(WM_COMMAND,ID_EDIT_REGRET);			
}

void CInfView::OnReput() 
{
	m_pBuddy->PostMessage(WM_COMMAND,ID_EDIT_REPUT);			
}

void CInfView::OnDelete() 
{
	m_pBuddy->PostMessage(WM_COMMAND,ID_EDIT_DELETE);				
}

void CInfView::OnRegretToStart() 
{
	m_pBuddy->PostMessage(WM_USER+201);		
}

void CInfView::OnReputToEnd() 
{
	m_pBuddy->PostMessage(WM_USER+202);	
}

void CInfView::OnCurrentSernum() 
{
	m_pBuddy->PostMessage(WM_COMMAND,ID_EDIT_REGRET_MORE);	
}

void CInfView::OnCurrentPosition() 
{
	m_pBuddy->PostMessage(WM_COMMAND,ID_FIND_PIECE);		
}

void CInfView::OnGiveIn() 
{
	m_pBuddy->PostMessage(WM_COMMAND,ID_GIVE_IN);			
}

void CInfView::OnGiveUp() 
{
	m_pBuddy->PostMessage(WM_COMMAND,ID_EDIT_LOST);			
}

void CInfView::CaretMoveUpdate()
{
	CBoard* pDoc=(CBoard*)GetDocument();
	PIECEINFO* pi=pDoc->GetPiece(m_nRow,m_nCol);
	PLAYMODE pm=pDoc->GetPlayMode();

	BOOL bAllowEdit;
	if(pm<REPLAY) bAllowEdit=pi->m_nSerNum>0;
	else if(pm>REPLAY) bAllowEdit=FALSE;
	else bAllowEdit=(pi->m_nSerNum>0)&&
		(AfxGetApp()->GetProfileInt("Settings","AllowEditComment",1));
	
	m_Discribe.SetReadOnly(!bAllowEdit);
	m_Discribe.SetWindowText(pi->m_Discribe);
	GetDlgItem(IDC_PUT_BLACK)->EnableWindow(pi->m_nColor==0&&pm==NORMAL);
	GetDlgItem(IDC_PUT_WHITE)->EnableWindow(pi->m_nColor==0&&pm==NORMAL);
	GetDlgItem(IDC_INVERT_COLOR)->EnableWindow(pi->m_nColor&&pm==NORMAL);
	GetDlgItem(IDC_DELETE)->EnableWindow(pi->m_nColor&&pm==NORMAL);
	CString sn;
	sn.Format("%d",pi->m_nSerNum);
	GetDlgItem(IDC_CURRENT_POSITION)->SetWindowText(sn);
}

void CInfView::PutPieceUpdate()
{
	CBoard* pDoc=(CBoard*)GetDocument();
	PLAYMODE pm=pDoc->GetPlayMode();
	bool crg=pDoc->CanRegret();
	bool crp=pDoc->CanReput();

	GetDlgItem(IDC_REGRET)->EnableWindow(crg);
	GetDlgItem(IDC_REGRET_TO_START)->EnableWindow(crg);
	GetDlgItem(IDC_REPUT)->EnableWindow(crp);
	GetDlgItem(IDC_REPUT_TO_END)->EnableWindow(crp);
	CString sn;
	sn.Format("%d",pDoc->GetSerNum());
	GetDlgItem(IDC_CURRENT_SERNUM)->SetWindowText(sn);
	GetDlgItem(IDC_CURRENT_SERNUM)->EnableWindow(crg||crp);

	int bk,wk;
	pDoc->GetKills(bk,wk);
	sn.Format("%d",bk);
	GetDlgItem(IDC_BLACK_KILLS)->SetWindowText(sn);
	sn.Format("%d",wk);
	GetDlgItem(IDC_WHITE_KILLS)->SetWindowText(sn);

	if(pm==STANDARD||pm==STANDFAST)
	{
		int color=pDoc->GetColor()==1?0:1;
		m_Timer[color].nCurrentHand=0;
		ShowTime(color);
	}
	if(pm==GUESS)
	{
		CString abc;
		int a[5];
		pDoc->GetGuessStat(a);
		for(int i=1;i<4;i++)
		{
			abc.Format("%d",a[i]);
			m_StatList.SetItemText(a[0],i,abc);
		}
		abc.Format("%d%%",a[4]);
		m_StatList.SetItemText(a[0],4,abc);
	}
}

void CInfView::NewDocUpdate()
{
	CBoard* pDoc=(CBoard*)GetDocument();
	GAMEINFO* pGi=pDoc->GetGameInfo();
	
	m_GameName = pGi->GameName;
	
	m_BlackName = pGi->BlackName;
	if(pGi->BlackDegree!="无")
		m_BlackName+=" "+pGi->BlackDegree;
	
	m_WhiteName = pGi->WhiteName;
	if(pGi->WhiteDegree!="无")
		m_WhiteName+=" "+pGi->WhiteDegree;
	
	UpdateData(false);
	//in normal mode and record mode set maxtime to big number
	m_nMaxTime=6000;	
	PLAYMODE pm=pDoc->GetPlayMode();
	if(pm==STANDARD)
	{
		m_nMaxTime=AfxGetApp()->GetProfileInt("Settings","EntireGameTime",300);
		m_nAllowOverTime=AfxGetApp()->GetProfileInt("Settings",
			"AllowOverTime",10);
	}
	else if(pm==STANDFAST)
	{
		m_nMaxTime=AfxGetApp()->GetProfileInt("Settings","EntireGameTimeFast",90);
		m_nAllowOverTime=AfxGetApp()->GetProfileInt("Settings",
			"AllowOverTimeFast",10);
	}
	m_nMaxTime*=60;

	for(int i=0;i<2;i++)
	{
		m_Timer[i].mode=1;
		m_Timer[i].nCurrentHand=0;
		m_Timer[i].nOverFlow=0;
	}
	m_Timer[0].nTotal=pGi->nBlackTimeUsed;
	m_Timer[1].nTotal=pGi->nWhiteTimeUsed;
	ShowTime(0);
	ShowTime(1);
	if(!m_bHasTimer)
	{
		SetTimer(3,1000,NULL);
		m_bHasTimer=true;
	}
}

void CInfView::PlayModeChgUpdate()
{
	CBoard* pDoc=(CBoard*)GetDocument();
	PLAYMODE pm=pDoc->GetPlayMode();
	GetDlgItem(IDC_GIVE_IN)->EnableWindow(!pDoc->IsGameOver());
	GetDlgItem(IDC_GIVE_UP)->EnableWindow(!pDoc->IsGameOver());
	m_StatList.ShowWindow(pm==GUESS?SW_SHOW:SW_HIDE);
	if(pm!=GUESS)
	{
		for(int i=0;i<3;i++)
			for(int j=1;j<5;j++)
				m_StatList.SetItemText(i,j,"");
	}
	if(pm<REPLAY)
	{
		if(!m_bHasTimer)
			SetTimer(3,1000,NULL);
		m_bHasTimer=true;
	}
	else
	{
		if(m_bHasTimer)
			KillTimer(3);
		m_bHasTimer=false;
	}
}

int CInfView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_StatList.Create( LVS_REPORT|LVS_ALIGNLEFT|WS_BORDER|WS_TABSTOP,
		CRect(15,395,244,452),this,IDC_STAT_LIST);

 	m_StatList.InsertColumn(0,"阶段");
 	m_StatList.InsertColumn(1,"总计");
 	m_StatList.InsertColumn(2,"正确");
 	m_StatList.InsertColumn(3,"错误");
 	m_StatList.InsertColumn(4,"正确率");
 	for(int i=0;i<4;i++)
 		m_StatList.SetColumnWidth(i,42);
 	m_StatList.SetColumnWidth(4,58);
 
 	m_StatList.InsertItem(0,"布局"); 
 	m_StatList.InsertItem(1,"中盘");
 	m_StatList.InsertItem(2,"官子");

	CDocument* pDoc=GetDocument();
	POSITION pos = pDoc->GetFirstViewPosition();
	m_pBuddy=(CBoardView*)pDoc->GetNextView( pos );

	return 0;
}

void CInfView::OnDestroy() 
{
	CFormView::OnDestroy();
	if(m_bHasTimer)
	{
		KillTimer(3);
		m_bHasTimer=false;
	}
}

void CInfView::OnTimer(UINT nIDEvent) 
{
	CBoard* pDoc=(CBoard*)GetDocument();
	int color=pDoc->GetColor()-1;
	
	m_Timer[color].nTotal++;
	m_Timer[color].nCurrentHand++;

	if(m_Timer[color].nTotal==m_nMaxTime&&m_Timer[color].mode==2)
		m_Timer[color].mode=1;
	if(m_Timer[color].nTotal>m_nMaxTime)
	{
		SoundEffect.Play(TIMEWARNING);
		if(m_Timer[color].nCurrentHand>30)
		{
			m_Timer[color].nCurrentHand=0;
			m_Timer[color].nOverFlow++;
			if(m_Timer[color].nOverFlow>m_nAllowOverTime)
			{
				KillTimer(3);
				m_bHasTimer=false;
				pDoc->EndGame(color+3);
			}
		}
	}	
	ShowTime(color);	
	CFormView::OnTimer(nIDEvent);
}

void CInfView::OnTimerClick(UINT nID)
{
	int color=nID-IDC_BLACK_TIME;
	CBoard* pDoc=(CBoard*)GetDocument();
	PLAYMODE pm=pDoc->GetPlayMode();
	//比赛模式允许多种计时方式,其他模式只允许全正
	if(pm==STANDARD||pm==STANDFAST)
		m_Timer[color].mode++;
	else
		m_Timer[color].mode=1;
	if(m_Timer[color].mode==5) m_Timer[color].mode=1;
	//如果为全倒,但已超过全局时间,则改为单正
	if(m_Timer[color].mode==2&&m_Timer[color].nTotal>m_nMaxTime)
		m_Timer[color].mode=3;
	//如果为单倒,但还未超过全局时间,则改为全正
	if(m_Timer[color].mode==4&&m_Timer[color].nTotal<m_nMaxTime)
		m_Timer[color].mode=1;
	
	ShowTime(color);	
}

void CInfView::GetUsedTime(int &bt, int &wt)
{
	bt=m_Timer[0].nTotal;
	wt=m_Timer[1].nTotal;
}

void CInfView::ShowTime(int color)
{
	int disp=0;
	switch(m_Timer[color].mode)
	{
	case 1:disp=m_Timer[color].nTotal;break;
	case 2:disp=m_nMaxTime-m_Timer[color].nTotal;break;
	case 3:disp=m_Timer[color].nCurrentHand;break;
	case 4:disp=30-m_Timer[color].nCurrentHand;break;
	}
	
	int hour,minute,second;
	hour=disp/3600;
	minute=(disp-hour*3600)/60;
	second=disp%60;
	CString t;
	t.Format("%02d:%02d:%02d",hour,minute,second);
	GetDlgItem(color?IDC_WHITE_TIME:IDC_BLACK_TIME)->SetWindowText(t);
}


//DEL BOOL CInfView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
//DEL {
//DEL 	if(!CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext))
//DEL 		return FALSE;
//DEL 	
//DEL 	UpdateData(false);
//DEL //	m_BtnRegret.AutoLoad(IDC_REGRET,this);
//DEL 
//DEL //	m_StatList.SubclassDlgItem(IDC_STAT_LIST,this);
//DEL 	m_StatList.InsertColumn(0,"阶段");
//DEL 	m_StatList.InsertColumn(1,"总计");
//DEL 	m_StatList.InsertColumn(2,"正确");
//DEL 	m_StatList.InsertColumn(3,"错误");
//DEL 	m_StatList.InsertColumn(4,"正确率");
//DEL 	for(int i=0;i<4;i++)
//DEL 		m_StatList.SetColumnWidth(i,44);
//DEL 	m_StatList.SetColumnWidth(4,60);
//DEL 
//DEL 	m_StatList.InsertItem(0,"布局"); 
//DEL 	m_StatList.InsertItem(1,"中盘");
//DEL 	m_StatList.InsertItem(2,"官子");
//DEL 
//DEL 
//DEL 	m_tooltip.Create(this,TTS_ALWAYSTIP);
//DEL 	m_tooltip.Activate(TRUE);
//DEL 	
//DEL 	// TODO: Use one of the following forms to add controls:
//DEL 	// m_tooltip.AddTool(GetDlgItem(IDC_<name>), <string-table-id>);
//DEL 	m_tooltip.AddTool(GetDlgItem(IDC_PUT_BLACK), IDC_PUT_BLACK);
//DEL 	m_tooltip.AddTool(GetDlgItem(IDC_PUT_WHITE), IDC_PUT_WHITE);
//DEL 	m_tooltip.AddTool(GetDlgItem(IDC_INVERT_COLOR), ID_EDIT_INVERT);
//DEL 	m_tooltip.AddTool(GetDlgItem(IDC_DELETE), ID_EDIT_DELETE);
//DEL 	m_tooltip.AddTool(GetDlgItem(IDC_CURRENT_POSITION), "当前位置棋子的序号");
//DEL 	//m_tooltip.AddTool(GetDlgItem(IDC_OPEN_CONVERT), "打开文件并转换");
//DEL 	//m_tooltip.AddTool(GetDlgItem(IDC_DECLARE), "作者声明");
//DEL 
//DEL 
//DEL 	SetTimer(3,1000,NULL);	
//DEL 	m_bHasTimer=true;
//DEL 
//DEL 	return TRUE;
//DEL }

//DEL BOOL CInfView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
//DEL {
//DEL 	if(pWnd!=this)
//DEL 		pWnd->SetFocus();
//DEL 
//DEL 	return CFormView::OnSetCursor(pWnd, nHitTest, message);
//DEL }
