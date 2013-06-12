#if !defined(AFX_MREGRETDLG_H__061382E1_FF68_11D3_B1EB_F53A238D7906__INCLUDED_)
#define AFX_MREGRETDLG_H__061382E1_FF68_11D3_B1EB_F53A238D7906__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MRegretDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMRegretDlg dialog

class CMRegretDlg : public CDialog
{
// Construction
public:
	int m_nCurrentHand;
	int m_nMaxHand;
	CMRegretDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMRegretDlg)
	enum { IDD = IDD_MULTI_REGRET };
	int		m_nToHand;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMRegretDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMRegretDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MREGRETDLG_H__061382E1_FF68_11D3_B1EB_F53A238D7906__INCLUDED_)
