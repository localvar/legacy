// Piece.cpp: implementation of the CPiece class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WinWq.h"
#include "Piece.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BOOL CPiece::bShowOrder=TRUE;
CImageList CPiece::m_PieceLst;
CBitmap* CPiece::pBckGrd;
CBitmap CPiece::m_bmpWhite;
CBitmap CPiece::m_bmpBlack;
int CPiece::m_nPieceSize;

CPiece::CPiece()
{

}

CPiece::~CPiece()
{

}

void CPiece::DrawPiece(CDC *pDC)
{
	if(m_nColor==0)
	{
		CDC dc;
		dc.CreateCompatibleDC(pDC);
		CBitmap* pOld;
		pOld=dc.SelectObject(pBckGrd);
		pDC->BitBlt(point.x,point.y,m_nPieceSize,m_nPieceSize,&dc,point.x,point.y,SRCCOPY);
		dc.SelectObject(pOld);
	}
	else 
	{
		m_PieceLst.Draw(pDC,m_nColor-1,point,ILD_TRANSPARENT);
		if(bShowOrder)
		{
			pDC->SetBkMode(TRANSPARENT);
//			pDC->SetTextCharacterExtra(-2);
			CString order;
			RECT rect={point.x,point.y,point.x+m_nPieceSize,point.y+m_nPieceSize};
			order.Format("%d",m_nSerNum);
			pDC->SetTextColor((m_nColor==2)?RGB(0,0,0):RGB(255,255,255));
			pDC->DrawText(order,&rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		}
	}
}

void CPiece::ClearPiece()
{
	m_nColor=0;
	m_nKills=0;
	m_nSerNum=0;
	m_Discribe.Empty();
	m_bChkFlg=false;
}

void CPiece::CreatePieceBitmap(CDC *pDC, int nLen,CBitmap* pBackGround)
{
	CDC dc1,dc2;
	COLORREF MaskColorBlack,MaskColorWhite;
	CBitmap bmp1,bmp2,*pOld1,*pOld2;
	BITMAP bm;

	dc1.CreateCompatibleDC(pDC);
	dc2.CreateCompatibleDC(pDC);
	bmp1.LoadBitmap(IDB_BLACK);
	bmp2.LoadBitmap(IDB_WHITE);
	CPiece::m_bmpBlack.CreateCompatibleBitmap(pDC,nLen,nLen);
	CPiece::m_bmpWhite.CreateCompatibleBitmap(pDC,nLen,nLen);
	//create pieces
	bmp1.GetBitmap(&bm);
	pOld1=dc1.SelectObject(&bmp1);
	pOld2=dc2.SelectObject(&CPiece::m_bmpBlack);
	dc2.StretchBlt(0,0,nLen,nLen,&dc1,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
	MaskColorBlack=dc2.GetPixel(0,0);

	bmp2.GetBitmap(&bm);
	dc1.SelectObject(&bmp2);
	dc2.SelectObject(&CPiece::m_bmpWhite);
	dc2.StretchBlt(0,0,nLen,nLen,&dc1,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
	MaskColorWhite=dc2.GetPixel(0,0);

	dc2.SelectObject(pOld1);
	dc2.SelectObject(pOld2);
	bmp1.DeleteObject();
	bmp2.DeleteObject();
	
	CPiece::m_nPieceSize=nLen;
	CPiece::pBckGrd=pBackGround;
	CPiece::m_PieceLst.Create(nLen,nLen,ILC_COLOR8|ILC_MASK,0,2);
	CPiece::m_PieceLst.Add(&CPiece::m_bmpBlack,MaskColorBlack);
	CPiece::m_PieceLst.Add(&CPiece::m_bmpWhite,MaskColorWhite);
}

void CPiece::DestroyPieceBitmap()
{
	CPiece::m_PieceLst.DeleteImageList();
	CPiece::m_bmpBlack.DeleteObject();
	CPiece::m_bmpWhite.DeleteObject();
}
