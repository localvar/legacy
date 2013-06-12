#if !defined(AFX_INFVIEW_H__DE0E316E_F441_11D3_B1EB_F638804E4003__INCLUDED_)
#define AFX_INFVIEW_H__DE0E316E_F441_11D3_B1EB_F638804E4003__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InfView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInfView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "BoardVW.h"

struct TIMER
{
	int mode;
	int nTotal;
	int nCurrentHand;
	int nOverFlow;
};

class CInfView : public CFormView
{
protected:
	CInfView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CInfView)

// Form Data
public:
	//{{AFX_DATA(CInfView)
	enum { IDD = IDD_INFORMATION };
	CListCtrl	m_StatList;
	CStatic	m_WhiteKills;
	CStatic	m_BlackKills;
	CEdit	m_Discribe;
	CString	m_BlackName;
	CString	m_GameName;
	CString	m_WhiteName;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	void PlayModeChgUpdate();
	void GetUsedTime(int& bt,int& wt);
	void NewDocUpdate();
	void PutPieceUpdate();
	void CaretMoveUpdate();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;
	int m_nAllowOverTime;
	void ShowTime(int color);
	CBoardView* m_pBuddy;
	virtual ~CInfView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CInfView)
	afx_msg void OnKillfocusDiscribe();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButton1();
	afx_msg void OnPutBlack();
	afx_msg void OnPutWhite();
	afx_msg void OnDestroy();
	afx_msg void OnInvertColor();
	afx_msg void OnRegret();
	afx_msg void OnReput();
	afx_msg void OnDelete();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRegretToStart();
	afx_msg void OnReputToEnd();
	afx_msg void OnCurrentSernum();
	afx_msg void OnCurrentPosition();
	afx_msg void OnGiveIn();
	afx_msg void OnGiveUp();
	//}}AFX_MSG
	afx_msg void OnTimerClick(UINT nID);
	DECLARE_MESSAGE_MAP()
private:
	bool m_bHasTimer;
	TIMER m_Timer[2];
	int m_nMaxTime;
	int m_nCol;
	int m_nRow;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFVIEW_H__DE0E316E_F441_11D3_B1EB_F638804E4003__INCLUDED_)
