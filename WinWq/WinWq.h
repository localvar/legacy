// WinWq.h : main header file for the WINWQ application
//

#if !defined(AFX_WINWQ_H__DE0E3145_F441_11D3_B1EB_F638804E4003__INCLUDED_)
#define AFX_WINWQ_H__DE0E3145_F441_11D3_B1EB_F638804E4003__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWinWqApp:
// See WinWq.cpp for the implementation of this class
//

class CWinWqApp : public CWinApp
{
public:
	CWinWqApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinWqApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CWinWqApp)
	afx_msg void OnAppAbout();
	afx_msg void OnOptionMusic();
	afx_msg void OnUpdateOptionMusic(CCmdUI* pCmdUI);
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ShowTipAtStartup(void);
private:
	void ShowTipOfTheDay(void);
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINWQ_H__DE0E3145_F441_11D3_B1EB_F638804E4003__INCLUDED_)
