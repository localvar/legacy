#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <process.h>

////////////////////////////////////////////////////////////////////////////////


class CCriSec : CRITICAL_SECTION
{
public:
	CCriSec()
	{
        _tprintf( _T("CCriSec::Constructor: Before Sleep\n") );
		Sleep( 1000 );
		InitializeCriticalSection( this );
        _tprintf( _T("CCriSec::Constructor: After Sleep\n") );
	}

	~CCriSec() { DeleteCriticalSection( this ); }
	void Enter()
	{
		_tprintf( _T("Enter Critical Section\n") );
		EnterCriticalSection( this );
	}
	void Leave() { LeaveCriticalSection( this ); }
};


////////////////////////////////////////////////////////////////////////////////


class CSingleton
{
public:
    CSingleton()
    {
        _tprintf( _T("CSingleton::Constructor: Before Sleep\n") );
        Sleep( 1000 );
        _tprintf( _T("CSingleton::Constructor: After Sleep\n") );
    }
    void DoSomeThing()
    {
        _tprintf( _T("CSingleton::DoSomeThing\n") );
    }


	// implementation one
	static CSingleton* GetInstance1()
	{
		static CSingleton* p = NULL;
		if( p == NULL )
			p = new CSingleton();
		return p;
	}


	// implementation two
	static CSingleton* GetInstance2()
	{
		static CSingleton* p = NULL;
		static CCriSec lock;

		lock.Enter();
		if( p == NULL )
			p = new CSingleton();
		lock.Leave();

		return p;
	}


	// implementation three
	static CSingleton* GetInstance3()
	{
		static CSingleton* p = NULL;
		static volatile long lock = 0;

		if( InterlockedCompareExchange( &lock, 1, 0 ) == 0 )
			p = new CSingleton();

		return p;
	}
};


////////////////////////////////////////////////////////////////////////////////


unsigned __stdcall thread( void* )
{
	CSingleton* p = CSingleton::GetInstance1();
    p->DoSomeThing();
    return 0;
}


////////////////////////////////////////////////////////////////////////////////


int _tmain( int argc, _TCHAR* argv[] )
{
    for( int i = 0; i < 3; ++i )
    {
        uintptr_t t = _beginthreadex( NULL, 0, thread, NULL, 0, NULL );
        CloseHandle( (HANDLE)t );
    }

	_getch();
    return 0;
}


////////////////////////////////////////////////////////////////////////////////






































/*




	// implementation four
	static CSingleton* GetInstance4()
	{
		static CSingleton* p = NULL;
		static volatile long lock = 0;

		if( InterlockedCompareExchange( &lock, 1, 0 ) != 0 )
		{
			while( lock != 2 )
				Sleep( 0 );
			return p;
		}

		p = new CSingleton();
		lock = 2;
		return p;
	}


*/
////////////////////////////////////////////////////////////////////////////////
