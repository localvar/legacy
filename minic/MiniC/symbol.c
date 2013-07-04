#include"d:\zbmprj\minic\misc.h"
#include"d:\zbmprj\minic\expr.h"
#include"d:\zbmprj\minic\symbol.h"
#include<stdlib.h>
#include<string.h>

BYTE* FxArgsTbl = NULL;
int nTopArg = 0;

int nLocalVars = 0;
int nGlobeVars = 0;

PSYMBOL SymbolTable = NULL;
PSYMBOL pTopSymbol = NULL;
BYTE nCurrentLevel = 0;

BOOL InitSymbolTable()
{
	if(SymbolTable != NULL)
		free(SymbolTable);

	SymbolTable = (PSYMBOL)malloc( sizeof(SYMBOL) * MAX_SYMBOL );
	if( SymbolTable == NULL )
		return FALSE;

	pTopSymbol = SymbolTable;
	nCurrentLevel = 0;
	nLocalVars = 0;
	nGlobeVars = 0;

	if(FxArgsTbl != NULL)
		free(FxArgsTbl);

	FxArgsTbl = (BYTE*)malloc(sizeof(BYTE) * MAX_FUNCTION_ARGS );
	if(FxArgsTbl == NULL)
	{
		free(SymbolTable);
		SymbolTable = NULL;
		return FALSE;
	}

	nTopArg = 0;

	return TRUE;
}

void DestroySymbolTable()
{
	if(SymbolTable != NULL)
	{
		free(SymbolTable);
		SymbolTable = NULL;
	}

	if(FxArgsTbl != NULL)
	{
		free(FxArgsTbl);
		FxArgsTbl = NULL;
	}
}

PSYMBOL FindSymbol(const char* szName, BYTE nStartLv, BYTE nEndLv)
{
	PSYMBOL pCur = pTopSymbol - 1;
	while( pCur>=SymbolTable && pCur->nLevel>=nEndLv )
	{
		if( pCur->nLevel > nStartLv )
		{
			pCur--;
			continue;
		}
		if(strcmp(szName, pCur->szName) == 0)
			return pCur;
		pCur--;
	}

	return NULL;
}
		
PSYMBOL AddSymbol(const char* szName, BYTE nClass, BYTE nType)
{
	if( pTopSymbol-SymbolTable >= MAX_SYMBOL )
	{
		yyerror("Symbol Table Overflow!");
		return NULL;
	}

	if( FindSymbol(szName, nCurrentLevel, nCurrentLevel) != NULL )
	{
		PrintError("Symbol already defined",szName);
		(pTopSymbol->szName)[0] = '\0';
	}
	else
		strcpy(pTopSymbol->szName, szName);

	pTopSymbol->nClass = nClass;
	pTopSymbol->nDataType = nType;
	pTopSymbol->nLevel = nCurrentLevel;
	pTopSymbol->pInitExpr = NULL;
	if( nClass == SCVARIABLE )
	{
		if(nCurrentLevel>0)
		{
			pTopSymbol->nEntry = nLocalVars;
			nLocalVars ++;
		}
		else
		{
			pTopSymbol->nEntry = nGlobeVars;
			nGlobeVars ++;
		}
	}
	pTopSymbol++;

	return pTopSymbol - 1;
}

int DecreaseLevel()
{
	PSYMBOL pSymbol = pTopSymbol;

	ASSERT(nCurrentLevel>=0)

	pTopSymbol--;
	while( pTopSymbol>=SymbolTable && pTopSymbol->nLevel>nCurrentLevel)
	{
		if(pTopSymbol->nClass == SCVARIABLE)
		{
			if(pTopSymbol->nLevel > 0)
				nLocalVars --;
			else
				nGlobeVars --;
		}
		pTopSymbol--;
	}

	pTopSymbol++;
	return pSymbol-pTopSymbol;
}

BOOL AddArgs(BYTE nType)
{
	if(nTopArg<MAX_FUNCTION_ARGS)
	{
		FxArgsTbl[nTopArg] = nType;
		nTopArg++;
		return TRUE;
	}
	else
	{
		yyerror("Function Arguments Table Overflow!");
		return FALSE;
	}
	return FALSE;
}
