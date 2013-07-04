#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include"d:\zbmprj\minic\variable.h"

struct tagEXPR;

#define SCFUNCTION 0	/*符号类别 函数*/
#define SCVARIABLE 1	/*符号类别 变量*/

/*符号*/
typedef struct tagSYMBOL
{
	BYTE nClass;
	BYTE nDataType;
/*	BOOL bInitValue;
	VARIABLE InitValue;*/
	struct tagEXPR* pInitExpr;
	UINT nEntry;
	BYTE nLevel;
	UINT nArgEntry;
	BYTE nArgs;
	char szName[MAX_SYMBOL_NAME_LENGTH + 1];	
}SYMBOL;

typedef SYMBOL*		PSYMBOL;

extern BYTE nCurrentLevel;
extern BYTE* FxArgsTbl;
extern int nTopArg;
extern PSYMBOL SymbolTable;
extern PSYMBOL pTopSymbol;
extern int nLocalVars;
extern int nGlobeVars;

PSYMBOL FindSymbol(const char* szName, BYTE nStartLv, BYTE EndLv);
PSYMBOL AddSymbol(const char* szName, BYTE nClass, BYTE nType);
BOOL AddArgs(BYTE nType);
int DecreaseLevel();
BOOL InitSymbolTable();
void DestroySymbolTable();

#endif __SYMBOL_H__