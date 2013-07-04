%{
#include "d:\zbmprj\minic\misc.h"
#include "d:\zbmprj\minic\symbol.h"
#include "d:\zbmprj\minic\expr.h"
#include"d:\zbmprj\minic\Trielem.h"

#include <stdlib.h>

int nErrors = 0;
UINT* JmpTbl = NULL;
BYTE  jp = 0;
#define IncreaseJp if(jp++>=MAX_BLOCK_NEST) yyerror("Jump table overflow");

extern int nLineNo;
extern char* yytext;
extern int yylex();
void GenWriteCode(PEXPR pExpr);

int nCurrentFxType = -1;
%}

%union
{
	float fValue;
	int nValue;
	int opValue;
	char* szName;
	PEXPR pExpr;
	void vValue;
}

%token<fValue>	REAL;
%token<nValue>	INTEGER;
%token<vValue>	VOID;
%token<nValue>	NAME;

%token<opValue> COMMA;
%token<opValue> ASSIGN;
%token<opValue>	OR;
%token<opValue> AND;
%token<opValue>	EQU;
%token<opValue>	COMPARE;
%token<opValue>	ADD;
%token<opValue>	MUL;
%token<opValue>	SIGN;
%token<opValue>	NOT;
%token<opValue>	INC;
%token<opValue> MATHFX;

%type<szName>	ID;
%type<pExpr>	EXPRESSION;
%type<pExpr>	OPT_EXPR;
%type<nValue>	TYPE

%token YTINT YTFLOAT YTVOID MAIN IF ELSE FOR DO WHILE RETURN NAME;
%token READ WRITE INITGRAPH CLOSEGRAPH SETCOLOR MOVETO LINETO;
%token ERRTOKEN;

%left COMMA				//	,
%right ASSIGN			//	=   +=  -=  *=  /=  %=
%right '?' ':'			//	?:
%left OR				//	||
%left AND				//	&&
%left EQU				//	==  !=
%left COMPARE			//	>   <   >=  <=
%left ADD				//	+   -
%left MUL				//	*   /
%right SIGN NOT INC		//	+   -   !   ++  --

%start PROGRAM;

%%

PROGRAM:	//程序
	|PROGRAM VAR_DEF ';'
	|PROGRAM FX_DEF
	;


VAR_DEF:	//变量定义
	 TYPE ID
	{
		PSYMBOL pSymbol = AddSymbol($2, SCVARIABLE, $1);
		pSymbol->pInitExpr = NULL;
		if(nCurrentLevel>0)
		{
			PTRIELEMEXPR p = TriElemExprTbl+ip;
			p->op = OTADDVAR;
			p->left.nValue = LOCAL;/*局部变量*/
			p->right.nValue = 1;/*数量一个*/
			IncreaseIp();
		}
		free($2);
	}

	|TYPE ID ASSIGN EXPRESSION
	{
		PSYMBOL pSymbol = AddSymbol($2, SCVARIABLE, $1);;

		if($3 != ETASSIGN) yyerror("Error in variable defination, expected '='");

		if(nCurrentLevel == 0)
		{
			if($4->SType != CONST)
				yyerror("Global variable assignment error, right value not a constant");
			else
				pSymbol->pInitExpr = MakeVarExpr( ETASSIGN, pSymbol, $4 );
		}
		else
		{
			PEXPR pExpr;
			PTRIELEMEXPR p = TriElemExprTbl+ip;
			p->op = OTADDVAR;/*添加变量*/
			p->left.nValue = LOCAL;/*局部变量*/
			p->right.nValue = 1;/*数量一个*/
			IncreaseIp();

			pExpr = MakeVarExpr( $3, pSymbol, $4 );
			GenExprCode(pExpr);
			FreeExpr(pExpr);
			p = TriElemExprTbl+ip;
			p->op = OTADDVAR;
			p->left.nValue = TEMP;
			p->right.nValue = -1;
			IncreaseIp();
		}
		free($2);
	}

	|VAR_DEF COMMA ID
	{
		int nType = (pTopSymbol-1)->nDataType;
		PSYMBOL pSymbol = AddSymbol($3, SCVARIABLE, nType);

		pSymbol->pInitExpr = NULL;

		if(nCurrentLevel>0)
		{
			PTRIELEMEXPR p = TriElemExprTbl+ip;
			p->op = OTADDVAR;
			p->left.nValue = LOCAL;/*局部变量*/
			p->right.nValue = 1;/*数量一个*/
			IncreaseIp();
		}
		free($3);
	}

	|VAR_DEF COMMA ID ASSIGN EXPRESSION
	{
		int nType = (pTopSymbol-1)->nDataType;
		PSYMBOL pSymbol = AddSymbol($3, SCVARIABLE, nType);
		if($4 != ETASSIGN)	yyerror("Error in variable defination, expected '='");

		if(nCurrentLevel == 0)
		{
			if($5->SType != CONST)
				yyerror("Global variable assignment error, right value not a constant");
			else
				pSymbol->pInitExpr = MakeVarExpr( ETASSIGN, pSymbol, $5 );
		}
		else
		{
			PEXPR pExpr;
			PTRIELEMEXPR p = TriElemExprTbl+ip;
			p->op = OTADDVAR;/*添加变量*/
			p->left.nValue = LOCAL;/*局部变量*/
			p->right.nValue = 1;/*数量一个*/
			IncreaseIp();

			pExpr = MakeVarExpr( $4, pSymbol, $5 );
			GenExprCode(pExpr);
			FreeExpr(pExpr);
			p = TriElemExprTbl+ip;
			p->op = OTADDVAR;
			p->left.nValue = TEMP;
			p->right.nValue = -1;
			IncreaseIp();
		}
		free($3);
	}
	;


FX_DEF:		//函数定义
	 FX_HEAD COMPOUND_STATEMENT
	 {
		PTRIELEMEXPR p;
	 	ASSERT(nCurrentLevel==0)
	 	ASSERT(nLocalVars==0)
	 	nCurrentFxType = -1;
		p = TriElemExprTbl+ip;		
		p->op = OTRETURN;
		IncreaseIp();
	 }
	;


TYPE:		//类型
	 YTINT {$$ = DTINT;}
	|YTFLOAT {$$ = DTFLOAT;}
	|YTVOID {$$ = DTVOID;}
	;


FX_HEAD:	//函数头
	 TYPE ID '(' ARGUMENTS ')'
	 {
	 	PSYMBOL pSymbol;
		if(nLocalVars>0)
	 	{
			pTopSymbol -= nLocalVars + 1;
			nCurrentLevel--;
		}
		pSymbol = AddSymbol($2, SCFUNCTION, $1);
		nCurrentFxType = $1;

		pSymbol->nEntry = ip;
		pSymbol->nArgs = nLocalVars;
		pSymbol->nArgEntry = nTopArg - nLocalVars;
		pTopSymbol += nLocalVars;

		free($2);
	}
	|TYPE MAIN '(' ')'	// ARGUMENTS ')'
	{
		int i;
		PSYMBOL pGV = SymbolTable;
		PTRIELEMEXPR p;
		nCurrentFxType = $1;
		/*First Runable instruction is a jump instruction*/

		if(TriElemExprTbl[0].op==OTJMP)
			yyerror("Redefination of function main()");

		TriElemExprTbl[0].op = OTJMP;
		TriElemExprTbl[0].right.nValue = ip;

		for(i=0; i<nGlobeVars; i++)
		{
			while(pGV->nClass != SCVARIABLE)
				pGV++;

			if(pGV->nLevel>0)		break;

			p = TriElemExprTbl+ip;
			p->op = OTADDVAR;
			p->left.nValue = GLOBE;
			p->right.nValue = 1;
			IncreaseIp();
			if(pGV->pInitExpr!=NULL)
			{
				GenExprCode(pGV->pInitExpr);
				FreeExpr(pGV->pInitExpr);
				pGV->pInitExpr = NULL;
				p = TriElemExprTbl+ip;
				p->op = OTADDVAR;
				p->left.nValue = TEMP;
				p->right.nValue = -1;
				IncreaseIp();
			}
			pGV++;
		}
		ASSERT(i==nGlobeVars);
	}
	;


COMPOUND_STATEMENT:		//组合语句
	 BEGIN OPTIONAL_STATEMENT END
	;


ARGUMENTS:	//形参
	|TYPE ID
	{
		/*hold a space for function name*/
		AddSymbol("SpaceHolder", SCFUNCTION, DTVOID);

		ASSERT(nCurrentLevel==0)
		ASSERT(nLocalVars == 0)

		nCurrentLevel++;
		AddSymbol($2, SCVARIABLE, $1);
		AddArgs($1);
		free($2);
	}
	|ARGUMENTS COMMA TYPE ID
	{
		AddSymbol($4, SCVARIABLE, $3);
		AddArgs($3);
		free($4);
	}
	;


BEGIN: '{'
	{
		nCurrentLevel++;
	}
	;

END: '}'
	{
		int nCount;
		PTRIELEMEXPR p=TriElemExprTbl+ip;
		nCurrentLevel--;
		nCount = DecreaseLevel();
		if(nCount>0)
		{
			p->op = OTADDVAR;
			p->left.nValue = LOCAL;
			p->right.nValue = -nCount;
			IncreaseIp();
		}
	}
	;

OPTIONAL_STATEMENT:	//可选语句
	|STATEMENTS
	;


STATEMENTS:		//语句组
	 STATEMENT
	|STATEMENTS STATEMENT
	;


STATEMENT:	//语句
	 VAR_DEF ';'
	 {}


	|OPT_EXPR	';'
	{
		if($1!=NULL && $1->SType!=CONST && $1->ep!=ETVARIABLE)
		{
			PTRIELEMEXPR p;
			GenExprCode($1);
			p = TriElemExprTbl+ip;
			p->op = OTADDVAR;
			p->left.nValue = TEMP;
			p->right.nValue = -1;
			IncreaseIp();
		}
		if($1!=NULL)	FreeExpr($1);
	}			


	|RETURN	OPT_EXPR ';'
	{
		PTRIELEMEXPR p;
		if((nCurrentFxType==DTVOID && $2!=NULL)
			|| (nCurrentFxType!=DTVOID && $2==NULL))
			yyerror("Function return type error");

		if($2 != NULL)
		{
			PEXPR pExpr;
			SYMBOL temp;
			temp.nClass = SCVARIABLE;
			temp.nDataType = nCurrentFxType;
			temp.nLevel = 1;
			temp.nEntry = -1;

			pExpr = MakeVarExpr(ETASSIGN, &temp, $2);
			GenExprCode(pExpr);
			FreeExpr(pExpr);
		}
		p = TriElemExprTbl+ip;		
		p->op = OTRETURN;
		IncreaseIp();
	}


	|READ '(' ')' ';'
	{
		PTRIELEMEXPR p = TriElemExprTbl+ip;
		p->op = OTREADLN;
		IncreaseIp();
	}


	|READ '(' ID ')' ';'
	{
		PSYMBOL pSymbol = FindSymbol( $3, nCurrentLevel, 0 );
		if( pSymbol==NULL || pSymbol->nClass!=SCVARIABLE )
		{
			PrintError("Unrecognized Variable Name",$3);
		}
		else
		{
			PTRIELEMEXPR p = TriElemExprTbl+ip;
			p->op = OTREAD;
			p->LsType = (pSymbol->nLevel>0)?LOCAL:GLOBE;
			p->LdType = pSymbol->nDataType;
			p->left.nValue = pSymbol->nEntry;
			IncreaseIp();
		}
		free($3);
	}


	|WRITE '(' OPT_EXPR ')' ';'
	{
		PTRIELEMEXPR p;
		if($3==NULL)
		{
			p = TriElemExprTbl+ip;
			p->op = OTWRITELN;
			IncreaseIp();
			break;
		}
		GenWriteCode($3);
		FreeExpr($3);
	}

	|INITGRAPH '(' ')' ';'
	{
		PTRIELEMEXPR p = TriElemExprTbl+ip;
		p->op = OTINITGRAPH;
		IncreaseIp();
	}
	|CLOSEGRAPH '(' ')' ';'
	{
		PTRIELEMEXPR p = TriElemExprTbl+ip;
		p->op = OTCLOSEGRAPH;
		IncreaseIp();
	}
	|MOVETO '(' EXPRESSION ')' ';'
	{
		PTRIELEMEXPR p;
		PEXPR pLeft, pRight;
		if($3->ep!=ETCOMMA || $3->bSubExpr)
		{
			yyerror("'moveto' need 2 parameters");
			FreeExpr($3);
			break;
		}
		pLeft = $3->Content.CaseEp.pLeft;
		pRight = $3->Content.CaseEp.pRight;
		if(pLeft->ep==ETCOMMA && !pLeft->bSubExpr)
		{
			yyerror("'moveto' need only 2 parameters");
			FreeExpr($3);
			break;
		}
		GenExprCode(pRight);
		GenExprCode(pLeft);
		p = TriElemExprTbl + ip;
		p->op = OTMOVETO;
		FillOperand(0, pLeft);
		FillOperand(1, pRight);
		IncreaseIp();
		FreeExpr($3);
	}
	|LINETO '(' EXPRESSION ')' ';'
	{
		PTRIELEMEXPR p;
		PEXPR pLeft, pRight;
		if($3->ep!=ETCOMMA || $3->bSubExpr)
		{
			yyerror("'lineto' need 2 parameters");
			FreeExpr($3);
			break;
		}
		pLeft = $3->Content.CaseEp.pLeft;
		pRight = $3->Content.CaseEp.pRight;
		if(pLeft->ep==ETCOMMA && !pLeft->bSubExpr)
		{
			yyerror("'lineto' need only 2 parameters");
			FreeExpr($3);
			break;
		}
		GenExprCode(pRight);
		GenExprCode(pLeft);
		p = TriElemExprTbl + ip;
		p->op = OTLINETO;
		FillOperand(0, pLeft);
		FillOperand(1, pRight);
		IncreaseIp();
		FreeExpr($3);
	}

	|SETCOLOR '(' EXPRESSION ')' ';'
	{
		PTRIELEMEXPR p;
		if($3->ep==ETCOMMA && !$3->bSubExpr)
			yyerror("'lineto' need 2 parameters");
		GenExprCode($3);
		p = TriElemExprTbl + ip;
		p->op = OTSETCOLOR;
		FillOperand(0, $3);
		IncreaseIp();
		FreeExpr($3);
	}

	|COMPOUND_STATEMENT


	|IF    '(' IF_EXPR  ')' STATEMENT
	{
		int nCount;
		PTRIELEMEXPR p = TriElemExprTbl+ip;
		nCurrentLevel--;
		nCount = DecreaseLevel();
		if(nCount>0)
		{
			p->op = OTADDVAR;
			p->left.nValue = LOCAL;
			p->right.nValue = -nCount;
			IncreaseIp();
		}
		jp--;
		p = TriElemExprTbl + JmpTbl[jp];
		p->right.nValue = ip;
	}
	|WHILE '(' WHILE_EXPR  ')' STATEMENT
	{
		int nCount;
		PTRIELEMEXPR p = TriElemExprTbl+ip;
		nCurrentLevel--;
		nCount = DecreaseLevel();
		if(nCount>0)
		{
			p->op = OTADDVAR;
			p->left.nValue = LOCAL;
			p->right.nValue = -nCount;
			IncreaseIp();
		}
		p = TriElemExprTbl+ip;
		p->op = OTJMP;
		p->right.nValue = JmpTbl[jp-2];
		IncreaseIp();
		jp--;
		p = TriElemExprTbl + JmpTbl[jp];
		p->right.nValue = ip;
		jp--;
	}

	|DODO        STATEMENT       WHILE     '('  EXPRESSION ')' ';'
	{
		int nCount;
		PTRIELEMEXPR p = TriElemExprTbl+ip;
		nCurrentLevel--;
		nCount = DecreaseLevel();
		if(nCount>0)
		{
			p->op = OTADDVAR;
			p->left.nValue = LOCAL;
			p->right.nValue = -nCount;
			IncreaseIp();
		}
		GenExprCode($5);
		p = TriElemExprTbl+ip;
		p->op = OTJNZ;
		FillOperand(0, $5);
		jp--;
		p->right.nValue = JmpTbl[jp];
		IncreaseIp();
		FreeExpr($5);
	}


	|IF    '(' IF_EXPR  ')' STATEMENT ELSEELSE STATEMENT
	{
		int nCount;
		PTRIELEMEXPR p = TriElemExprTbl+ip;
		nCurrentLevel--;
		nCount = DecreaseLevel();
		if(nCount>0)
		{
			p->op = OTADDVAR;
			p->left.nValue = LOCAL;
			p->right.nValue = -nCount;
			IncreaseIp();
		}
		jp--;
		p = TriElemExprTbl + JmpTbl[jp];
		p->right.nValue = ip;
	}

	|FOR   '(' FOR_EXPR1    ';' OPT_EXPR  ';'  OPT_EXPR   ')' STATEMENT
	{
		int nCount;
		PTRIELEMEXPR p = TriElemExprTbl+ip;
		nCurrentLevel--;
		nCount = DecreaseLevel();
		if(nCount>0)
		{
			p->op = OTADDVAR;
			p->left.nValue = LOCAL;
			p->right.nValue = -nCount;
			IncreaseIp();
		}
		GenExprCode($7);
		if($7!=NULL && $7->SType!=CONST && $7->ep!=ETVARIABLE)
		{
			p = TriElemExprTbl + ip;
			p->op = OTADDVAR;
			p->left.nValue = TEMP;
			p->right.nValue = -1;
			IncreaseIp();
		}
		jp--;
		p = TriElemExprTbl + JmpTbl[jp];
		p->right.nValue = ip;
		if($5==NULL)
		{
			p = TriElemExprTbl + ip;
			p->op = OTJMP;
			p->right.nValue = JmpTbl[jp]+1;
		}
		else
		{
			GenExprCode($5);
			p = TriElemExprTbl + ip;
			p->op = OTJNZ;
			FillOperand(0,$5);
			p->right.nValue = JmpTbl[jp]+1;
		}
		IncreaseIp();
		FreeExpr($5);
		FreeExpr($7);
	}
	;


EXPRESSION:	//表达式
	 ID		 		ASSIGN 		EXPRESSION
	{
		PSYMBOL pSymbol = FindSymbol( $1, nCurrentLevel, 0 );
		if( pSymbol==NULL || pSymbol->nClass!=SCVARIABLE )
		{
			PrintError("Unrecognized Variable Name",$1);
			$$ = $3;
		}
		else
		{
			if($2==ETMODASSIGN &&( pSymbol->nDataType!=DTINT || $3->DType!=DTINT))
				yyerror("Illegal use of floating point");
			$$ = MakeVarExpr( $2, pSymbol, $3 );
			$$->DType = pSymbol->nDataType;
		}
		free($1);
	}

	|EXPRESSION 	OR 			EXPRESSION
	{
		$$ = MakeEpExpr( $2, $1, $3 );
		$$->DType = DTINT;
	}

	|EXPRESSION 	AND 		EXPRESSION
	{
		$$ = MakeEpExpr( $2, $1, $3 );
		$$->DType = DTINT;		
	}

	|EXPRESSION 	EQU 		EXPRESSION
	{
		$$ = MakeEpExpr( $2, $1, $3 );
		$$->DType = DTINT;		
	}

	|EXPRESSION 	COMPARE 	EXPRESSION
	{
		$$ = MakeEpExpr( $2, $1, $3 );
		$$->DType = DTINT;		
	}

	|EXPRESSION 	ADD 		EXPRESSION
	{
		$$ = MakeEpExpr( $2, $1, $3 );
		if($1->DType==DTINT && $3->DType==DTINT)
			$$->DType = DTINT;
		else
			$$->DType = DTFLOAT;
	}

	|EXPRESSION 	MUL 		EXPRESSION
	{
		if($2==ETMOD &&( $1->DType!=DTINT || $3->DType!=DTINT))
			yyerror("Illegal use of floating point");
		$$ = MakeEpExpr( $2, $1, $3 );
		if($1->DType==DTINT && $3->DType==DTINT)
			$$->DType = DTINT;
		else
			$$->DType = DTFLOAT;
	}

	|EXPRESSION 	COMMA 		EXPRESSION
	{
		$$ = MakeEpExpr( $2, $1, $3 );
		$$->DType = $3->DType;
	}

	|MATHFX '(' EXPRESSION ')'
	{
		$$ = MakeEpExpr( $1, $3, NULL);
		$$->DType = DTFLOAT;
	}

	|NOT 			EXPRESSION
	{
		$$ = MakeEpExpr( $1, $2, NULL );
		$$->DType = DTINT;		
	}

	|ADD 			EXPRESSION	%prec SIGN
	{
		if($1 == ETADD)
			$$ = $2;
		else
		{
			$$ = MakeEpExpr(ETMINUS, $2, NULL);
			$$->DType = $2->DType;
		}
	}

	|INC 			ID
	{
		PSYMBOL pSymbol = FindSymbol( $2, nCurrentLevel, 0 );
		if( pSymbol==NULL || pSymbol->nClass!=SCVARIABLE )
		{
			PrintError("Unrecognized variable name",$2);
			$$ = NULL;
		}
		else
		{
			$$ = MakeVarExpr($1, pSymbol, NULL);
			$$->DType = pSymbol->nDataType;
		}
		free($2);
	}

	|ID		 		INC
	{
		PSYMBOL pSymbol = FindSymbol( $1, nCurrentLevel, 0 );
		if( pSymbol==NULL || pSymbol->nClass!=SCVARIABLE )
		{
			PrintError("Unrecognized variable name",$1);
			$$ = NULL;
		}
		else
		{
			$$ = MakeVarExpr($2 + 2, pSymbol, NULL); /*post inc should be $2+2*/
			$$->DType = pSymbol->nDataType;			
		}
		free($1);
	}
/*
	|EXPRESSION 	'?' 		EXPRESSION 		':' 		EXPRESSION
	{
		$$ = MakeEpExpr( ETCONDITION, $1, MakeEpExpr(ETCONDITION, $3, $5) );
	}
*/	
	|'(' 			EXPRESSION 	')'
	{
		$$ = $2;
		$$->bSubExpr = TRUE;
	}

	|ID
	{
		PSYMBOL pSymbol = FindSymbol( $1, nCurrentLevel, 0 );
		if( pSymbol==NULL || pSymbol->nClass!=SCVARIABLE )
		{
			PrintError("Unrecognized variable name",$1);
			$$ = NULL;
		}
		else
		{
			$$ = MakeVarExpr(ETVARIABLE, pSymbol, NULL);
			$$->DType = pSymbol->nDataType;			
		}
		free($1);
	}	

	|REAL
	{
		$$ = MakeFloatExpr( $1 );
		$$->DType = DTFLOAT;
	}

	|INTEGER
	{
		$$ = MakeIntExpr( $1 );
		$$->DType = DTINT;
	}	

	|ID '(' OPT_EXPR ')'
	{
		PSYMBOL pSymbol = FindSymbol( $1, nCurrentLevel, 0 );
		if( pSymbol==NULL || pSymbol->nClass!=SCFUNCTION )
		{
			PrintError("Unrecognized function name",$1);
			$$ = $3;
		}
		else
		{
			BYTE nArgs = 0;
			PEXPR pTemp = $3;
			while( pTemp!=NULL )
			{
				nArgs++;
				if(pTemp->ep==ETCOMMA && !pTemp->bSubExpr)
					pTemp = pTemp->Content.CaseEp.pLeft;
				else
					pTemp = NULL;
			}
			if( nArgs > pSymbol->nArgs )
				PrintError("Too more arguments in function call",$1);
			else if( nArgs<pSymbol->nArgs )
				PrintError("Too few arguments in function call",$1);
			$$ = MakeFxExpr( pSymbol, $3 );
			$$->DType = pSymbol->nDataType;
		}
		free($1);
	}	
	;


ID:
	 NAME
	{
		int nLen = $1;
		if( nLen > MAX_SYMBOL_NAME_LENGTH )
			nLen = MAX_SYMBOL_NAME_LENGTH;
		$$ = (char*)malloc(	MAX_SYMBOL_NAME_LENGTH + 1 );
		memcpy( $$, yytext, nLen );
		$$[nLen] = '\0';
	}

	|'(' ID ')'
	{
		$$ = $2;
	}
	;

IF_EXPR:
	 EXPRESSION
	{
		PTRIELEMEXPR p;
		GenExprCode($1);
		JmpTbl[jp] = ip;
		IncreaseJp;
		p = TriElemExprTbl + ip;
		p->op = OTJZ;
		FillOperand(0, $1);
		IncreaseIp();
		nCurrentLevel++;
		FreeExpr($1);
	};


FOR_EXPR1:
	 OPT_EXPR
	{
		PTRIELEMEXPR p;
		GenExprCode($1);
		if($1!=NULL && $1->SType!=CONST && $1->ep!=ETVARIABLE)
		{
			p = TriElemExprTbl + ip;
			p->op = OTADDVAR;
			p->left.nValue = TEMP;
			p->right.nValue = -1;
			IncreaseIp();
		}
		p = TriElemExprTbl + ip;
		p->op = OTJMP;
		JmpTbl[jp] = ip;
		IncreaseJp;
		IncreaseIp();
		nCurrentLevel++;
		FreeExpr($1);
	}
	;


WHILE_EXPR:
	 EXPRESSION
	{
		PTRIELEMEXPR p;
		JmpTbl[jp] = ip;
		IncreaseJp;

		GenExprCode($1);
		p = TriElemExprTbl + ip;
		p->op = OTJZ;
		FillOperand(0, $1);
		JmpTbl[jp] = ip;
		IncreaseJp;
		IncreaseIp();

		nCurrentLevel++;
		FreeExpr($1);
	};


ELSEELSE:
	 ELSE
	 {
	 	int nCount;
		PTRIELEMEXPR p;
		nCurrentLevel--;
		p = TriElemExprTbl + ip;
		nCount = DecreaseLevel();
		if(nCount>0)
		{
			p->op = OTADDVAR;
			p->left.nValue = LOCAL;
			p->right.nValue = -nCount;
			IncreaseIp();
		}

		p = TriElemExprTbl + ip;
		p->op = OTJMP;		
		IncreaseIp();
		jp--;
		p = TriElemExprTbl + JmpTbl[jp];
		p->right.nValue = ip;
		JmpTbl[jp] = ip - 1;
		IncreaseJp;
		nCurrentLevel++;
	 };


DODO:
	 DO
	{
		JmpTbl[jp] = ip;
		nCurrentLevel++;
		IncreaseJp;
	};


OPT_EXPR: //可选表达式
	{
		$$ = NULL;
	}

	|EXPRESSION
	{
		$$ = $1;
	}
	;


%%

void PrintError(const char *msg, const char* text)
{
	nErrors++;
	printf("Error at Line %3d: %s: %s.\n", nLineNo, msg, text);
}

void yyerror(const char *msg)
{
	nErrors++;
	printf("Error at Line %3d: %s.\n", nLineNo, msg);
}

void GenWriteCode(PEXPR pExpr)
{
	PTRIELEMEXPR p;

	ASSERT(pExpr!=NULL)

	if(pExpr->ep==ETCOMMA && !pExpr->bSubExpr)
	{
		GenWriteCode(pExpr->Content.CaseEp.pLeft);
		GenExprCode(pExpr->Content.CaseEp.pRight);
		p = TriElemExprTbl+ip;
		p->op = OTWRITE;
		FillOperand(0, pExpr->Content.CaseEp.pRight);
		IncreaseIp();
	}
	else
	{
		GenExprCode(pExpr);
		p = TriElemExprTbl+ip;
		p->op = OTWRITE;
		FillOperand(0, pExpr);
		IncreaseIp();
	}		
}