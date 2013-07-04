#include"d:\zbmprj\minic\misc.h"
#include"d:\zbmprj\minic\symbol.h"
#include"d:\zbmprj\minic\expr.h"
#include"d:\zbmprj\minic\trielem.h"
#include<stdlib.h>
#include<math.h>

static PEXPR CreateNewExpr()
{
	PEXPR pExpr = (PEXPR) malloc(sizeof(EXPR));
	if(pExpr == NULL)
	{
		yyerror("Unable to allocate memory for new expression");
		return NULL;
	}
	pExpr -> bSubExpr = 0;
	return pExpr;
}

PEXPR MakeEpExpr(EPCODE ep,   PEXPR pLeft,  PEXPR pRight)
{
	PEXPR pExpr = CreateNewExpr();
	pExpr->ep = ep;
	pExpr->Content.CaseEp.pLeft = pLeft;
	pExpr->Content.CaseEp.pRight = pRight;

	if(pLeft->SType==CONST && (pRight==NULL||pRight->SType==CONST))
		pExpr->SType = CONST;
	else
		pExpr->SType = TEMP;
	
	if(pLeft->DType==DTVOID || (pRight!=NULL&&pRight->DType==DTVOID))
		yyerror("'void' is not an allowed type in arithmetic");

	return pExpr;
}

PEXPR MakeFxExpr(PSYMBOL pFx, PEXPR pArgs)
{
	PEXPR pExpr = CreateNewExpr();
	pExpr->ep = ETFUNCTION;
	pExpr->Content.CaseFx.pFx = pFx;
	pExpr->Content.CaseFx.pArgs = pArgs;
	pExpr->SType = TEMP;
	pExpr->DType = pFx->nDataType;

	return pExpr;
}

PEXPR MakeIntExpr(int nValue)
{
	PEXPR pExpr = CreateNewExpr();
	pExpr->ep = DTINT;
	pExpr->SType = CONST;
	pExpr->DType = DTINT;
	pExpr->Content.CaseConst.nValue = nValue;
	return pExpr;
}

PEXPR MakeFloatExpr(float fValue)
{
	PEXPR pExpr = CreateNewExpr();
	pExpr->ep = DTFLOAT;
	pExpr->SType = CONST;
	pExpr->DType = DTFLOAT;
	pExpr->Content.CaseConst.fValue = fValue;
	return pExpr;
}

PEXPR MakeVoidExpr(void vValue)
{
	ASSERT(FALSE);
	return NULL;
}

PEXPR MakeVarExpr(EPCODE ep, PSYMBOL pVar, PEXPR pExpr)
{
	PEXPR p = CreateNewExpr();
	p->ep = ep;
	p->Content.CaseAssign.pVar = pVar;
	p->Content.CaseAssign.pExpr = pExpr;

	if(ep==ETVARIABLE)
		p->SType = (pVar->nLevel>0)?LOCAL:GLOBE;
	else
		p->SType = TEMP;

	p->DType = pVar->nDataType;

	if(p->DType == DTVOID && ep!=ETVARIABLE)
		yyerror("'void' is not an allowed type in arithmetic");
	if(pExpr!=NULL && pExpr->DType==DTVOID)
		yyerror("'void' is not an allowed type in arithmetic");
	
	return p;
}


void GenExprCode(PEXPR pExpr)
{
	int ep;
	PSYMBOL pVar;
	PEXPR pLeft, pRight;
	PTRIELEMEXPR pInst;

	if(pExpr==NULL)		return;
	ep = pExpr->ep;
	if(ep<ETASSIGN)		return;/*常数*/
	if(ep==ETVARIABLE)	return;/*变量*/

	if(ep<=ETMODASSIGN)		/*赋值*/
	{
		pRight = pExpr->Content.CaseAssign.pExpr;
		pVar = pExpr->Content.CaseAssign.pVar;

		GenExprCode(pRight);

		pInst = TriElemExprTbl+ip;
		pInst->op = ep;
		pInst->LsType = (pVar->nLevel>0)?LOCAL:GLOBE;
		pInst->LdType = pVar->nDataType;
		pInst->left.nValue = pVar->nEntry;
		FillOperand(1, pRight);
	}
	else if(ep<=ETMINUS)	/*各种单双目运算*/
	{
		PEXPR pLeft = pExpr->Content.CaseEp.pLeft;
		PEXPR pRight = pExpr->Content.CaseEp.pRight;
		if(pExpr->SType == CONST)
		{
			VARIABLE temp = GetValue(pExpr);
			pExpr->ep = pExpr->DType;
			pExpr->Content.CaseConst = temp;
			FreeExpr(pLeft);
			FreeExpr(pRight);
			return;
		}

		GenExprCode(pLeft);

		if(pRight!=NULL) GenExprCode(pRight);
		else{ ASSERT(ep>=ETSIN || ep<=ETMINUS)}

		pInst = TriElemExprTbl+ip;
		pInst->op = ep;
		FillOperand(0, pLeft);
		if(pRight!=NULL)	FillOperand(1, pRight);
	}
	else if(ep==ETCONDITION)	/*条件表达式*/
	{
	}
	else if(ep<=ETPOSTDEC)	/*自增自减运算*/
	{
		pVar = pExpr->Content.CaseAssign.pVar;
		pInst = TriElemExprTbl+ip;
		pInst->op = ep;
		pInst->LsType = (pVar->nLevel>0)?LOCAL:GLOBE;
		pInst->LdType = pVar->nDataType;
		pInst->left.nValue = pVar->nEntry;
		IncreaseIp();
		return;
	}
	else if(ep==ETFUNCTION)
	{
		PSYMBOL pFx;
		PEXPR pArgs, pArg;
		BYTE *ArgTbl, nArgs, i;/*, nCount=0;*/
		pFx = pExpr->Content.CaseFx.pFx;
		pArgs = pExpr->Content.CaseFx.pArgs;
		nArgs = pFx->nArgs;
		ArgTbl = FxArgsTbl + pFx->nArgEntry;

		pInst = TriElemExprTbl+ip;
		pInst->op = OTADDVAR;
		pInst->left.nValue = LOCAL;
		pInst->right.nValue = nArgs + 1;
		IncreaseIp();

		for(i=0; i<nArgs; i++)
		{
			if(pArgs==NULL) break;
			if(pArgs->ep!=ETCOMMA || pArgs->bSubExpr)
			{
				pArg = pArgs;
				pArgs = NULL;
			}
			else
			{
				pArg = pArgs->Content.CaseEp.pRight;
				pArgs = pArgs->Content.CaseEp.pLeft;
			}
			GenExprCode(pArg);

			pInst = TriElemExprTbl+ip;
			pInst->op = ETASSIGN;
			pInst->LsType = TEMP;
			pInst->LdType = ArgTbl[nArgs-i-1];
			if(pArg->SType==TEMP)
				pInst->left.nValue = -i-i-2;
			else
				pInst->left.nValue = -i-i-1;
			FillOperand(1, pArg);

			if(pInst->LdType==DTVOID || pInst->RdType==DTVOID)
				PrintError("Parameter type mismatch in calling function", pFx->szName);

			IncreaseIp();
		}
		if(i>0)
		{
			pInst = TriElemExprTbl+ip;
			pInst->op = OTADDVAR;
			pInst->left.nValue = LOCAL;
			pInst->right.nValue = -i;
			IncreaseIp();
		}
		pInst = TriElemExprTbl+ip;
		pInst->op = OTCALL;
		pInst->left.nValue = pFx->nEntry;
		pInst->right.nValue = nArgs;
	}
	else
	{
		ASSERT(FALSE)
	}

	IncreaseIp();
}

void FillOperand(int nWhich, PEXPR pExpr)
{
	PSYMBOL pVar;
 	BYTE SType = pExpr->SType;
 	BYTE DType = pExpr->DType;
	PTRIELEMEXPR pInst = TriElemExprTbl +ip;

	ASSERT(pExpr!=NULL)

	if(nWhich==0)/*left one*/
	{
		pInst->LsType = SType;
		pInst->LdType = DType;

		if(SType == CONST)
			pInst->left = pExpr->Content.CaseConst;
		else if(SType < TEMP)
		{
			pVar = pExpr->Content.CaseAssign.pVar;
			pInst->left.nValue = pVar->nEntry;
		}
	}
	else/*right one*/
	{
		pInst->RsType = SType;
		pInst->RdType = DType;

		if(SType == CONST)
			pInst->right = pExpr->Content.CaseConst;
		else if(SType < TEMP)
		{
			pVar = pExpr->Content.CaseAssign.pVar;
			pInst->right.nValue = pVar->nEntry;
		}
	}
}

void FreeExpr(PEXPR pExpr)
{
	EPCODE ep;
	if(pExpr==NULL) return;
	ep = pExpr->ep;
	if(ep<ETVARIABLE)
		;/*DO NOTHING*/
	else if(ep<=ETMODASSIGN)
		FreeExpr(pExpr->Content.CaseAssign.pExpr);
	else if(ep<=ETCONDITION)
	{
		FreeExpr(pExpr->Content.CaseEp.pLeft);
		FreeExpr(pExpr->Content.CaseEp.pRight);
	}
	else if(ep==ETFUNCTION)
		FreeExpr(pExpr->Content.CaseFx.pArgs);
	free(pExpr);
}


#define MATH_CAL(sign)		\
		if(pLeft->DType==DTINT)\
		{\
			if(pRight->DType==DTINT)\
				ret.nValue = lResult.nValue sign rResult.nValue;\
			else\
				ret.fValue = lResult.nValue sign rResult.fValue;\
		}\
		else\
		{\
			if(pRight->DType==DTINT)\
				ret.fValue = lResult.fValue sign rResult.nValue;\
			else\
				ret.fValue = lResult.fValue sign rResult.fValue;\
		}


#define RELATION_CAL(sign)		\
		if(pLeft->DType==DTINT)\
		{\
			if(pRight->DType==DTINT)\
				ret.nValue = lResult.nValue > rResult.nValue;\
			else\
				ret.nValue = lResult.nValue > rResult.fValue;\
		}\
		else\
		{\
			if(pRight->DType==DTINT)\
				ret.nValue = lResult.fValue > rResult.nValue;\
			else\
				ret.nValue = lResult.fValue > rResult.fValue;\
		}



VARIABLE GetValue(PEXPR pExpr)
{
	EPCODE ep = pExpr->ep;
	VARIABLE ret, lResult, rResult;
	PEXPR pLeft, pRight;

	ASSERT(pExpr->SType == CONST)

	if(ep<ETVARIABLE) return (pExpr->Content.CaseConst);

	ASSERT(ep>ETMODASSIGN)
	ASSERT(ep<=ETCONDITION)

	pLeft = pExpr->Content.CaseEp.pLeft;
	pRight = pExpr->Content.CaseEp.pRight;

	lResult = GetValue(pLeft);
	if(ep>=ETSIN && ep<=ETMINUS)
	{
		ASSERT(pRight == NULL)
	}
	else
	{
		ASSERT(pRight != NULL)
		rResult = GetValue(pRight);
	}

	switch(ep)
	{
	case ETCOMMA:
		ret = rResult;
		break;
	case ETADD:
		MATH_CAL(+)
		break;	
	case ETSUB:
		MATH_CAL(-)
		break;	
	case ETMUL:
		MATH_CAL(*)
		break;	
	case ETDIV:
		MATH_CAL(/)
		break;	
	case ETMOD:
		ASSERT(pLeft->DType==DTINT&&pRight->DType==DTINT)
		ret.nValue = lResult.nValue%rResult.nValue;
		break;
	case ETLARGE:
		RELATION_CAL(>)
		break;
	case ETSMALL:
		RELATION_CAL(<)
		break;
	case ETLARGEEQU:
		RELATION_CAL(>=)
		break;
	case ETSMALLEQU:
		RELATION_CAL(<=)
		break;
	case ETAND:
		RELATION_CAL(&&)
		break;
	case ETOR:
		RELATION_CAL(||)
		break;
	case ETEQU:
		RELATION_CAL(==)
		break;
	case ETNOTEQU:
		RELATION_CAL(!=)
		break;
	case ETSIN:
		if(pLeft->DType==DTINT)
			ret.fValue = sin(lResult.nValue);
		else
			ret.fValue = sin(lResult.fValue);
		break;		
	case ETCOS:
		if(pLeft->DType==DTINT)
			ret.fValue = cos(lResult.nValue);
		else
			ret.fValue = cos(lResult.fValue);
		break;		
	case ETTAN:
		if(pLeft->DType==DTINT)
			ret.fValue = tan(lResult.nValue);
		else
			ret.fValue = tan(lResult.fValue);
		break;		
	case ETSQRT:
		if(pLeft->DType==DTINT)
			ret.fValue = sqrt(lResult.nValue);
		else
			ret.fValue = sqrt(lResult.fValue);
		break;		
	case ETEXP:
		if(pLeft->DType==DTINT)
			ret.fValue = exp(lResult.nValue);
		else
			ret.fValue = exp(lResult.fValue);
		break;		
	case ETLOG:
		if(pLeft->DType==DTINT)
			ret.fValue = log(lResult.nValue);
		else
			ret.fValue = log(lResult.fValue);
		break;		
	case ETNOT:
		if(pLeft->DType==DTINT)
			ret.nValue = !lResult.nValue;
		else
			ret.nValue = !lResult.fValue;
		break;
	case ETMINUS:
		if(pLeft->DType==DTINT)
			ret.fValue = -lResult.nValue;
		else
			ret.fValue = -lResult.fValue;
		break;
	default:
		ASSERT(FALSE)
		break;
	}
	return ret;
}
