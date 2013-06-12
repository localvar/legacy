#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>
#include <conio.h>
#include "mc.h"


////////////////////////////////////////////////////////////////////////////////


class CMultipleEvent
{
private:
	HANDLE m_event[64];
	DWORD m_count;

public:
	CMultipleEvent( DWORD dwNumObjects, BOOL bManualReset )
	{
		memset( m_event, 0, sizeof(m_event) );
		for( DWORD i = 0; i < dwNumObjects; ++i )
			m_event[i] = CreateEvent( NULL, bManualReset, FALSE, NULL );
		m_count = dwNumObjects;
	}
	~CMultipleEvent()
	{
		for( DWORD i = 0; i < m_count; ++i )
			CloseHandle( m_event[i] );
	}
	BOOL AddEvent( BOOL bManualReset )
	{
		m_event[m_count] = CreateEvent( NULL, bManualReset, FALSE, NULL );
		++m_count;
		return TRUE;
	}
	BOOL SetEvent( DWORD dwIndex )
	{
		return ::SetEvent( m_event[dwIndex] );
	}
	DWORD WaitForAny( DWORD dwTimeout )
	{
		return WaitForMultipleObjects( m_count, m_event, FALSE, dwTimeout );
	}
};


////////////////////////////////////////////////////////////////////////////////

DWORD g_event_count = 32;
DWORD g_rounds = 1000000;

////////////////////////////////////////////////////////////////////////////////


CMultipleCondition g_mc1( 0, FALSE );
CMultipleCondition g_mc2( 0, FALSE );
DWORD64 g_mc_tick = 0;

unsigned int __stdcall mcthread1( void* )
{
	g_mc1.WaitForAny( INFINITE );

	g_mc_tick = __rdtsc();
	for( DWORD i = 0; i < g_rounds; ++i )
	{
		g_mc2.SetCondition( i % g_event_count );
		g_mc1.WaitForAny( INFINITE );
	}
	g_mc_tick = __rdtsc() - g_mc_tick;
	_tprintf( _T("multiple condition test result: %lld\n"), g_mc_tick );
	return 0;
}

unsigned int __stdcall mcthread2( void* )
{
	Sleep( 100 );
	g_mc1.SetCondition( 0 );
	for( DWORD i = 0; ; ++i )
	{
		if( g_mc2.WaitForAny( 1000 ) == WAIT_TIMEOUT )
			break;
		g_mc1.SetCondition( i % g_event_count );
	}
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


CMultipleEvent g_me1( 0, FALSE );
CMultipleEvent g_me2( 0, FALSE );
DWORD64 g_me_tick = 0;

unsigned int __stdcall methread1( void* )
{
	g_me1.WaitForAny( INFINITE );

	g_me_tick = __rdtsc();
	for( DWORD i = 0; i < g_rounds; ++i )
	{
		g_me2.SetEvent( i % g_event_count );
		g_me1.WaitForAny( INFINITE );
	}
	g_me_tick = __rdtsc() - g_me_tick;
	_tprintf( _T("multiple event test result    : %lld\n"), g_me_tick );
	return 0;
}

unsigned int __stdcall methread2( void* )
{
	Sleep( 100 );
	g_me1.SetEvent( 0 );
	for( DWORD i = 0; ; ++i )
	{
		if( g_me2.WaitForAny( 1000 ) == WAIT_TIMEOUT )
			break;
		g_me1.SetEvent( i % g_event_count );
	}
	return 0;
}


////////////////////////////////////////////////////////////////////////////////


int _tmain( int argc, _TCHAR* argv[] )
{
	if( argc > 2 )
		g_rounds = _ttoi( argv[1] );

	if( argc >= 3 )
	{
		g_event_count = _ttoi( argv[2] );
		if( g_event_count > MAXIMUM_WAIT_OBJECTS )
			g_event_count = MAXIMUM_WAIT_OBJECTS;
	}

	_tprintf( _T("Test Rounds: %d,	Number of Events (Conditions): %d\n"), g_rounds, g_event_count );

	for( DWORD i = 0; i < g_event_count; ++i )
	{
		g_mc1.AddCondition( FALSE );
		g_mc2.AddCondition( FALSE );
		g_me1.AddEvent( FALSE );
		g_me2.AddEvent( FALSE );
	}

	{
		uintptr_t h = _beginthreadex( NULL, 0, mcthread1, NULL, 0, NULL );
		CloseHandle( reinterpret_cast<HANDLE>( h ) );
		h = _beginthreadex( NULL, 0, mcthread2, NULL, 0, NULL );
		WaitForSingleObject( (HANDLE)h, INFINITE );
		CloseHandle( reinterpret_cast<HANDLE>( h ) );
	}

	{
		uintptr_t h = _beginthreadex( NULL, 0, methread1, NULL, 0, NULL );
		CloseHandle( reinterpret_cast<HANDLE>( h ) );
		h = _beginthreadex( NULL, 0, methread2, NULL, 0, NULL );
		WaitForSingleObject( (HANDLE)h, INFINITE );
		CloseHandle( reinterpret_cast<HANDLE>( h ) );
	}

	_tprintf( _T("multiple condition is %f times faster than multiple event\n"), g_me_tick * 1.0 / g_mc_tick );
	return 0;
}


////////////////////////////////////////////////////////////////////////////////
