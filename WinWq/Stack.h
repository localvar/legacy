// Stack.h: interface for the CStack class.
//
//////////////////////////////////////////////////////////////////////

#include "piece.h"

#if !defined(AFX_STACK_H__B6F6EB05_F6C2_11D3_B1EB_CA7D699C45B1__INCLUDED_)
#define AFX_STACK_H__B6F6EB05_F6C2_11D3_B1EB_CA7D699C45B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGameRecord:public CObject
{
	DECLARE_DYNCREATE(CGameRecord)
private:
	bool bLastLocked;
	PIECEINFO* pStart;
	PIECEINFO* pCurrent;
	PIECEINFO* pEnd;	//堆栈的末尾
	PIECEINFO* pLast;	//输入的最后一个,用于对重下的支持
public:
	inline PIECEINFO* GetLast();
	inline PIECEINFO* GetBottom();
	inline int GetRemain();
	inline void UnlockLast();
	inline void LockLast();
	bool Push(int row,int col,int color,int serno, int kills=0);
	PIECEINFO* GetTopItem();
	PIECEINFO* Pop();
	virtual void Serialize(CArchive& ar);
	inline PIECEINFO* GetItem(int nIndex);
	bool Push(CPiece& piece);
	void Create(int size);
	bool SetCurrent(PIECEINFO *pNew);
	inline int GetSize();
	inline PIECEINFO* GetCurrent();
	void ReInit();
	CGameRecord();
	virtual ~CGameRecord();
};

inline int CGameRecord::GetSize()
{
	return pCurrent-pStart;
}

inline PIECEINFO* CGameRecord::GetCurrent()
{
	return pCurrent;
}

inline PIECEINFO* CGameRecord::GetItem(int nIndex)
{
	return pStart+nIndex-1;
}

inline void CGameRecord::LockLast()
{
	bLastLocked=true;
}

inline void CGameRecord::UnlockLast()
{
	bLastLocked=false;
}

inline int CGameRecord::GetRemain()
{
	return pLast-pCurrent;
}

inline PIECEINFO* CGameRecord::GetBottom()
{
	return pStart;
}


inline PIECEINFO* CGameRecord::GetLast()
{
	return pLast;
}
#endif // !defined(AFX_STACK_H__B6F6EB05_F6C2_11D3_B1EB_CA7D699C45B1__INCLUDED_)
