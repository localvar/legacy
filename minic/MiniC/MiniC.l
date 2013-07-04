%{
#include<stdio.h>
#include<math.h>
#include "d:\zbmprj\minic\misc.h"
#include "d:\zbmprj\minic\symbol.h"
#include "d:\zbmprj\minic\expr.h"
#include "d:\zbmprj\minic\term.h"

unsigned nLineNo = 1;
%}

%x comment1 comment2 selfop

name [_a-zA-Z]([_a-zA-Z0-9])*
num  [0-9]+
WhiteSpace   [ \t]+
LineComment  "//"
BlockComment "/*"

%%

{LineComment}          BEGIN comment1;
{BlockComment}         BEGIN comment2;
{WhiteSpace}           ;
{num}                  yylval.nValue = atoi(yytext); return INTEGER;
{num}\.{num}?          yylval.fValue = atof(yytext); return REAL;
{num}(\.{num}*)?[Ee][-+]?{num}   yylval.fValue = atof(yytext); return REAL;
\n		               nLineNo++;
"if"                   return IF;
"for"				   return FOR;
"while"				   return WHILE;
"do"				   return DO;
"int"                  return YTINT;
"float"				   return YTFLOAT;
"void"				   return YTVOID;
"return"               return RETURN;
"main"				   return MAIN;
"else"				   return ELSE;
"read"				   return READ;
"write"				   return WRITE;
"initgraph"			   return INITGRAPH;
"closegraph"		   return CLOSEGRAPH;
"moveto"			   return MOVETO;
"lineto"			   return LINETO;
"setcolor"			   return SETCOLOR;
"sin"				   yylval.opValue = ETSIN; 			return MATHFX;
"cos"				   yylval.opValue = ETCOS;			return MATHFX;
"tan"				   yylval.opValue = ETTAN;			return MATHFX;
"sqrt"				   yylval.opValue = ETSQRT;			return MATHFX;
"exp"				   yylval.opValue = ETEXP;			return MATHFX;
"log"				   yylval.opValue = ETLOG;			return MATHFX;
","					   yylval.opValue = ETCOMMA;		return COMMA;
[(){};]				   return yytext[0];
"<"					   yylval.opValue = ETSMALL; 		return COMPARE;
">"					   yylval.opValue = ETLARGE; 		return COMPARE;
"="					   yylval.opValue = ETASSIGN; 		return ASSIGN;
"+"                    yylval.opValue = ETADD; 			return ADD;
"-"                    yylval.opValue = ETSUB; 			return ADD;
"*"                    yylval.opValue = ETMUL; 			return MUL;
"/"                    yylval.opValue = ETDIV; 			return MUL;
"%"                    yylval.opValue = ETMOD; 			return MUL;
"!"                    yylval.opValue = ETNOT; 			return NOT;
">="				   yylval.opValue = ETLARGEEQU; 	return COMPARE;
"<="  				   yylval.opValue = ETSMALLEQU; 	return COMPARE;
"+="                   yylval.opValue = ETADDASSIGN; 	return ASSIGN;
"-="                   yylval.opValue = ETSUBASSIGN; 	return ASSIGN;
"*="                   yylval.opValue = ETMULASSIGN; 	return ASSIGN;
"/="                   yylval.opValue = ETDIVASSIGN; 	return ASSIGN;
"%="                   yylval.opValue = ETMODASSIGN; 	return ASSIGN;
"&&"                   yylval.opValue = ETAND; 			return AND;
"||"                   yylval.opValue = ETOR; 			return OR;
"=="				   yylval.opValue = ETEQU; 			return EQU;
"!="				   yylval.opValue = ETNOTEQU; 		return EQU;
"++"				   yylval.opValue = ETINC; BEGIN selfop; return INC;
"--"				   yylval.opValue = ETDEC; BEGIN selfop; return INC;
{name}				   yylval.nValue = yyleng; return NAME;
{num}{name}	           return ERRTOKEN;
.                      return ERRTOKEN;
<comment1>.			   ;
<comment1>\n		   BEGIN 0; nLineNo++;
<comment2>.			   ;
<comment2>\n 		   nLineNo++;
<comment2>"*/"         BEGIN 0;
<selfop>"-"			   yylval.opValue = ETSUB; BEGIN 0; return ADD;	
<selfop>"+"			   yylval.opValue = ETADD; BEGIN 0; return ADD;
<selfop>\n			   nLineNo++;
<selfop>{WhiteSpace}   ;
<selfop>.			   unput(yytext[0]); BEGIN 0;

%%

void ScannerRestart(FILE* fp)
{
	if(fp==NULL)
	{
    	if ( yyin != stdin )
		{
			fclose( yyin );
			yyrestart( stdin );
		}
		return;
	}
	yyrestart(fp);
}