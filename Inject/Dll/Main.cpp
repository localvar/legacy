#include "stdafx.h"
#include "resource.h"

DWORD ThreadMain(HINSTANCE hInst)
{
	TCHAR szModule[256], szText[512], szFormat[256];
	LoadString(hInst, IDS_FORMAT, szFormat, sizeof(szFormat) / sizeof(TCHAR));
	GetModuleFileName(NULL, szModule, 256);
	_stprintf(szText, szFormat, szModule);
	MessageBox(NULL, szText, _T("Ô¶³ÌÏß³Ì"), MB_OK|MB_ICONINFORMATION);
	return 0;
}