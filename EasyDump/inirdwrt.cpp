#include "stdafx.h"
#include "inirdwrt.h"


////////////////////////////////////////////////////////////////////////////////


CIniKey::CIniKey( LPCTSTR szName )
{
	_tcsncpy( m_szName, szName, _countof(m_szName) );
	m_szName[_countof(m_szName) - 1] = 0;
	m_szValue[0] = 0;
	m_pValue = m_szValue;
}

//------------------------------------------------------------------------------

CIniKey::~CIniKey()
{
	if( m_pValue != m_szValue )
		free( m_pValue );
}

//------------------------------------------------------------------------------

LPCTSTR CIniKey::GetName()
{
	return m_szName;
}

//------------------------------------------------------------------------------

LPCTSTR CIniKey::GetValueString()
{
	return m_pValue;
}

//------------------------------------------------------------------------------

int CIniKey::GetValueInt()
{
	return _tcstol( m_pValue, NULL, 0 );
}

//------------------------------------------------------------------------------

bool CIniKey::GetValueBool()
{
	return (_tcsicmp( m_pValue, _T("true") ) == 0);
}

//------------------------------------------------------------------------------

void CIniKey::GetValueBinary( BYTE* bin, size_t* pLen )
{
	size_t len = _tcslen( m_pValue );
	len /= 2;
	len *= 2;

	if( *pLen < len / 2 )
		len = *pLen * 2;
	for( size_t i = 0; i < len; i += 2 )
	{
		BYTE c1 = static_cast<BYTE>( m_pValue[i] );
		BYTE c2 = static_cast<BYTE>( m_pValue[i + 1] );
		bin[i / 2] = ((c1 - 'A') << 4) | (c2 - 'A');
	}
	*pLen = len / 2;
}

//------------------------------------------------------------------------------

void CIniKey::SetValueString( LPCTSTR str )
{
	if( m_pValue != m_szValue )
	{
		free( m_pValue );
		m_pValue = m_szValue;
	}
	size_t len = _tcslen( str ) + 1;
	if( len > _countof(m_szValue) )
	{
		void* buf = malloc( len * sizeof(TCHAR) );
		_ASSERTE( buf != NULL );
		m_pValue = reinterpret_cast<LPTSTR>( buf );
	}
	_tcscpy( m_pValue, str );
}

//------------------------------------------------------------------------------

void CIniKey::SetValueInt( int n )
{
	TCHAR buf[16];
	SetValueString( _itot( n, buf, 10 ) );
}

//------------------------------------------------------------------------------

void CIniKey::SetValueBool( bool b )
{
	SetValueString( b ? _T("true") : _T("false") );
}

//------------------------------------------------------------------------------

void CIniKey::SetValueBinary( const BYTE* bin, size_t len )
{
	if( m_pValue != m_szValue )
	{
		free( m_pValue );
		m_pValue = m_szValue;
	}

	if( len * 2 + 1 > _countof(m_szValue) )
	{
		void* buf = malloc( (len * 2 + 1) * sizeof(TCHAR) );
		_ASSERTE( buf != NULL );
		m_pValue = reinterpret_cast<LPTSTR>( buf );
	}

	for( size_t i = 0; i < len; ++i )
	{
		BYTE c = bin[i];
		m_pValue[i * 2] = ((c & 0xf0) >> 4) + 'A';
		m_pValue[i * 2 + 1] = (c & 0x0f) + 'A';
	}

	m_pValue[len * 2] = 0;
}


////////////////////////////////////////////////////////////////////////////////


CIniSection::CIniSection( LPCTSTR szName )
{
	_tcsncpy( m_szName, szName, _countof(m_szName) );
	m_szName[_countof(m_szName) - 1] = 0;
	m_capacity = 0;
	m_arrKey = NULL;
	EnsureCapacity( 16 );
}

//------------------------------------------------------------------------------

CIniSection::~CIniSection()
{
	for( size_t i = 0; i < m_capacity; ++i )
		if( m_arrKey[i] != NULL )
			delete m_arrKey[i];
	free( m_arrKey );
}

//------------------------------------------------------------------------------

LPCTSTR CIniSection::GetName()
{
	return m_szName;
}

//------------------------------------------------------------------------------

void CIniSection::EnsureCapacity( size_t capacity )
{
	_ASSERTE( capacity > m_capacity );
	void* buf = realloc( m_arrKey, capacity * sizeof(CIniKey*) );
	_ASSERTE( buf != NULL );
	m_arrKey = reinterpret_cast<CIniKey**>( buf );
	for( ; m_capacity < capacity; ++m_capacity )
		m_arrKey[m_capacity] = NULL;
}

//------------------------------------------------------------------------------

CIniKey* CIniSection::FindKey( LPCTSTR szKey )
{
	for( size_t pos = 0; pos < m_capacity; ++pos )
	{
		CIniKey* key = m_arrKey[pos];
		if( (key != NULL) && (_tcsicmp( key->GetName(), szKey ) == 0) )
			return key;
	}
	return NULL;
}

//------------------------------------------------------------------------------

CIniKey* CIniSection::AddKey( LPCTSTR szKey )
{
	CIniKey* key = new CIniKey( szKey );
	_ASSERTE( key != NULL );
	for( size_t i = 0; i < m_capacity; ++i )
	{
		if( m_arrKey[i] == NULL )
		{
			m_arrKey[i] = key;
			return key;
		}
	}

	size_t pos = m_capacity;
	EnsureCapacity( m_capacity + 16 );
	m_arrKey[pos] = key;

	return key;
}

//------------------------------------------------------------------------------

CIniKey* CIniSection::GetKey( LPCTSTR szKey )
{
	CIniKey* key = FindKey( szKey );
	if( key == NULL )
		key = AddKey( szKey );
	return key;
}

//------------------------------------------------------------------------------

void CIniSection::RemoveKey( LPCTSTR szKey )
{
	for( size_t pos = 0; pos < m_capacity; ++pos )
	{
		CIniKey* key = m_arrKey[pos];
		if( (key != NULL) && (_tcsicmp( key->GetName(), szKey ) == 0) )
		{
			m_arrKey[pos] = NULL;
			delete key;
			break;
		}
	}
}

//------------------------------------------------------------------------------

size_t CIniSection::GetFirstKeyPosition()
{
	for( size_t pos = 0; pos < m_capacity; ++pos )
		if( m_arrKey[pos] != NULL )
			return pos;
	return 0xffffffff;
}

//------------------------------------------------------------------------------

CIniKey* CIniSection::GetNextKey( size_t& pos )
{
	CIniKey* ret = m_arrKey[pos];
	for( ++pos; pos < m_capacity; ++pos )
		if( m_arrKey[pos] != NULL )
			break;
	if( pos == m_capacity )
		pos = 0xffffffff;
	return ret;
}

//------------------------------------------------------------------------------

LPCTSTR CIniSection::GetValueString( LPCTSTR szKey, LPCTSTR szDflt )
{
	CIniKey* key = FindKey( szKey );
	if( key != NULL )
		return key->GetValueString();
	return szDflt;
}

//------------------------------------------------------------------------------

int CIniSection::GetValueInt( LPCTSTR szKey, int nDflt )
{
	CIniKey* key = FindKey( szKey );
	if( key != NULL )
		return key->GetValueInt();
	return nDflt;
}

//------------------------------------------------------------------------------

bool CIniSection::GetValueBool( LPCTSTR szKey, bool bDflt )
{
	CIniKey* key = FindKey( szKey );
	if( key != NULL )
		return key->GetValueBool();
	return bDflt;
}

//------------------------------------------------------------------------------

void CIniSection::GetValueBinary( LPCTSTR szKey, BYTE* bin, size_t* pLen )
{
	CIniKey* key = FindKey( szKey );
	if( key != NULL )
		key->GetValueBinary( bin, pLen );
}

//------------------------------------------------------------------------------

void CIniSection::SetValueString( LPCTSTR szKey, LPCTSTR str )
{
	GetKey( szKey )->SetValueString( str );
}

//------------------------------------------------------------------------------

void CIniSection::SetValueInt( LPCTSTR szKey, int n )
{
	GetKey( szKey )->SetValueInt( n );
}

//------------------------------------------------------------------------------

void CIniSection::SetValueBool( LPCTSTR szKey, bool b )
{
	GetKey( szKey )->SetValueBool( b );
}

//------------------------------------------------------------------------------

void CIniSection::SetValueBinary( LPCTSTR szKey, const BYTE* bin, size_t len )
{
	GetKey( szKey )->SetValueBinary( bin, len );
}


////////////////////////////////////////////////////////////////////////////////


CIniFile::CIniFile()
{
	m_arrSection = NULL;
	m_capacity = 0;
	EnsureCapacity( 16 );
}

//------------------------------------------------------------------------------

CIniFile::~CIniFile()
{
	Clear();
}

//------------------------------------------------------------------------------

LPTSTR CIniFile::GetNextLine( FILE* fp, LPTSTR buf, int size )
{
	do{
		if( _fgetts( buf, size, fp ) == NULL )
			return NULL;
	} while( buf[0] == 0 || buf[0] == _T('#') );

	buf[size - 1] = 0;
	size = static_cast<int>( _tcslen( buf ) - 1 );
	if( buf[size] == _T('\n') )
		buf[size] = 0;

	return buf;
}

//------------------------------------------------------------------------------

bool CIniFile::Open( LPCTSTR szPath )
{
	TCHAR buf[2048];

	FILE* fp = _tfopen( szPath, _T("rt,ccs=UNICODE") );
	if( fp == NULL )
		return false;

	CIniSection* sctn = NULL;
	while( GetNextLine( fp, buf, _countof(buf) ) != NULL )
	{
		if( buf[0] == _T('[') )
		{
			TCHAR* p = buf + 1;
			while( (*p) != 0 )
			{
				if( (*p) != _T(']') )
				{
					++p;
					continue;
				}

				if( p - buf > 1 )
				{
					*p = 0;
					sctn = AddSection( buf + 1 );
				}
				break;
			}
		}
		else if( sctn != NULL )
		{
			TCHAR* v = buf;
			while( (*v) != 0 )
			{
				if( (*v) != _T('=') )
				{
					++v;
					continue;
				}

				if( v - buf > 0 )
				{
					*v = 0;
					sctn->SetValueString( buf, ++v );
				}

				break;
			}
		}
	}

	fclose( fp );

	return true;
}

//------------------------------------------------------------------------------

bool CIniFile::OpenDefault()
{
	TCHAR path[FILENAME_MAX];
	int len = GetModuleFileName( NULL, path, FILENAME_MAX );
	_tcscpy( path + len - 3, _T("ini") );
	return Open( path );
}

//------------------------------------------------------------------------------

bool CIniFile::Save( LPCTSTR szPath )
{
	FILE* fp = _tfopen( szPath, _T("wt,ccs=UNICODE") );
	if( fp == NULL )
		return false;

	for( size_t i = 0; i < m_capacity; ++i )
	{
		CIniSection* sctn = m_arrSection[i];
		if( sctn == NULL )
			continue;

		_ftprintf( fp, _T("[%s]\n"), sctn->GetName() );

		size_t pos = sctn->GetFirstKeyPosition();
		while( pos != 0xffffffff )
		{
			CIniKey* key = sctn->GetNextKey( pos );
			_ftprintf(fp, _T("%s=%s\n"), key->GetName(), key->GetValueString());
		}

		_ftprintf( fp, _T("\n") );
	}

	fclose( fp );
	return true;
}

//------------------------------------------------------------------------------

bool CIniFile::SaveToDefault()
{
	TCHAR path[FILENAME_MAX];
	int len = GetModuleFileName( NULL, path, FILENAME_MAX );
	_tcscpy( path + len - 3, _T("ini") );
	return Save( path );
}

//------------------------------------------------------------------------------

void CIniFile::Clear()
{
	for( size_t i = 0; i < m_capacity; ++i )
	{
		if( m_arrSection[i] != NULL )
		{
			delete m_arrSection[i];
			m_arrSection[i] = NULL;
		}
	}
	free( m_arrSection );
	m_arrSection = NULL;
	m_capacity = 0;
}

//------------------------------------------------------------------------------

void CIniFile::EnsureCapacity( size_t capacity )
{
	_ASSERTE( capacity > m_capacity );
	void* buf = realloc( m_arrSection, capacity * sizeof(CIniSection*) );
	_ASSERTE( buf != NULL );
	m_arrSection = reinterpret_cast<CIniSection**>( buf );
	for( ; m_capacity < capacity; ++m_capacity )
		m_arrSection[m_capacity] = NULL;
}

//------------------------------------------------------------------------------

CIniSection* CIniFile::FindSection( LPCTSTR szSctn )
{
	for( size_t pos = 0; pos < m_capacity; ++pos )
	{
		CIniSection* sctn = m_arrSection[pos];
		if( (sctn != NULL) && (_tcsicmp( sctn->GetName(), szSctn ) == 0) )
			return sctn;
	}
	return NULL;
}

//------------------------------------------------------------------------------

CIniSection* CIniFile::AddSection( LPCTSTR szSctn )
{
	CIniSection* sctn = new CIniSection( szSctn );
	_ASSERTE( sctn != NULL );
	for( size_t i = 0; i < m_capacity; ++i )
	{
		if( m_arrSection[i] == NULL )
		{
			m_arrSection[i] = sctn;
			return sctn;
		}
	}

	size_t pos = m_capacity;
	EnsureCapacity( m_capacity + 16 );
	m_arrSection[pos] = sctn;

	return sctn;
}

//------------------------------------------------------------------------------

CIniSection* CIniFile::GetSection( LPCTSTR szSctn )
{
	CIniSection* sctn = FindSection( szSctn );
	if( sctn == NULL )
		sctn = AddSection( szSctn );
	return sctn;
}

//------------------------------------------------------------------------------

void CIniFile::RemoveSection( LPCTSTR szSctn )
{
	for( size_t pos = 0; pos < m_capacity; ++pos )
	{
		CIniSection* sctn = m_arrSection[pos];
		if( (sctn != NULL) && (_tcsicmp( sctn->GetName(), szSctn ) == 0) )
		{
			m_arrSection[pos] = NULL;
			delete sctn;
			break;
		}
	}
}

//------------------------------------------------------------------------------

void CIniFile::RemoveSection( CIniSection* pSctn )
{
	size_t pos = 0;
	for( pos = 0; pos < m_capacity; ++pos )
	{
		if( m_arrSection[pos] == pSctn )
		{
			m_arrSection[pos] = NULL;
			delete pSctn;
			break;
		}
	}
	_ASSERTE( pos != m_capacity );
}

//------------------------------------------------------------------------------

size_t CIniFile::GetFirstSectionPosition()
{
	for( size_t pos = 0; pos < m_capacity; ++pos )
		if( m_arrSection[pos] != NULL )
			return pos;
	return 0xffffffff;
}

//------------------------------------------------------------------------------

CIniSection* CIniFile::GetNextSection( size_t& pos )
{
	CIniSection* ret = m_arrSection[pos];
	for( ++pos; pos < m_capacity; ++pos )
		if( m_arrSection[pos] != NULL )
			break;
	if( pos == m_capacity )
		pos = 0xffffffff;
	return ret;
}


//------------------------------------------------------------------------------

CIniKey* CIniFile::FindKey( LPCTSTR szSctn, LPCTSTR szKey )
{
	CIniSection* sctn = FindSection( szSctn );
	if( sctn != NULL )
		return sctn->FindKey( szKey );
	return NULL;
}

//------------------------------------------------------------------------------

CIniKey* CIniFile::GetKey( LPCTSTR szSctn, LPCTSTR szKey )
{
	return GetSection( szSctn )->GetKey( szKey );
}

//------------------------------------------------------------------------------

void CIniFile::RemoveKey( LPCTSTR szSctn, LPCTSTR szKey )
{
	CIniSection* sctn = FindSection( szSctn );
	if( sctn != NULL )
		return sctn->RemoveKey( szKey );
}

//------------------------------------------------------------------------------

LPCTSTR CIniFile::GetValueString( LPCTSTR szSctn, LPCTSTR szKey, LPCTSTR szDflt )
{
	CIniSection* sctn = FindSection( szSctn );
	if( sctn != NULL )
		return sctn->GetValueString( szKey, szDflt );
	return szDflt;
}

//------------------------------------------------------------------------------

int CIniFile::GetValueInt( LPCTSTR szSctn, LPCTSTR szKey, int nDflt )
{
	CIniSection* sctn = FindSection( szSctn );
	if( sctn != NULL )
		return sctn->GetValueInt( szKey, nDflt );
	return nDflt;
}

//------------------------------------------------------------------------------

bool CIniFile::GetValueBool( LPCTSTR szSctn, LPCTSTR szKey, bool bDflt )
{
	CIniSection* sctn = FindSection( szSctn );
	if( sctn != NULL )
		return sctn->GetValueBool( szKey, bDflt );
	return bDflt;
}

//------------------------------------------------------------------------------

void CIniFile::
GetValueBinary( LPCTSTR szSctn, LPCTSTR szKey, BYTE* bin, size_t* pLen )
{
	CIniSection* sctn = FindSection( szSctn );
	if( sctn != NULL )
		sctn->GetValueBinary( szKey, bin, pLen );
}

//------------------------------------------------------------------------------

void CIniFile::SetValueString( LPCTSTR szSctn, LPCTSTR szKey, LPCTSTR str )
{
	GetSection( szSctn )->SetValueString( szKey, str );
}

//------------------------------------------------------------------------------

void CIniFile::SetValueInt( LPCTSTR szSctn, LPCTSTR szKey, int n )
{
	GetSection( szSctn )->SetValueInt( szKey, n );
}

//------------------------------------------------------------------------------

void CIniFile::SetValueBool( LPCTSTR szSctn, LPCTSTR szKey, bool b )
{
	GetSection( szSctn )->SetValueBool( szKey, b );
}

//------------------------------------------------------------------------------

void CIniFile::
SetValueBinary( LPCTSTR szSctn, LPCTSTR szKey, const BYTE* bin, size_t len )
{
	GetSection( szSctn )->SetValueBinary( szKey, bin, len );
}


////////////////////////////////////////////////////////////////////////////////