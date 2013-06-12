#if !defined(AFX_FINDPIECEDLG_H__B202C101_0022_11D4_B1EB_BFEABCD2F818__INCLUDED_)
#define AFX_FINDPIECEDLG_H__B202C101_0022_11D4_B1EB_BFEABCD2F818__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindPieceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFindPieceDlg dialog

class CFindPieceDlg : public CDialog
{
// Construction
public:
	int nMaxHand;
	CFindPieceDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFindPieceDlg)
	enum { IDD = IDD_FINDPIECE };
	CString	m_MaxHand;
	int		m_nPieceToFind;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindPieceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFindPieceDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDPIECEDLG_H__B202C101_0022_11D4_B1EB_BFEABCD2F818__INCLUDED_)
