#pragma once

typedef HMODULE (WINAPI *FxLoadLibrary)(LPCSTR lpFileName);
typedef FARPROC (WINAPI *FxGetProcAddr)(HMODULE hModule, LPCSTR lpProcName);

typedef struct tagTHREADPARAM
{
	FxLoadLibrary fnLoadLibrary;
	FxGetProcAddr fnGetProcAddr;
	LPBYTE pImageBase;
}THREADPARAM, *PTHREADPARAM;
