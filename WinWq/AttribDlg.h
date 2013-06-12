#if !defined(AFX_ATTRIBDLG_H__F7E14DFB_0289_11D4_B1EB_E0DB7F481023__INCLUDED_)
#define AFX_ATTRIBDLG_H__F7E14DFB_0289_11D4_B1EB_E0DB7F481023__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AttribDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAttribDlg dialog

#include "CBoard.h"

class CAttribDlg : public CDialog
{
// Construction
public:
	PIECEINFO* pi;
	GAMEINFO* pGi;
	CAttribDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAttribDlg)
	enum { IDD = IDD_ATTRIB };
	int		m_nGuanZi;
	int		m_nMiddle;
	CString	m_GameDiscribe;
	CString	m_PieceDiscribe;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAttribDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAttribDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int nTotalHand;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATTRIBDLG_H__F7E14DFB_0289_11D4_B1EB_E0DB7F481023__INCLUDED_)
