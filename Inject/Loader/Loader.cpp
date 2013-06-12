#include "stdafx.h"
#include "..\ThreadParam.h"

// 全局变量：
static TCHAR _szTitle[] = _T("远程线程装载器");			// 标题栏文本
static PIMAGE_NT_HEADERS _pinh;

#define IMAGE_SIZE			(_pinh->OptionalHeader.SizeOfImage)
#define RVA_EXPORT_TABEL	(_pinh->OptionalHeader.DataDirectory[0].VirtualAddress)
#define RVA_RELOC_TABEL		(_pinh->OptionalHeader.DataDirectory[5].VirtualAddress)
#define PROCESS_OPEN_MODE   (PROCESS_CREATE_THREAD|PROCESS_VM_WRITE|PROCESS_VM_OPERATION)

//get the process id of the target process
//here, we aimed at "explorer.exe"
static DWORD GetTargetProcessId()
{
	DWORD dwProcessId = 0;
	HWND hWnd = FindWindow(_T("Progman"), _T("Program Manager"));
	if(hWnd != NULL)
		GetWindowThreadProcessId(hWnd, &dwProcessId);
	return dwProcessId;
}


//map the dll's code and data in resource to memory
static LPBYTE MapRsrcToImage()
{
	HRSRC hRsrc = FindResource(NULL, _T("rtdll"), _T("RT_DLL"));
	if(hRsrc == NULL)
		return NULL;
	HGLOBAL hGlobal = LoadResource(NULL, hRsrc);
	if(hGlobal == NULL)
		return NULL;
	LPBYTE pRsrc = (LPBYTE)LockResource(hGlobal);
	if(pRsrc == NULL)
		return NULL;

	_pinh = (PIMAGE_NT_HEADERS)(pRsrc + ((PIMAGE_DOS_HEADER)pRsrc)->e_lfanew);
	LPBYTE pImage = (LPBYTE)VirtualAlloc(NULL, IMAGE_SIZE, MEM_COMMIT, PAGE_READWRITE);

	if(pImage != NULL)
	{
		DWORD dwSections = _pinh->FileHeader.NumberOfSections;

		DWORD dwBytes2Copy = (((LPBYTE)_pinh) - pRsrc) + sizeof(IMAGE_NT_HEADERS);
		PIMAGE_SECTION_HEADER pish = (PIMAGE_SECTION_HEADER)(pRsrc + dwBytes2Copy);
		dwBytes2Copy += dwSections * sizeof(IMAGE_SECTION_HEADER);
		memcpy(pImage, pRsrc, dwBytes2Copy);

		for(DWORD i=0; i<dwSections; i++, pish++)
		{
			LPBYTE pSrc = pRsrc + pish->PointerToRawData;
			LPBYTE pDest = pImage + pish->VirtualAddress;
			dwBytes2Copy = pish->SizeOfRawData;
			memcpy(pDest, pSrc, dwBytes2Copy);
		}

		_pinh = (PIMAGE_NT_HEADERS)(pImage + ((PIMAGE_DOS_HEADER)pImage)->e_lfanew);
	}

	return pImage;
}

//get the rva of the entry of the exported function "ThreadEntry"
static DWORD GetEntryPoint(LPBYTE pImage)
{
	DWORD dwEntry = 0, index = 0;
	IMAGE_EXPORT_DIRECTORY* pied = (IMAGE_EXPORT_DIRECTORY*)(pImage + RVA_EXPORT_TABEL);
	DWORD* pNameTbl = (DWORD*)(pImage + pied->AddressOfNames);
	for(index=0; index<pied->NumberOfNames; index++, pNameTbl++)
	{
		if(strcmp("ThreadEntry", (char*)(pImage + (*pNameTbl))) == 0)
		{
			index = ((WORD*)(pImage + pied->AddressOfNameOrdinals))[index];
			dwEntry = ((DWORD*)(pImage + pied->AddressOfFunctions))[index];
			break;
		}
	}
	return dwEntry;
}

//relocate the image
static void RelocImage(PBYTE pImage, PBYTE pRelocTbl, DWORD dwRelocOffset)
{
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


static void PrepareData(LPBYTE pImage, LPBYTE pInjectPos, PVOID* ppEntry, PVOID* ppParam)
{
	LPBYTE pRelocTbl = pImage + RVA_RELOC_TABEL;
	DWORD dwRelocOffset = (DWORD)pInjectPos - _pinh->OptionalHeader.ImageBase;
	RelocImage(pImage, pRelocTbl, dwRelocOffset);

	PTHREADPARAM param = (PTHREADPARAM)pRelocTbl;
	HMODULE hKernel32 = GetModuleHandle(_T("kernel32.dll"));
	param->fnGetProcAddr = (FxGetProcAddr)GetProcAddress(hKernel32, "GetProcAddress");
	param->fnLoadLibrary = (FxLoadLibrary)GetProcAddress(hKernel32, "LoadLibraryA");
	param->pImageBase = pInjectPos;

	*ppEntry = pInjectPos + GetEntryPoint(pImage);
	*ppParam = pInjectPos + RVA_RELOC_TABEL;
}



int APIENTRY _tWinMain(HINSTANCE hInst, HINSTANCE, LPTSTR lpCmdLine, int nCmdShow)
{
	LPBYTE pImage = NULL, pInjectPos = NULL;
	HANDLE hProcess = NULL, hThread = NULL;
	DWORD dwProcessId = 0;
	LPTHREAD_START_ROUTINE pEntry = NULL;
	PTHREADPARAM pParam = NULL;
	BOOL bOk = FALSE;

	__try
	{
		if((pImage = (LPBYTE)MapRsrcToImage()) == NULL)
			__leave;
		if((dwProcessId = GetTargetProcessId()) == 0)
			__leave;
		if((hProcess = OpenProcess(PROCESS_OPEN_MODE, FALSE, dwProcessId)) == NULL)
			__leave;
		if((pInjectPos = (LPBYTE)VirtualAllocEx(hProcess, NULL, IMAGE_SIZE, 
					MEM_COMMIT, PAGE_EXECUTE_READWRITE)) == NULL)
			__leave;
		PrepareData(pImage, pInjectPos, (PVOID*)&pEntry, (PVOID*)&pParam);
		if(!WriteProcessMemory(hProcess, pInjectPos, pImage, IMAGE_SIZE, NULL))
			__leave;
		hThread = CreateRemoteThread(hProcess, NULL, 0, pEntry, pParam, 0, NULL);
		if(hThread == NULL)
			__leave;
		bOk = TRUE;
	}
	__finally
	{
		if(!bOk && pInjectPos != NULL)
			VirtualFreeEx(hProcess, pInjectPos, 0, MEM_RELEASE);
		if(hThread != NULL)
			CloseHandle(hThread);
		if(hProcess != NULL)
			CloseHandle(hProcess);
		if(pImage != NULL)
			VirtualFree(pImage, 0, MEM_RELEASE);
	}

	
	if(bOk)
		MessageBox(NULL, _T("线程插入成功！"), _szTitle, MB_OK | MB_ICONINFORMATION);
	else
		MessageBox(NULL, _T("线程插入失败！"), _szTitle, MB_OK | MB_ICONINFORMATION);

	return 0;
}