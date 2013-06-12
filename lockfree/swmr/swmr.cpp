#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <process.h>


////////////////////////////////////////////////////////////////////////////////


class CLiteSwmrl
{
private:
	enum { WRITING_FLAG  = 0x80000000, };
	volatile long m_lock;

public:
	CLiteSwmrl() : m_lock( 0 ) {}
	~CLiteSwmrl() {}

	void BeginRead()
	{
		while( true )
		{
			long old = m_lock;
			if( old & WRITING_FLAG )
			{
				SwitchToThread();
				continue;
			}

			long xchg = old + 1;
			if( InterlockedCompareExchange( &m_lock, xchg, old ) == old )
				break;
		}
	}

	void EndRead()
	{
		InterlockedDecrement( &m_lock );
	}

	void BeginWrite()
	{
		long old, xchg;
		do {
			old = m_lock;
			xchg = old | WRITING_FLAG;
		} while( InterlockedCompareExchange( &m_lock, xchg, old ) != old );

		// wait until all readers quit reading
		while( m_lock != WRITING_FLAG )
			SwitchToThread();
	}

	void EndWrite()
	{
		m_lock = 0;
	}
};


////////////////////////////////////////////////////////////////////////////////


class CSlimSwmrl
{
private:
	SRWLOCK m_lock;

public:
	CSlimSwmrl()
	{
		InitializeSRWLock( &m_lock );
	}

	~CSlimSwmrl() {}

	void BeginRead()
	{
		AcquireSRWLockShared( &m_lock );
	}

	void EndRead()
	{
		ReleaseSRWLockShared( &m_lock );
	}

	void BeginWrite()
	{
		AcquireSRWLockExclusive( &m_lock );
	}

	void EndWrite()
	{
		ReleaseSRWLockExclusive( &m_lock );
	}
};



////////////////////////////////////////////////////////////////////////////////


class CFakeSwmrl
{
public:
	CFakeSwmrl() {}
	~CFakeSwmrl() {}
	void BeginRead() {}
	void EndRead() {}
	void BeginWrite() {}
	void EndWrite() {}
};



////////////////////////////////////////////////////////////////////////////////

#pragma optimize( "", off )

void delay( unsigned count )
{
	for( unsigned i = 0; i < count; ++i )
	{
	}
}

#pragma optimize( "", on )

////////////////////////////////////////////////////////////////////////////////


volatile long g_num_conflict = 0;


////////////////////////////////////////////////////////////////////////////////


class CTinyObject
{
private:
	 CLiteSwmrl m_lock;
	//CSlimSwmrl m_lock;
	//CFakeSwmrl m_lock;
	int m_a;
	int m_b;

public:
	CTinyObject() : m_a( 0 ), m_b( 0 ) {}
	~CTinyObject() {}

	void DisplayIfNotEqual()
	{
		delay( 19000 );

		m_lock.BeginRead();
		int a = m_a;
		delay( 1000 );
		int b = m_b;
		m_lock.EndRead();

		if( a != b )
			InterlockedIncrement( &g_num_conflict );
	}

	void Update()
	{
		delay( 19000 );
		m_lock.BeginWrite();
		++m_a;
		delay( 1000 );
		++m_b;
		m_lock.EndWrite();
	}
};


////////////////////////////////////////////////////////////////////////////////

#define MAX_TINY_OBJECT		10
CTinyObject* g_objects = NULL;

////////////////////////////////////////////////////////////////////////////////


uintptr_t __stdcall reader_thread( void* )
{
	srand( GetTickCount() );

	while( true )
	{
		int idx = rand() % MAX_TINY_OBJECT;
		g_objects[idx].DisplayIfNotEqual();
	}

	return 0;
}


////////////////////////////////////////////////////////////////////////////////


uintptr_t __stdcall writer_thread( void* )
{
	srand( GetTickCount() );

	while( true )
	{
		int idx = rand() % MAX_TINY_OBJECT;
		g_objects[idx].Update();
	}

	return 0;
}


////////////////////////////////////////////////////////////////////////////////


int _tmain( int argc, _TCHAR* argv[] )
{
	g_objects = new CTinyObject[MAX_TINY_OBJECT];

	for( int i = 0; i < 1; ++i )
	{
		uintptr_t h = _beginthreadex( NULL, 0, writer_thread, NULL, 0, NULL );
		Sleep( 1 );
		CloseHandle( reinterpret_cast<HANDLE>( h ) );
	}

	for( int i = 0; i < 10; ++i )
	{
		uintptr_t h = _beginthreadex( NULL, 0, reader_thread, NULL, 0, NULL );
		Sleep( 1 );
		CloseHandle( reinterpret_cast<HANDLE>( h ) );
	}

	DWORD tick = GetTickCount();

	while( !_kbhit() )
	{
		Sleep( 1000 );
		DWORD now = GetTickCount();
		long nc = InterlockedExchange( &g_num_conflict, 0 );
		_tprintf( _T("%d conflicts in last %d ms\n"), nc, now - tick );
		tick = now;
	}

	delete[] g_objects;
	return 0;
}


////////////////////////////////////////////////////////////////////////////////