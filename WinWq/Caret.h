// Caret.h: interface for the CCaret class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CARET_H__DE0E316F_F441_11D3_B1EB_F638804E4003__INCLUDED_)
#define AFX_CARET_H__DE0E316F_F441_11D3_B1EB_F638804E4003__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define HALFCARETLONG 6

class CCaret  
{
private:
	CBitmap* m_pOldbmp;
	CDC memDC;
	int m_nStepLen;
	CWnd* m_pWnd;
	int m_nMax;
	int m_nMin;
	CRect m_rect;	//caret rect
	int m_nColor;	//caret color
	CPen m_Pen[3];	
	int m_nVisible;	//if==1 show caret 
public:
	CBitmap m_Cover;
	void SetStepLen(int nMax,int nMin,int nStepLen);
	void Move(UINT dir);
	inline bool IsVisible();
	inline CPoint GetCaretPos();
	void ChangeColor();
	bool Create(CWnd* pWnd);
	void MoveTo(int a,int b);
	void Hide();
	void Show();
	CCaret();
	virtual ~CCaret();
};

inline CPoint CCaret::GetCaretPos()
{
	return CPoint(m_rect.left+HALFCARETLONG,m_rect.top+HALFCARETLONG);
}

inline bool CCaret::IsVisible()
{
	return m_nVisible==1;
}

#endif // !defined(AFX_CARET_H__DE0E316F_F441_11D3_B1EB_F638804E4003__INCLUDED_)
