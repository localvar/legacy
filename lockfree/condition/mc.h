#pragma once

class CMultipleCondition
{
public:
	static const unsigned MAXIMUM_CONDITIONS = MAXIMUM_WAIT_OBJECTS;

private:
	SRWLOCK m_lock;
	CONDITION_VARIABLE m_cv;

#ifdef _WIN64
	typedef DWORD64	ITEMTYPE;
#else
	typedef DWORD	ITEMTYPE;
#endif

	static const unsigned ITEMBITS = sizeof(ITEMTYPE) * 8;
	static const unsigned ARRAY_SIZE = (MAXIMUM_CONDITIONS + (ITEMBITS - 1)) / ITEMBITS;

	ITEMTYPE m_cond[ARRAY_SIZE];
	ITEMTYPE m_valid[ARRAY_SIZE];
	ITEMTYPE m_manual[ARRAY_SIZE];

private:
	DWORD CheckForSingle( DWORD dwCondIndex );
	DWORD CheckForAny();
	BOOL CheckForAll();

public:
	CMultipleCondition( DWORD dwNumConditions, BOOL bManualReset );
	DWORD AddCondition( BOOL bManualReset );
	BOOL RemoveCondition( DWORD dwCondIndex );

	BOOL SetCondition( DWORD dwCondIndex );
	BOOL ResetCondition( DWORD dwCondIndex );

	DWORD WaitForSingle( DWORD dwCondIndex, DWORD dwTimeout );
	DWORD WaitForAny( DWORD dwTimeout );
	DWORD WaitForAll( DWORD dwTimeout );
};

