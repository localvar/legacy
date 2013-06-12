// CBoard.h : interface of the CBoard class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBOARD_H__DE0E314B_F441_11D3_B1EB_F638804E4003__INCLUDED_)
#define AFX_CBOARD_H__DE0E314B_F441_11D3_B1EB_F638804E4003__INCLUDED_

#include "Piece.h"	// Added by ClassView
#include "Stack.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct GAMEINFO
{
	CString GameName;
	int nYear;
	int nMonth;
	int nDay;
	CString BlackName;
	CString WhiteName;
	CString BlackDegree;
	CString WhiteDegree;
	int nTotalHand;	//总手数
	int nPlayMode;	//录入模式
	int nPanes;	//棋盘路数
	int nBlackPrevPut;	//让子数
	int nBlackTimeUsed;		//黑方用时
	int nWhiteTimeUsed;
	CString WinLost;	//胜负
	int nMiddle;	//中盘开始位置
	int nGuanZi;	//官子开始位置
	BOOL bIsOver;	//是否录入完成
};

enum PLAYMODE
{
	NORMAL,STANDARD,STANDFAST,RECORD,REPLAY,AUTOREPLAY,GUESS
};

struct GUESSSTAT
{
	int nTotal;
	int nRight;
	int nWrong;
	int nPercent;
};

class CBoard : public CDocument
{
protected: // create from serialization only
	CBoard();
	DECLARE_DYNCREATE(CBoard)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBoard)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	void GetGuessStat(int a[]);
	bool SetPlayMode(PLAYMODE pm);
	inline BOOL IsGameOver();
	bool FindPiece(int SerNum,CPoint& pt);
	int GetTotalHand();
	bool EndGame(int mode=0);
	int PutColor(int row,int col,int color,CDC* pDC);
	void RegretNormal(CDC* pDC);
	int GiveIn(bool bRegret=false);
	void PutInvalide(int row,int col,bool bRegret=false);
	bool InvertColor(int row,int col,CDC* pDC,bool bRegret=false);
	void Delete(int row,int col,CDC* pDC,bool bRegret=false);
	CPoint GetLastPiecePos();
	int Guess(int row,int col,CDC* pDC);
	bool CanReput();
	bool CanRegret();
	int Reput(CDC* pDC);
	int Regret(CDC* pDC);
	inline void GetKills(int &bk,int &wk);
	inline PLAYMODE GetPlayMode();
	inline int GetSerNum();
	inline int GetColor();
	inline int GetPanes();
	void ShowOrder(CDC* pDC);
	void SetPieceDiscribe(int row,int col,CString& NewD);
	inline PIECEINFO* GetPiece(int row,int col);
	inline GAMEINFO* GetGameInfo();
	void DrawBoard(CDC* pDC,CRect& rectBoard,CRect& rectPiece);
	int PutPiece(int row,int col,CDC *pDC);
	void PreparePiece(CDC* pDC,int start,int steplen);
	void PrepareBoard(CDC* pDC,CRect rtBoard,int steplen);
	virtual ~CBoard();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void BlackPrePut(int nCount);
	int m_nColor;
	CGameRecord GameRec;
	CGameRecord ChkRec;
	CGameRecord DelRec;
	GAMEINFO GameInfo;
	void ClrChkFlg(PIECEINFO* pStart);
	int Death(int row,int col);
	int Alive(int row,int col);
	int CanHere(int row,int col);
	//{{AFX_MSG(CBoard)
	afx_msg void OnUpdateShowOrder(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_nSection;
	GUESSSTAT GuessStat[3];
	int kills[3];
	PLAYMODE m_nPlayMode;
	int m_nSerNum;
	CBitmap m_BackGround;
	int m_nPanes;
	static int m_nFirst;
	CPiece piece[21][21];
};

inline GAMEINFO* CBoard::GetGameInfo()
{
	return &GameInfo;
}

inline int CBoard::GetPanes()
{
	return m_nPanes;
}

inline int CBoard::GetColor()
{
	return m_nColor;
}

inline PLAYMODE CBoard::GetPlayMode()
{
	return m_nPlayMode;
}

inline void CBoard::GetKills(int &bk, int &wk)
{
	bk=kills[1];
	wk=kills[2];
}

inline PIECEINFO* CBoard::GetPiece(int row, int col)
{
	return &piece[row][col];
}

inline int CBoard::GetSerNum()
{
	return m_nSerNum;
}

inline BOOL CBoard::IsGameOver()
{
	return GameInfo.bIsOver;
}
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CBOARD_H__DE0E314B_F441_11D3_B1EB_F638804E4003__INCLUDED_)
