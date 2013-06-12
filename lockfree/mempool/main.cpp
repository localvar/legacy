#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <process.h>


////////////////////////////////////////////////////////////////////////////////


int mp_register_usage( size_t size, size_t count );
bool mp_create();
void mp_destory();
void* mp_alloc( int objtype );
void mp_free( int objtype, void* mem );


////////////////////////////////////////////////////////////////////////////////


template<size_t size>
class CSomeObject
{
private:
	static int s_objtype;

private:
	char m_data[size];

public:
	CSomeObject() {}
	void DoSomeThing()
	{
		_tprintf( _T("Object Type = %d, Object Size = %d\n"), s_objtype, size );
	}
	~CSomeObject() {}

public:
	static void RegisterMemoryUsage( size_t count )
	{
		s_objtype = mp_register_usage( sizeof(CSomeObject<size>), count );
	}
	static void* operator new( size_t size )
	{
		return mp_alloc( s_objtype );
	}
	static void operator delete( void* mem )
	{
		mp_free( s_objtype, mem );
	}
};


template<size_t size> int CSomeObject<size>::s_objtype = 0;


////////////////////////////////////////////////////////////////////////////////


HANDLE g_stopevent = NULL;

#define TEST_OBJECT( c, s ) \
	case c:\
	{\
		CSomeObject<s>* p = new CSomeObject<s>;\
		if( p != NULL )\
		{\
			p->DoSomeThing();\
			delete p;\
		}\
	}\
	break;


uintptr_t __stdcall worker_thread( void* )
{
	srand( GetTickCount() );

	while( WaitForSingleObject( g_stopevent, 0 ) == WAIT_TIMEOUT )
	{
		switch( rand() % 7 )
		{
			TEST_OBJECT( 0, 1 )
			TEST_OBJECT( 1, 9 )
			TEST_OBJECT( 2, 10 )
			TEST_OBJECT( 3, 20 )
			TEST_OBJECT( 4, 36 )
			TEST_OBJECT( 5, 100 )
			TEST_OBJECT( 6, 1000 )
		}
	}

	return 0;
}


////////////////////////////////////////////////////////////////////////////////


int _tmain( int argc, _TCHAR* argv[] )
{
	CSomeObject<1>::RegisterMemoryUsage( 100 );
	CSomeObject<9>::RegisterMemoryUsage( 2 );
	CSomeObject<10>::RegisterMemoryUsage( 100 );
	CSomeObject<20>::RegisterMemoryUsage( 200 );
	CSomeObject<36>::RegisterMemoryUsage( 300 );
	CSomeObject<100>::RegisterMemoryUsage( 205 );
	CSomeObject<1000>::RegisterMemoryUsage( 128 );

	mp_create();

	g_stopevent = CreateEvent( NULL, TRUE, FALSE, NULL );
	for( int i = 0; i < 10; ++i )
	{
		uintptr_t h = _beginthreadex( NULL, 0, worker_thread, NULL, 0, NULL );
		CloseHandle( reinterpret_cast<HANDLE>( h ) );
	}

	_getch();

	SetEvent( g_stopevent );
	Sleep( 500 );
	CloseHandle( g_stopevent );
	mp_destory();

	return 0;
}


////////////////////////////////////////////////////////////////////////////////