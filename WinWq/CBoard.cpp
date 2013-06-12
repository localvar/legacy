// CBoard.cpp : implementation of the CBoard class
//

#include "stdafx.h"
#include "WinWq.h"

#include "CBoard.h"
#include "NewGameDlg.h"
#include "BoardVw.h"
#include "InfView.h"
#include "EndGameDlg.h"

#include <mmsystem.h>
#include "DirectSound.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CDirectSound SoundEffect;

void operator <<(CArchive& ar,GAMEINFO& gi)
{
	ar<<gi.GameName;
	ar<<(BYTE)gi.nPlayMode;
	ar<<(WORD)gi.nTotalHand;
	ar<<(BYTE)gi.nDay;
	ar<<(BYTE)gi.nMonth;
	ar<<(WORD)gi.nYear;
	ar<<(BYTE)gi.nPanes;
	ar<<(BYTE)gi.nBlackPrevPut;
	ar<<gi.WinLost;
	ar<<gi.BlackName;
	ar<<gi.BlackDegree;
	ar<<gi.nBlackTimeUsed;
	ar<<gi.WhiteName;
	ar<<gi.WhiteDegree;
	ar<<gi.nWhiteTimeUsed;
	ar<<(WORD)gi.nMiddle;
	ar<<(WORD)gi.nGuanZi;
	ar<<(BYTE)gi.bIsOver;
}

void operator >>(CArchive& ar,GAMEINFO& gi)
{
	WORD a;
	BYTE b;
	ar>>gi.GameName;
	ar>>b;
	gi.nPlayMode=b;
	ar>>a;
	gi.nTotalHand=a;
	ar>>b;
	gi.nDay=b;
	ar>>b;
	gi.nMonth=b;
	ar>>a;
	gi.nYear=a;
	ar>>b;
	gi.nPanes=b;
	ar>>b;
	gi.nBlackPrevPut=b;
	ar>>gi.WinLost;
	ar>>gi.BlackName;
	ar>>gi.BlackDegree;
	ar>>gi.nBlackTimeUsed;
	ar>>gi.WhiteName;
	ar>>gi.WhiteDegree;
	ar>>gi.nWhiteTimeUsed;
	ar>>a;
	gi.nMiddle=a;
	ar>>a;
	gi.nGuanZi=a;
	ar>>b;
	gi.bIsOver=b;
}
/////////////////////////////////////////////////////////////////////////////
// CBoard

IMPLEMENT_DYNCREATE(CBoard, CDocument)

BEGIN_MESSAGE_MAP(CBoard, CDocument)
	//{{AFX_MSG_MAP(CBoard)
	ON_UPDATE_COMMAND_UI(ID_SHOW_ORDER, OnUpdateShowOrder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoard construction/destruction

int CBoard::m_nFirst=-1;

CBoard::CBoard()
{
	CWinApp* pApp=AfxGetApp();
	int temp=pApp->GetProfileInt("Settings","MaxKills",128);
	DelRec.Create(temp);
	temp=pApp->GetProfileInt("Settings","MaxBlock",256);
	ChkRec.Create(temp);
	temp=pApp->GetProfileInt("Settings","MaxHand",360);
	GameRec.Create(temp);

	CPiece::bShowOrder=AfxGetApp()->GetProfileInt("Settings","ShowOrder",1);
	for(int i=1;i<20;i++)
		for(int j=1;j<20;j++)
		{
			piece[i][j].m_nRow=i;
			piece[i][j].m_nCol=j;
		}
}

CBoard::~CBoard()
{
	AfxGetApp()->WriteProfileInt("Settings","ShowOrder",CPiece::bShowOrder);
	CPiece::DestroyPieceBitmap();
	m_BackGround.DeleteObject();	
	TRACE("Delete Board\n");
}

BOOL CBoard::OnNewDocument()
{
	CNewGameDlg newGameDlg;
	//if not just start then display the newgame dialog
	m_nFirst++;
	if(m_nFirst>0&&newGameDlg.DoModal()!=IDOK)
		return FALSE;

	if (!CDocument::OnNewDocument())
		return FALSE;

	CWinApp* pApp=AfxGetApp();
	m_nPanes=pApp->GetProfileInt("Settings","BoardPanes",19);
	if(m_nPanes/2*2==m_nPanes) m_nPanes++;	//m_nPanes must be an odd number
	if(m_nPanes>19) m_nPanes=19;	//the max board size is 19
	if(m_nPanes<9) m_nPanes=9;	//the min board size is 9
	
	GameInfo.bIsOver=FALSE;
	GameInfo.BlackDegree=newGameDlg.m_BlackDegree;
	GameInfo.BlackName=newGameDlg.m_BlackName;
	GameInfo.GameName=newGameDlg.m_GameName;
	GameInfo.nBlackPrevPut=newGameDlg.m_nBlackPrePut;
	GameInfo.nBlackTimeUsed=0;
	GameInfo.nDay=newGameDlg.m_nDay;
	GameInfo.nGuanZi=0;
	GameInfo.nMiddle=0;
	GameInfo.nMonth=newGameDlg.m_nMonth;
	GameInfo.nPanes=m_nPanes;
	GameInfo.nPlayMode=newGameDlg.m_nPlayMode;
	GameInfo.nTotalHand=0;
	GameInfo.nWhiteTimeUsed=0;
	GameInfo.nYear=newGameDlg.m_nYear;
	GameInfo.WhiteDegree=newGameDlg.m_WhiteDegree;
	GameInfo.WhiteName=newGameDlg.m_WhiteName;	
	GameInfo.WinLost.Empty();

	m_nSerNum=1;
	m_nColor=1;
	m_nPlayMode=(PLAYMODE)GameInfo.nPlayMode;

	kills[0]=kills[1]=kills[2]=0;
	
	UpdateAllViews(NULL,0,NULL);
	return TRUE;
}

BOOL CBoard::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	m_nFirst++;
	
	m_nPanes=GameInfo.nPanes;
	m_nSerNum=1;
	m_nColor=1;
	
	if(!IsGameOver())
		m_nPlayMode=(PLAYMODE)GameInfo.nPlayMode;
	else m_nPlayMode=REPLAY;
	
	kills[0]=kills[1]=kills[2]=0;

	UpdateAllViews(NULL,0,NULL);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CBoard serialization

void CBoard::Serialize(CArchive& ar)
{
	DWORD dwSchema=552931;
	if (ar.IsStoring())
	{
		ar<<dwSchema;
		ar<<GameInfo;
	}
	else
	{
		ar>>dwSchema;
		if(dwSchema!=552931)
		{
			//if file format error then set m_nFirst to -1 to indicate
			//OnNewDocument not to display the newgame dialog
			m_nFirst=-1;
			AfxThrowArchiveException(CArchiveException::badIndex);
		}
		ar>>GameInfo;
	}
	GameRec.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CBoard diagnostics

#ifdef _DEBUG
void CBoard::AssertValid() const
{
	CDocument::AssertValid();
}

void CBoard::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBoard commands

void CBoard::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	DelRec.ReInit();
	ChkRec.ReInit();
	GameRec.ReInit();

	CDocument::DeleteContents();
}

void CBoard::PrepareBoard(CDC* pDC,CRect rtBoard,int steplen)
{
	//create board
	//make the background bitmap to fit the client rectangle
	CDC dc1,dc2;
	dc1.CreateCompatibleDC(pDC);
	dc2.CreateCompatibleDC(pDC);

	CBitmap bmp,*pOld1,*pOld2;
	BITMAP bm;
	bmp.LoadBitmap(IDB_BOARD);
	bmp.GetBitmap(&bm);
	m_BackGround.DeleteObject();
	m_BackGround.CreateCompatibleBitmap(pDC,rtBoard.Width(),rtBoard.Height());
	pOld1=dc1.SelectObject(&bmp);
	pOld2=dc2.SelectObject(&m_BackGround);
	dc2.StretchBlt(0,0,rtBoard.Width(),rtBoard.Height(),
		&dc1,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
	
	//draw lines on the background
	dc2.SetROP2(R2_BLACK);
	CPoint center=rtBoard.CenterPoint();
	int start,end;
	start=center.x-steplen*(m_nPanes/2);
	end=center.x+steplen*(m_nPanes/2);
	
	int i;
	for(i=start;i<=end;i+=steplen)
	{
		dc2.MoveTo(i,start);
		dc2.LineTo(i,end);
		dc2.MoveTo(start,i);
		dc2.LineTo(end,i);
	}
	//make the edges bold
	dc2.MoveTo(start-1,start-1);
	dc2.LineTo(start-1,end+1);
	dc2.LineTo(end+1,end+1);
	dc2.LineTo(end+1,start-1);
	dc2.LineTo(start-1,start-1);

	//draw stars
	if(m_nPanes==19)
	{
		for(i=start+3*steplen;i<end;i+=steplen*6)
			for(int j=start+3*steplen;j<end;j+=steplen*6)
				dc2.Ellipse(i-3,j-3,i+4,j+4);
	}
	else	
	{
		int pos=start+m_nPanes/2*steplen;
		dc2.Ellipse(pos-3,pos-3,pos+4,pos+4);
	}
	
	dc1.SelectObject(pOld1);
	dc2.SelectObject(pOld2);
	bmp.DeleteObject();
}

void CBoard::PreparePiece(CDC* pDC,int start,int steplen)
{
	CPiece::DestroyPieceBitmap();
	CPiece::CreatePieceBitmap(pDC,steplen,&m_BackGround);

	start-=steplen;

	int i,j;

	for(i=1;i<=m_nPanes;i++)
		for(j=1;j<=m_nPanes;j++)
		{
			piece[i][j].ClearPiece();
			piece[i][j].SetPos(start+i*steplen,start+j*steplen);
		}
	//make pieces at bounds have a color diffrent from both black and white
	for(i=0;i<m_nPanes+2;i++)
	{
		piece[0][i].m_nColor=100;
		piece[i][0].m_nColor=100;
		piece[m_nPanes+1][i].m_nColor=100;
		piece[i][m_nPanes+1].m_nColor=100;
	}
	//如果是让子棋
	if(m_nPanes==19&&GameInfo.nBlackPrevPut>1)
	{
		BlackPrePut(GameInfo.nBlackPrevPut);
		m_nColor=2;
	}
}

void CBoard::DrawBoard(CDC *pDC, CRect &rectBoard, CRect &rectPiece)
{
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap* pOld;
	pOld=dc.SelectObject(&m_BackGround);
	pDC->BitBlt(rectBoard.left,rectBoard.top,rectBoard.Width(),rectBoard.Height(),
		&dc,rectBoard.left,rectBoard.top,SRCCOPY);
	dc.SelectObject(pOld);

	int i,j;
	for(i=rectPiece.left;i<=rectPiece.right;i++)
		for(j=rectPiece.top;j<=rectPiece.bottom;j++)
			if(piece[i][j].m_nColor)
				piece[i][j].DrawPiece(pDC);
}

int CBoard::PutPiece(int row,int col, CDC *pDC)
{
	int nCanPut;
	//如果不能放子,返回原因
	if((nCanPut=CanHere(row,col))!=0)
		return nCanPut;
	//放子
	piece[row][col].m_nColor=m_nColor;
	piece[row][col].m_nSerNum=m_nSerNum;
	piece[row][col].m_nKills=ChkRec.GetSize();
	piece[row][col].DrawPiece(pDC);
	kills[m_nColor]+=piece[row][col].m_nKills;
	GameRec.Push(piece[row][col]);
	//拔去死子
	PIECEINFO* pi;
	while(pi=ChkRec.Pop())
	{
		DelRec.Push(piece[pi->m_nRow][pi->m_nCol]);
		DelRec.GetTopItem()->m_Discribe=piece[pi->m_nRow][pi->m_nCol].m_Discribe;
		piece[pi->m_nRow][pi->m_nCol].m_bChkFlg=false;
		piece[pi->m_nRow][pi->m_nCol].m_nColor=0;
		piece[pi->m_nRow][pi->m_nCol].m_nSerNum=0;
		piece[pi->m_nRow][pi->m_nCol].m_nKills=0;
		piece[pi->m_nRow][pi->m_nCol].m_Discribe.Empty();
		piece[pi->m_nRow][pi->m_nCol].DrawPiece(pDC);
	}
	m_nSerNum++;	//落子数加一
	m_nColor=m_nColor==1?2:1;	//改变当前颜色
	if(m_nPlayMode<REPLAY)	SetModifiedFlag();
	return 0;
}

//返回0:能放子 1:无气且不能拔子  2:打劫  3:当前位置已有子
int CBoard::CanHere(int row, int col)
{
	int alive,death;                            
	if(piece[row][col].m_nColor) return 3;    //3 表示当前位置已有子
	piece[row][col].m_nColor=m_nColor;
	alive=Alive(row,col);	//首先判断是否有气

	ClrChkFlg(ChkRec.GetBottom());
	death=Death(row,col);	//判断是否能拔子
	piece[row][col].m_nColor=0;
	
	if(alive||death==1) return 0;
	if(death==0) return 1;
	return 2;
}

//返回0:无气  1:有气
int CBoard::Alive(int row, int col)
{
	if(piece[row][col].m_nColor!=m_nColor||piece[row][col].m_bChkFlg)
		return 0;	//如果颜色不同或者已经检查过
	if(!(piece[row-1][col].m_nColor&&piece[row][col-1].m_nColor&&
		piece[row+1][col].m_nColor&&piece[row][col+1].m_nColor))
		return 1;	//如果四周有空白
	piece[row][col].m_bChkFlg=true;	//置检查过标志为真
	ChkRec.Push(piece[row][col]);
	//将此子的信息压入检测纪录
	return(Alive(row-1,col)||Alive(row,col-1)||
		Alive(row+1,col)||Alive(row,col+1));
}

//返回0:不能拔子  1:能拔子  2:打劫
int CBoard::Death(int row, int col)
{
	int cflag[3]={0,0,0};
	m_nColor=m_nColor==1?2:1;
	PIECEINFO* pCur;

	pCur=ChkRec.GetCurrent();
	if(Alive(row-1,col))
	{
		cflag[0]=piece[row][col-1].m_bChkFlg;
		cflag[1]=piece[row+1][col].m_bChkFlg;
		cflag[2]=piece[row][col+1].m_bChkFlg;
		ClrChkFlg(pCur);
	}
	else pCur=ChkRec.GetCurrent();
	
	if(!cflag[0]&&Alive(row,col-1))
	{
		cflag[1]=piece[row+1][col].m_bChkFlg||cflag[1];
		cflag[2]=piece[row][col+1].m_bChkFlg||cflag[2];
		ClrChkFlg(pCur);
	}
	else pCur=ChkRec.GetCurrent();
	
	if(!cflag[1]&&Alive(row+1,col))
	{
		cflag[2]=piece[row][col+1].m_bChkFlg||cflag[2];
		ClrChkFlg(pCur);
	}
	else pCur=ChkRec.GetCurrent();
	
	if(!cflag[2]&&Alive(row,col+1))
		ClrChkFlg(pCur);
	
	m_nColor=m_nColor==1?2:1;
	if(ChkRec.GetSize()==0) return 0;  //不能拔子
	if(ChkRec.GetSize()>1) return 1; //拔子数超过一个
	
	PIECEINFO* pi=ChkRec.GetTopItem();
	//所拔子为上一手,且其拔子数为一个,判为打劫
	if((pi->m_nSerNum==m_nSerNum-1)&&pi->m_nKills==1)
	{
		ClrChkFlg(ChkRec.GetBottom());
		return 2;	//打劫
	}
	return 1;
}

void CBoard::ClrChkFlg(PIECEINFO* pStart)
{
	PIECEINFO* pi;
	while(ChkRec.GetCurrent()>pStart)
	{
		pi=ChkRec.Pop();
		piece[pi->m_nRow][pi->m_nCol].m_bChkFlg=false;
	}
}

void CBoard::SetPieceDiscribe(int row, int col, CString &NewD)
{
	if(piece[row][col].m_Discribe!=NewD)
	{	
		piece[row][col].m_Discribe=NewD;
		GameRec.GetItem(piece[row][col].m_nSerNum)->m_Discribe=NewD;
		SetModifiedFlag();
	}
}

void CBoard::ShowOrder(CDC* pDC)
{
	CPiece::bShowOrder=!CPiece::bShowOrder;
	for(int i=1;i<=m_nPanes;i++)
		for(int j=1;j<=m_nPanes;j++)
			if(piece[i][j].m_nColor)
				piece[i][j].DrawPiece(pDC);
}

///////////////////////////////////////////////////////////////////////
//NOTE: these messages' handler is in CBoardView
void CBoard::OnUpdateShowOrder(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(CPiece::bShowOrder);	
}
///////////////////////////////////////////////////////////////////////

// 处理悔棋
int CBoard::Regret(CDC* pDC)
{
	ASSERT(CanRegret());

	PIECEINFO* pi=GameRec.GetTopItem();
	if(pi==NULL) return -1;
	int ret=pi->m_nColor;
	switch(pi->m_nColor)
	{
	case 0:	//弃权
		GiveIn(true);
		break;
	case 1:
	case 2:
		RegretNormal(pDC);
		break;
	case 3:	//DELETE PIECE
		Delete(pi->m_nRow,pi->m_nCol,pDC,true);
		break;
	case 4:	//INVERT COLOR
		InvertColor(pi->m_nRow,pi->m_nCol,pDC,true);
		break;
	case 5:	//非法着手
		PutInvalide(pi->m_nRow,pi->m_nCol,true);
		break;
	}
	//返回-1表示没有悔棋,其他情况返回所悔棋的颜色
	return ret;
}

//处理重下
int CBoard::Reput(CDC *pDC)
{
	if(GameRec.GetRemain()==0) return -1;

	GameRec.LockLast();	

	PIECEINFO* pi=GameRec.GetCurrent();
	int ret=pi->m_nColor;
	switch(pi->m_nColor)
	{
	case 0:
		GiveIn();
		break;
	case 1:
	case 2:
		m_nColor=pi->m_nColor;
		PutPiece(pi->m_nRow,pi->m_nCol,pDC);
		piece[pi->m_nRow][pi->m_nCol].m_Discribe=pi->m_Discribe;
		break;			
	case 3:
		Delete(pi->m_nRow,pi->m_nCol,pDC);
		break;
	case 4:
		InvertColor(pi->m_nRow,pi->m_nCol,pDC);
		piece[pi->m_nRow][pi->m_nCol].m_Discribe=pi->m_Discribe;
		break;
	case 5:
		PutInvalide(pi->m_nRow,pi->m_nCol);
		break;
	}
	
	GameRec.UnlockLast();
	//return -1 to indicate not reput,otherwise return the piece's color
	return ret;
}

//猜局
//return value 0:right; 1:right not put; 2:wrong put; 3:wrong not put;4:game over
int CBoard::Guess(int row,int col,CDC* pDC)
{
	ASSERT(m_nPlayMode==GUESS);
	if(!GameRec.GetRemain()) return 4;
	PIECEINFO* pi=GameRec.GetCurrent();
	//如果是非正常下法,则给出正确答案	
	if(pi->m_nColor!=1&&pi->m_nColor!=2)
	{
		Reput(pDC);
		return 1;
	}
	int ret;
	if(m_nSerNum>=GameInfo.nMiddle) m_nSection=1;
	if(m_nSerNum>=GameInfo.nGuanZi) m_nSection=2;
	GuessStat[m_nSection].nTotal++;
	if(pi->m_nRow==row&&pi->m_nCol==col)
	{
		GuessStat[m_nSection].nRight++;
		Reput(pDC);
		ret=0;
	}
	else
	{
		GuessStat[m_nSection].nWrong++;	
		BOOL bGiveAnswer=AfxGetApp()->
			GetProfileInt("Settings","GiveAnswer",1);
		if(bGiveAnswer)
		{
			Reput(pDC);
			ret=2;
		}
		else ret=3;
	}
	GuessStat[m_nSection].nPercent=(GuessStat[m_nSection].nRight*100)/GuessStat[m_nSection].nTotal;
	return ret;
}

CPoint CBoard::GetLastPiecePos()
{
	PIECEINFO* pi=GameRec.GetTopItem();
	if(pi!=NULL) return CPoint(pi->m_nRow,pi->m_nCol);
	return CPoint(m_nPanes/2+1,m_nPanes/2+1);
}

void CBoard::Delete(int row, int col, CDC *pDC, bool bRegret)
{
	if(bRegret)	//如果是悔棋
	{
		GameRec.Pop();
		PIECEINFO* pi=DelRec.Pop();
		piece[pi->m_nRow][pi->m_nCol].m_nColor=pi->m_nColor;
		piece[pi->m_nRow][pi->m_nCol].m_nKills=pi->m_nKills;
		piece[pi->m_nRow][pi->m_nCol].m_nSerNum=pi->m_nSerNum;
		piece[pi->m_nRow][pi->m_nCol].m_Discribe=pi->m_Discribe;
		piece[pi->m_nRow][pi->m_nCol].DrawPiece(pDC);
		m_nSerNum--;
	}
	else
	{
		ASSERT(m_nPlayMode!=STANDARD&&m_nPlayMode!=STANDFAST);
		ASSERT(piece[row][col].m_nColor);

		GameRec.Push(row,col,3,m_nSerNum,1);
		DelRec.Push(piece[row][col]);
		DelRec.GetTopItem()->m_Discribe=piece[row][col].m_Discribe;
		piece[row][col].m_nColor=0;
		piece[row][col].m_nKills=0;
		piece[row][col].m_nSerNum=0;
		piece[row][col].m_Discribe.Empty();
		piece[row][col].DrawPiece(pDC);
		m_nSerNum++;
	}	
	if(m_nPlayMode<REPLAY) SetModifiedFlag();
}

bool CBoard::InvertColor(int row, int col, CDC *pDC, bool bRegret)
{
	bool ret=true;

	if(bRegret)
	{
		PIECEINFO* pi=GameRec.Pop();
		piece[row][col].m_nColor=0;
		piece[row][col].DrawPiece(pDC);
		//????
		kills[piece[pi->m_nRow][pi->m_nCol].m_nColor]-=pi->m_nKills;
		int kill=pi->m_nKills;
		for(int i=0;i<=kill;i++) //NOTE: NOT i<kill BUT i<=kill
		{
			pi=DelRec.Pop();
			ASSERT(pi!=NULL);
			piece[pi->m_nRow][pi->m_nCol].m_nColor=pi->m_nColor;
			piece[pi->m_nRow][pi->m_nCol].m_nKills=pi->m_nKills;
			piece[pi->m_nRow][pi->m_nCol].m_nSerNum=pi->m_nSerNum;
			piece[pi->m_nRow][pi->m_nCol].m_Discribe=pi->m_Discribe;
			piece[pi->m_nRow][pi->m_nCol].DrawPiece(pDC);
		}
		m_nSerNum--;
	}
	else
	{
		ASSERT(piece[row][col].m_nColor!=0);
		//first push it into the DelRec
		DelRec.Push(piece[row][col]);
		int color=piece[row][col].m_nColor;
//		int sn=piece[row][col].m_nSerNum;
		int cc=m_nColor;
		m_nColor=color==1?2:1;
		piece[row][col].m_nColor=0;
		//白变黑时有黑边,使用下一行消除
		piece[row][col].DrawPiece(pDC);
		if(PutPiece(row,col,pDC)==0) 
		{
			//在PutPiece中压入的是棋子的本来颜色
			//必须将它的颜色改为"改变颜色"
			int kills=GameRec.Pop()->m_nKills;
			GameRec.Push(row,col,4,m_nSerNum,kills);
			//don't use the next line because in putpiece already do it
			//m_nSerNum++;
		}
		else
		{
			piece[row][col].m_nColor=color;
			piece[row][col].DrawPiece(pDC);
			//if can't InvertColor then pop it
			DelRec.Pop();
			ret=false;
		}
		m_nColor=cc;
	}

	if(m_nPlayMode<REPLAY) SetModifiedFlag();
	
	return ret;
}

void CBoard::PutInvalide(int row, int col, bool bRegret)
{
	if(bRegret)
	{
		GameRec.Pop();
		m_nSerNum--;
		m_nColor=m_nColor==1?2:1;
	}
	else
	{
		GameRec.Push(row,col,5,0);
		m_nSerNum++;
		m_nColor=m_nColor==1?2:1;
	}
	if(m_nPlayMode<REPLAY) SetModifiedFlag();
}

int CBoard::GiveIn(bool bRegret)
{
	if(bRegret)
	{
		GameRec.Pop();
		m_nSerNum--;
		m_nColor=m_nColor==1?2:1;
	}
	else
	{
		if(GameRec.GetSize()&&GameRec.GetTopItem()->m_nColor==0)
			return 1;
		GameRec.Push(1,1,0,0);
		m_nSerNum++;
		m_nColor=m_nColor==1?2:1;
	}
	if(m_nPlayMode<REPLAY) SetModifiedFlag();
	return 0;
}

void CBoard::RegretNormal(CDC *pDC)
{
	PIECEINFO* pi=GameRec.Pop();
	//删去当前子
	piece[pi->m_nRow][pi->m_nCol].m_nColor=0;
	piece[pi->m_nRow][pi->m_nCol].m_nKills=0;
	piece[pi->m_nRow][pi->m_nCol].m_nSerNum=0;
	piece[pi->m_nRow][pi->m_nCol].m_Discribe.Empty();
	piece[pi->m_nRow][pi->m_nCol].DrawPiece(pDC);
	m_nColor=pi->m_nColor;
	kills[m_nColor]-=pi->m_nKills;
	m_nSerNum--;
	//恢复被它拔掉的子
	int kill=pi->m_nKills;
	for(int i=0;i<kill;i++)	//NOTE: HERE IS i<kill
	{
		pi=DelRec.Pop();
		ASSERT(pi!=NULL);
		piece[pi->m_nRow][pi->m_nCol].m_nColor=pi->m_nColor;
		piece[pi->m_nRow][pi->m_nCol].m_nKills=pi->m_nKills;
		piece[pi->m_nRow][pi->m_nCol].m_nSerNum=pi->m_nSerNum;
		piece[pi->m_nRow][pi->m_nCol].m_Discribe=pi->m_Discribe;
		piece[pi->m_nRow][pi->m_nCol].DrawPiece(pDC);
	}
	
	if(m_nPlayMode<REPLAY) SetModifiedFlag();
}

int CBoard::PutColor(int row, int col, int color, CDC *pDC)
{
	ASSERT(m_nPlayMode!=STANDARD&&m_nPlayMode!=STANDFAST);
	int co=m_nColor;
	m_nColor=color;
	int ret=PutPiece(row,col,pDC);
	m_nColor=co;
	if(m_nPlayMode<REPLAY) SetModifiedFlag();
	return ret;
}

int CBoard::GetTotalHand()
{
	return GameRec.GetSize()+GameRec.GetRemain();
}

bool CBoard::EndGame(int mode)
{
	POSITION pos = GetFirstViewPosition();
	GetNextView( pos );
	CInfView* pView=(CInfView*)GetNextView(pos);
	pView->GetUsedTime(GameInfo.nBlackTimeUsed,GameInfo.nWhiteTimeUsed);
	
//	if(mode==3||mode==4)
//		SoundEffect.Play(TIMEOVER)
	SoundEffect.Play(GAMEOVER);

	CEndGameDlg dlg;
	dlg.nEndType=mode;
	dlg.m_nBlackSecond=GameInfo.nBlackTimeUsed;
	dlg.m_nWhiteSecond=GameInfo.nWhiteTimeUsed;
	dlg.nMaxHand=GameRec.GetSize();
	if(mode==0) dlg.nMaxHand--;
	dlg.PlayMode=GetPlayMode();
	if(dlg.DoModal()==IDOK)
	{
		GameInfo.nTotalHand=GameRec.GetSize();
		GameInfo.WinLost=dlg.m_WinLost;
		GameInfo.nMiddle=dlg.m_nMiddle;
		GameInfo.nGuanZi=dlg.m_nGuanZi;
		GameInfo.bIsOver=TRUE;
		if(mode==0) GameRec.Pop();
		SetModifiedFlag();
		UpdateAllViews(NULL,4);
		return true;
	}
	return false;
}

bool CBoard::FindPiece(int SerNum, CPoint& pt)
{
	PIECEINFO* pi=GameRec.GetItem(SerNum);
	pt.x=pi->m_nRow,pt.y=pi->m_nCol;
	if(piece[pt.x][pt.y].m_nSerNum==SerNum)
		return true;
	else
		return false;
}

void CBoard::BlackPrePut(int nCount)
{
	POINT a[]= {{10,10},
				{4,4},{16,16},
				{4,4},{10,10},{16,16},
				{4,4},{4,16},{16,16},{16,4},
				{4,4},{4,16},{16,16},{16,4},{10,10},
				{4,4},{4,10},{4,16},{16,4},{16,10},{16,16},
				{4,4},{4,10},{4,16},{16,4},{16,10},{16,16},{10,10},
				{4,4},{4,10},{4,16},{16,4},{16,10},{16,16},{10,4},{10,16},
				{4,4},{4,10},{4,16},{16,4},{16,10},{16,16},{10,4},{10,16},{10,10}
				};
	int i,m=0;
	for(i=0;i<nCount;i++)	m+=i;
	for(i=0;i<nCount;i++)
	{
		piece[a[m+i].x][a[m+i].y].m_nColor=1;
		piece[a[m+i].x][a[m+i].y].m_nSerNum=-1;
	}
}

BOOL CBoard::OnSaveDocument(LPCTSTR lpszPathName) 
{
	//如果是录入模式或还没有结束,则取时间
	if(m_nPlayMode<REPLAY&&!IsGameOver())
	{
		POSITION pos = GetFirstViewPosition();
		GetNextView( pos );
		CInfView* pView=(CInfView*)GetNextView(pos);
		pView->GetUsedTime(GameInfo.nBlackTimeUsed,GameInfo.nWhiteTimeUsed);
		GameInfo.nTotalHand=GameRec.GetSize();
	}

	PIECEINFO* pi=GameRec.GetCurrent();
	if(IsGameOver())
		GameRec.SetCurrent(GameRec.GetLast());
	BOOL ret=CDocument::OnSaveDocument(lpszPathName);
	
	GameRec.SetCurrent(pi);
	return ret;
}

bool CBoard::CanRegret()
{
	if(m_nPlayMode==GUESS||GameRec.GetSize()==0)
		return false;
	return (IsGameOver()||(m_nPlayMode!=STANDARD&&
		m_nPlayMode!=STANDFAST));
}

bool CBoard::CanReput()
{
	if(m_nPlayMode==GUESS||GameRec.GetRemain()==0)
		return false;
	return (IsGameOver()||(m_nPlayMode!=STANDARD&&
		m_nPlayMode!=STANDFAST));
}

bool CBoard::SetPlayMode(PLAYMODE pm)
{
	if(pm==m_nPlayMode) return false;
	if(pm==GUESS)
	{
		m_nSection=0;
		int i;
		for(i=0;i<3;i++)
		{
			GuessStat[i].nTotal=0;
			GuessStat[i].nRight=0;
			GuessStat[i].nWrong=0;
			GuessStat[i].nPercent=0;
		}
		int preput=AfxGetApp()->GetProfileInt("Settings",
			"PreputNumInGuess",5);
		if(preput>GetTotalHand()) preput=5;
		if(preput>GetTotalHand()) return false;
		if(m_nSerNum>GetTotalHand()) return false;
		
		POSITION pos=GetFirstViewPosition();
		CView* pView=GetNextView(pos);
		CClientDC dc(pView);
		int nCount=preput-m_nSerNum+1;
		for(i=0;i<nCount;i++)
			Reput(&dc);
	}

	m_nPlayMode=pm;
	return true;
}

void CBoard::GetGuessStat(int a[])
{
	a[0]=m_nSection;
	a[1]=GuessStat[m_nSection].nTotal;
	a[2]=GuessStat[m_nSection].nRight;
	a[3]=GuessStat[m_nSection].nWrong;
	a[4]=GuessStat[m_nSection].nPercent;
}
