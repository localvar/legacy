// BoardVw.h : interface of the CBoardView class
//
/////////////////////////////////////////////////////////////////////////////

#include "Caret.h"
#include "CBoard.h"
#include "FindPieceDlg.h"

#if !defined(AFX_BOARDVW_H__DE0E314D_F441_11D3_B1EB_F638804E4003__INCLUDED_)
#define AFX_BOARDVW_H__DE0E314D_F441_11D3_B1EB_F638804E4003__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBoardView : public CView
{
protected: // create from serialization only
	CBoardView();
	DECLARE_DYNCREATE(CBoardView)

// Attributes
public:
	CBoard* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBoardView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CBoardView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void Guess(int row,int col);
	void PutPiece(int row,int col);
//	CView* m_pBuddy;
	CPoint CPtoBP(CPoint ptSource);
	CPoint BPtoCP(CPoint ptSource);
	int m_nStepLen;
	int m_nMin;
	int m_nMax;
	//{{AFX_MSG(CBoardView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPutBlack();
	afx_msg void OnPutWhite();
	afx_msg void OnCancel();
	afx_msg void OnShowOrder();
	afx_msg void OnEditRegret();
	afx_msg void OnEditInvert();
	afx_msg void OnEditDelete();
	afx_msg void OnEditReput();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnUpdateEditDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditInvert(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePutWhite(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePutBlack(CCmdUI* pCmdUI);
	afx_msg void OnGiveIn();
	afx_msg void OnEditRegretMore();
	afx_msg void OnEditLost();
	afx_msg void OnFindPiece();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnOptionSettings();
	afx_msg void OnUpdateGiveIn(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditLost(CCmdUI* pCmdUI);
	afx_msg void OnGuess();
	afx_msg void OnOptionSound();
	afx_msg void OnUpdateOptionSound(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditRegret(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditRegretMore(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditReput(CCmdUI* pCmdUI);
	afx_msg void OnAutoReplay();
	afx_msg void OnUpdateAutoReplay(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGuess(CCmdUI* pCmdUI);
	afx_msg void OnReplay();
	afx_msg void OnUpdateReplay(CCmdUI* pCmdUI);
	afx_msg void OnProperties();
	afx_msg void OnConvert();
	//}}AFX_MSG
	afx_msg LRESULT OnCaretShow(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnRegretToStart(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnReputToEnd(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	HCURSOR m_hWhite;
	HCURSOR m_hBlack;
	CCaret m_caret;
};

#ifndef _DEBUG  // debug version in BoardVw.cpp
inline CBoard* CBoardView::GetDocument()
   { return (CBoard*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOARDVW_H__DE0E314D_F441_11D3_B1EB_F638804E4003__INCLUDED_)
