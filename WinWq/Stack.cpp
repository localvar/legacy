// Stack.cpp: implementation of the CStack class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "winwq.h"
#include "Stack.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


void operator <<(CArchive& ar,PIECEINFO& pi)
{
	ar<<(BYTE)pi.m_nRow;
	ar<<(BYTE)pi.m_nCol;
	ar<<(BYTE)pi.m_nColor;
//	ar<<pi.m_nKills;
	ar<<pi.m_Discribe;
}

void operator >>(CArchive& ar,PIECEINFO& pi)
{
	BYTE data;
	
	ar>>data;
	pi.m_nRow=data;
	ar>>data;
	pi.m_nCol=data;
	ar>>data;
	pi.m_nColor=data;
//	ar>>pi.m_nKills;
	ar>>pi.m_Discribe;
}

//////////////////////////////////////////////////////////////////////
// CGameRecord Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CGameRecord,CObject)

CGameRecord::CGameRecord()
{
	pStart=NULL;
	pCurrent=NULL;
	pEnd=NULL;
	pLast=NULL;
	bLastLocked=false;
}

void CGameRecord::ReInit()
{
	pCurrent=pStart;
	while(pLast>pStart)
	{
		pLast--;
		pLast->m_Discribe.Empty();
	}
	bLastLocked=false;
}

CGameRecord::~CGameRecord()
{
	if(pStart!=NULL) delete[]pStart;
}

void CGameRecord::Serialize(CArchive& ar)
{
	int size;
	if(ar.IsStoring())
	{
		PIECEINFO* pPI;
		size=pCurrent-pStart;
		ar<<size;
		pPI=pStart;
		for(int i=0;i<size;i++,pPI++)
			ar<<*pPI;
	}
	else
	{
		ar>>size;
		pLast=pStart+size;
		pCurrent=pStart;
		for(int i=0;i<size;i++)
			ar>>*(pStart+i);
	}
}

bool CGameRecord::SetCurrent(PIECEINFO *pNew)
{
	if(pNew<pStart||pNew>pEnd)
		return false;
	pCurrent=pNew;
	return true;
}

void CGameRecord::Create(int size)
{
	pStart=new PIECEINFO[size];
	pCurrent=pStart;
	pLast=pStart;
	pEnd=pStart+size;
}

bool CGameRecord::Push(CPiece &piece)
{
	ASSERT(pStart!=NULL);
	if(pCurrent<pEnd)
	{
		pCurrent->m_nRow=piece.m_nRow;
		pCurrent->m_nCol=piece.m_nCol;
		pCurrent->m_nKills=piece.m_nKills;
		pCurrent->m_nColor=piece.m_nColor;
		pCurrent->m_nSerNum=piece.m_nSerNum;
		pCurrent++;
		if(!bLastLocked)  pLast=pCurrent;
		ASSERT(pCurrent<=pLast);
		return true;
	}
	return false;
}


PIECEINFO* CGameRecord::Pop()
{
	ASSERT(pStart!=NULL);
	if(pCurrent>pStart)
	{
		pCurrent--;
		return pCurrent;
	}
	return NULL;
}

PIECEINFO* CGameRecord::GetTopItem()
{
	if(pCurrent<=pStart)
		return NULL;
	return pCurrent-1;
}

bool CGameRecord::Push(int row, int col, int color, int serno, int kills)
{
	if(pCurrent<pEnd)
	{
		pCurrent->m_nRow=row;
		pCurrent->m_nCol=col;
		pCurrent->m_nColor=color;
		pCurrent->m_nSerNum=serno;
		pCurrent->m_nKills=kills;
		pCurrent++;
		if(!bLastLocked)  pLast=pCurrent;
		ASSERT(pCurrent<=pLast);
		return true;
	}
	return false;
}

