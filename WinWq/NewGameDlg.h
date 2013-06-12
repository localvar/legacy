#if !defined(AFX_NEWGAMEDLG_H__B6235261_F585_11D3_B1EB_CCE708905B02__INCLUDED_)
#define AFX_NEWGAMEDLG_H__B6235261_F585_11D3_B1EB_CCE708905B02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewGameDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewGameDlg dialog

class CNewGameDlg : public CDialog
{
// Construction
public:
	CString m_WhiteDegree;
	CString m_BlackDegree;
	int m_nDay;
	int m_nMonth;
	int m_nYear;
	CNewGameDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewGameDlg)
	enum { IDD = IDD_NEWGAME };
	CString	m_GameName;
	CTime	m_GameTime;
	CString	m_WhiteName;
	CString	m_BlackName;
	int		m_nBlackDegree;
	int		m_nWhiteDegree;
	int		m_nBlackPrePut;
	int		m_nPlayMode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewGameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewGameDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWGAMEDLG_H__B6235261_F585_11D3_B1EB_CCE708905B02__INCLUDED_)
