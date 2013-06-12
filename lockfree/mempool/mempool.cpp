#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#include <windows.h>


////////////////////////////////////////////////////////////////////////////////


#define MP_MAX_OBJECT_TYPE		8

struct MP_OBJECT_ENTRY
{
	SLIST_HEADER lsthdr;
	size_t size;
	size_t count;
};

static MP_OBJECT_ENTRY s_entries[MP_MAX_OBJECT_TYPE] = { 0 };
static void* s_base = NULL;


////////////////////////////////////////////////////////////////////////////////


int mp_register_usage( size_t size, size_t count )
{
	if( size == 0 || count == 0 )
		return -1;

	size += MEMORY_ALLOCATION_ALIGNMENT - 1;
	size /= MEMORY_ALLOCATION_ALIGNMENT;
	size *= MEMORY_ALLOCATION_ALIGNMENT;

	for( int i = 0; i < MP_MAX_OBJECT_TYPE; ++i )
	{
		MP_OBJECT_ENTRY* entry = s_entries + i;
		if( entry->size == size || entry->size == 0 )
		{
			entry->size = size;
			entry->count += count;
			return i;
		}
	}

	return -1;
}


//------------------------------------------------------------------------------


bool mp_create()
{
	size_t total = 0;
	for( int i = 0; i < MP_MAX_OBJECT_TYPE; ++i )
		total += s_entries[i].count * s_entries[i].size;

	s_base = VirtualAlloc( NULL, total, MEM_COMMIT, PAGE_READWRITE );
	if( s_base == NULL )
		return false;

	char* base = reinterpret_cast<char*>( s_base );
	for( int i = 0; i < MP_MAX_OBJECT_TYPE; ++i )
	{
		MP_OBJECT_ENTRY* entry = s_entries + i;
		InitializeSListHead( &entry->lsthdr );

		char* addr = base + entry->size * entry->count;
		addr -= MEMORY_ALLOCATION_ALIGNMENT;

		for( size_t j = 0; j < entry->count; ++j )
		{
			SLIST_ENTRY* node = reinterpret_cast<SLIST_ENTRY*>( addr );
			InterlockedPushEntrySList( &entry->lsthdr, node );
			addr -= entry->size;
		}

		base += entry->count * entry->size;
	}

	return true;
}


//------------------------------------------------------------------------------


void mp_destory()
{
	if( s_base != NULL )
	{
		VirtualFree( s_base, 0, MEM_RELEASE );
		s_base = NULL;
	}
}


//------------------------------------------------------------------------------


void* mp_alloc( int objtype )
{
	MP_OBJECT_ENTRY* entry = s_entries + objtype;
	SLIST_ENTRY* node = InterlockedPopEntrySList( &entry->lsthdr );
	char* p = reinterpret_cast<char*>( node );
	if( p != NULL )
		p -= entry->size - MEMORY_ALLOCATION_ALIGNMENT;

	return p;
}


//------------------------------------------------------------------------------


void mp_free( int objtype, void* mem )
{
	if( mem == NULL )
		return;

	MP_OBJECT_ENTRY* entry = s_entries + objtype;
	char* p = reinterpret_cast<char*>( mem );
	p += entry->size - MEMORY_ALLOCATION_ALIGNMENT;

	SLIST_ENTRY* node = reinterpret_cast<SLIST_ENTRY*>( p );
	InterlockedPushEntrySList( &s_entries[objtype].lsthdr, node );
}


////////////////////////////////////////////////////////////////////////////////