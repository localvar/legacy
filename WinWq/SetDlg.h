#if !defined(AFX_SETDLG_H__03B7EA25_002D_11D4_B1EB_BFEABCD2F818__INCLUDED_)
#define AFX_SETDLG_H__03B7EA25_002D_11D4_B1EB_BFEABCD2F818__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetDlg dialog

class CSetDlg : public CDialog
{
// Construction
public:
	CSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetDlg)
	enum { IDD = IDD_SETTINGDLG };
	int		m_nAllowOverTime;
	int		m_nAllowOverTimeFast;
	int		m_nBoardPanes;
	BOOL	m_bContextMenu;
	CString	m_MusicFileName;
	int		m_bGiveAnswer;
	int		m_nAutoReplayDelayTime;
	BOOL	m_bEditComment;
	int		m_nEntireGameTime;
	int		m_nEntireGameTimeFast;
	int		m_nPrePutNumInGuess;
	int		m_nMaxBlock;
	int		m_nMaxHand;
	int		m_nMaxKills;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetDlg)
	virtual void OnOK();
	afx_msg void OnBtnMusicFile();
	virtual BOOL OnInitDialog();
	afx_msg void OnDefault();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETDLG_H__03B7EA25_002D_11D4_B1EB_BFEABCD2F818__INCLUDED_)
