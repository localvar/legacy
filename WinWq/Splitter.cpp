// Splitter.cpp : implementation file
//

#include "stdafx.h"
#include "WinWq.h"
#include "Splitter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplitter

CSplitter::CSplitter()
{
}

CSplitter::~CSplitter()
{
}


BEGIN_MESSAGE_MAP(CSplitter, CSplitterWnd)
	//{{AFX_MSG_MAP(CSplitter)
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSplitter message handlers

void CSplitter::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd::OnMouseMove(nFlags, point);
}

BOOL CSplitter::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CSplitter::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	// CSplitterWnd::OnLButtonDown(nFlags, point);
}
