#if !defined(AFX_SPLITTER_H__DE0E316A_F441_11D3_B1EB_F638804E4003__INCLUDED_)
#define AFX_SPLITTER_H__DE0E316A_F441_11D3_B1EB_F638804E4003__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Splitter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSplitter window

class CSplitter : public CSplitterWnd
{
// Construction
public:
	CSplitter();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplitter)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSplitter();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSplitter)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLITTER_H__DE0E316A_F441_11D3_B1EB_F638804E4003__INCLUDED_)
