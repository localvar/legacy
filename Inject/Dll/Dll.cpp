#include "stdafx.h"
#include "..\ThreadParam.h"


BOOL LoadImportFx(LPBYTE pBase, FxLoadLibrary fnLoadLibrary, FxGetProcAddr fnGetProcAddr)
{
	PIMAGE_DOS_HEADER pidh = (PIMAGE_DOS_HEADER)pBase;
	PIMAGE_NT_HEADERS pinh = (PIMAGE_NT_HEADERS)(pBase + pidh->e_lfanew);
	PIMAGE_IMPORT_DESCRIPTOR piid = (PIMAGE_IMPORT_DESCRIPTOR)
		(pBase + pinh->OptionalHeader.DataDirectory[1].VirtualAddress);

	for(; piid->OriginalFirstThunk != 0; piid++)
	{
		HMODULE hDll = fnLoadLibrary((LPCSTR)(pBase + piid->Name));
		if(hDll == NULL)
			return FALSE;

		PIMAGE_THUNK_DATA pOrigin = (PIMAGE_THUNK_DATA)(pBase + piid->OriginalFirstThunk);
		PIMAGE_THUNK_DATA pFirst = (PIMAGE_THUNK_DATA)(pBase + piid->FirstThunk);

		LPCSTR pFxName = NULL;
		PIMAGE_IMPORT_BY_NAME piibn = NULL;

		for(; pOrigin->u1.Ordinal != 0; pOrigin++, pFirst++)
		{
			if(pOrigin->u1.Ordinal & IMAGE_ORDINAL_FLAG)
				pFxName = (LPCSTR)IMAGE_ORDINAL(pOrigin->u1.Ordinal);
			else
			{
				piibn = (PIMAGE_IMPORT_BY_NAME)(pBase + pOrigin->u1.AddressOfData);
				pFxName = (LPCSTR)piibn->Name;
			}
			pFirst->u1.Function = (DWORD)fnGetProcAddr(hDll, pFxName);
			if(pFirst->u1.Function == NULL)
				return FALSE;
		}
	}

	return TRUE;
}


extern DWORD ThreadMain(HINSTANCE hInst);

DWORD WINAPI ThreadEntry(PTHREADPARAM pParam)
{
	DWORD dwResult = -1;
	__try
	{
		if(LoadImportFx(pParam->pImageBase, pParam->fnLoadLibrary, pParam->fnGetProcAddr))
			dwResult = ThreadMain((HINSTANCE)pParam->pImageBase);
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		dwResult = -2;
	}
	return dwResult;
}
