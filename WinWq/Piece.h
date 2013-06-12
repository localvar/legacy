// Piece.h: interface for the CPiece class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PIECE_H__E329BC21_F523_11D3_B1EB_BF32A6422505__INCLUDED_)
#define AFX_PIECE_H__E329BC21_F523_11D3_B1EB_BF32A6422505__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct PIECEINFO
{
	int m_nRow;
	int m_nCol;
	int m_nColor;	//color
	int m_nSerNum;	//serial numer
	int m_nKills;
	CString m_Discribe;
};	

class CPiece:public PIECEINFO
{
private:
	POINT point;
	static CBitmap m_bmpWhite;
	static CBitmap m_bmpBlack;
	static CBitmap* pBckGrd;
	static CImageList m_PieceLst;
	static int m_nPieceSize;
public:
	static BOOL bShowOrder;
	bool m_bChkFlg;
public:
	static void DestroyPieceBitmap();
	static void CreatePieceBitmap(CDC* pDC,int nLen,CBitmap* pBackGround);
	inline void SetPos(int a,int b);
	void ClearPiece();
	void DrawPiece(CDC* pDC);
	CPiece();
	virtual ~CPiece();
};

inline void CPiece::SetPos(int a,int b)
{
	point.x=a,point.y=b;
}

#endif // !defined(AFX_PIECE_H__E329BC21_F523_11D3_B1EB_BF32A6422505__INCLUDED_)
