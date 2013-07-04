#include"d:\zbmprj\minic\misc.h"
#include"d:\zbmprj\minic\variable.h"
#include"d:\zbmprj\minic\trielem.h"
#include<stdio.h>
#include<graphics.h>
#include<math.h>

TRIELEMEXPR TriElemExprTbl[MAX_TRI_ELEM_EXPR];
UINT ip = 0;
STACK		CallStack[MAX_CALL_NEST];
UINT sp = 0;

void IncreaseIp()
{
	if(ip >= MAX_TRI_ELEM_EXPR)
		yyerror("Triple Element Expression Table Overflow!");
	else
		ip++;
}


#define GET_LEFT_VAR_OPERAND	\
			if(p->LsType==LOCAL)\
				pLVar = pLocalVar + p->left.nValue;\
			else if(p->LsType==GLOBE)\
				pLVar = VarTable + p->left.nValue;\
			else\
				pLVar = pTempVar + p->left.nValue;


#define GET_LEFT_OPERAND		\
			if(p->LsType==LOCAL)\
				pLVar = pLocalVar + p->left.nValue;\
			else if(p->LsType==TEMP)\
				pLVar = --pTempVar;\
			else if(p->LsType==GLOBE)\
				pLVar = VarTable + p->left.nValue;\
			else\
				pLVar = &(p->left);


#define GET_RIGHT_OPERAND 		\
			if(p->RsType==LOCAL)\
				pRVar = pLocalVar + p->right.nValue;\
			else if(p->RsType==TEMP)\
				pRVar = --pTempVar;\
			else if(p->RsType==GLOBE)\
				pRVar = VarTable + p->right.nValue;\
			else\
				pRVar = &(p->right);



#define ASSIGN_CAL(sign)		\
			if(p->LdType==DTINT)\
			{\
				if(p->RdType==DTINT)\
					pLVar->nValue sign pRVar->nValue;\
				else\
					pLVar->nValue sign (int)pRVar->fValue;\
			}\
			else\
			{\
				if(p->RdType==DTINT)\
					pLVar->fValue sign pRVar->nValue;\
				else\
					pLVar->fValue sign pRVar->fValue;\
			}


#define CALCULATE(sign)			\
			if(p->LdType==DTINT)\
			{\
				if(p->RdType==DTINT)\
					pTempVar->nValue = pLVar->nValue sign pRVar->nValue;\
				else\
					pTempVar->fValue = pLVar->nValue sign pRVar->fValue;\
			}\
			else\
			{\
				if(p->RdType==DTINT)\
					pTempVar->fValue = pLVar->fValue sign pRVar->nValue;\
				else\
					pTempVar->fValue = pLVar->fValue sign pRVar->fValue;\
			}



#define RELATION_CAL(sign)		\
			if(p->LdType==DTINT)\
			{\
				if(p->RdType==DTINT)\
					pTempVar->nValue = pLVar->nValue sign pRVar->nValue;\
				else\
					pTempVar->nValue = pLVar->nValue sign pRVar->fValue;\
			}\
			else\
			{\
				if(p->RdType==DTINT)\
					pTempVar->nValue = pLVar->fValue sign pRVar->nValue;\
				else\
					pTempVar->nValue = pLVar->fValue sign pRVar->fValue;\
			}



void RunProgram()
{
	PTRIELEMEXPR p;
	PVARIABLE pLVar, pRVar;

	while(TRUE)
	{
		p = TriElemExprTbl + ip;
		ip++;
		switch(p->op)
		{
		case ETASSIGN:
			GET_LEFT_VAR_OPERAND
			GET_RIGHT_OPERAND
			ASSIGN_CAL(=)
			*pTempVar = *pLVar;
			pTempVar++;
			break;

		case ETADDASSIGN:
			GET_LEFT_VAR_OPERAND
			GET_RIGHT_OPERAND
			ASSIGN_CAL(+=)
			*pTempVar = *pLVar;
			pTempVar++;
			break;

		case ETSUBASSIGN:
			GET_LEFT_VAR_OPERAND
			GET_RIGHT_OPERAND
			ASSIGN_CAL(-=)
			*pTempVar = *pLVar;
			pTempVar++;
			break;
		case ETMULASSIGN:
			GET_LEFT_VAR_OPERAND
			GET_RIGHT_OPERAND
			ASSIGN_CAL(*=)
			*pTempVar = *pLVar;
			pTempVar++;
			break;

		case ETDIVASSIGN:
			GET_LEFT_VAR_OPERAND
			GET_RIGHT_OPERAND
			ASSIGN_CAL(/=)
			*pTempVar = *pLVar;
			pTempVar++;
			break;

		case ETMODASSIGN:
			GET_LEFT_VAR_OPERAND
			GET_RIGHT_OPERAND
			pLVar->nValue %= pRVar->nValue;
			*pTempVar = *pLVar;
			pTempVar++;
			break;

		case ETCOMMA:
			GET_RIGHT_OPERAND	/*MUST GET THE RIGHT FIRST*/
			GET_LEFT_OPERAND
			*pTempVar = *pRVar;
			pTempVar++;
			break;

		case ETADD:
			GET_RIGHT_OPERAND	/*MUST GET THE RIGHT FIRST*/
			GET_LEFT_OPERAND
			CALCULATE(+)
			pTempVar++;
			break;

		case ETSUB:
			GET_RIGHT_OPERAND	/*MUST GET THE RIGHT FIRST*/
			GET_LEFT_OPERAND
			CALCULATE(-)
			pTempVar++;
			break;

		case ETMUL:
			GET_RIGHT_OPERAND	/*MUST GET THE RIGHT FIRST*/
			GET_LEFT_OPERAND
			CALCULATE(*)
			pTempVar++;
			break;

		case ETDIV:
			GET_RIGHT_OPERAND	/*MUST GET THE RIGHT FIRST*/
			GET_LEFT_OPERAND
			CALCULATE(/)
			pTempVar++;
			break;

		case ETMOD:
			GET_RIGHT_OPERAND	/*MUST GET THE RIGHT FIRST*/
			GET_LEFT_OPERAND
			pTempVar->nValue = pLVar->nValue % pRVar->nValue;
			pTempVar++;
			break;

		case ETLARGE:
			GET_RIGHT_OPERAND	/*MUST GET THE RIGHT FIRST*/
			GET_LEFT_OPERAND
			RELATION_CAL(>)
			pTempVar++;
			break;

		case ETSMALL:
			GET_RIGHT_OPERAND	/*MUST GET THE RIGHT FIRST*/
			GET_LEFT_OPERAND
			RELATION_CAL(<)
			pTempVar++;
			break;

		case ETLARGEEQU:
			GET_RIGHT_OPERAND	/*MUST GET THE RIGHT FIRST*/
			GET_LEFT_OPERAND
			RELATION_CAL(>=)
			pTempVar++;
			break;

		case ETSMALLEQU:
			GET_RIGHT_OPERAND	/*MUST GET THE RIGHT FIRST*/
			GET_LEFT_OPERAND
			RELATION_CAL(<=)
			pTempVar++;
			break;

		case ETAND:
			GET_RIGHT_OPERAND	/*MUST GET THE RIGHT FIRST*/
			GET_LEFT_OPERAND
			RELATION_CAL(&&)
			pTempVar++;
			break;

		case ETOR:
			GET_RIGHT_OPERAND	/*MUST GET THE RIGHT FIRST*/
			GET_LEFT_OPERAND
			RELATION_CAL(||)
			pTempVar++;
			break;

		case ETEQU:
			GET_RIGHT_OPERAND	/*MUST GET THE RIGHT FIRST*/
			GET_LEFT_OPERAND
			RELATION_CAL(==)
			pTempVar++;
			break;

		case ETNOTEQU:
			GET_RIGHT_OPERAND	/*MUST GET THE RIGHT FIRST*/
			GET_LEFT_OPERAND
			RELATION_CAL(!=)
			pTempVar++;
			break;

		case ETSIN:
			GET_LEFT_OPERAND
			if(p->LdType==DTINT)
				pTempVar->fValue = sin(pLVar->nValue);
			else
				pTempVar->fValue = sin(pLVar->fValue);
			pTempVar++;
			break;

		case ETCOS:
			GET_LEFT_OPERAND
			if(p->LdType==DTINT)
				pTempVar->fValue = cos(pLVar->nValue);
			else
				pTempVar->fValue = cos(pLVar->fValue);
			pTempVar++;
			break;

		case ETTAN:
			GET_LEFT_OPERAND
			if(p->LdType==DTINT)
				pTempVar->fValue = tan(pLVar->nValue);
			else
				pTempVar->fValue = tan(pLVar->fValue);
			pTempVar++;
			break;

		case ETSQRT:
			GET_LEFT_OPERAND
			if(p->LdType==DTINT)
				pTempVar->fValue = sqrt(pLVar->nValue);
			else
				pTempVar->fValue = sqrt(pLVar->fValue);
			pTempVar++;
			break;

		case ETEXP:
			GET_LEFT_OPERAND
			if(p->LdType==DTINT)
				pTempVar->fValue = exp(pLVar->nValue);
			else
				pTempVar->fValue = exp(pLVar->fValue);
			pTempVar++;
			break;

		case ETLOG:
			GET_LEFT_OPERAND
			if(p->LdType==DTINT)
				pTempVar->fValue = log(pLVar->nValue);
			else
				pTempVar->fValue = log(pLVar->fValue);
			pTempVar++;
			break;

		case ETINC:
			GET_LEFT_VAR_OPERAND
			if(p->LdType==DTINT)
				pLVar->nValue++;
			else
				pLVar->fValue++;

			*pTempVar = *pLVar;
			pTempVar++;
			break;

		case ETDEC:
			GET_LEFT_VAR_OPERAND
			if(p->LdType==DTINT)
				pLVar->nValue--;
			else
				pLVar->fValue--;
			*pTempVar = *pLVar;
			pTempVar++;
			break;

		case ETPOSTINC:
			GET_LEFT_VAR_OPERAND
			*pTempVar = *pLVar;
			pTempVar++;
			if(p->LdType==DTINT)
				pLVar->nValue++;
			else
				pLVar->fValue++;
			break;

		case ETPOSTDEC:
			GET_LEFT_VAR_OPERAND
			*pTempVar = *pLVar;
			pTempVar++;
			if(p->LdType==DTINT)
				pLVar->nValue--;
			else
				pLVar->fValue--;
			break;

		case ETNOT:
			GET_LEFT_OPERAND
			if(p->LdType==DTINT)
				pTempVar->nValue = !pLVar->nValue;
			else
				pTempVar->nValue = !pLVar->fValue;
			pTempVar++;
			break;

		case ETMINUS:
			GET_LEFT_OPERAND
			if(p->LdType==DTINT)
				pTempVar->nValue = -pLVar->nValue;
			else
				pTempVar->fValue = -pLVar->fValue;
			pTempVar++;
			break;

		case OTJMP:
			ip = p->right.nValue;
			break;

		case OTJNZ:
			GET_LEFT_OPERAND
			if((p->LdType==DTINT && pLVar->nValue!=0) ||
					(p->LdType==DTFLOAT && pLVar->nValue!=0.0))
					ip = p->right.nValue;
			break;

		case OTJZ:
			GET_LEFT_OPERAND
			if((p->LdType==DTINT && pLVar->nValue==0) ||
					(p->LdType==DTFLOAT && pLVar->nValue==0.0))
					ip = p->right.nValue;
			break;

		case OTADDVAR:
			if(p->left.nValue==GLOBE)
			{
				pLocalVar += p->right.nValue;
				pTempVar = pLocalVar;
			}
			else
				pTempVar += p->right.nValue;
			break;

		case OTRETURN:
			sp--;
			ip = CallStack[sp].ip;
			pTempVar = pLocalVar;
			pLocalVar = VarTable + CallStack[sp].nLocalVar;
			break;

		case OTREAD:
			GET_LEFT_VAR_OPERAND
			if(p->LdType==DTINT)
				scanf("%d", &(pLVar->nValue));
			else
				scanf("%f", &(pLVar->fValue));
			break;

		case OTREADLN:
			getch();
			break;

		case OTWRITE:
			GET_LEFT_OPERAND
			if(p->LdType==DTINT)
				printf("%d ", pLVar->nValue);
			else
				printf("%f ", pLVar->fValue);
			break;

		case OTWRITELN:
			printf("\n");
			break;

		case OTCALL:
			CallStack[sp].ip = ip;
			CallStack[sp].nLocalVar = pLocalVar-VarTable;
			sp++;
			ip = p->left.nValue;
			pLocalVar = pTempVar - p->right.nValue;
			break;

		case OTINITGRAPH:
			{
				int gd=VGA, gm=VGAHI;
				initgraph(&gd, &gm, "");
			}
			break;

		case OTCLOSEGRAPH:
			closegraph();
			break;

		case OTMOVETO:
			GET_RIGHT_OPERAND
			GET_LEFT_OPERAND
			{
				int x,y;
				if(p->LdType==DTINT) x=pLVar->nValue;
				else x=(int)pLVar->fValue;
				if(p->RdType==DTINT) y=pRVar->nValue;
				else y=(int)pRVar->fValue;
				moveto(x,y);
			}
			break;

		case OTLINETO:
			GET_RIGHT_OPERAND
			GET_LEFT_OPERAND
			{
				int x,y;
				if(p->LdType==DTINT) x=pLVar->nValue;
				else x=(int)pLVar->fValue;
				if(p->RdType==DTINT) y=pRVar->nValue;
				else y=(int)pRVar->fValue;
				lineto(x,y);
			}
			break;

		case OTSETCOLOR:
			GET_LEFT_OPERAND
			if(p->LdType==DTINT)
				setcolor(pLVar->nValue);
			else
				setcolor((int)pLVar->fValue);
			break;

		case OTLAST:
			return;

		default:
			ASSERT(FALSE)
			printf("Abnormally program termenation\n");
			return;
		}
	}
}
