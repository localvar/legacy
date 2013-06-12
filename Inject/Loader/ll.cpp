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
	HWND hWnd = FindWindow(NULL, _T("虚拟网关"));//*/_T("Progman"), _T("Program Manager"));
	GetWindowThreadProcessId(hWnd, &dwProcessId);
	return dwProcessId;
}


//map the dll's code and data in resource to memory
static LPBYTE MapRsrcToImage()
{
	HRSRC hRsrc = FindResource(NULL, _T("rtdll"), _T("RT_DLL"));
	HGLOBAL hGlobal = LoadResource(NULL, hRsrc);
	LPBYTE pRsrc = (LPBYTE)LockResource(hGlobal);
	_pinh = (PIMAGE_NT_HEADERS)(pRsrc + ((PIMAGE_DOS_HEADER)pRsrc)->e_lfanew);
	LPBYTE pImage = (LPBYTE)VirtualAlloc(NULL, IMAGE_SIZE, MEM_COMMIT, PAGE_READWRITE);
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
	LPTHREAD_START_ROUTINE pEntry = NULL;
	PTHREADPARAM pParam = NULL;
	LPBYTE pImage = (LPBYTE)MapRsrcToImage();							
	DWORD dwProcessId = GetTargetProcessId();							
	HANDLE hProcess = OpenProcess(PROCESS_OPEN_MODE, FALSE, dwProcessId);
	LPBYTE pInjectPos = (LPBYTE)VirtualAllocEx(hProcess, NULL, IMAGE_SIZE,
		MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	PrepareData(pImage, pInjectPos, (PVOID*)&pEntry, (PVOID*)&pParam);	
	WriteProcessMemory(hProcess, pInjectPos, pImage, IMAGE_SIZE, NULL);	
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, pEntry, pParam, 0, NULL);
	CloseHandle(hThread);									
	CloseHandle(hProcess);
	VirtualFree(pImage, 0, MEM_RELEASE);
	return 0;
}
