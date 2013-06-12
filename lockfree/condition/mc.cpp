#include <windows.h>
#include "mc.h"


////////////////////////////////////////////////////////////////////////////////


#ifdef _WIN64
    #define BITSCANFORWARD	 _BitScanForward64
#else
    #define BITSCANFORWARD	 _BitScanForward
#endif

////////////////////////////////////////////////////////////////////////////////


CMultipleCondition::CMultipleCondition(DWORD dwNumConditions, BOOL bManualReset)
{
	InitializeSRWLock( &m_lock );
	InitializeConditionVariable( &m_cv );
	memset( m_cond, 0, sizeof(m_cond) );
	memset( m_valid, 0, sizeof(m_valid) );
	memset( m_manual, 0, sizeof(m_manual) );

	for( DWORD i = 0; i < dwNumConditions; ++i )
		AddCondition( bManualReset );
}


////////////////////////////////////////////////////////////////////////////////


DWORD CMultipleCondition::AddCondition( BOOL bManualReset )
{
	DWORD result = MAXIMUM_CONDITIONS;

	AcquireSRWLockExclusive( &m_lock );

	for( DWORD i = 0; i < _countof(m_valid); ++i )
	{
		ITEMTYPE v = ~m_valid[i];
		DWORD idx;

		if( BITSCANFORWARD( &idx, v ) )
		{
			result = i * ITEMBITS + idx;
			m_valid[i] |= (static_cast<ITEMTYPE>(1) << idx);
			if( bManualReset )
				m_manual[i] |= (static_cast<ITEMTYPE>(1) << idx);
		}
	}

	ReleaseSRWLockExclusive( &m_lock );
	return result;
}


////////////////////////////////////////////////////////////////////////////////


BOOL CMultipleCondition::RemoveCondition( DWORD dwCondIndex )
{
	DWORD error = ERROR_BAD_ARGUMENTS;

	if( dwCondIndex < MAXIMUM_CONDITIONS )
	{
		DWORD i = dwCondIndex / ITEMBITS;
		ITEMTYPE mask = static_cast<ITEMTYPE>(1) << (dwCondIndex % ITEMBITS);

		AcquireSRWLockExclusive( &m_lock );

		if( (m_valid[i] & mask) == mask )
		{
			m_cond[i] &= ~mask;
			m_valid[i] &= ~mask;
			m_manual[i] &= ~mask;
			error = ERROR_SUCCESS;
			WakeAllConditionVariable( &m_cv );
		}

		ReleaseSRWLockExclusive( &m_lock );
	}

	if( error != ERROR_SUCCESS )
	{
		SetLastError( error );
		return FALSE;
	}

	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////


BOOL CMultipleCondition::SetCondition( DWORD dwCondIndex )
{
	DWORD error = ERROR_BAD_ARGUMENTS;

	if( dwCondIndex < MAXIMUM_CONDITIONS )
	{
		DWORD i = dwCondIndex / ITEMBITS;
		ITEMTYPE mask = static_cast<ITEMTYPE>(1) << (dwCondIndex % ITEMBITS);

		AcquireSRWLockExclusive( &m_lock );

		if( (m_valid[i] & mask) == mask )
		{
			m_cond[i] |= mask;
			error = ERROR_SUCCESS;
			WakeAllConditionVariable( &m_cv );
		}

		ReleaseSRWLockExclusive( &m_lock );
	}

	if( error != ERROR_SUCCESS )
	{
		SetLastError( error );
		return FALSE;
	}

	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////


BOOL CMultipleCondition::ResetCondition( DWORD dwCondIndex )
{
	DWORD error = ERROR_BAD_ARGUMENTS;

	if( dwCondIndex < MAXIMUM_CONDITIONS )
	{
		DWORD i = dwCondIndex / ITEMBITS;
		ITEMTYPE mask = static_cast<ITEMTYPE>(1) << (dwCondIndex % ITEMBITS);

		AcquireSRWLockExclusive( &m_lock );

		if( (m_valid[i] & mask) == mask )
		{
			m_cond[i] &= ~mask;
			error = ERROR_SUCCESS;
		}

		ReleaseSRWLockExclusive( &m_lock );
	}

	if( error != ERROR_SUCCESS )
	{
		SetLastError( error );
		return FALSE;
	}

	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////


DWORD CMultipleCondition::CheckForSingle( DWORD dwCondIndex )
{
	ITEMTYPE m = static_cast<ITEMTYPE>(1) << (dwCondIndex % ITEMBITS);
	DWORD i = dwCondIndex / ITEMBITS;

	if( (m_valid[i] & m) == 0 )
		return 0xffffffff;

	if( m_cond[i] & m )
	{
		m_cond[i] &= (m_manual[i] | ~m);
		return dwCondIndex;
	}

	return MAXIMUM_CONDITIONS;
}

////////////////////////////////////////////////////////////////////////////////


DWORD CMultipleCondition::WaitForSingle( DWORD dwCondIndex, DWORD dwTimeout )
{
	DWORD result = WAIT_FAILED;

	if( dwCondIndex > MAXIMUM_CONDITIONS )
	{
		SetLastError( ERROR_BAD_ARGUMENTS );
		return result;
	}

	DWORD start = GetTickCount();

	AcquireSRWLockExclusive( &m_lock );

	do {
		DWORD r = CheckForSingle( dwCondIndex );
		if( r == 0xffffffff )
		{
			SetLastError( ERROR_BAD_ARGUMENTS );
			break;
		}
		if( r != dwCondIndex )
		{
			result = dwCondIndex;
			break;
		}

		if( dwTimeout != INFINITE )
		{
			DWORD end = GetTickCount();
			if( end - start >= dwTimeout )
			{
				result = WAIT_TIMEOUT;
				break;
			}
			dwTimeout -= end - start;
			start = end;
		}
	} while( SleepConditionVariableSRW( &m_cv, &m_lock, dwTimeout, 0 ) );

	ReleaseSRWLockExclusive( &m_lock );

	if( result == WAIT_FAILED && GetLastError() == ERROR_TIMEOUT )
		result = WAIT_TIMEOUT;
	return result;
}


////////////////////////////////////////////////////////////////////////////////


DWORD CMultipleCondition::CheckForAny()
{
	for( DWORD i = 0; i < _countof(m_cond); ++i )
	{
		DWORD idx;
		if( BITSCANFORWARD( &idx, m_cond[i] ) )
		{
			m_cond[i] &= (~(static_cast<ITEMTYPE>(1) << idx)) | m_manual[i];
			return i * ITEMBITS + idx;
		}
	}
	return MAXIMUM_CONDITIONS;
}


////////////////////////////////////////////////////////////////////////////////


DWORD CMultipleCondition::WaitForAny( DWORD dwTimeout )
{
	DWORD result = WAIT_FAILED;
	DWORD start = GetTickCount();

	AcquireSRWLockExclusive( &m_lock );

	do {
		DWORD r = CheckForAny();
		if( r != MAXIMUM_CONDITIONS )
		{
			result = r;
			break;
		}

		if( dwTimeout != INFINITE )
		{
			DWORD end = GetTickCount();
			if( end - start >= dwTimeout )
			{
				result = WAIT_TIMEOUT;
				break;
			}
			dwTimeout -= end - start;
			start = end;
		}
	} while( SleepConditionVariableSRW( &m_cv, &m_lock, dwTimeout, 0 ) );

	ReleaseSRWLockExclusive( &m_lock );

	if( result == WAIT_FAILED && GetLastError() == ERROR_TIMEOUT )
		result = WAIT_TIMEOUT;
	return result;
}


////////////////////////////////////////////////////////////////////////////////


BOOL CMultipleCondition::CheckForAll()
{
	for( DWORD i = 0; i < _countof(m_cond); ++i )
		if( m_cond[i] != m_valid[i] )
			return FALSE;
	for( DWORD i = 0; i < _countof(m_cond); ++i )
		m_cond[i] &= m_manual[i];
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////


DWORD CMultipleCondition::WaitForAll( DWORD dwTimeout )
{
	DWORD result = WAIT_FAILED;
	DWORD start = GetTickCount();

	AcquireSRWLockExclusive( &m_lock );

	do {
		if( CheckForAll() )
		{
			result = 0;
			break;
		}

		if( dwTimeout != INFINITE )
		{
			DWORD end = GetTickCount();
			if( end - start >= dwTimeout )
			{
				result = WAIT_TIMEOUT;
				break;
			}
			dwTimeout -= end - start;
			start = end;
		}
	} while( SleepConditionVariableSRW( &m_cv, &m_lock, dwTimeout, 0 ) );

	ReleaseSRWLockExclusive( &m_lock );

	if( result == WAIT_FAILED && GetLastError() == ERROR_TIMEOUT )
		result = WAIT_TIMEOUT;
	return result;
}


////////////////////////////////////////////////////////////////////////////////
