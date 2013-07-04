typedef union  {
	float fValue;
	int nValue;
	int opValue;
	char* szName;
	PEXPR pExpr;
	void vValue;
} YYSTYPE;
extern YYSTYPE yylval;
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
