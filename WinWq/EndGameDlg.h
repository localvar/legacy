#if !defined(AFX_ENDGAMEDLG_H__3C009B61_000B_11D4_B1EB_94D77B40FA06__INCLUDED_)
#define AFX_ENDGAMEDLG_H__3C009B61_000B_11D4_B1EB_94D77B40FA06__INCLUDED_

#include "CBoard.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EndGameDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEndGameDlg dialog

class CEndGameDlg : public CDialog
{
// Construction
public:
	PLAYMODE PlayMode;
	int nMaxHand;
	int m_nWhiteSecond;
	int m_nBlackSecond;
	CEndGameDlg(CWnd* pParent = NULL);   // standard constructor
	int nEndType;
// Dialog Data
	//{{AFX_DATA(CEndGameDlg)
	enum { IDD = IDD_ENDGAME };
	CTime	m_BlackTimeUsed;
	int		m_nGuanZi;
	int		m_nMiddle;
	CTime	m_WhiteTimeUsed;
	CString	m_WinLost;
	CString	m_MaxHand;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEndGameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEndGameDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENDGAMEDLG_H__3C009B61_000B_11D4_B1EB_94D77B40FA06__INCLUDED_)
