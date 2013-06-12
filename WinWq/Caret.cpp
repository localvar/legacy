// Caret.cpp: implementation of the CCaret class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WinWq.h"
#include "Caret.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCaret::CCaret()
{
	m_nVisible=0;
}

CCaret::~CCaret()
{
	memDC.SelectObject(m_pOldbmp);
	m_Cover.DeleteObject();
}

void CCaret::Show()
{
	if(m_nVisible<1) m_nVisible++;
	if(m_nVisible==1)
	{
		CClientDC dc(m_pWnd);
		memDC.BitBlt(0,0,m_rect.Width(),m_rect.Height(),&dc,m_rect.left,m_rect.top,SRCCOPY);
		CPen* pOldpen;
		pOldpen=dc.SelectObject(&m_Pen[m_nColor]);
		dc.MoveTo(m_rect.left+1,m_rect.top+1);
		dc.LineTo(m_rect.right-1,m_rect.top+1);
		dc.LineTo(m_rect.right-1,m_rect.bottom-1);
		dc.LineTo(m_rect.left+1,m_rect.bottom-1);
		dc.LineTo(m_rect.left+1,m_rect.top+1);
		dc.SelectObject(pOldpen);
		m_pWnd->PostMessage(WM_USER+200,(WPARAM)m_rect.left+HALFCARETLONG,(LPARAM)m_rect.top+HALFCARETLONG);
	}
}

void CCaret::Hide()
{
	if(m_nVisible==1)
	{
		CClientDC dc(m_pWnd);
		dc.BitBlt(m_rect.left,m_rect.top,m_rect.Width(),m_rect.Height(),&memDC,0,0,SRCCOPY);
	}
	m_nVisible--;
}

void CCaret::MoveTo(int a, int b)
{
	if(a<m_nMin||a>m_nMax||b<m_nMin||b>m_nMax)
		return;
	Hide();
	m_rect.SetRect(a-HALFCARETLONG,b-HALFCARETLONG,
		a+HALFCARETLONG+1,b+HALFCARETLONG+1);
	Show();
//	m_pWnd->PostMessage(WM_USER+200,0,
//		MAKELONG(m_rect.left+HALFCARETLONG,m_rect.top+HALFCARETLONG));
}

bool CCaret::Create(CWnd *pWnd)
{
	m_pWnd=pWnd;
	
	m_Pen[0].CreatePen(PS_SOLID,2,RGB(255,0,0));
	m_Pen[1].CreatePen(PS_SOLID,2,RGB(0,255,0));
	m_Pen[2].CreatePen(PS_SOLID,2,RGB(0,0,255));
	m_nColor=0;

	CClientDC dc(m_pWnd);
	memDC.CreateCompatibleDC(&dc);
	m_Cover.CreateCompatibleBitmap(&dc,3,3);
	m_pOldbmp=memDC.SelectObject(&m_Cover);

	return true;
}

void CCaret::ChangeColor()
{
	if(m_nVisible==1)
	{
	/*	CClientDC dc(m_pWnd);
		dc.FillRect(&m_rect,&brush[m_nColor]);
		m_nColor++;
		if(m_nColor==3) m_nColor=0;
	*/}
}

void CCaret::Move(UINT dir)
{
	Hide();
	switch(dir)
	{
	case VK_LEFT: if(GetCaretPos().x<=m_nMin)
			   {
				   m_rect.left=m_nMax-HALFCARETLONG;
				   m_rect.right=m_nMax+HALFCARETLONG+1;
			   }else
			   {
				   m_rect.left-=m_nStepLen;
				   m_rect.right-=m_nStepLen;
			   }
			   break;
	case VK_RIGHT:if(GetCaretPos().x>=m_nMax)
			   {
				   m_rect.left=m_nMin-HALFCARETLONG;
				   m_rect.right=m_nMin+HALFCARETLONG+1;
			   }else
			   {
				   m_rect.left+=m_nStepLen;
				   m_rect.right+=m_nStepLen;
			   }
			   break;
	case VK_UP:if(GetCaretPos().y<=m_nMin)
			   {
				   m_rect.top=m_nMax-HALFCARETLONG;
				   m_rect.bottom=m_nMax+HALFCARETLONG+1;
			   }else
			   {
				   m_rect.top-=m_nStepLen;
				   m_rect.bottom-=m_nStepLen;
			   }
			   break;
	case VK_DOWN:if(GetCaretPos().y>=m_nMax)
			   {
				   m_rect.top=m_nMin-HALFCARETLONG;
				   m_rect.bottom=m_nMin+HALFCARETLONG+1;
			   }else
			   {
				   m_rect.top+=m_nStepLen;
				   m_rect.bottom+=m_nStepLen;
			   }
			   break;
	}
	Show();
//	m_pWnd->PostMessage(WM_USER+200,0,
//		MAKELONG(m_rect.left+HALFCARETLONG,m_rect.top+HALFCARETLONG));
}

void CCaret::SetStepLen(int nMax, int nMin, int nStepLen)
{
	m_nStepLen=nStepLen;
	m_nMin=nMin;
	m_nMax=nMax;
	int center=(nMax+nMin)/2;
	m_rect.SetRect(center-HALFCARETLONG,center-HALFCARETLONG,
		center+HALFCARETLONG+1,center+HALFCARETLONG+1);

	CClientDC dc(m_pWnd);
	memDC.SelectObject(m_pOldbmp);
	m_Cover.DeleteObject();
	m_Cover.CreateCompatibleBitmap(&dc,m_rect.Width(),m_rect.Height());
	m_pOldbmp=memDC.SelectObject(&m_Cover);
}
