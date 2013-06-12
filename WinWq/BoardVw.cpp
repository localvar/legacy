// BoardVw.cpp : implementation of the CBoardView class
//

#include "stdafx.h"
#include "WinWq.h"

#include "CBoard.h"
#include "BoardVw.h"
#include "MRegretDlg.h"
#include "SetDlg.h"
#include "AttribDlg.h"

#include <mmsystem.h>
//#include <dsound.h>
#include "DirectSound.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBoardView

CDirectSound SoundEffect;

IMPLEMENT_DYNCREATE(CBoardView, CView)

BEGIN_MESSAGE_MAP(CBoardView, CView)
	//{{AFX_MSG_MAP(CBoardView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PUT_BLACK, OnPutBlack)
	ON_COMMAND(ID_PUT_WHITE, OnPutWhite)
	ON_COMMAND(ID_SHOW_ORDER, OnShowOrder)
	ON_COMMAND(ID_EDIT_REGRET, OnEditRegret)
	ON_COMMAND(ID_EDIT_INVERT, OnEditInvert)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_COMMAND(ID_EDIT_REPUT, OnEditReput)
	ON_WM_SETCURSOR()
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_INVERT, OnUpdateEditInvert)
	ON_UPDATE_COMMAND_UI(ID_PUT_WHITE, OnUpdatePutWhite)
	ON_UPDATE_COMMAND_UI(ID_PUT_BLACK, OnUpdatePutBlack)
	ON_COMMAND(ID_GIVE_IN, OnGiveIn)
	ON_COMMAND(ID_EDIT_REGRET_MORE, OnEditRegretMore)
	ON_COMMAND(ID_EDIT_LOST, OnEditLost)
	ON_COMMAND(ID_FIND_PIECE, OnFindPiece)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_OPTION_SETTINGS, OnOptionSettings)
	ON_UPDATE_COMMAND_UI(ID_GIVE_IN, OnUpdateGiveIn)
	ON_UPDATE_COMMAND_UI(ID_EDIT_LOST, OnUpdateEditLost)
	ON_COMMAND(ID_GUESS, OnGuess)
	ON_COMMAND(ID_OPTION_SOUND, OnOptionSound)
	ON_UPDATE_COMMAND_UI(ID_OPTION_SOUND, OnUpdateOptionSound)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REGRET, OnUpdateEditRegret)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REGRET_MORE, OnUpdateEditRegretMore)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REPUT, OnUpdateEditReput)
	ON_COMMAND(ID_AUTO_REPLAY, OnAutoReplay)
	ON_UPDATE_COMMAND_UI(ID_AUTO_REPLAY, OnUpdateAutoReplay)
	ON_UPDATE_COMMAND_UI(ID_GUESS, OnUpdateGuess)
	ON_COMMAND(ID_REPLAY, OnReplay)
	ON_UPDATE_COMMAND_UI(ID_REPLAY, OnUpdateReplay)
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_CANCEL, OnCancel)
	ON_COMMAND(ID_CONVERT, OnConvert)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_MESSAGE(WM_USER+200,OnCaretShow)
	ON_MESSAGE(WM_USER+201,OnRegretToStart)
	ON_MESSAGE(WM_USER+202,OnReputToEnd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoardView construction/destruction

CBoardView::CBoardView()
{
	// TODO: add construction code here
}

CBoardView::~CBoardView()
{
	AfxGetApp()->WriteProfileInt("Settings","Sound",SoundEffect.IsSoundEnable());
}

BOOL CBoardView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBoardView drawing

void CBoardView::OnDraw(CDC* pDC)
{
	CBoard* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	m_caret.Hide();
	
	CRect rtBoard,rtPiece;
	
	//get the board rectangle need to redraw
	pDC->GetClipBox(&rtBoard);
	
	//calculate the piece rectangle need to redraw
	//NOTE:the following lines need to rewrite
	rtPiece=rtBoard;

	rtPiece.left=(rtPiece.left-m_nMin)/m_nStepLen+1;
	rtPiece.top=(rtPiece.top-m_nMin)/m_nStepLen+1;
	rtPiece.right=(rtPiece.right-m_nMin)/m_nStepLen+1;
	rtPiece.bottom=(rtPiece.bottom-m_nMin)/m_nStepLen+1;

	if(rtPiece.left<1) rtPiece.left=1;
	if(rtPiece.top<1) rtPiece.top=1;
	int nPanes=pDoc->GetPanes();
	if(rtPiece.right>nPanes) rtPiece.right=nPanes;
	if(rtPiece.bottom>nPanes) rtPiece.bottom=nPanes;

	pDoc->DrawBoard(pDC,rtBoard,rtPiece);
	
	m_caret.Show();
}

/////////////////////////////////////////////////////////////////////////////
// CBoardView printing

BOOL CBoardView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBoardView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBoardView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBoardView diagnostics

#ifdef _DEBUG
void CBoardView::AssertValid() const
{
	CView::AssertValid();
}

void CBoardView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBoard* CBoardView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBoard)));
	return (CBoard*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBoardView message handlers

int CBoardView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_hBlack=AfxGetApp()->LoadCursor(IDC_BLACK);
	m_hWhite=AfxGetApp()->LoadCursor(IDC_WHITE);

	if(SoundEffect.Create(this))
	{
		BOOL bSound=AfxGetApp()->GetProfileInt("Settings","Sound",1);		
		SoundEffect.EnableSound(bSound);
	}
	else
	{
		CString msg;
		CString title;
		title.LoadString(AFX_IDS_APP_TITLE);
		msg.LoadString(IDS_NO_DIRECTSOUND);
		MessageBox(msg,title);
	}
	
	m_caret.Create(this);

	return 0;
}

void CBoardView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//没有点在棋盘之内
	if(point.x>=m_nMax||point.x<m_nMin||point.y>=m_nMax||point.y<m_nMin)
	{
		CView::OnLButtonDown(nFlags,point);
		return;
	}

	int row,col;
	row = (( point.x - m_nMin ) / m_nStepLen ) + 1;
	col = (( point.y - m_nMin ) / m_nStepLen ) + 1;
	
	PLAYMODE pm=GetDocument()->GetPlayMode();
	
	if(pm<REPLAY)
		PutPiece(row,col);
	else if(pm<GUESS)
		OnEditReput();
	else
		Guess(row,col);

	CView::OnLButtonDown(nFlags,point);
}

void CBoardView::OnTimer(UINT nIDEvent) 
{
	if(GetDocument()->GetPlayMode()!=AUTOREPLAY)
		KillTimer(nIDEvent);
	else
		OnEditReput();
	CView::OnTimer(nIDEvent);
}

void CBoardView::OnDestroy() 
{
	CView::OnDestroy();
	if(GetDocument()->GetPlayMode()==AUTOREPLAY)
		KillTimer(2);
}

BOOL CBoardView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	CBoard* pDoc = GetDocument();
	if(pDoc->GetColor()==1)
		SetCursor(m_hBlack);
	else
		SetCursor(m_hWhite);
	return true;
}

void CBoardView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CPoint point;
	CBoard* pDoc=GetDocument();
	POSITION pos;

	switch(nChar)
	{
	case VK_LEFT:
	case VK_RIGHT:
	case VK_UP:
	case VK_DOWN:
		m_caret.Hide();
		m_caret.Move(nChar);
		m_caret.Show();
		point=CPtoBP(m_caret.GetCaretPos());
		pDoc->UpdateAllViews(this,2,(CObject*)&point);
		break;
	case VK_SPACE:
		point=m_caret.GetCaretPos();
		PostMessage(WM_LBUTTONDOWN,MK_LBUTTON,MAKELONG(point.x,point.y));
		break;
	case VK_RETURN:
		pos =pDoc->GetFirstViewPosition();
		pDoc->GetNextView(pos);
		((CFrameWnd*)AfxGetMainWnd())->SetActiveView(pDoc->GetNextView(pos));
		break;
	case 'B':
	case 'b':
		PostMessage(WM_COMMAND,ID_PUT_BLACK);
		break;
	case 'W':
	case 'w':
		PostMessage(WM_COMMAND,ID_PUT_WHITE);
		break;
	case VK_BACK:
		PostMessage(WM_COMMAND,ID_EDIT_REGRET);
		break;
	case 'i':
	case 'I':
		PostMessage(WM_COMMAND,ID_EDIT_INVERT);
		break;
	case 'p':
	case 'P'://弃权
		PostMessage(WM_COMMAND,ID_GIVE_IN);
		break;
	case 'a':
	case 'A':
		PostMessage(WM_COMMAND,ID_EDIT_REPUT);
		break;
	}	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

CPoint CBoardView::CPtoBP(CPoint ptSource)
{
	CPoint point;
	point.x=(ptSource.x-m_nMin)/m_nStepLen+1;
	point.y=(ptSource.y-m_nMin)/m_nStepLen+1;
	return point;
}

CPoint CBoardView::BPtoCP(CPoint ptSource)
{
	CPoint point;
	point.x=(ptSource.x-1)*m_nStepLen+m_nMin+m_nStepLen/2;
	point.y=(ptSource.y-1)*m_nStepLen+m_nMin+m_nStepLen/2;
	return point;
}

void CBoardView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	BOOL bMenu=AfxGetApp()->GetProfileInt("Settings","ContextMenu",1);
	if(!bMenu)
	{
		DefWindowProc(WM_CONTEXTMENU,(WPARAM)pWnd->m_hWnd,MAKELONG(point.x,point.y));
		return;
	}
	CBoard* pDoc=GetDocument();
	PIECEINFO* pi;
	CPoint pt=CPtoBP(m_caret.GetCaretPos());
	pi=pDoc->GetPiece(pt.x,pt.y);
	int pm=pDoc->GetPlayMode();

	bool bCanRegret=pDoc->CanRegret();
	bool bCanReput=pDoc->CanReput();
	BOOL bOver=pDoc->IsGameOver();

	CMenu menu,*pMenu;
	menu.LoadMenu(IDR_BWMENU);
	pMenu=menu.GetSubMenu(0);
	pMenu->EnableMenuItem(ID_EDIT_REGRET,bCanRegret?MF_ENABLED:MF_GRAYED);
	pMenu->EnableMenuItem(ID_EDIT_REPUT,bCanReput?MF_ENABLED:MF_GRAYED);
	pMenu->EnableMenuItem(ID_EDIT_REGRET_MORE,(bCanReput||bCanRegret)?MF_ENABLED:MF_GRAYED);
	pMenu->EnableMenuItem(ID_PUT_BLACK,pm==NORMAL&&pi->m_nColor==0&&!bOver?MF_ENABLED:MF_GRAYED);
	pMenu->EnableMenuItem(ID_PUT_WHITE,pm==NORMAL&&pi->m_nColor==0&&!bOver?MF_ENABLED:MF_GRAYED);
	pMenu->EnableMenuItem(ID_EDIT_INVERT,pm==NORMAL&&pi->m_nColor&&!bOver?MF_ENABLED:MF_GRAYED);
	pMenu->EnableMenuItem(ID_EDIT_DELETE,pm==NORMAL&&pi->m_nColor&&!bOver?MF_ENABLED:MF_GRAYED);
	pMenu->EnableMenuItem(ID_EDIT_LOST,pm<REPLAY&&!bOver?MF_ENABLED:MF_GRAYED);
	pMenu->EnableMenuItem(ID_GIVE_IN,pm<REPLAY&&!bOver?MF_ENABLED:MF_GRAYED);
	pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,pWnd);
}

void CBoardView::OnPutBlack() 
{
	CBoard* pDoc=GetDocument();
	CPoint point=CPtoBP(m_caret.GetCaretPos());
	CClientDC dc(this);
	m_caret.Hide();
	switch(pDoc->PutColor(point.x,point.y,1,&dc))
	{
	case 0://play sound
		SoundEffect.Play(PUTPIECE);
		pDoc->UpdateAllViews(this,1,(CObject*)&point);
		break;
	case 1:
		//play sound
		break;
	case 2:
		SoundEffect.Play(INVALIDE);
		break;
	case 3:
		SoundEffect.Play(DAJIE);
		break;
	}
	m_caret.Show();
}

void CBoardView::OnPutWhite() 
{
	CBoard* pDoc=GetDocument();
	CPoint point=CPtoBP(m_caret.GetCaretPos());
	CClientDC dc(this);
	m_caret.Hide();
	switch(pDoc->PutColor(point.x,point.y,2,&dc))
	{
	case 0:
		SoundEffect.Play(PUTPIECE);
		pDoc->UpdateAllViews(this,1,(CObject*)&point);
		break;
	case 1:
		break;
	case 2:
		SoundEffect.Play(INVALIDE);
		break;
	case 3:
		SoundEffect.Play(DAJIE);
		break;
	}
	m_caret.Show();
}

void CBoardView::OnCancel() 
{
;//this function does nothing 
//only to destroy the contextmenu
}

//NOTE: the update cmdui function is in CBoard
void CBoardView::OnShowOrder() 
{
	CClientDC dc(this);
	m_caret.Hide();
	GetDocument()->ShowOrder(&dc);
	m_caret.Show();
}

void CBoardView::OnEditRegret() 
{
	CBoard* pDoc=GetDocument();
	ASSERT(pDoc->CanRegret());
	CClientDC dc(this);
	m_caret.Hide();
	if(pDoc->Regret(&dc)!=-1)
	{
		CPoint p=pDoc->GetLastPiecePos();
		CPoint point=BPtoCP(p);
		m_caret.MoveTo(point.x,point.y);
		pDoc->UpdateAllViews(this,1,(CObject*)&p);
	}
	m_caret.Show();
}

void CBoardView::OnEditInvert() 
{
	CBoard* pDoc=GetDocument();
	CPoint point=CPtoBP(m_caret.GetCaretPos());
	CClientDC dc(this);
	m_caret.Hide();
	if(pDoc->InvertColor(point.x,point.y,&dc))
		SoundEffect.Play(CHANGECOLOR);
	m_caret.Show();
	pDoc->UpdateAllViews(this,1,(CObject*)&point);
}

void CBoardView::OnEditDelete() 
{
	CBoard* pDoc=GetDocument();
	CPoint point=CPtoBP(m_caret.GetCaretPos());
	CClientDC dc(this);
	m_caret.Hide();
	pDoc->Delete(point.x,point.y,&dc);
	SoundEffect.Play(DELETEPIECE);
	m_caret.Show();
	pDoc->UpdateAllViews(this,1,(CObject*)&point);
}

void CBoardView::OnEditReput() 
{
	CBoard* pDoc=GetDocument();
	CClientDC dc(this);
	m_caret.Hide();
	switch(pDoc->Reput(&dc))
	{
	case 0://弃权
		if(pDoc->GetColor()==1)
			SoundEffect.Play(BLACKNONUSER);
		else
			SoundEffect.Play(WHITENONUSER);
		break;
	case 1:
	case 2:
		SoundEffect.Play(PUTPIECE);
		break;
	case 3:
		SoundEffect.Play(DELETEPIECE);
		break;
	case 4:
		SoundEffect.Play(CHANGECOLOR);
		break;
	case 5:
		if(pDoc->GetColor()==1)
			SoundEffect.Play(WHITEINVALIDE);
		else
			SoundEffect.Play(BLACKINVALIDE);
		break;
	case -1://不能重下
		SoundEffect.Play(CONGRATULATIONS);
		if(pDoc->GetPlayMode()==AUTOREPLAY)
		{
			KillTimer(2);
			pDoc->SetPlayMode(REPLAY);
		}
		MessageBox("棋谱结束了,祝贺您又打完了一局棋谱!","名局赏析");
		break;
	}
	CPoint p=pDoc->GetLastPiecePos();
	CPoint pt=BPtoCP(p);
	m_caret.MoveTo(pt.x,pt.y);
	pDoc->UpdateAllViews(this,1,(CObject*)&p);
	m_caret.Show();
}

void CBoardView::OnGiveIn() 
{
	CBoard* pDoc=GetDocument();
	GAMEINFO* gi=pDoc->GetGameInfo();
	int color=pDoc->GetColor();
	CString msg=(color==1?gi->BlackName:gi->WhiteName)
		+",您真的要放弃下这一手吗?";
	CString title;
	title.LoadString(AFX_IDS_APP_TITLE);
	SoundEffect.Play(REALYNONUSER);
	if(MessageBox(msg,title,MB_ICONQUESTION|MB_YESNO)==IDNO)
		return;
	if(pDoc->GiveIn()) //如果连续弃权两手
	{
		pDoc->EndGame();
	}
	else
	{
		CPoint point=CPtoBP(m_caret.GetCaretPos());
		pDoc->UpdateAllViews(this,1,(CObject*)&point);
	}
}

LRESULT CBoardView::OnCaretShow(WPARAM wParam,LPARAM lParam)
{
	CBoard* pDoc=GetDocument();
	CPoint pt=CPtoBP(m_caret.GetCaretPos());
	PIECEINFO* p=pDoc->GetPiece(pt.x,pt.y);
	CString dis;
	if(p->m_nColor)
		dis.Format("%d行,%d列 %s第%d手",pt.y,pt.x,p->m_nColor==1?"黑方:":"白方:",p->m_nSerNum);
	else
		dis.Format("%d行,%d列",pt.y,pt.x);
	CStatusBar* pStatus=(CStatusBar*)(AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR));
	pStatus->SetPaneText(1,dis);
	return true;
}

LRESULT CBoardView::OnRegretToStart(WPARAM wParam,LPARAM lParam)
{
	CBoard* pDoc=GetDocument();
	//计算要悔多少手棋
	int nCount=pDoc->GetSerNum()-1;
	CClientDC dc(this);
	m_caret.Hide();
	for(int i=0;i<nCount;i++)
		pDoc->Regret(&dc);
	CPoint point=pDoc->GetLastPiecePos();
	CPoint pt=BPtoCP(point);
	m_caret.MoveTo(pt.x,pt.y);
	m_caret.Show();
	pDoc->UpdateAllViews(this,1,(CObject*)&point);
	return true;
}

LRESULT CBoardView::OnReputToEnd(WPARAM wParam,LPARAM lParam)
{
	CBoard* pDoc=GetDocument();
	//计算要重下多少手
	int nCount=pDoc->GetTotalHand()-pDoc->GetSerNum()+1;
	CClientDC dc(this);
	m_caret.Hide();
	for(int i=0;i<nCount;i++)
		pDoc->Reput(&dc);
	CPoint point=pDoc->GetLastPiecePos();
	CPoint pt=BPtoCP(point);
	m_caret.MoveTo(pt.x,pt.y);
	m_caret.Show();
	pDoc->UpdateAllViews(this,1,(CObject*)&point);
	return true;
}

void CBoardView::OnEditRegretMore() 
{
	CBoard* pDoc=GetDocument();
	CMRegretDlg dlg;
	dlg.m_nMaxHand=pDoc->GetTotalHand();
	int nCount=pDoc->GetSerNum()-1;
	int i;
	dlg.m_nCurrentHand=nCount;
	if(dlg.DoModal()!=IDOK) return;
	CClientDC dc(this);
	m_caret.Hide();
	nCount=dlg.m_nToHand-nCount;
	//if nCount>0 then reput otherwise regret
	if(nCount>0)
	{
		for(i=0;i<nCount;i++)
			pDoc->Reput(&dc);
	}
	else
	{
		for(i=0;i<-nCount;i++)
			pDoc->Regret(&dc);
	}
	CPoint point=pDoc->GetLastPiecePos();
	CPoint pt=BPtoCP(point);
	m_caret.MoveTo(pt.x,pt.y);
	m_caret.Show();
	pDoc->UpdateAllViews(this,1,(CObject*)&point);
}

void CBoardView::OnEditLost() 
{
	CBoard* pDoc=GetDocument();
	GAMEINFO* gi=pDoc->GetGameInfo();
	int color=pDoc->GetColor();
	CString msg=(color==1?gi->BlackName:gi->WhiteName)+",您确实要认输吗?";
	CString title;
	title.LoadString(AFX_IDS_APP_TITLE);
	SoundEffect.Play(REALYGIVEUP);
	if(MessageBox(msg,title,MB_ICONQUESTION|MB_YESNO)==IDNO)
		return;
	pDoc->EndGame(color==1?2:1);
}

void CBoardView::OnFindPiece() 
{
	CBoard* pDoc=GetDocument();
	CFindPieceDlg dlg;
	dlg.nMaxHand=pDoc->GetSerNum()-1;
	if(dlg.nMaxHand<1||dlg.DoModal()!=IDOK) return;
	CPoint pt;
	//bFind indicates whether the piece was killed
	bool bFind=pDoc->FindPiece(dlg.m_nPieceToFind,pt);
	pDoc->UpdateAllViews(this,2,(CObject*)&pt);
	m_caret.Hide();
	pt=BPtoCP(pt);
	m_caret.MoveTo(pt.x,pt.y);
	m_caret.Show();
	if(!bFind)
	{
		CString msg;
		msg.Format("光标已经移到了第%d手棋的位置,但这手棋已经被拔掉了.",dlg.m_nPieceToFind);
		MessageBox(msg,"查找结果",MB_ICONINFORMATION|MB_OK);
	}
}

void CBoardView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if(point.x>=m_nMax||point.x<m_nMin||point.y>=m_nMax||point.y<m_nMin)
	{
		CView::OnLButtonDown(nFlags,point);
		return;
	}

	int row,col;
	row = (( point.x - m_nMin ) / m_nStepLen ) + 1;
	col = (( point.y - m_nMin ) / m_nStepLen ) + 1;
	CPoint p(row,col);
	GetDocument()->UpdateAllViews(this,2,(CObject*)&p);
	p=BPtoCP(p);
	
	m_caret.Hide();
	m_caret.MoveTo(p.x,p.y);
	m_caret.Show();

	CPoint pt=CPtoBP(point);
	
	CView::OnRButtonDown(nFlags, point);
}

void CBoardView::OnOptionSettings() 
{
	CSetDlg dlg;
	dlg.DoModal();
	CPoint pt=CPtoBP(m_caret.GetCaretPos());
	GetDocument()->UpdateAllViews(this,2,(CObject*)&pt);
}

void CBoardView::OnOptionSound() 
{
	SoundEffect.EnableSound(!SoundEffect.IsSoundEnable());
}

//CMDUI update functions
void CBoardView::OnUpdateOptionSound(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(SoundEffect.IsSoundEnable());	
}

void CBoardView::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	CBoard* pDoc=GetDocument();
	PIECEINFO* pi;
	CPoint pt=CPtoBP(m_caret.GetCaretPos());
	pi=pDoc->GetPiece(pt.x,pt.y);
	pCmdUI->Enable(pDoc->GetPlayMode()==NORMAL&&pi->m_nColor
		&&!pDoc->IsGameOver());	
}

void CBoardView::OnUpdateEditInvert(CCmdUI* pCmdUI) 
{
	CBoard* pDoc=GetDocument();
	PIECEINFO* pi;
	CPoint pt=CPtoBP(m_caret.GetCaretPos());
	pi=pDoc->GetPiece(pt.x,pt.y);
	pCmdUI->Enable(pDoc->GetPlayMode()==NORMAL&&pi->m_nColor
		&&!pDoc->IsGameOver());	
}

void CBoardView::OnUpdatePutWhite(CCmdUI* pCmdUI) 
{
	CBoard* pDoc=GetDocument();
	PIECEINFO* pi;
	CPoint pt=CPtoBP(m_caret.GetCaretPos());
	pi=pDoc->GetPiece(pt.x,pt.y);
	pCmdUI->Enable(pDoc->GetPlayMode()==NORMAL&&pi->m_nColor==0
		&&!pDoc->IsGameOver());	
}

void CBoardView::OnUpdatePutBlack(CCmdUI* pCmdUI) 
{
	CBoard* pDoc=GetDocument();
	PIECEINFO* pi;
	CPoint pt=CPtoBP(m_caret.GetCaretPos());
	pi=pDoc->GetPiece(pt.x,pt.y);
	pCmdUI->Enable(pDoc->GetPlayMode()==NORMAL&&pi->m_nColor==0
		&&!pDoc->IsGameOver());	
}

void CBoardView::OnUpdateGiveIn(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!GetDocument()->IsGameOver());
}

void CBoardView::OnUpdateEditLost(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!GetDocument()->IsGameOver());
}

void CBoardView::OnUpdateEditRegret(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetDocument()->CanRegret());	
}

void CBoardView::OnUpdateEditRegretMore(CCmdUI* pCmdUI) 
{
	CBoard* pDoc=GetDocument();
	pCmdUI->Enable(pDoc->CanRegret()||pDoc->CanReput());	
}

void CBoardView::OnUpdateEditReput(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetDocument()->CanReput());	
}

void CBoardView::OnUpdateAutoReplay(CCmdUI* pCmdUI) 
{
	CBoard* pDoc=GetDocument();
	pCmdUI->Enable(pDoc->GetPlayMode()>=REPLAY);	
	pCmdUI->SetRadio(pDoc->GetPlayMode()==AUTOREPLAY);
}

void CBoardView::OnUpdateGuess(CCmdUI* pCmdUI) 
{
	CBoard* pDoc=GetDocument();
	pCmdUI->Enable(pDoc->GetPlayMode()>=REPLAY);	
	pCmdUI->SetRadio(pDoc->GetPlayMode()==GUESS);
}

void CBoardView::OnUpdateReplay(CCmdUI* pCmdUI) 
{
	CBoard* pDoc=GetDocument();
	pCmdUI->Enable(pDoc->GetPlayMode()>=REPLAY);	
	pCmdUI->SetRadio(pDoc->GetPlayMode()==REPLAY);
}

void CBoardView::OnAutoReplay() 
{
	CBoard* pDoc=GetDocument();
	if(pDoc->SetPlayMode(AUTOREPLAY))
	{
		pDoc->UpdateAllViews(this,3);
		int ti=AfxGetApp()->GetProfileInt("Settings","AutoReplayDelayTime",5);
		SetTimer(2,1000*ti,NULL);
	}
}

void CBoardView::OnReplay() 
{
	CBoard* pDoc=GetDocument();
	if(pDoc->GetPlayMode()==AUTOREPLAY)
		KillTimer(2);
	if(pDoc->SetPlayMode(REPLAY))
		pDoc->UpdateAllViews(this,3);
}

void CBoardView::OnGuess() 
{
	CBoard* pDoc=GetDocument();
	PLAYMODE pm=pDoc->GetPlayMode();
	if(pm==GUESS)	return;
	if(!pDoc->SetPlayMode(GUESS))
		MessageBox("这盘棋手数太少或所剩手数太少","不能猜局");
	else
	{
		if(pm==AUTOREPLAY)	KillTimer(2);
		pDoc->UpdateAllViews(this,3);
	}
}

void CBoardView::OnProperties() 
{
	CBoard* pDoc=GetDocument();
	GAMEINFO* pGi=pDoc->GetGameInfo();
	if(!pDoc->IsGameOver())
		pGi->nTotalHand=pDoc->GetSerNum()-1;
	CPoint pt=CPtoBP(m_caret.GetCaretPos());
	PIECEINFO* pi=pDoc->GetPiece(pt.x,pt.y);
	CAttribDlg dlg;
	dlg.pGi=pGi;
	dlg.pi=pi;
	if(dlg.DoModal()==IDOK&&(pGi->nMiddle!=dlg.m_nMiddle||pGi->nGuanZi!=dlg.m_nGuanZi))
	{
		pGi->nMiddle=dlg.m_nMiddle;
		pGi->nGuanZi=dlg.m_nGuanZi;
		pDoc->SetModifiedFlag();
	}
}

void CBoardView::OnConvert() 
{
	WinExec("conv.exe",SW_SHOWNORMAL);
}

void CBoardView::OnInitialUpdate() 
{
	CBoard* pDoc=GetDocument();
	if(!pDoc->IsGameOver())
		OnReputToEnd((WPARAM)0,(LPARAM)0);
	pDoc->SetModifiedFlag(FALSE);
	//Don't call default because already call OnUpdate(NULL,0,NULL);
}

void CBoardView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CBoard* pDoc=GetDocument();
	int nPanes;
	CPoint point;
	CRect rtBoard;
	
	CClientDC dc(this);

	switch(lHint)
	{
	case 0:
		GetClientRect(&rtBoard);
		nPanes=pDoc->GetPanes();
		
		//calculate the left-top position and step length
		point=rtBoard.CenterPoint();
		m_nStepLen=rtBoard.Width()/(nPanes+2);
		m_nMin=point.x-m_nStepLen*(nPanes/2)-m_nStepLen/2;
		m_nMax=point.x+m_nStepLen*(nPanes/2)+m_nStepLen/2;
		
		pDoc->PrepareBoard(&dc,rtBoard,m_nStepLen);
		pDoc->PreparePiece(&dc,m_nMin,m_nStepLen);
		
		if(m_caret.IsVisible()) m_caret.Hide();
		m_caret.SetStepLen(m_nMax-m_nStepLen/2,m_nMin+m_nStepLen/2,m_nStepLen);
		while(!m_caret.IsVisible()) m_caret.Show();
		Invalidate();
		break;
	default:
		break;
	}
}

void CBoardView::PutPiece(int row, int col)
{
	CString title;
	title.LoadString(AFX_IDS_APP_TITLE);
	CBoard* pDoc=GetDocument();
	PLAYMODE pm=pDoc->GetPlayMode();

	if(pDoc->IsGameOver())
	{
		MessageBox("比赛已经结束,您不能再放子了.移动光标,请用右键",
			title,MB_ICONINFORMATION|MB_OK);
		return;
	}
	
	CClientDC dc(this);

	m_caret.Hide();
	int ret=pDoc->PutPiece(row,col,&dc);
	CPoint pt(row,col);
	CPoint point=BPtoCP(pt);
	m_caret.MoveTo(point.x,point.y);
	m_caret.Show();
	
	switch(ret)
	{
	case 0:	
		//play sound;
		SoundEffect.Play(PUTPIECE);
		PostMessage(WM_SETCURSOR,WPARAM(this->m_hWnd));
		break;
	case 1:
		//play sound
		SoundEffect.Play(INVALIDE);
		if(pm==STANDARD||pm==STANDFAST||(pm==RECORD&&
			MessageBox("这一点没有气,请确认这手棋的正确性?",title,
			MB_ICONQUESTION|MB_YESNO)==IDYES))
			pDoc->PutInvalide(row,col);
		break;
	case 2:
		//play sound
		SoundEffect.Play(DAJIE);
		if(pm==STANDARD||pm==STANDFAST||(pm==RECORD&&
			MessageBox("打劫,请确认这手棋的正确性?",title,
			MB_ICONQUESTION|MB_YESNO)==IDYES))
			pDoc->PutInvalide(row,col);
		break;
	case 3:
		SoundEffect.Play(ALREADYONE);
		if(pm==RECORD)
			MessageBox("这里已经有一枚棋子了.",title,
			MB_ICONINFORMATION|MB_OK);
		break;
	}
	
	pDoc->UpdateAllViews(this,1,(CObject*)&pt);
}

void CBoardView::Guess(int row, int col)
{
	CString title;
	title.LoadString(AFX_IDS_APP_TITLE);
	CClientDC dc(this);
	CPoint pt(row,col);
	CBoard* pDoc=GetDocument();

	m_caret.Hide();

	switch(pDoc->Guess(row,col,&dc))
	{
	case 0:
		SoundEffect.Play(PUTPIECE);
		break;
	case 1://right not put
	case 2://wrong put
		pt=pDoc->GetLastPiecePos();
		SoundEffect.Play(SEEANSWER);
		break;
	case 3:	//wrong not put
		SoundEffect.Play(TRYAGAIN);
		break;
	case 4://game over
		SoundEffect.Play(CONGRATULATIONS);
		MessageBox("猜局结束",title,MB_ICONINFORMATION|MB_OK);
		break;
	}
	
	pDoc->UpdateAllViews(this,1,(CObject*)&pt);
	pt=BPtoCP(pt);
	m_caret.MoveTo(pt.x,pt.y);
	m_caret.Show();	
}
