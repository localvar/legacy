#if !defined(AFX_WQOPENDLG_H__7311A16F_0FCB_11D4_9E24_CD9AB45B3B11__INCLUDED_)
#define AFX_WQOPENDLG_H__7311A16F_0FCB_11D4_9E24_CD9AB45B3B11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WqOpenDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWqOpenDlg dialog

class CWqOpenDlg : public CFileDialog
{
	DECLARE_DYNAMIC(CWqOpenDlg)

public:
	void OnInitDone();
	CWqOpenDlg(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

protected:
	void OnFileNameChange();
	//{{AFX_MSG(CWqOpenDlg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WQOPENDLG_H__7311A16F_0FCB_11D4_9E24_CD9AB45B3B11__INCLUDED_)
