// Victim.cpp : 定义应用程序的入口点。
//

#define WIN32_LEAN_AND_MEAN		// 从 Windows 头中排除极少使用的资料
// Windows 头文件:
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <Winsock2.h>
#include "resource.h"


#ifdef UNICODE
#error to use unicode, you must also modify the attacker code, or the demo will fail
#endif


#define WM_CLIENT_CONNECT (WM_USER+200)
#define WM_RECV_MSG (WM_USER+201)

HINSTANCE g_hInst = NULL;
SOCKET g_sckListen = INVALID_SOCKET, g_sckClnt = INVALID_SOCKET;


LRESULT CALLBACK MainDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL OnInitDialog(HWND hDlg);
DWORD FindJmpEsp(HINSTANCE hInst);
void GetAddress(HWND hDlg);
BOOL InitNetwork(HWND hDlg);
void OnClientConnect(HWND hDlg);
void OnRecvComputerName(HWND hDlg);
void RecvComputerName(LPTSTR szComputer);


int APIENTRY _tWinMain(HINSTANCE hInst, HINSTANCE, LPTSTR, int)
{
	g_hInst = hInst;

	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	DialogBox(hInst, MAKEINTRESOURCE(IDD_MAIN), NULL, (DLGPROC)MainDlgProc);

	WSACleanup();

	return 0;
}



LRESULT CALLBACK MainDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	switch(message)
	{
	case WM_INITDIALOG:
		result = OnInitDialog(hDlg);
		break;

	case WM_COMMAND:
		if(LOWORD(wParam) == IDCANCEL)
		{
			if(g_sckClnt != INVALID_SOCKET)
			{
				closesocket(g_sckClnt);
				g_sckClnt = INVALID_SOCKET;
			}
			if(g_sckListen != INVALID_SOCKET)
			{
				closesocket(g_sckListen);
				g_sckListen = INVALID_SOCKET;
			}
			EndDialog(hDlg, IDCANCEL);
		}
		break;

	case WM_CLIENT_CONNECT:
		OnClientConnect(hDlg);
		break;

	case WM_RECV_MSG:
		OnRecvComputerName(hDlg);
		break;
	}

	return result;
}



BOOL OnInitDialog(HWND hDlg)
{
	GetAddress(hDlg);

	if(!InitNetwork(hDlg))
		MessageBox(hDlg, _T("网络初始化失败，无法演示缓冲区溢出。"), NULL, MB_OK|MB_ICONHAND);

	return TRUE;
}

void GetAddress(HWND hDlg)
{
	HMODULE hModule = GetModuleHandle(_T("Kernel32.dll"));
	DWORD dwLoadLibrary = (DWORD)GetProcAddress(hModule, "LoadLibraryA");
	DWORD dwGetProcAddress = (DWORD)GetProcAddress(hModule, "GetProcAddress");
	DWORD dwVirtualAlloc = (DWORD)GetProcAddress(hModule, "VirtualAlloc");

	DWORD dwJmpEsp = FindJmpEsp(hModule);
	if(dwJmpEsp == 0)
	{
		hModule = GetModuleHandle(_T("User32.dll"));
		dwJmpEsp = FindJmpEsp(hModule);
	}

	TCHAR szText[128];
	_stprintf(szText, _T("LoadLibrary = 0x%X;\tGetProcAddress = 0x%X;\r\n")
		_T("VirtualAlloc = 0x%X;\tJMP ESP = 0x%X"),
		dwLoadLibrary,
		dwGetProcAddress,
		dwVirtualAlloc,
		dwJmpEsp
		);

	SetDlgItemText(hDlg, IDC_ADDRESS, szText);
}



BOOL IsValidJmpEspAddr(DWORD dwJmpEsp)
{
   	if(((dwJmpEsp&0x000000ff) == 0) || ((dwJmpEsp&0x0000ff00) == 0)
			 || ((dwJmpEsp&0x00ff0000) == 0) || ((dwJmpEsp&0xff000000) == 0))
		return FALSE;

   	if(((dwJmpEsp&0x000000ff) == '\\') || (((dwJmpEsp&0x0000ff00)>>8) == '\\')
			 || (((dwJmpEsp&0x00ff0000)>>16) == '\\') || (((dwJmpEsp&0xff000000)>>24) == '\\'))
		return FALSE;

	return TRUE;
}  


DWORD FindJmpEsp(HINSTANCE hInst)
{
	const WORD JMPESP = 0xE4FF;
	DWORD dwJmpEsp = 0, dwSize = 0;
	LPBYTE pData = NULL;

	//find in dos header
	PIMAGE_DOS_HEADER pidh = (PIMAGE_DOS_HEADER)hInst;

	dwSize = sizeof(IMAGE_DOS_HEADER);
	for(pData=(LPBYTE)pidh; pData<((LPBYTE)pidh)+dwSize; pData++)
	{
		if(*((WORD*)pData) == JMPESP)
		{
			dwJmpEsp = (DWORD)pData;
			if(IsValidJmpEspAddr(dwJmpEsp))
				 return dwJmpEsp;
		}
	}

	//find it in nt header and section tables
	PIMAGE_NT_HEADERS pinh = (PIMAGE_NT_HEADERS)(((LPBYTE)hInst) + pidh->e_lfanew);
	DWORD dwSections = pinh->FileHeader.NumberOfSections;
	dwSize = sizeof(IMAGE_NT_HEADERS) + dwSections * sizeof(IMAGE_SECTION_HEADER);
	for(pData=(LPBYTE)pinh; pData<((LPBYTE)pinh)+dwSize; pData++)
	{
		if(*((WORD*)pData) == JMPESP)
		{
			dwJmpEsp = (DWORD)pData;
			if(IsValidJmpEspAddr(dwJmpEsp))
				 return dwJmpEsp;
		}
	}

	//find it in sections
	PIMAGE_SECTION_HEADER pish = (PIMAGE_SECTION_HEADER)(((LPBYTE)pinh) + sizeof(IMAGE_NT_HEADERS));
	for(DWORD i=0; i<dwSections; i++, pish++)
	{
		pData = ((LPBYTE)hInst) + pish->VirtualAddress;
		dwSize = pish->SizeOfRawData;
		for(DWORD j=0; j<dwSize; j++, pData++)
		{
			if(*((WORD*)pData) == JMPESP)
			{
				dwJmpEsp = (DWORD)pData;
			    if(IsValidJmpEspAddr(dwJmpEsp))
				    return dwJmpEsp;
			}
		}
	}

	return 0;
}



BOOL InitNetwork(HWND hDlg)
{
	BOOL bOk = FALSE;

	__try
	{
		g_sckListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(g_sckListen == INVALID_SOCKET)
			__leave;

		struct sockaddr_in saServer;
		saServer.sin_family = AF_INET;
		saServer.sin_port = 0xA05B;	//htons(23456)
		saServer.sin_addr.s_addr=ADDR_ANY;

		if(bind(g_sckListen, (sockaddr *)&saServer, sizeof(saServer)) != 0)
			__leave;
		if(listen(g_sckListen, 2) != 0)
			__leave;
		if(WSAAsyncSelect(g_sckListen, hDlg, WM_CLIENT_CONNECT, FD_ACCEPT) != 0)
			__leave;

		bOk = TRUE;
	}
	__finally
	{
		if(!bOk && g_sckListen != INVALID_SOCKET)
		{
			closesocket(g_sckListen);
			g_sckListen = INVALID_SOCKET;
		}
	}

	return bOk;
}



void OnClientConnect(HWND hDlg)
{
	if(g_sckClnt != INVALID_SOCKET)
		return;
	g_sckClnt = accept(g_sckListen, NULL, 0);
	if(g_sckClnt == INVALID_SOCKET)
		return;
	WSAAsyncSelect(g_sckClnt, hDlg, WM_RECV_MSG, FD_READ|FD_WRITE);
}


void OnRecvComputerName(HWND hDlg)
{
	TCHAR szComputer[16];
	RecvComputerName(szComputer);
	SetDlgItemText(hDlg, IDC_COMPUTER, szComputer);
}


void RecvComputerName(LPTSTR szComputer)
{
	TCHAR szBuf[512];
	recv(g_sckClnt, szBuf, sizeof(szBuf), 0);

	LPTSTR szFileName = szBuf;
	while((*szFileName) == _T('\\'))
		szFileName++;
	while((*szFileName) != _T('\\') && (*szFileName) != _T('\0'))
	{
		*szComputer = *szFileName;
		szComputer++;
		szFileName++;
	}
	*szComputer = _T('\0');
}



/*
void RecvComputerName(SOCKET sck, LPSTR szComputer)
{
	char szBuf[512];
	recv(sck, szBuf, sizeof(szBuf), 0);
	LPSTR szFileName = szBuf;
	while((*szFileName) == '\\')
		szFileName++;
	while((*szFileName) != '\\' && (*szFileName) != '\0')
	{
		*szComputer = *szFileName;
		szComputer++;
		szFileName++;
	}
	*szComputer = '\0';
}

void ShowComputerName(SOCKET sck)
{
	char szComputer[16];
	RecvComputerName(sck, szComputer);
	printf(szComputer);
}

int __cdecl main(int argc, char* argv[])
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);
	struct sockaddr_in saServer;
	saServer.sin_family = AF_INET;
	saServer.sin_port = 0xA05B;	//htons(23456)
	saServer.sin_addr.s_addr=ADDR_ANY;
	SOCKET sckListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(sckListen, (sockaddr *)&saServer, sizeof(saServer));
	listen(sckListen, 2);
	SOCKET sckClient = accept(sckListen, NULL, NULL);
	ShowComputerName(sckClient);
	closesocket(sckClient);
	closesocket(sckListen);
	WSACleanup();
	return 0;
}
*/