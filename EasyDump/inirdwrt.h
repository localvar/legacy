////////////////////////////////////////////////////////////////////////////////
// 读写ini文件, 允许Section重名, 但不允许Key重名. 如果通过CIniFile操作有重名的
// Section可能会有错误, 因为不能保证到底操作的是哪一个. 此时应逐个枚举Section,
// 找到需要的Section后, 再操作它. 每个Key的Value在内部都用字符串表示, 最大Value
// 长度约为2000, 一般这足够使用了. 对于超长的Value, 内部实现是直接截断的.
// 要注意binary类型的Value, 内部转换时膨胀的很厉害, 一个字节会变成两个字符.

#pragma once

////////////////////////////////////////////////////////////////////////////////

class CIniKey
{
protected:
	TCHAR m_szName[16];
	TCHAR m_szValue[16];
	LPTSTR m_pValue;

public:
	explicit CIniKey( LPCTSTR szName );
	~CIniKey();

	LPCTSTR GetName();

	LPCTSTR GetValueString();
	int GetValueInt();
	bool GetValueBool();
	void GetValueBinary( BYTE* bin, size_t* pLen );

	void SetValueString( LPCTSTR str );
	void SetValueInt( int n );
	void SetValueBool( bool b );
	void SetValueBinary( const BYTE* bin, size_t len );
};

////////////////////////////////////////////////////////////////////////////////

class CIniSection
{
protected:
	TCHAR m_szName[16];
	CIniKey** m_arrKey;
	size_t m_capacity;

protected:
	void EnsureCapacity( size_t capacity );
	CIniKey* AddKey( LPCTSTR szKey );

public:
	explicit CIniSection( LPCTSTR szName );
	~CIniSection();

	LPCTSTR GetName();

	CIniKey* FindKey( LPCTSTR szKey );
	CIniKey* GetKey( LPCTSTR szKey );
	void RemoveKey( LPCTSTR szKey );

	size_t GetFirstKeyPosition();
	CIniKey* GetNextKey( size_t& pos );

	LPCTSTR GetValueString( LPCTSTR szKey, LPCTSTR szDflt );
	int GetValueInt( LPCTSTR szKey, int nDflt );
	bool GetValueBool( LPCTSTR szKey, bool bDflt );
	void GetValueBinary( LPCTSTR szKey, BYTE* bin, size_t* pLen );

	void SetValueString( LPCTSTR szKey, LPCTSTR str );
	void SetValueInt( LPCTSTR szKey, int n );
	void SetValueBool( LPCTSTR szKey, bool b );
	void SetValueBinary( LPCTSTR szKey, const BYTE* bin, size_t len );
};

////////////////////////////////////////////////////////////////////////////////

class CIniFile
{
protected:
	CIniSection** m_arrSection;
	size_t m_capacity;

protected:
	LPTSTR GetNextLine( FILE* fp, LPTSTR buf, int size );
	void EnsureCapacity( size_t capacity );

public:
	CIniFile();
	~CIniFile();
	bool Open( LPCTSTR szPath );
	bool OpenDefault();
	bool Save( LPCTSTR szPath );
	bool SaveToDefault();
	void Clear();

	CIniSection* FindSection( LPCTSTR szSctn );
	CIniSection* AddSection( LPCTSTR szSctn );
	CIniSection* GetSection( LPCTSTR szSctn );
	void RemoveSection( LPCTSTR szSctn );
	void RemoveSection( CIniSection* pSctn );

	size_t GetFirstSectionPosition();
	CIniSection* GetNextSection( size_t& pos );

	CIniKey* FindKey( LPCTSTR szSctn, LPCTSTR szKey );
	CIniKey* GetKey( LPCTSTR szSctn, LPCTSTR szKey );
	void RemoveKey( LPCTSTR szSctn, LPCTSTR szKey );

	LPCTSTR GetValueString( LPCTSTR szSctn, LPCTSTR szKey, LPCTSTR szDflt );
	int GetValueInt( LPCTSTR szSctn, LPCTSTR szKey, int nDflt );
	bool GetValueBool( LPCTSTR szSctn, LPCTSTR szKey, bool bDflt );
	void GetValueBinary( LPCTSTR szSctn, LPCTSTR szKey, BYTE* bin, size_t* pLen );

	void SetValueString( LPCTSTR szSctn, LPCTSTR szKey, LPCTSTR str );
	void SetValueInt( LPCTSTR szSctn, LPCTSTR szKey, int n );
	void SetValueBool( LPCTSTR szSctn, LPCTSTR szKey, bool b );
	void SetValueBinary( LPCTSTR szSctn, LPCTSTR szKey, const BYTE* bin, size_t len );
};

////////////////////////////////////////////////////////////////////////////////