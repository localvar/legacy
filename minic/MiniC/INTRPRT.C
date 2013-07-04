# line 1 "minic.y"

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

# line 23 "minic.y"
typedef union  {
	float fValue;
	int nValue;
	int opValue;
	char* szName;
	PEXPR pExpr;
	void vValue;
} YYSTYPE;
# define REAL 257
# define INTEGER 258
# define VOID 259
# define NAME 260
# define COMMA 261
# define ASSIGN 262
# define OR 263
# define AND 264
# define EQU 265
# define COMPARE 266
# define ADD 267
# define MUL 268
# define SIGN 269
# define NOT 270
# define INC 271
# define MATHFX 272
# define YTINT 273
# define YTFLOAT 274
# define YTVOID 275
# define MAIN 276
# define IF 277
# define ELSE 278
# define FOR 279
# define DO 280
# define WHILE 281
# define RETURN 282
# define READ 283
# define WRITE 284
# define INITGRAPH 285
# define CLOSEGRAPH 286
# define SETCOLOR 287
# define MOVETO 288
# define LINETO 289
# define ERRTOKEN 290
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern int yyerrflag;
typedef int yytabelem;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
YYSTYPE yylval, yyval;
# define YYERRCODE 256
# line 950 "minic.y"


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
}yytabelem yyexca[] = {
-1, 1,
	0, -1,
	-2, 0,
-1, 16,
	59, 66,
	-2, 20,
-1, 30,
	59, 66,
	-2, 21,
	};
yytabelem yyr1 [] = {
     0,     5,     5,     5,     6,     6,     6,     6,     7,     4,
     4,     4,     8,     8,     9,    10,    10,    10,    11,    13,
    12,    12,    14,    14,    15,    15,    15,    15,    15,    15,
    15,    15,    15,    15,    15,    15,    15,    15,    15,    15,
    15,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     1,
     1,    16,    20,    17,    19,    18,     3,     3};
yytabelem yyr2 [] = {
     0,     0,     6,     4,     5,     9,     7,    11,     5,     3,
     3,     3,    11,     9,     6,     0,     5,     9,     3,     3,
     0,     2,     2,     4,     5,     5,     7,     9,    11,    11,
     9,     9,    11,    11,    11,     2,    11,    11,    15,    15,
    19,     7,     7,     7,     7,     7,     7,     7,     7,     9,
     5,     5,     5,     5,     7,     3,     3,     3,     9,     3,
     7,     3,     3,     3,     3,     3,     1,     3};
yytabelem yychk [] = {
 -1000,    -5,    -4,    -6,    -7,    -8,   273,   274,   275,    -1,
   260,   276,    40,   261,    59,    -9,   -11,   123,   262,    40,
    40,    -1,    -1,    -1,    -2,    -3,    -4,    -6,    -9,   -12,
   -14,   -15,   -18,   257,   258,   267,   270,   271,   272,   277,
   279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
   289,    40,    -2,    -4,   -10,    41,    41,   262,   262,   271,
    40,   261,   263,   264,   265,   266,   267,   268,    59,    -1,
    59,   -13,   125,   -15,   -15,    -2,    -2,    -1,    40,    40,
    40,    40,    -3,    40,    40,    40,    40,    40,    40,    40,
    -1,    -2,    -1,   261,    41,    -2,    -2,    -3,    -2,    -2,
    -2,    -2,    -2,    -2,    -2,   281,    -2,    -2,   -16,    -3,
   -20,    -2,   -17,    59,    -1,    41,    -3,    41,    41,    -2,
    -2,    -2,    41,    -4,    41,    40,    41,    41,    59,    41,
    41,    59,    41,    59,    59,    41,    41,    41,    -1,    -2,
   -15,    -3,   -15,    59,    59,    59,    59,    59,    41,   -19,
   278,    59,    59,   -15,    -3,    41,   -15};
yytabelem yydef [] = {
     1,    -2,     0,     0,     3,     0,     9,    10,    11,     4,
    59,     0,     0,     0,     2,     8,    -2,    18,     0,    15,
     0,     0,     6,    55,    67,     0,     0,     0,    35,     0,
    -2,    22,    66,    56,    57,     0,     0,     0,     0,     0,
     0,    65,     0,    66,     0,     0,     0,     0,     0,     0,
     0,     0,     5,     0,     0,    13,    60,     0,     0,    53,
    66,     0,     0,     0,     0,     0,     0,     0,    25,     4,
    24,    14,    19,    23,     0,    51,    50,    52,     0,     0,
    66,     0,     0,     0,    66,     0,     0,     0,     0,     0,
    55,     0,    16,     0,    12,     7,    41,     0,    48,    42,
    43,    44,    45,    46,    47,     0,     0,    61,     0,    62,
     0,    63,     0,    26,     0,     0,     0,     0,     0,     0,
     0,     0,    54,     0,    58,     0,    49,    66,    66,    66,
     0,    27,     0,    30,    31,     0,     0,     0,    17,     0,
    36,     0,    37,    28,    29,    34,    32,    33,     0,    66,
    64,    66,    38,    39,     0,    66,    40};
# define YYNPROD 21
# define YYLAST  315
yytabelem yyact [] = {
    51,    19,    12,    70,    12,   115,    94,    14,    12,    25,
    31,   149,    26,    61,     2,    62,    63,    64,    65,    66,
    67,    28,    66,    67,    73,    72,    74,    15,    17,   112,
    60,    56,    53,    51,    27,    60,     3,    24,    62,    63,
    64,    65,    66,    67,     6,     7,     8,   148,    63,    64,
    65,    66,    67,    82,   110,   137,    52,    64,    65,    66,
    67,   108,   152,   136,    65,    66,    67,   151,   147,   146,
    97,   135,   145,    75,    76,   144,   143,   134,   133,   126,
   131,   155,   128,    17,   113,    68,   132,   122,   130,    91,
   109,   129,   127,   124,   116,    95,    96,   118,   117,    98,
    99,   100,   101,   102,   103,   104,   123,    56,    55,   125,
    89,    88,    87,    86,    85,    84,   106,   107,    83,   111,
    81,   140,    80,   142,    79,   119,   120,   121,    78,    20,
    71,    23,   105,   150,     9,    54,    30,    29,   141,    67,
    57,    18,     5,   153,    21,    22,     4,     1,    32,   156,
    16,     0,     0,     0,     0,     0,     0,     0,    69,     0,
     0,   154,     0,   139,     0,     0,     0,     0,     0,    77,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    90,     0,    92,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    13,     0,     0,     0,    13,
     0,     0,     0,     0,     0,   114,     0,    33,    34,     0,
    10,     0,    10,    18,    10,     0,    93,    35,    10,     0,
    36,    37,    38,     6,     7,     8,     0,    39,    11,    40,
    41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
    33,    34,    58,    10,     0,   138,     0,    58,     0,     0,
    35,    59,     0,    36,    37,    38,    59,    61,     0,    62,
    63,    64,    65,    66,    67,    61,     0,    62,    63,    64,
    65,    66,    67,    61,     0,    62,    63,    64,    65,    66,
    67,    61,     0,    62,    63,    64,    65,    66,    67,    61,
     0,    62,    63,    64,    65,    66,    67,    61,     0,    62,
    63,    64,    65,    66,    67};
yytabelem yypact [] = {
 -1000,  -229,   -38,   -52, -1000,   -95, -1000, -1000, -1000,   -39,
 -1000,    89,   -32,   -32, -1000, -1000,   -40, -1000,    -7,  -229,
    67,    66,  -122,    -5,  -248,    26,   -32,   -56, -1000,  -100,
   -40, -1000,   -40, -1000, -1000,    -7,    -7,   -32,    88,    84,
    82, -1000,    80,    -7,    78,    75,    74,    73,    72,    71,
    70,    -7,  -225,   -32,   -35, -1000, -1000,    -7,    -7, -1000,
    -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7, -1000,  -121,
 -1000, -1000, -1000, -1000,  -149, -1000, -1000, -1000,    -7,    -7,
    -7,    -7,    25,   -36,    -7,    57,    56,    -7,    -7,    -7,
   -10,    46, -1000,  -229, -1000,  -225,  -225,    52,  -225,  -216,
  -208,  -202,  -245,  -129, -1000,    69,    38,  -248,    51, -1000,
    23,  -248,    50, -1000,    47,    21,    45,    19,    18,    30,
    22,    14, -1000,   -32, -1000,    -7, -1000,   -40,    -7,   -40,
    17, -1000,    16, -1000, -1000,    13,    10,     9, -1000,     6,
  -145,     8, -1000, -1000, -1000, -1000, -1000, -1000,     3,   -40,
 -1000,    -7, -1000, -1000,    40,   -40, -1000};
yytabelem yypgo [] = {
     0,   131,    37,     9,    12,   146,    34,   144,   140,    21,
   115,   150,   120,   100,   119,    -7,   -19,   -53,   148,  -130,
   -27};
typedef struct { char *t_name; int t_val; } yytoktype;
#ifndef YYDEBUG
#	define YYDEBUG	0	/* don't allow debugging */
#endif

#if YYDEBUG

yytoktype yytoks[] =

{
	{"REAL",	257},
	{"INTEGER",	258},
	{"VOID",	259},
	{"NAME",	260},
	{"COMMA",	261},
	{"ASSIGN",	262},
	{"OR",	263},
	{"AND",	264},
	{"EQU",	265},
	{"COMPARE",	266},
	{"ADD",	267},
	{"MUL",	268},
	{"SIGN",	269},
	{"NOT",	270},
	{"INC",	271},
	{"MATHFX",	272},
	{"YTINT",	273},
	{"YTFLOAT",	274},
	{"YTVOID",	275},
	{"MAIN",	276},
	{"IF",	277},
	{"ELSE",	278},
	{"FOR",	279},
	{"DO",	280},
	{"WHILE",	281},
	{"RETURN",	282},
	{"NAME",	260},
	{"READ",	283},
	{"WRITE",	284},
	{"INITGRAPH",	285},
	{"CLOSEGRAPH",	286},
	{"SETCOLOR",	287},
	{"MOVETO",	288},
	{"LINETO",	289},
	{"ERRTOKEN",	290},
	{"COMMA",	261},
	{"ASSIGN",	262},
	{"?",	63},
	{":",	58},
	{"OR",	263},
	{"AND",	264},
	{"EQU",	265},
	{"COMPARE",	266},
	{"ADD",	267},
	{"MUL",	268},
	{"SIGN",	269},
	{"NOT",	270},
	{"INC",	271},
	{"-unknown-",	-1}	/* ends search */
};

char * yyreds[] =
{

	"-no such reduction-",
	"PROGRAM : /* empty */",
	"PROGRAM : PROGRAM VAR_DEF ';'",
	"PROGRAM : PROGRAM FX_DEF",
	"VAR_DEF : TYPE ID",
	"VAR_DEF : TYPE ID ASSIGN EXPRESSION",
	"VAR_DEF : VAR_DEF COMMA ID",
	"VAR_DEF : VAR_DEF COMMA ID ASSIGN EXPRESSION",
	"FX_DEF : FX_HEAD COMPOUND_STATEMENT",
	"TYPE : YTINT",
	"TYPE : YTFLOAT",
	"TYPE : YTVOID",
	"FX_HEAD : TYPE ID '(' ARGUMENTS ')'",
	"FX_HEAD : TYPE MAIN '(' ')'",
	"COMPOUND_STATEMENT : BEGIN OPTIONAL_STATEMENT END",
	"ARGUMENTS : /* empty */",
	"ARGUMENTS : TYPE ID",
	"ARGUMENTS : ARGUMENTS COMMA TYPE ID",
	"BEGIN : '{'",
	"END : '}'",
	"OPTIONAL_STATEMENT : /* empty */",
	"OPTIONAL_STATEMENT : STATEMENTS",
	"STATEMENTS : STATEMENT",
	"STATEMENTS : STATEMENTS STATEMENT",
	"STATEMENT : VAR_DEF ';'",
	"STATEMENT : OPT_EXPR ';'",
	"STATEMENT : RETURN OPT_EXPR ';'",
	"STATEMENT : READ '(' ')' ';'",
	"STATEMENT : READ '(' ID ')' ';'",
	"STATEMENT : WRITE '(' OPT_EXPR ')' ';'",
	"STATEMENT : INITGRAPH '(' ')' ';'",
	"STATEMENT : CLOSEGRAPH '(' ')' ';'",
	"STATEMENT : MOVETO '(' EXPRESSION ')' ';'",
	"STATEMENT : LINETO '(' EXPRESSION ')' ';'",
	"STATEMENT : SETCOLOR '(' EXPRESSION ')' ';'",
	"STATEMENT : COMPOUND_STATEMENT",
	"STATEMENT : IF '(' IF_EXPR ')' STATEMENT",
	"STATEMENT : WHILE '(' WHILE_EXPR ')' STATEMENT",
	"STATEMENT : DODO STATEMENT WHILE '(' EXPRESSION ')' ';'",
	"STATEMENT : IF '(' IF_EXPR ')' STATEMENT ELSEELSE STATEMENT",
	"STATEMENT : FOR '(' FOR_EXPR1 ';' OPT_EXPR ';' OPT_EXPR ')' STATEMENT",
	"EXPRESSION : ID ASSIGN EXPRESSION",
	"EXPRESSION : EXPRESSION OR EXPRESSION",
	"EXPRESSION : EXPRESSION AND EXPRESSION",
	"EXPRESSION : EXPRESSION EQU EXPRESSION",
	"EXPRESSION : EXPRESSION COMPARE EXPRESSION",
	"EXPRESSION : EXPRESSION ADD EXPRESSION",
	"EXPRESSION : EXPRESSION MUL EXPRESSION",
	"EXPRESSION : EXPRESSION COMMA EXPRESSION",
	"EXPRESSION : MATHFX '(' EXPRESSION ')'",
	"EXPRESSION : NOT EXPRESSION",
	"EXPRESSION : ADD EXPRESSION",
	"EXPRESSION : INC ID",
	"EXPRESSION : ID INC",
	"EXPRESSION : '(' EXPRESSION ')'",
	"EXPRESSION : ID",
	"EXPRESSION : REAL",
	"EXPRESSION : INTEGER",
	"EXPRESSION : ID '(' OPT_EXPR ')'",
	"ID : NAME",
	"ID : '(' ID ')'",
	"IF_EXPR : EXPRESSION",
	"FOR_EXPR1 : OPT_EXPR",
	"WHILE_EXPR : EXPRESSION",
	"ELSEELSE : ELSE",
	"DODO : DO",
	"OPT_EXPR : /* empty */",
	"OPT_EXPR : EXPRESSION",
};

#endif /* YYDEBUG */
# line 1 "D:\ZBMPRJ\MINIC\YACCPAR"
/*                 XD-YACC parser skeleton file

		     Programmar: Qiang.Guo
	    Department of Computer Science,XIDIAN University.

	This parser skeleton is a reuse of SCO xenix V YACC parser.

	yaccpar.src 1.2 88/10/25
	Copyright (C) The Santa Cruz Operation, 1985.
*/

/*
** yacc user known macros and defines
*/
# include <stdio.h>
FILE *file;
#define YYINSERT(token,value) yyinsert(token,value)
#define YYGIVEUPREDUCE  { yyerrflag = 0; yystate = * yyps ; goto yynewstate;}
#define YYERROR         goto yyerrlab
#define YYEXPECT(token) yyexpect(token)
#define YYACCEPT        return(0)
#define YYABORT         return(1)
#define YYBACKUP( newtoken, newvalue )\
{\
	if ( yychar >= 0 || ( yyr2[ yytmp ] >> 1 ) != 1 )\
	{\
		yyerror( "syntax error - cannot backup" );\
		goto yyerrlab;\
	}\
	yychar = newtoken;\
	yystate = *yyps;\
	yylval = newvalue;\
	goto yynewstate;\
}
#define YYRECOVERING()  (!!yyerrflag)
#ifndef YYDEBUG
#       define YYDEBUG  1       /* make debugging available */
#endif

/*
** user known globals
*/
int yydebug;                    /* set to 1 to get debugging */

/*
** driver internal defines
*/
#define YYFLAG          (-1000)

/*
** global variables used by the parser
*/
YYSTYPE yyv[ YYMAXDEPTH ];      /* value stack */
int yys[ YYMAXDEPTH ];          /* state stack */

YYSTYPE *yypv;                  /* top of value stack */
int *yyps;                      /* top of state stack */

int yystate;                    /* current state */
int yytmp;                      /* extra var (lasts between blocks) */

int yynerrs;                    /* number of errors */
int yyerrflag;                  /* error recovery flag */
int yychar;                     /* current input token number */

/*
** yyparse - return 0 if worked, 1 if syntax error not recovered from
*/
int yyparse()
{
	register YYSTYPE *yypvt;        /* top of value stack for $vars */

	/*
	** Initialize externals - yyparse may be called more than once
	*/
	if (yydebug)
	{
		file = fopen ("debug.inf","w");
		if (file == NULL)
		{
			perror ("open file");
			exit (1);
		}
	}
	yypv = &yyv[-1];
	yyps = &yys[-1];
	yystate = 0;
	yytmp = 0;
	yynerrs = 0;
	yyerrflag = 0;
	yychar = -1;

	goto yystack;
	{
		register YYSTYPE *yy_pv;        /* top of value stack */
		register int *yy_ps;            /* top of state stack */
		register int yy_state;          /* current state */
		register int  yy_n;             /* internal state number info */

		/*
		** get globals into registers.
		** branch to here only if YYBACKUP was called.
		*/
	yynewstate:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;
		goto yy_newstate;

		/*
		** get globals into registers.
		** either we just started, or we just finished a reduction
		*/
	yystack:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;

		/*
		** top of for (;;) loop while no reductions done
		*/
	yy_stack:
		/*
		** put a state and value onto the stacks
		*/
#if YYDEBUG
		/*
		** if debugging, look up token value in list of value vs.
		** name pairs.  0 and negative (-1) are special values.
		** Note: linear search is used since time is not a real
		** consideration while debugging.
		*/
		if ( yydebug )
		{
			register int yy_i;

			fprintf(file, "State %d, token ", yy_state );
			if ( yychar == 0 )
				fprintf(file, "end-of-file\n" );
			else if ( yychar < 0 )
				fprintf(file, "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				fprintf(file, "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ++yy_ps >= &yys[ YYMAXDEPTH ] )    /* room on stack? */
		{
			yyerror( "yacc stack overflow" );
			YYABORT;
		}
		*yy_ps = yy_state;
		*++yy_pv = yyval;

		/*
		** we have a new state - find out what to do
		*/
	yy_newstate:
		if ( ( yy_n = yypact[ yy_state ] ) <= YYFLAG )
			goto yydefault;         /* simple state */
#if YYDEBUG
		/*
		** if debugging, need to mark whether new token grabbed
		*/
		yytmp = yychar < 0;
#endif
		if ( ( yychar < 0 ) && ( ( yychar = yylex() ) < 0 ) )
			yychar = 0;             /* reached EOF */
#if YYDEBUG
		if ( yydebug && yytmp )
		{
			register int yy_i;

			fprintf(file, "Received token " );
			if ( yychar == 0 )
				fprintf(file, "end-of-file\n" );
			else if ( yychar < 0 )
				fprintf(file, "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				fprintf(file, "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ( ( yy_n += yychar ) < 0 ) || ( yy_n >= YYLAST ) )
			goto yydefault;
		if ( yychk[ yy_n = yyact[ yy_n ] ] == yychar )  /*valid shift*/
		{
			yychar = -1;
			yyval = yylval;
			yy_state = yy_n;
			if ( yyerrflag > 0 )
				yyerrflag--;
			goto yy_stack;
		}

	yydefault:
		if ( ( yy_n = yydef[ yy_state ] ) == -2 )
		{
#if YYDEBUG
			yytmp = yychar < 0;
#endif
			if ( ( yychar < 0 ) && ( ( yychar = yylex() ) < 0 ) )
				yychar = 0;             /* reached EOF */
#if YYDEBUG
			if ( yydebug && yytmp )
			{
				register int yy_i;

				fprintf(file, "Received token " );
				if ( yychar == 0 )
					fprintf(file, "end-of-file\n" );
				else if ( yychar < 0 )
					fprintf(file, "-none-\n" );
				else
				{
					for ( yy_i = 0;
						yytoks[yy_i].t_val >= 0;
						yy_i++ )
					{
						if ( yytoks[yy_i].t_val
							== yychar )
						{
							break;
						}
					}
					fprintf(file, "%s\n", yytoks[yy_i].t_name );
				}
			}
#endif /* YYDEBUG */
			/*
			** look through exception table
			*/
			{
				register int *yyxi = yyexca;

				while ( ( *yyxi != -1 ) ||
					( yyxi[1] != yy_state ) )
				{
					yyxi += 2;
				}
				while ( ( *(yyxi += 2) >= 0 ) &&
					( *yyxi != yychar ) )
					;
				if ( ( yy_n = yyxi[1] ) < 0 )
					YYACCEPT;
			}
		}

		/*
		** check for syntax error
		*/
		if ( yy_n == 0 )        /* have an error */
		{
			/* no worry about speed here! */
			switch ( yyerrflag )
			{
			case 0:         /* new error */
				yyerror( "syntax error" );
				goto skip_init;
			yyerrlab:
				/*
				** get globals into registers.
				** we have a user generated syntax type error
				*/
				yy_pv = yypv;
				yy_ps = yyps;
				yy_state = yystate;
				yynerrs++;
			skip_init:
			case 1:
			case 2:         /* incompletely recovered error */
					/* try again... */
				yyerrflag = 3;
				/*
				** find state where "error" is a legal
				** shift action
				*/
				while ( yy_ps >= yys )
				{
					yy_n = yypact[ *yy_ps ] + YYERRCODE;
					if ( yy_n >= 0 && yy_n < YYLAST &&
						yychk[yyact[yy_n]] == YYERRCODE)                                        {
						/*
						** simulate shift of "error"
						*/
						yy_state = yyact[ yy_n ];
						goto yy_stack;
					}
					/*
					** current state has no shift on
					** "error", pop stack
					*/
#if YYDEBUG
#       define _POP_ "Error recovery pops state %d, uncovers state %d\n"
					if ( yydebug )
						fprintf(file, _POP_, *yy_ps,
							yy_ps[-1] );
#       undef _POP_
#endif
					yy_ps--;
					yy_pv--;
				}
				/*
				** there is no state on stack with "error" as
				** a valid shift.  give up.
				*/
				YYABORT;
			case 3:         /* no shift yet; eat a token */
#if YYDEBUG
				/*
				** if debugging, look up token in list of
				** pairs.  0 and negative shouldn't occur,
				** but since timing doesn't matter when
				** debugging, it doesn't hurt to leave the
				** tests here.
				*/
				if ( yydebug )
				{
					register int yy_i;

					fprintf(file, "Error recovery discards " );
					if ( yychar == 0 )
						fprintf(file, "token end-of-file\n" );
					else if ( yychar < 0 )
						fprintf(file, "token -none-\n" );
					else
					{
						for ( yy_i = 0;
							yytoks[yy_i].t_val >= 0;
							yy_i++ )
						{
							if ( yytoks[yy_i].t_val
								== yychar )
							{
								break;
							}
						}
						fprintf(file, "token %s\n",
							yytoks[yy_i].t_name );
					}
				}
#endif /* YYDEBUG */
				if ( yychar == 0 )      /* reached EOF. quit */
					YYABORT;
				yychar = -1;
				goto yy_newstate;
			}
		}/* end if ( yy_n == 0 ) */
		/*
		** reduction by production yy_n
		** put stack tops, etc. so things right after switch
		*/
#if YYDEBUG
		/*
		** if debugging, print the string that is the user's
		** specification of the reduction which is just about
		** to be done.
		*/
		if ( yydebug )
			fprintf(file, "Reduce by (%d) \"%s\"\n",
				yy_n, yyreds[ yy_n ] );
#endif
		yytmp = yy_n;                   /* value to switch over */
		yypvt = yy_pv;                  /* $vars top of value stack */
		/*
		** Look in goto table for next state
		** Sorry about using yy_state here as temporary
		** register variable, but why not, if it works...
		** If yyr2[ yy_n ] doesn't have the low order bit
		** set, then there is no action to be done for
		** this reduction.  So, no saving & unsaving of
		** registers done.  The only difference between the
		** code just after the if and the body of the if is
		** the goto yy_stack in the body.  This way the test
		** can be made before the choice of what to do is needed.
		*/
		{
			/* length of production doubled with extra bit */
			register int yy_len = yyr2[ yy_n ];

			if ( !( yy_len & 01 ) )
			{
				yy_len >>= 1;
				yyval = ( yy_pv -= yy_len )[1]; /* $$ = $1 */
				yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
					*( yy_ps -= yy_len ) + 1;
				if ( yy_state >= YYLAST ||
					yychk[ yy_state =
					yyact[ yy_state ] ] != -yy_n )
				{
					yy_state = yyact[ yypgo[ yy_n ] ];
				}
				goto yy_stack;
			}
			yy_len >>= 1;
			yyval = ( yy_pv -= yy_len )[1]; /* $$ = $1 */
			yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
				*( yy_ps -= yy_len ) + 1;
			if ( yy_state >= YYLAST ||
				yychk[ yy_state = yyact[ yy_state ] ] != -yy_n )
			{
				yy_state = yyact[ yypgo[ yy_n ] ];
			}
		}
					/* save until reenter driver code */
		yystate = yy_state;
		yyps = yy_ps;
		yypv = yy_pv;
	}
	/*
	** code supplied by user is placed in this switch
	*/
	switch( yytmp )
	{
case 4:	/* VAR_DEF : TYPE ID */
# line 82 "minic.y"
{
		PSYMBOL pSymbol = AddSymbol(yypvt[-0].szName, SCVARIABLE, yypvt[-1].nValue);
		pSymbol->pInitExpr = NULL;
		if(nCurrentLevel>0)
		{
			PTRIELEMEXPR p = TriElemExprTbl+ip;
			p->op = OTADDVAR;
			p->left.nValue = LOCAL;/*????????*/
			p->right.nValue = 1;/*????????*/
			IncreaseIp();
		}
		free(yypvt[-0].szName);
	} break;
case 5:	/* VAR_DEF : TYPE ID ASSIGN EXPRESSION */
# line 97 "minic.y"
{
		PSYMBOL pSymbol = AddSymbol(yypvt[-2].szName, SCVARIABLE, yypvt[-3].nValue);;

		if(yypvt[-1].opValue != ETASSIGN) yyerror("Error in variable defination, expected '='");

		if(nCurrentLevel == 0)
		{
			if(yypvt[-0].pExpr->SType != CONST)
				yyerror("Global variable assignment error, right value not a constant");
			else
				pSymbol->pInitExpr = MakeVarExpr( ETASSIGN, pSymbol, yypvt[-0].pExpr );
		}
		else
		{
			PEXPR pExpr;
			PTRIELEMEXPR p = TriElemExprTbl+ip;
			p->op = OTADDVAR;/*????????*/
			p->left.nValue = LOCAL;/*????????*/
			p->right.nValue = 1;/*????????*/
			IncreaseIp();

			pExpr = MakeVarExpr( yypvt[-1].opValue, pSymbol, yypvt[-0].pExpr );
			GenExprCode(pExpr);
			FreeExpr(pExpr);
			p = TriElemExprTbl+ip;
			p->op = OTADDVAR;
			p->left.nValue = TEMP;
			p->right.nValue = -1;
			IncreaseIp();
		}
		free(yypvt[-2].szName);
	} break;
case 6:	/* VAR_DEF : VAR_DEF COMMA ID */
# line 131 "minic.y"
{
		int nType = (pTopSymbol-1)->nDataType;
		PSYMBOL pSymbol = AddSymbol(yypvt[-0].szName, SCVARIABLE, nType);

		pSymbol->pInitExpr = NULL;

		if(nCurrentLevel>0)
		{
			PTRIELEMEXPR p = TriElemExprTbl+ip;
			p->op = OTADDVAR;
			p->left.nValue = LOCAL;/*????????*/
			p->right.nValue = 1;/*????????*/
			IncreaseIp();
		}
		free(yypvt[-0].szName);
	} break;
case 7:	/* VAR_DEF : VAR_DEF COMMA ID ASSIGN EXPRESSION */
# line 149 "minic.y"
{
		int nType = (pTopSymbol-1)->nDataType;
		PSYMBOL pSymbol = AddSymbol(yypvt[-2].szName, SCVARIABLE, nType);
		if(yypvt[-1].opValue != ETASSIGN)	yyerror("Error in variable defination, expected '='");

		if(nCurrentLevel == 0)
		{
			if(yypvt[-0].pExpr->SType != CONST)
				yyerror("Global variable assignment error, right value not a constant");
			else
				pSymbol->pInitExpr = MakeVarExpr( ETASSIGN, pSymbol, yypvt[-0].pExpr );
		}
		else
		{
			PEXPR pExpr;
			PTRIELEMEXPR p = TriElemExprTbl+ip;
			p->op = OTADDVAR;/*????????*/
			p->left.nValue = LOCAL;/*????????*/
			p->right.nValue = 1;/*????????*/
			IncreaseIp();

			pExpr = MakeVarExpr( yypvt[-1].opValue, pSymbol, yypvt[-0].pExpr );
			GenExprCode(pExpr);
			FreeExpr(pExpr);
			p = TriElemExprTbl+ip;
			p->op = OTADDVAR;
			p->left.nValue = TEMP;
			p->right.nValue = -1;
			IncreaseIp();
		}
		free(yypvt[-2].szName);
	} break;
case 8:	/* FX_DEF : FX_HEAD COMPOUND_STATEMENT */
# line 186 "minic.y"
{
		PTRIELEMEXPR p;
	 	ASSERT(nCurrentLevel==0)
	 	ASSERT(nLocalVars==0)
	 	nCurrentFxType = -1;
		p = TriElemExprTbl+ip;		
		p->op = OTRETURN;
		IncreaseIp();
	 } break;
case 9:	/* TYPE : YTINT */
# line 199 "minic.y"
{yyval.nValue = DTINT;} break;
case 10:	/* TYPE : YTFLOAT */
# line 200 "minic.y"
{yyval.nValue = DTFLOAT;} break;
case 11:	/* TYPE : YTVOID */
# line 201 "minic.y"
{yyval.nValue = DTVOID;} break;
case 12:	/* FX_HEAD : TYPE ID '(' ARGUMENTS ')' */
# line 207 "minic.y"
{
	 	PSYMBOL pSymbol;
		if(nLocalVars>0)
	 	{
			pTopSymbol -= nLocalVars + 1;
			nCurrentLevel--;
		}
		pSymbol = AddSymbol(yypvt[-3].szName, SCFUNCTION, yypvt[-4].nValue);
		nCurrentFxType = yypvt[-4].nValue;

		pSymbol->nEntry = ip;
		pSymbol->nArgs = nLocalVars;
		pSymbol->nArgEntry = nTopArg - nLocalVars;
		pTopSymbol += nLocalVars;

		free(yypvt[-3].szName);
	} break;
case 13:	/* FX_HEAD : TYPE MAIN '(' ')' */
# line 225 "minic.y"
{
		int i;
		PSYMBOL pGV = SymbolTable;
		PTRIELEMEXPR p;
		nCurrentFxType = yypvt[-3].nValue;
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
	} break;
case 16:	/* ARGUMENTS : TYPE ID */
# line 275 "minic.y"
{
		/*hold a space for function name*/
		AddSymbol("SpaceHolder", SCFUNCTION, DTVOID);

		ASSERT(nCurrentLevel==0)
		ASSERT(nLocalVars == 0)

		nCurrentLevel++;
		AddSymbol(yypvt[-0].szName, SCVARIABLE, yypvt[-1].nValue);
		AddArgs(yypvt[-1].nValue);
		free(yypvt[-0].szName);
	} break;
case 17:	/* ARGUMENTS : ARGUMENTS COMMA TYPE ID */
# line 288 "minic.y"
{
		AddSymbol(yypvt[-0].szName, SCVARIABLE, yypvt[-1].nValue);
		AddArgs(yypvt[-1].nValue);
		free(yypvt[-0].szName);
	} break;
case 18:	/* BEGIN : '{' */
# line 297 "minic.y"
{
		nCurrentLevel++;
	} break;
case 19:	/* END : '}' */
# line 303 "minic.y"
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
	} break;
case 24:	/* STATEMENT : VAR_DEF ';' */
# line 331 "minic.y"
{} break;
case 25:	/* STATEMENT : OPT_EXPR ';' */
# line 335 "minic.y"
{
		if(yypvt[-1].pExpr!=NULL && yypvt[-1].pExpr->SType!=CONST && yypvt[-1].pExpr->ep!=ETVARIABLE)
		{
			PTRIELEMEXPR p;
			GenExprCode(yypvt[-1].pExpr);
			p = TriElemExprTbl+ip;
			p->op = OTADDVAR;
			p->left.nValue = TEMP;
			p->right.nValue = -1;
			IncreaseIp();
		}
		if(yypvt[-1].pExpr!=NULL)	FreeExpr(yypvt[-1].pExpr);
	} break;
case 26:	/* STATEMENT : RETURN OPT_EXPR ';' */
# line 351 "minic.y"
{
		PTRIELEMEXPR p;
		if((nCurrentFxType==DTVOID && yypvt[-1].pExpr!=NULL)
			|| (nCurrentFxType!=DTVOID && yypvt[-1].pExpr==NULL))
			yyerror("Function return type error");

		if(yypvt[-1].pExpr != NULL)
		{
			PEXPR pExpr;
			SYMBOL temp;
			temp.nClass = SCVARIABLE;
			temp.nDataType = nCurrentFxType;
			temp.nLevel = 1;
			temp.nEntry = -1;

			pExpr = MakeVarExpr(ETASSIGN, &temp, yypvt[-1].pExpr);
			GenExprCode(pExpr);
			FreeExpr(pExpr);
		}
		p = TriElemExprTbl+ip;		
		p->op = OTRETURN;
		IncreaseIp();
	} break;
case 27:	/* STATEMENT : READ '(' ')' ';' */
# line 377 "minic.y"
{
		PTRIELEMEXPR p = TriElemExprTbl+ip;
		p->op = OTREADLN;
		IncreaseIp();
	} break;
case 28:	/* STATEMENT : READ '(' ID ')' ';' */
# line 385 "minic.y"
{
		PSYMBOL pSymbol = FindSymbol( yypvt[-2].szName, nCurrentLevel, 0 );
		if( pSymbol==NULL || pSymbol->nClass!=SCVARIABLE )
		{
			PrintError("Unrecognized Variable Name",yypvt[-2].szName);
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
		free(yypvt[-2].szName);
	} break;
case 29:	/* STATEMENT : WRITE '(' OPT_EXPR ')' ';' */
# line 405 "minic.y"
{
		PTRIELEMEXPR p;
		if(yypvt[-2].pExpr==NULL)
		{
			p = TriElemExprTbl+ip;
			p->op = OTWRITELN;
			IncreaseIp();
			break;
		}
		GenWriteCode(yypvt[-2].pExpr);
		FreeExpr(yypvt[-2].pExpr);
	} break;
case 30:	/* STATEMENT : INITGRAPH '(' ')' ';' */
# line 419 "minic.y"
{
		PTRIELEMEXPR p = TriElemExprTbl+ip;
		p->op = OTINITGRAPH;
		IncreaseIp();
	} break;
case 31:	/* STATEMENT : CLOSEGRAPH '(' ')' ';' */
# line 425 "minic.y"
{
		PTRIELEMEXPR p = TriElemExprTbl+ip;
		p->op = OTCLOSEGRAPH;
		IncreaseIp();
	} break;
case 32:	/* STATEMENT : MOVETO '(' EXPRESSION ')' ';' */
# line 431 "minic.y"
{
		PTRIELEMEXPR p;
		PEXPR pLeft, pRight;
		if(yypvt[-2].pExpr->ep!=ETCOMMA || yypvt[-2].pExpr->bSubExpr)
		{
			yyerror("'moveto' need 2 parameters");
			FreeExpr(yypvt[-2].pExpr);
			break;
		}
		pLeft = yypvt[-2].pExpr->Content.CaseEp.pLeft;
		pRight = yypvt[-2].pExpr->Content.CaseEp.pRight;
		if(pLeft->ep==ETCOMMA && !pLeft->bSubExpr)
		{
			yyerror("'moveto' need only 2 parameters");
			FreeExpr(yypvt[-2].pExpr);
			break;
		}
		GenExprCode(pRight);
		GenExprCode(pLeft);
		p = TriElemExprTbl + ip;
		p->op = OTMOVETO;
		FillOperand(0, pLeft);
		FillOperand(1, pRight);
		IncreaseIp();
		FreeExpr(yypvt[-2].pExpr);
	} break;
case 33:	/* STATEMENT : LINETO '(' EXPRESSION ')' ';' */
# line 458 "minic.y"
{
		PTRIELEMEXPR p;
		PEXPR pLeft, pRight;
		if(yypvt[-2].pExpr->ep!=ETCOMMA || yypvt[-2].pExpr->bSubExpr)
		{
			yyerror("'lineto' need 2 parameters");
			FreeExpr(yypvt[-2].pExpr);
			break;
		}
		pLeft = yypvt[-2].pExpr->Content.CaseEp.pLeft;
		pRight = yypvt[-2].pExpr->Content.CaseEp.pRight;
		if(pLeft->ep==ETCOMMA && !pLeft->bSubExpr)
		{
			yyerror("'lineto' need only 2 parameters");
			FreeExpr(yypvt[-2].pExpr);
			break;
		}
		GenExprCode(pRight);
		GenExprCode(pLeft);
		p = TriElemExprTbl + ip;
		p->op = OTLINETO;
		FillOperand(0, pLeft);
		FillOperand(1, pRight);
		IncreaseIp();
		FreeExpr(yypvt[-2].pExpr);
	} break;
case 34:	/* STATEMENT : SETCOLOR '(' EXPRESSION ')' ';' */
# line 486 "minic.y"
{
		PTRIELEMEXPR p;
		if(yypvt[-2].pExpr->ep==ETCOMMA && !yypvt[-2].pExpr->bSubExpr)
			yyerror("'lineto' need 2 parameters");
		GenExprCode(yypvt[-2].pExpr);
		p = TriElemExprTbl + ip;
		p->op = OTSETCOLOR;
		FillOperand(0, yypvt[-2].pExpr);
		IncreaseIp();
		FreeExpr(yypvt[-2].pExpr);
	} break;
case 36:	/* STATEMENT : IF '(' IF_EXPR ')' STATEMENT */
# line 502 "minic.y"
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
	} break;
case 37:	/* STATEMENT : WHILE '(' WHILE_EXPR ')' STATEMENT */
# line 519 "minic.y"
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
	} break;
case 38:	/* STATEMENT : DODO STATEMENT WHILE '(' EXPRESSION ')' ';' */
# line 542 "minic.y"
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
		GenExprCode(yypvt[-2].pExpr);
		p = TriElemExprTbl+ip;
		p->op = OTJNZ;
		FillOperand(0, yypvt[-2].pExpr);
		jp--;
		p->right.nValue = JmpTbl[jp];
		IncreaseIp();
		FreeExpr(yypvt[-2].pExpr);
	} break;
case 39:	/* STATEMENT : IF '(' IF_EXPR ')' STATEMENT ELSEELSE STATEMENT */
# line 566 "minic.y"
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
	} break;
case 40:	/* STATEMENT : FOR '(' FOR_EXPR1 ';' OPT_EXPR ';' OPT_EXPR ')' STATEMENT */
# line 584 "minic.y"
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
		GenExprCode(yypvt[-2].pExpr);
		if(yypvt[-2].pExpr!=NULL && yypvt[-2].pExpr->SType!=CONST && yypvt[-2].pExpr->ep!=ETVARIABLE)
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
		if(yypvt[-4].pExpr==NULL)
		{
			p = TriElemExprTbl + ip;
			p->op = OTJMP;
			p->right.nValue = JmpTbl[jp]+1;
		}
		else
		{
			GenExprCode(yypvt[-4].pExpr);
			p = TriElemExprTbl + ip;
			p->op = OTJNZ;
			FillOperand(0,yypvt[-4].pExpr);
			p->right.nValue = JmpTbl[jp]+1;
		}
		IncreaseIp();
		FreeExpr(yypvt[-4].pExpr);
		FreeExpr(yypvt[-2].pExpr);
	} break;
case 41:	/* EXPRESSION : ID ASSIGN EXPRESSION */
# line 631 "minic.y"
{
		PSYMBOL pSymbol = FindSymbol( yypvt[-2].szName, nCurrentLevel, 0 );
		if( pSymbol==NULL || pSymbol->nClass!=SCVARIABLE )
		{
			PrintError("Unrecognized Variable Name",yypvt[-2].szName);
			yyval.pExpr = yypvt[-0].pExpr;
		}
		else
		{
			if(yypvt[-1].opValue==ETMODASSIGN &&( pSymbol->nDataType!=DTINT || yypvt[-0].pExpr->DType!=DTINT))
				yyerror("Illegal use of floating point");
			yyval.pExpr = MakeVarExpr( yypvt[-1].opValue, pSymbol, yypvt[-0].pExpr );
			yyval.pExpr->DType = pSymbol->nDataType;
		}
		free(yypvt[-2].szName);
	} break;
case 42:	/* EXPRESSION : EXPRESSION OR EXPRESSION */
# line 649 "minic.y"
{
		yyval.pExpr = MakeEpExpr( yypvt[-1].opValue, yypvt[-2].pExpr, yypvt[-0].pExpr );
		yyval.pExpr->DType = DTINT;
	} break;
case 43:	/* EXPRESSION : EXPRESSION AND EXPRESSION */
# line 655 "minic.y"
{
		yyval.pExpr = MakeEpExpr( yypvt[-1].opValue, yypvt[-2].pExpr, yypvt[-0].pExpr );
		yyval.pExpr->DType = DTINT;		
	} break;
case 44:	/* EXPRESSION : EXPRESSION EQU EXPRESSION */
# line 661 "minic.y"
{
		yyval.pExpr = MakeEpExpr( yypvt[-1].opValue, yypvt[-2].pExpr, yypvt[-0].pExpr );
		yyval.pExpr->DType = DTINT;		
	} break;
case 45:	/* EXPRESSION : EXPRESSION COMPARE EXPRESSION */
# line 667 "minic.y"
{
		yyval.pExpr = MakeEpExpr( yypvt[-1].opValue, yypvt[-2].pExpr, yypvt[-0].pExpr );
		yyval.pExpr->DType = DTINT;		
	} break;
case 46:	/* EXPRESSION : EXPRESSION ADD EXPRESSION */
# line 673 "minic.y"
{
		yyval.pExpr = MakeEpExpr( yypvt[-1].opValue, yypvt[-2].pExpr, yypvt[-0].pExpr );
		if(yypvt[-2].pExpr->DType==DTINT && yypvt[-0].pExpr->DType==DTINT)
			yyval.pExpr->DType = DTINT;
		else
			yyval.pExpr->DType = DTFLOAT;
	} break;
case 47:	/* EXPRESSION : EXPRESSION MUL EXPRESSION */
# line 682 "minic.y"
{
		if(yypvt[-1].opValue==ETMOD &&( yypvt[-2].pExpr->DType!=DTINT || yypvt[-0].pExpr->DType!=DTINT))
			yyerror("Illegal use of floating point");
		yyval.pExpr = MakeEpExpr( yypvt[-1].opValue, yypvt[-2].pExpr, yypvt[-0].pExpr );
		if(yypvt[-2].pExpr->DType==DTINT && yypvt[-0].pExpr->DType==DTINT)
			yyval.pExpr->DType = DTINT;
		else
			yyval.pExpr->DType = DTFLOAT;
	} break;
case 48:	/* EXPRESSION : EXPRESSION COMMA EXPRESSION */
# line 693 "minic.y"
{
		yyval.pExpr = MakeEpExpr( yypvt[-1].opValue, yypvt[-2].pExpr, yypvt[-0].pExpr );
		yyval.pExpr->DType = yypvt[-0].pExpr->DType;
	} break;
case 49:	/* EXPRESSION : MATHFX '(' EXPRESSION ')' */
# line 699 "minic.y"
{
		yyval.pExpr = MakeEpExpr( yypvt[-3].opValue, yypvt[-1].pExpr, NULL);
		yyval.pExpr->DType = DTFLOAT;
	} break;
case 50:	/* EXPRESSION : NOT EXPRESSION */
# line 705 "minic.y"
{
		yyval.pExpr = MakeEpExpr( yypvt[-1].opValue, yypvt[-0].pExpr, NULL );
		yyval.pExpr->DType = DTINT;		
	} break;
case 51:	/* EXPRESSION : ADD EXPRESSION */
# line 711 "minic.y"
{
		if(yypvt[-1].opValue == ETADD)
			yyval.pExpr = yypvt[-0].pExpr;
		else
		{
			yyval.pExpr = MakeEpExpr(ETMINUS, yypvt[-0].pExpr, NULL);
			yyval.pExpr->DType = yypvt[-0].pExpr->DType;
		}
	} break;
case 52:	/* EXPRESSION : INC ID */
# line 722 "minic.y"
{
		PSYMBOL pSymbol = FindSymbol( yypvt[-0].szName, nCurrentLevel, 0 );
		if( pSymbol==NULL || pSymbol->nClass!=SCVARIABLE )
		{
			PrintError("Unrecognized variable name",yypvt[-0].szName);
			yyval.pExpr = NULL;
		}
		else
		{
			yyval.pExpr = MakeVarExpr(yypvt[-1].opValue, pSymbol, NULL);
			yyval.pExpr->DType = pSymbol->nDataType;
		}
		free(yypvt[-0].szName);
	} break;
case 53:	/* EXPRESSION : ID INC */
# line 738 "minic.y"
{
		PSYMBOL pSymbol = FindSymbol( yypvt[-1].szName, nCurrentLevel, 0 );
		if( pSymbol==NULL || pSymbol->nClass!=SCVARIABLE )
		{
			PrintError("Unrecognized variable name",yypvt[-1].szName);
			yyval.pExpr = NULL;
		}
		else
		{
			yyval.pExpr = MakeVarExpr(yypvt[-0].opValue + 2, pSymbol, NULL); /*post inc should be $2+2*/
			yyval.pExpr->DType = pSymbol->nDataType;			
		}
		free(yypvt[-1].szName);
	} break;
case 54:	/* EXPRESSION : '(' EXPRESSION ')' */
# line 759 "minic.y"
{
		yyval.pExpr = yypvt[-1].pExpr;
		yyval.pExpr->bSubExpr = TRUE;
	} break;
case 55:	/* EXPRESSION : ID */
# line 765 "minic.y"
{
		PSYMBOL pSymbol = FindSymbol( yypvt[-0].szName, nCurrentLevel, 0 );
		if( pSymbol==NULL || pSymbol->nClass!=SCVARIABLE )
		{
			PrintError("Unrecognized variable name",yypvt[-0].szName);
			yyval.pExpr = NULL;
		}
		else
		{
			yyval.pExpr = MakeVarExpr(ETVARIABLE, pSymbol, NULL);
			yyval.pExpr->DType = pSymbol->nDataType;			
		}
		free(yypvt[-0].szName);
	} break;
case 56:	/* EXPRESSION : REAL */
# line 781 "minic.y"
{
		yyval.pExpr = MakeFloatExpr( yypvt[-0].fValue );
		yyval.pExpr->DType = DTFLOAT;
	} break;
case 57:	/* EXPRESSION : INTEGER */
# line 787 "minic.y"
{
		yyval.pExpr = MakeIntExpr( yypvt[-0].nValue );
		yyval.pExpr->DType = DTINT;
	} break;
case 58:	/* EXPRESSION : ID '(' OPT_EXPR ')' */
# line 793 "minic.y"
{
		PSYMBOL pSymbol = FindSymbol( yypvt[-3].szName, nCurrentLevel, 0 );
		if( pSymbol==NULL || pSymbol->nClass!=SCFUNCTION )
		{
			PrintError("Unrecognized function name",yypvt[-3].szName);
			yyval.pExpr = yypvt[-1].pExpr;
		}
		else
		{
			BYTE nArgs = 0;
			PEXPR pTemp = yypvt[-1].pExpr;
			while( pTemp!=NULL )
			{
				nArgs++;
				if(pTemp->ep==ETCOMMA && !pTemp->bSubExpr)
					pTemp = pTemp->Content.CaseEp.pLeft;
				else
					pTemp = NULL;
			}
			if( nArgs > pSymbol->nArgs )
				PrintError("Too more arguments in function call",yypvt[-3].szName);
			else if( nArgs<pSymbol->nArgs )
				PrintError("Too few arguments in function call",yypvt[-3].szName);
			yyval.pExpr = MakeFxExpr( pSymbol, yypvt[-1].pExpr );
			yyval.pExpr->DType = pSymbol->nDataType;
		}
		free(yypvt[-3].szName);
	} break;
case 59:	/* ID : NAME */
# line 826 "minic.y"
{
		int nLen = yypvt[-0].nValue;
		if( nLen > MAX_SYMBOL_NAME_LENGTH )
			nLen = MAX_SYMBOL_NAME_LENGTH;
		yyval.szName = (char*)malloc(	MAX_SYMBOL_NAME_LENGTH + 1 );
		memcpy( yyval.szName, yytext, nLen );
		yyval.szName[nLen] = '\0';
	} break;
case 60:	/* ID : '(' ID ')' */
# line 836 "minic.y"
{
		yyval.szName = yypvt[-1].szName;
	} break;
case 61:	/* IF_EXPR : EXPRESSION */
# line 843 "minic.y"
{
		PTRIELEMEXPR p;
		GenExprCode(yypvt[-0].pExpr);
		JmpTbl[jp] = ip;
		IncreaseJp;
		p = TriElemExprTbl + ip;
		p->op = OTJZ;
		FillOperand(0, yypvt[-0].pExpr);
		IncreaseIp();
		nCurrentLevel++;
		FreeExpr(yypvt[-0].pExpr);
	} break;
case 62:	/* FOR_EXPR1 : OPT_EXPR */
# line 859 "minic.y"
{
		PTRIELEMEXPR p;
		GenExprCode(yypvt[-0].pExpr);
		if(yypvt[-0].pExpr!=NULL && yypvt[-0].pExpr->SType!=CONST && yypvt[-0].pExpr->ep!=ETVARIABLE)
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
		FreeExpr(yypvt[-0].pExpr);
	} break;
case 63:	/* WHILE_EXPR : EXPRESSION */
# line 883 "minic.y"
{
		PTRIELEMEXPR p;
		JmpTbl[jp] = ip;
		IncreaseJp;

		GenExprCode(yypvt[-0].pExpr);
		p = TriElemExprTbl + ip;
		p->op = OTJZ;
		FillOperand(0, yypvt[-0].pExpr);
		JmpTbl[jp] = ip;
		IncreaseJp;
		IncreaseIp();

		nCurrentLevel++;
		FreeExpr(yypvt[-0].pExpr);
	} break;
case 64:	/* ELSEELSE : ELSE */
# line 903 "minic.y"
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
	 } break;
case 65:	/* DODO : DO */
# line 931 "minic.y"
{
		JmpTbl[jp] = ip;
		nCurrentLevel++;
		IncreaseJp;
	} break;
case 66:	/* OPT_EXPR : (empty) */
# line 939 "minic.y"
{
		yyval.pExpr = NULL;
	} break;
case 67:	/* OPT_EXPR : EXPRESSION */
# line 944 "minic.y"
{
		yyval.pExpr = yypvt[-0].pExpr;
	} break;

	}
	goto yystack;           /* reset registers in driver code */
}
# ifndef YY_ADVANCE_ERROR_HOLD_NOT_USED
yyinsert (int token, YYSTYPE value)
{
		int yyn;

		if ( ( yyn = yypact[ *yyps ] ) <= YYFLAG )
			return 0 ;
		if ( ( ( yyn += token ) < 0 ) || ( yyn >= YYLAST ) )
			return 0 ;
		if ( yychk[ yyn = yyact[ yyn ] ] != token )
			return 0 ;
		yystate = yyn;
		if ( ++yyps >= &yys[ YYMAXDEPTH ] )
		{
			yyerror( "yacc stack overflow" );
			return 0 ;
		}
		*yyps = yystate;
		*++yypv = value;
		return 1 ;
}

int yyexpect (int token)
{ 
	while (yychar && yychar != (token)) 
		if ((yychar = yylex()) <=0) 
			yychar = 0;
	return yychar != 0;
}
# endif