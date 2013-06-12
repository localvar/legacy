#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <process.h>


////////////////////////////////////////////////////////////////////////////////


long InterlockedIncrementIfLessThan100( volatile long* addend )
{
	long old, xchg;

	do {
		old = *addend;
		if( old >= 100 )
			break;
		xchg = old + 1;
	} while( InterlockedCompareExchange( addend, xchg, old ) != old );

	return old;
}


////////////////////////////////////////////////////////////////////////////////


HANDLE g_stop_event = NULL;


////////////////////////////////////////////////////////////////////////////////


struct QueueItem
{
	volatile QueueItem* next;
	int data;
};


QueueItem* g_head = NULL;
QueueItem* g_tail = NULL;


//------------------------------------------------------------------------------


uintptr_t __stdcall queue_producer_thread( void* )
{
	int count = 0;

	while( WaitForSingleObject( g_stop_event, 10 ) == WAIT_TIMEOUT )
	{
		QueueItem* item = new QueueItem;
		item->next = NULL;
		item->data = count++;
		g_tail->next = item;
		g_tail = item;
	}

	return 0;
}


//------------------------------------------------------------------------------


uintptr_t __stdcall queue_consumer_thread( void* )
{
	while( WaitForSingleObject( g_stop_event, 10 ) == WAIT_TIMEOUT )
	{
		QueueItem* next = const_cast<QueueItem*>( g_head->next );
		while( next != NULL )
		{
			delete g_head;
			g_head = next;
			next = const_cast<QueueItem*>( g_head->next );
			_tprintf( _T("Consumer: object %d\n"), g_head->data );
		}
	}

	return 0;
}


////////////////////////////////////////////////////////////////////////////////


struct Foo
{
	volatile long ver;
	int i;
	short s;
	char c;
	long long ll;
	float f;
	double d;
};


Foo g_foo = { 0 };


//------------------------------------------------------------------------------


uintptr_t __stdcall producer_thread( void* )
{
	int count = 0;

	while( WaitForSingleObject( g_stop_event, 100 ) == WAIT_TIMEOUT )
	{
		++g_foo.ver; // acquire

		++g_foo.i;
		++g_foo.s;
		++g_foo.ll;
		g_foo.c += 2;
		g_foo.d += 1.5;

		++g_foo.ver; // release
	}

	return 0;
}


//------------------------------------------------------------------------------


uintptr_t __stdcall consumer_thread( void* )
{
	while( WaitForSingleObject( g_stop_event, 1 ) == WAIT_TIMEOUT )
	{
		long ver = g_foo.ver;
		if( ver & 0x00000001 )
			continue;
		Foo f = g_foo;
		if( ver != g_foo.ver )
			continue;

		if( g_foo.i * 2 != ver )
			_tprintf( _T("partly updated detected\n") );
	}

	return 0;
}


////////////////////////////////////////////////////////////////////////////////


int _tmain( int argc, _TCHAR* argv[] )
{
	g_stop_event = CreateEvent( NULL, TRUE, FALSE, NULL );

#if 0

	g_tail = new QueueItem;
	g_tail->next = NULL;
	g_tail->data = -1;
	g_head = g_tail;

	uintptr_t h = _beginthreadex( NULL, 0, queue_producer_thread, NULL, 0, NULL );
	CloseHandle( reinterpret_cast<HANDLE>( h ) );
	h = _beginthreadex( NULL, 0, queue_consumer_thread, NULL, 0, NULL );
	CloseHandle( reinterpret_cast<HANDLE>( h ) );

#else

	uintptr_t h = _beginthreadex( NULL, 0, producer_thread, NULL, 0, NULL );
	CloseHandle( reinterpret_cast<HANDLE>( h ) );

	for( int i = 0; i < 10; ++i )
	{
		uintptr_t h = _beginthreadex( NULL, 0, consumer_thread, NULL, 0, NULL );
		CloseHandle( reinterpret_cast<HANDLE>( h ) );
	}

#endif

	_getch();
	SetEvent( g_stop_event );
	Sleep( 500 );
	CloseHandle( g_stop_event );

	return 0;
}


////////////////////////////////////////////////////////////////////////////////