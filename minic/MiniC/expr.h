#ifndef __EXPR_H__
#define __EXPR_H__

#include"d:\zbmprj\minic\variable.h"

struct tagSYMBOL;
struct tagEXPR;
typedef struct tagEXPR EXPR;

struct tagEXPR
{
	EPCODE ep;
	BOOL bSubExpr;
	BYTE SType;
	BYTE DType;
	union
	{
		struct{EXPR* pLeft;  EXPR* pRight;}	CaseEp;
		struct{struct tagSYMBOL* pFx;  EXPR* pArgs; }	CaseFx;
		struct{struct tagSYMBOL* pVar; EXPR* pExpr; }	CaseAssign;
		VARIABLE		CaseConst;
	}Content;
};

/*typedef struct tagEXPR	EXPR;*/
typedef	EXPR*		PEXPR;

PEXPR MakeEpExpr(EPCODE ep,   PEXPR pLeft,  PEXPR pRight);
PEXPR MakeFxExpr(struct tagSYMBOL* pFx, PEXPR pArgs);
PEXPR MakeIntExpr(int nValue);
PEXPR MakeFloatExpr(float fValue);
PEXPR MakeVoidExpr(void vValue);
PEXPR MakeVarExpr(EPCODE ep, struct tagSYMBOL* pVar, PEXPR pExpr);
void GenExprCode(PEXPR pExpr);
void FreeExpr(PEXPR pExpr);
void FillOperand(int nWhich, PEXPR pExpr);
VARIABLE GetValue(PEXPR pExpr);
/*double GetValue(PEXPR pExpr);*/

#endif __EXPR_H__