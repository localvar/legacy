#include"d:\zbmprj\MiniC\Misc.h"
#include"d:\zbmprj\minic\trielem.h"
#include"d:\zbmprj\minic\variable.h"
#include"d:\zbmprj\minic\symbol.h"
#include"d:\zbmprj\minic\expr.h"

#include<stdio.h>

extern int yyparse();
extern void ScannerRestart(FILE* fp);
extern void RunProgram();

extern UINT* JmpTbl;
extern BYTE  jp;
extern int nErrors;

BOOL PrepareCompile(const char* szFileName)
{
	FILE* fp;

	if(!InitSymbolTable())
	{
		printf("Unable to allocate memory for symbol table\n");
		return FALSE;
	}

	JmpTbl = (UINT*)malloc(sizeof(UINT)*MAX_BLOCK_NEST);
	if(JmpTbl==NULL)
	{
		printf("Unable to allocate memory for jump table\n");
		return FALSE;
	}
	jp = 0;

	fp = fopen(szFileName , "rt");
	if(fp == NULL)
	{
		printf("Unable to Open File: %s\n", szFileName);
		return FALSE;
	}

	ScannerRestart(fp);
	/*make sure the first runable instruction is not jmp
	so we can detect the redefination of function main()*/
	TriElemExprTbl[0].op = OTJMP - 1;
	TriElemExprTbl[1].op = OTLAST;
	ip = 2;

	return TRUE;
}

void EndCompile()
{
	if(TriElemExprTbl[0].op != OTJMP)
		yyerror("'main()' not found");
	if(JmpTbl!=NULL)
	{
		free(JmpTbl);
		JmpTbl = NULL;
	}
	ScannerRestart(NULL);
	DestroySymbolTable();
}

BOOL PrepareRunning()
{
	if(nErrors>0)
	{
		printf("\nTotal %d error(s), Unable to run program.\n", nErrors);	
		return FALSE;
	}
	ip = 0;

	VarTable = (PVARIABLE)malloc(sizeof(VARIABLE)*MAX_VARIABLE);
	if(VarTable==NULL)		return FALSE;

	pLocalVar = VarTable;
	pTempVar = VarTable;

	CallStack[0].ip = 1;
	CallStack[0].nLocalVar = 1;
	sp=1;

	return TRUE;
}

void EndRunning()
{
	if(VarTable!=NULL)
	{
		free(VarTable);
		VarTable = NULL;
	}
}

void FreeAll()
{
	if(JmpTbl!=NULL)
	{
		free(JmpTbl);
		JmpTbl = NULL;
	}
	ScannerRestart(NULL);
	DestroySymbolTable();
	if(VarTable!=NULL)
	{
		free(VarTable);
		VarTable = NULL;
	}
}

int main(int argc, char** argv)
{
	char *szFileName = "example.c";
	if(argc>=2) szFileName = argv[1];
	
	if(!PrepareCompile(szFileName))
		goto EXIT;

	yyparse();

	EndCompile();

#ifdef _ENABLE_DEBUG_
	printf("Total %d Triple Element Expressions\n",ip);
#endif

	if(!PrepareRunning())
		goto EXIT;

	RunProgram();
	EndRunning();

EXIT:
	FreeAll();
	printf("\n\nMiniC is a mini C language Intepretor.\n");
	printf("It is a subset of the C Language.\n");
	printf("NAME:    ZhangBoMin\n");
	printf("NO. :    002293051\n");
	printf("TEL :    8209416\n");
	return 0;
}
