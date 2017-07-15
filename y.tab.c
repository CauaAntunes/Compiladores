/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "parser.y"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

AST* create(int type, char* key, AST* son0, AST* son1, AST* son2, AST* son3){
	AST *tree = (AST*) calloc(1, sizeof(AST));
	tree->type = type;
	if(key == NULL)
		tree->hash_key = NULL;
	else
		tree->hash_key = strdup(key);
	tree->son[0] = son0;
	tree->son[1] = son1;
	tree->son[2] = son2;
	tree->son[3] = son3;
	return tree;
}

#line 23 "parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union{ char* symbol; AST* tree;} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 50 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define KW_BYTE 257
#define KW_SHORT 258
#define KW_LONG 259
#define KW_FLOAT 260
#define KW_DOUBLE 261
#define KW_WHEN 262
#define KW_THEN 263
#define KW_ELSE 264
#define KW_WHILE 265
#define KW_FOR 266
#define KW_TO 267
#define KW_READ 268
#define KW_RETURN 269
#define KW_PRINT 270
#define OPERATOR_LE 271
#define OPERATOR_GE 272
#define OPERATOR_EQ 273
#define OPERATOR_NE 274
#define OPERATOR_AND 275
#define OPERATOR_OR 276
#define TK_IDENTIFIER 277
#define LIT_INTEGER 278
#define LIT_REAL 279
#define LIT_CHAR 280
#define LIT_STRING 281
#define TOKEN_ERROR 282
#define VDEF 283
#define FDEF 284
#define FCALL 285
#define FPAR 286
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    1,    1,    2,    2,   18,    3,    3,   19,    4,
    4,    5,    5,    5,    6,    6,    6,    6,    6,    7,
    8,    8,    9,    9,   10,   10,   11,   11,   12,   12,
   14,   14,   13,   13,   13,   13,   13,   13,   13,   13,
   13,   13,   13,   15,   15,   16,   16,   17,   17,   17,
   17,   17,   17,   17,   17,   17,   17,   17,   17,   17,
   17,   17,   17,   17,   17,
};
static const YYINT yylen[] = {                            2,
    1,    3,    2,    1,    1,    1,    4,    7,    1,    2,
    0,    1,    1,    1,    1,    1,    1,    1,    1,    6,
    1,    0,    4,    2,    1,    0,    3,    1,    3,    2,
    3,    2,    1,    3,    5,    2,    2,    2,    6,    8,
    5,    9,    0,    2,    1,    1,    1,    3,    3,    3,
    3,    1,    4,    4,    3,    3,    2,    3,    3,    3,
    3,    3,    3,    1,    3,
};
static const YYINT yydefred[] = {                         0,
   15,   16,   17,   18,   19,    6,    0,    1,    0,    4,
    0,    5,    0,    0,    0,    0,    2,    0,    0,    0,
    0,   21,   12,   13,   14,    0,    7,    0,    0,    9,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   33,
   20,    0,    0,   23,    0,    0,    0,   36,    0,    0,
   64,    0,    0,   47,   37,    0,    0,   30,    0,    0,
    0,    0,    8,    0,    0,    0,    0,   57,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   44,    0,   29,    0,    0,   10,    0,
    0,    0,   65,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   50,   51,    0,    0,   25,    0,   31,
    0,    0,   41,    0,   54,   53,    0,    0,    0,    0,
   27,    0,    0,   40,    0,   42,
};
static const YYINT yydgoto[] = {                          7,
    8,    9,   10,   63,   51,   11,   12,   21,   22,  107,
  108,   40,   59,   60,   55,   56,   57,   53,   31,
};
static const YYINT yysindex[] = {                      -239,
    0,    0,    0,    0,    0,    0,    0,    0,  -52,    0,
 -253,    0,  -26, -239,  -15, -170,    0, -170,  -78, -253,
    1,    0,    0,    0,    0, -234,    0,    3,  323,    0,
  -48, -170,    8,   15,   19, -253,  145,  137,  -86,    0,
    0,  -18, -171,    0,  145,  145, -253,    0,  145,  145,
    0,  351,  -25,    0,    0,  137,  351,    0,    4,  -60,
  145,  145,    0, -171,  425,  433,    6,    0,  447,  145,
  145,  145,  145,  145,  145,  145,  145,  145,  145,  145,
  145,  145,  145,    0,  323,    0,  351,  259,    0, -193,
  323,  145,    0,   39,   39,   39,   39,  503,  503,   39,
   39,   -6,   -6,    0,    0,  282,   30,    0,  482,    0,
  145,  323,    0,  305,    0,    0,  145,  351, -185,  145,
    0,  323,  461,    0,  323,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   85,    0,    0,    0,   52,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   53,   42,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   42,    0,
    0,    0,   43,    0,    0,    0,    0,    0,    0,    0,
    0,  -58,  -33,    0,    0,  -56,  219,    0,    0,    0,
    0,    0,    0,   43,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   63,    0,  -57,    0,  -55,    0,    0,    0,
  -54,    0,    0,   36,   59,   82,  105,  388,  412,  128,
  163,  -10,   13,    0,    0,    0,    0,    0,   64,    0,
    0,  -54,    0,    0,    0,    0,    0,  -53,   51,    0,
    0,  -54,    0,    0,  -54,    0,
};
static const YYINT yygindex[] = {                         0,
   97,    0,    0,   48,   -3,   46,    0,    0,   81,    0,
   -1,    0,  104,   29,   61,    0,  537,  731,    0,
};
#define YYTABLESIZE 856
static const YYINT yytable[] = {                         52,
   38,   43,   45,   34,   43,   35,   14,   52,   52,   52,
   52,   52,   26,   52,   83,   27,   62,    1,    2,    3,
    4,    5,   48,    6,   18,   52,   52,   52,   52,   48,
   48,   16,   48,   48,   48,   80,   39,    6,   58,   64,
   81,   29,   61,   30,   43,   49,   32,   45,   48,   48,
   48,   48,   49,   49,   46,   49,   49,   49,   47,   52,
   64,   19,   85,   20,   86,   82,   92,   32,   58,  112,
  116,   49,   49,   49,   49,   58,   58,   20,  122,   58,
   80,   78,   48,   79,    3,   81,    1,    2,    3,    4,
    5,   59,   22,   24,   58,   58,   58,   58,   59,   59,
   43,   11,   59,   26,   28,   49,   23,   24,   25,   39,
   17,   89,   44,  110,   60,  121,   84,   59,   59,   59,
   59,   60,   60,    0,    0,   60,    0,    0,   58,    0,
    0,    0,   41,    0,    0,    0,    0,   61,    0,    0,
   60,   60,   60,   60,   61,   61,    0,    0,   61,    0,
    0,   59,    0,    0,    0,    0,    0,    0,    0,    0,
   56,    0,    0,   61,   61,   61,   61,   56,   56,   49,
    0,   56,    0,    0,   60,   33,   50,   49,   34,   35,
    0,   36,   37,   38,   50,    0,   56,   56,   56,   56,
    6,    0,    0,    0,  113,   55,    0,   61,    0,   23,
   24,   25,   55,   55,    0,   38,   55,   45,   34,   43,
   35,    0,    0,    0,    0,  119,    0,    0,    0,    0,
   56,   55,   55,   55,   55,  124,    0,    0,  126,    0,
   52,    0,    0,   52,    0,    0,    0,   52,   52,   52,
   52,   52,   52,   52,   52,   52,   52,   52,    0,    0,
    0,   46,    0,   48,    0,   55,   48,    0,   46,    0,
   48,   48,   48,   48,   48,   48,   48,   48,   48,   48,
   48,    0,    0,    0,    0,    0,   49,   46,    0,   49,
    0,    0,    0,   49,   49,   49,   49,   49,   49,   49,
   49,   49,   49,   49,    0,    0,    0,    0,    0,   58,
   80,   78,   58,   79,    0,   81,   58,   58,   58,   58,
   58,   58,   58,   58,   58,   58,   58,    0,   77,  111,
   76,    0,   59,   80,   78,   59,   79,    0,   81,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
    0,   77,    0,   76,    0,   60,   80,   78,   60,   79,
    0,   81,   60,   60,   60,   60,   60,   60,   60,   60,
   60,   60,   60,    0,   77,    0,   76,    0,   61,    0,
    0,   61,    0,    0,  115,   61,   61,   61,   61,   61,
   61,   61,   61,   61,   61,   61,    0,    0,    0,    0,
    0,   56,   80,   78,   56,   79,    0,   81,   56,   56,
   56,   56,   56,   56,   56,   56,   56,   56,   56,    0,
   77,    0,   76,    6,   23,   24,   25,   54,    0,    0,
   62,    6,   23,   24,   25,    0,   55,   62,   62,   55,
    0,   62,    0,   55,   55,   55,   55,   55,   55,   55,
   55,   55,   55,   55,   63,   39,   62,    0,   62,    0,
    0,   63,   63,    0,    0,   63,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   90,   80,   78,    0,   79,
   63,   81,   63,   91,   80,   78,    0,   79,    0,   81,
   62,    0,   46,    0,   77,    0,   76,   93,   80,   78,
    0,   79,   77,   81,   76,   46,   46,   46,   46,   46,
    0,  125,   80,   78,   63,   79,   77,   81,   76,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   77,    0,   76,   80,   78,  117,   79,    0,   81,   70,
   71,   72,   73,   74,   75,    0,    0,    0,    0,    0,
    0,   77,    0,   76,   80,   78,    0,   79,    0,   81,
    0,    0,   70,   71,   72,   73,   74,   75,    0,    0,
    0,    0,   77,    0,   76,    0,    0,    0,    0,    0,
    0,  120,    0,   52,    0,   70,   71,   72,   73,   74,
   75,   65,   66,    0,   33,   68,   69,   34,   35,    0,
   36,   37,   38,    0,    0,    0,    0,   87,   88,    6,
    0,    0,    0,    0,    0,    0,   94,   95,   96,   97,
   98,   99,  100,  101,  102,  103,  104,  105,  106,  109,
    0,   70,   71,   72,   73,   74,   75,    0,  114,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  118,    0,    0,
    0,   62,    0,  109,   62,    0,  123,    0,    0,    0,
    0,    0,   62,   62,   62,   62,   62,   62,   62,    0,
    0,    0,    0,    0,    0,   63,    0,    0,   63,    0,
    0,    0,    0,    0,    0,    0,   63,   63,   63,   63,
   63,   63,   63,    0,    0,   70,   71,   72,   73,   74,
   75,    0,    0,   70,   71,   72,   73,   74,   75,    0,
    0,    0,    0,    0,    0,    0,    0,   70,   71,   72,
   73,   74,   75,    0,    0,    0,    0,    0,    0,    0,
   13,   70,   71,   72,   73,   74,   75,    0,    0,    0,
    0,   15,    0,    0,   13,    0,    0,    0,    0,    0,
   28,    0,   70,   71,   72,   73,   74,   75,    0,   42,
    0,    0,    0,    0,    0,    0,   48,    0,    0,   42,
    0,    0,    0,   70,   71,   72,   73,   67,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   42,    0,    0,    0,    0,
    0,   42,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   42,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   42,    0,    0,   42,
};
static const YYINT yycheck[] = {                         33,
   59,   59,   59,   59,   59,   59,   59,   41,   42,   43,
   44,   45,   91,   47,   40,   19,   35,  257,  258,  259,
  260,  261,   33,  277,   40,   59,   60,   61,   62,   40,
   41,   58,   43,   44,   45,   42,  123,  277,  125,   43,
   47,   41,   61,  278,   93,   33,   44,   40,   59,   60,
   61,   62,   40,   41,   40,   43,   44,   45,   40,   93,
   64,   16,   59,   18,  125,   91,   61,  125,   33,  263,
   41,   59,   60,   61,   62,   40,   41,   32,  264,   44,
   42,   43,   93,   45,    0,   47,  257,  258,  259,  260,
  261,   33,   41,   41,   59,   60,   61,   62,   40,   41,
   59,   59,   44,   41,   41,   93,  278,  279,  280,   59,
   14,   64,   32,   85,   33,  117,   56,   59,   60,   61,
   62,   40,   41,   -1,   -1,   44,   -1,   -1,   93,   -1,
   -1,   -1,   29,   -1,   -1,   -1,   -1,   33,   -1,   -1,
   59,   60,   61,   62,   40,   41,   -1,   -1,   44,   -1,
   -1,   93,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   33,   -1,   -1,   59,   60,   61,   62,   40,   41,   33,
   -1,   44,   -1,   -1,   93,  262,   40,   33,  265,  266,
   -1,  268,  269,  270,   40,   -1,   59,   60,   61,   62,
  277,   -1,   -1,   -1,   91,   33,   -1,   93,   -1,  278,
  279,  280,   40,   41,   -1,  264,   44,  264,  264,  264,
  264,   -1,   -1,   -1,   -1,  112,   -1,   -1,   -1,   -1,
   93,   59,   60,   61,   62,  122,   -1,   -1,  125,   -1,
  264,   -1,   -1,  267,   -1,   -1,   -1,  271,  272,  273,
  274,  275,  276,  277,  278,  279,  280,  281,   -1,   -1,
   -1,   33,   -1,  264,   -1,   93,  267,   -1,   40,   -1,
  271,  272,  273,  274,  275,  276,  277,  278,  279,  280,
  281,   -1,   -1,   -1,   -1,   -1,  264,   59,   -1,  267,
   -1,   -1,   -1,  271,  272,  273,  274,  275,  276,  277,
  278,  279,  280,  281,   -1,   -1,   -1,   -1,   -1,  264,
   42,   43,  267,   45,   -1,   47,  271,  272,  273,  274,
  275,  276,  277,  278,  279,  280,  281,   -1,   60,   61,
   62,   -1,  264,   42,   43,  267,   45,   -1,   47,  271,
  272,  273,  274,  275,  276,  277,  278,  279,  280,  281,
   -1,   60,   -1,   62,   -1,  264,   42,   43,  267,   45,
   -1,   47,  271,  272,  273,  274,  275,  276,  277,  278,
  279,  280,  281,   -1,   60,   -1,   62,   -1,  264,   -1,
   -1,  267,   -1,   -1,   93,  271,  272,  273,  274,  275,
  276,  277,  278,  279,  280,  281,   -1,   -1,   -1,   -1,
   -1,  264,   42,   43,  267,   45,   -1,   47,  271,  272,
  273,  274,  275,  276,  277,  278,  279,  280,  281,   -1,
   60,   -1,   62,  277,  278,  279,  280,  281,   -1,   -1,
   33,  277,  278,  279,  280,   -1,  264,   40,   41,  267,
   -1,   44,   -1,  271,  272,  273,  274,  275,  276,  277,
  278,  279,  280,  281,   33,  123,   59,   -1,   61,   -1,
   -1,   40,   41,   -1,   -1,   44,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   41,   42,   43,   -1,   45,
   59,   47,   61,   41,   42,   43,   -1,   45,   -1,   47,
   93,   -1,  264,   -1,   60,   -1,   62,   41,   42,   43,
   -1,   45,   60,   47,   62,  277,  278,  279,  280,  281,
   -1,   41,   42,   43,   93,   45,   60,   47,   62,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   60,   -1,   62,   42,   43,   44,   45,   -1,   47,  271,
  272,  273,  274,  275,  276,   -1,   -1,   -1,   -1,   -1,
   -1,   60,   -1,   62,   42,   43,   -1,   45,   -1,   47,
   -1,   -1,  271,  272,  273,  274,  275,  276,   -1,   -1,
   -1,   -1,   60,   -1,   62,   -1,   -1,   -1,   -1,   -1,
   -1,  267,   -1,   37,   -1,  271,  272,  273,  274,  275,
  276,   45,   46,   -1,  262,   49,   50,  265,  266,   -1,
  268,  269,  270,   -1,   -1,   -1,   -1,   61,   62,  277,
   -1,   -1,   -1,   -1,   -1,   -1,   70,   71,   72,   73,
   74,   75,   76,   77,   78,   79,   80,   81,   82,   83,
   -1,  271,  272,  273,  274,  275,  276,   -1,   92,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  111,   -1,   -1,
   -1,  264,   -1,  117,  267,   -1,  120,   -1,   -1,   -1,
   -1,   -1,  275,  276,  277,  278,  279,  280,  281,   -1,
   -1,   -1,   -1,   -1,   -1,  264,   -1,   -1,  267,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  275,  276,  277,  278,
  279,  280,  281,   -1,   -1,  271,  272,  273,  274,  275,
  276,   -1,   -1,  271,  272,  273,  274,  275,  276,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  271,  272,  273,
  274,  275,  276,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
    0,  271,  272,  273,  274,  275,  276,   -1,   -1,   -1,
   -1,   11,   -1,   -1,   14,   -1,   -1,   -1,   -1,   -1,
   20,   -1,  271,  272,  273,  274,  275,  276,   -1,   29,
   -1,   -1,   -1,   -1,   -1,   -1,   36,   -1,   -1,   39,
   -1,   -1,   -1,  271,  272,  273,  274,   47,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   85,   -1,   -1,   -1,   -1,
   -1,   91,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  112,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  122,   -1,   -1,  125,
};
#define YYFINAL 7
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 286
#define YYUNDFTOKEN 308
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,"'#'",0,0,0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,
0,0,0,"':'","';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"KW_BYTE","KW_SHORT","KW_LONG",
"KW_FLOAT","KW_DOUBLE","KW_WHEN","KW_THEN","KW_ELSE","KW_WHILE","KW_FOR",
"KW_TO","KW_READ","KW_RETURN","KW_PRINT","OPERATOR_LE","OPERATOR_GE",
"OPERATOR_EQ","OPERATOR_NE","OPERATOR_AND","OPERATOR_OR","TK_IDENTIFIER",
"LIT_INTEGER","LIT_REAL","LIT_CHAR","LIT_STRING","TOKEN_ERROR","VDEF","FDEF",
"FCALL","FPAR",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : code",
"code : program",
"program : def ';' program",
"program : def ';'",
"def : var",
"def : func",
"id : TK_IDENTIFIER",
"var : id ':' type litinit",
"var : id ':' type '[' litinteger ']' vec",
"litinteger : LIT_INTEGER",
"vec : litinit vec",
"vec :",
"litinit : LIT_INTEGER",
"litinit : LIT_REAL",
"litinit : LIT_CHAR",
"type : KW_BYTE",
"type : KW_SHORT",
"type : KW_LONG",
"type : KW_FLOAT",
"type : KW_DOUBLE",
"func : type id '(' parempty ')' cmd",
"parempty : param",
"parempty :",
"param : type id ',' param",
"param : type id",
"inputempty : input",
"inputempty :",
"input : exp ',' input",
"input : exp",
"cmdblock : '{' cmdlist '}'",
"cmdblock : '{' '}'",
"cmdlist : cmd ';' cmdlist",
"cmdlist : cmd ';'",
"cmd : cmdblock",
"cmd : id '=' exp",
"cmd : id '#' exp '=' exp",
"cmd : KW_READ id",
"cmd : KW_PRINT printlist",
"cmd : KW_RETURN exp",
"cmd : KW_WHEN '(' exp ')' KW_THEN cmd",
"cmd : KW_WHEN '(' exp ')' KW_THEN cmd KW_ELSE cmd",
"cmd : KW_WHILE '(' exp ')' cmd",
"cmd : KW_FOR '(' id '=' exp KW_TO exp ')' cmd",
"cmd :",
"printlist : printable printlist",
"printlist : printable",
"printable : exp",
"printable : LIT_STRING",
"exp : exp '+' exp",
"exp : exp '-' exp",
"exp : exp '*' exp",
"exp : exp '/' exp",
"exp : id",
"exp : id '(' inputempty ')'",
"exp : id '[' exp ']'",
"exp : exp '<' exp",
"exp : exp '>' exp",
"exp : '!' exp",
"exp : exp OPERATOR_LE exp",
"exp : exp OPERATOR_GE exp",
"exp : exp OPERATOR_EQ exp",
"exp : exp OPERATOR_NE exp",
"exp : exp OPERATOR_AND exp",
"exp : exp OPERATOR_OR exp",
"exp : litinit",
"exp : '(' exp ')'",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 156 "parser.y"
/*
void print(FILE *f,AST *tree)
{
	if (tree != NULL){
		switch (tree->type){
			case KW_READ:	
					fprintf(f,"read ");
					print(f, tree->son[0]);
					break;

			case KW_PRINT:	
					fprintf(f,"print ");
					print(f, tree->son[0]);
					break;

			case KW_RETURN:
					fprintf(f,"return ");
					print(f,tree->son[0]);
					break;

			case KW_WHEN:
					fprintf(f,"when (");
					print(f, tree->son[0]);
					fprintf(f,") then ");
					print(f, tree->son[1]);
					break;

			case KW_ELSE:
					fprintf(f,"when (");
					print(f, tree->son[0]);
					fprintf(f,") then ");
					print(f, tree->son[1]);
					fprintf(f," else ");
					print(f, tree->son[2]);
					break;

			case KW_WHILE:
					fprintf(f,"while (");
					print(f, tree->son[0]);
					fprintf(f,") ");
					print(f, tree->son[1]);
					break;

			case KW_FOR:	
					fprintf(f,"for (");
					print(f, tree->son[0]);
					fprintf(f," = ");
					print(f, tree->son[1]);
					fprintf(f," to ");
					print(f, tree->son[2]);
					fprintf(f,") ");
					print(f, tree->son[3]);
					break;

			case KW_BYTE:
					fprintf(f,"byte ");
					break;

			case KW_SHORT:
					fprintf(f,"short ");
					break;

			case KW_LONG:
					fprintf(f,"long ");
					break;

			case KW_FLOAT:
					fprintf(f,"float ");
					break;

			case KW_DOUBLE:
					fprintf(f,"double ");
					break;

			case TK_IDENTIFIER:
					fprintf(f,tree->hash_key);
					break;

			case LIT_INTEGER:
					fprintf(f,tree->hash_key);
					break;

			case LIT_REAL:
					fprintf(f,tree->hash_key);
					break;

			case LIT_CHAR:
					fprintf(f,tree->hash_key);
					break;

			case LIT_STRING:
					fprintf(f,tree->hash_key);
					break;

			case ':':
					print(f, tree->son[0]);
					fprintf(f," : ");
					print(f, tree->son[1]);
					fprintf(f," ");
					print(f, tree->son[2]);
					break;

			case VDEF:
					print(f, tree->son[0]);
					fprintf(f," : ");
					print(f, tree->son[1]);
					fprintf(f,"[");
					print(f, tree->son[2]);
					fprintf(f,"]");
					if(tree->son != NULL){
						fprintf(f," ");
						print(f, tree->son[3]);
					}
					break;

			case FDEF:
					print(f, tree->son[0]);
					fprintf(f," ");
					print(f, tree->son[1]);
					fprintf(f,"(");
					print(f, tree->son[2]);
					fprintf(f,") ");
					print(f, tree->son[3]);
					break;

			case FPAR:
					print(f, tree->son[0]);
					fprintf(f," ");
					print(f, tree->son[1]);
					break;

			case FCALL:
					print(f, tree->son[0]);
					fprintf(f,"(");
					print(f, tree->son[1]);
					fprintf(f,")");
					break;

			case '[':
					print(f, tree->son[0]);
					fprintf(f,"[");
					print(f, tree->son[1]);
					fprintf(f,"]");
					break;

			case '=':
					print(f, tree->son[0]);
					fprintf(f," = ");
					print(f, tree->son[1]);
					break;

			case '#':
					print(f, tree->son[0]);
					fprintf(f,"#");
					print(f, tree->son[1]);
					fprintf(f," = ");
					print(f, tree->son[2]);
					break;

			case ';':
					print(f, tree->son[0]);
					fprintf(f, ";\n");
					print(f, tree->son[1]);
					break;

			case ',':
					print(f, tree->son[0]);
					fprintf(f, ", ");
					print(f, tree->son[1]);
					break;

			case ' ':
					print(f, tree->son[0]);
					if(tree->son[1] != NULL){
						fprintf(f, " ");
						print(f, tree->son[1]);
					}
					break;

			case OPERATOR_LE:
					print(f, tree->son[0]);
					fprintf(f, " <= ");
					print(f, tree->son[1]);
					break;

			case OPERATOR_GE:
					print(f, tree->son[0]);
					fprintf(f, " >= ");
					print(f, tree->son[1]);
					break;


			case OPERATOR_EQ:
					print(f, tree->son[0]);
					fprintf(f, " == ");
					print(f, tree->son[1]);
					break;

			case OPERATOR_NE:
					print(f, tree->son[0]);
					fprintf(f, " != ");
					print(f, tree->son[1]);
					break;


			case OPERATOR_AND:
					print(f, tree->son[0]);
					fprintf(f, " && ");
					print(f, tree->son[1]);
					break;

			case OPERATOR_OR:
					print(f, tree->son[0]);
					fprintf(f, " || ");
					print(f, tree->son[1]);
					break;

			case '>':
					print(f, tree->son[0]);
					fprintf(f, " > ");
					print(f, tree->son[1]);
					break;

			case '<':
					print(f, tree->son[0]);
					fprintf(f, " < ");
					print(f, tree->son[1]);
					break;

			case '+':
					print(f, tree->son[0]);
					fprintf(f, " + ");
					print(f, tree->son[1]);
					break;

			case '-':
					print(f, tree->son[0]);
					fprintf(f, " - ");
					print(f, tree->son[1]);
					break;

			case '*':
					print(f, tree->son[0]);
					fprintf(f, " * ");
					print(f, tree->son[1]);
					break;

			case '/':
					print(f, tree->son[0]);
					fprintf(f, " / ");
					print(f, tree->son[1]);
					break;

			case '!':
					fprintf(f, "! ");
					print(f, tree->son[0]);
					break;

			case '(':
					fprintf(f, "(");
					print(f, tree->son[0]);
					fprintf(f, ")");
					break;

			case '{':
					fprintf(f, "{\n");
					print(f, tree->son[0]);
					fprintf(f, "}");
					break;

		}
	}
}*/
#line 765 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 69 "parser.y"
	{yyval.tree = yystack.l_mark[0].tree; ASTree = yyval.tree;}
break;
case 2:
#line 71 "parser.y"
	{yyval.tree = create(';',0,yystack.l_mark[-2].tree,yystack.l_mark[0].tree,0,0);}
break;
case 3:
#line 72 "parser.y"
	{yyval.tree = create(';',0,yystack.l_mark[-1].tree,0,0,0);}
break;
case 6:
#line 77 "parser.y"
	{yyval.tree = create(TK_IDENTIFIER,yystack.l_mark[0].symbol,0,0,0,0);}
break;
case 7:
#line 79 "parser.y"
	{yyval.tree = create(':',0,yystack.l_mark[-3].tree,yystack.l_mark[-1].tree,yystack.l_mark[0].tree,0);}
break;
case 8:
#line 80 "parser.y"
	{yyval.tree = create(VDEF,0,yystack.l_mark[-6].tree,yystack.l_mark[-4].tree,yystack.l_mark[-2].tree,yystack.l_mark[0].tree);}
break;
case 9:
#line 82 "parser.y"
	{yyval.tree = create(LIT_INTEGER,yystack.l_mark[0].symbol,0,0,0,0);}
break;
case 10:
#line 84 "parser.y"
	{yyval.tree = create(' ',0,yystack.l_mark[-1].tree,yystack.l_mark[0].tree,0,0);}
break;
case 11:
#line 85 "parser.y"
	{yyval.tree = 0;}
break;
case 12:
#line 87 "parser.y"
	{yyval.tree = create(LIT_INTEGER,yystack.l_mark[0].symbol,0,0,0,0);}
break;
case 13:
#line 88 "parser.y"
	{yyval.tree = create(LIT_REAL,yystack.l_mark[0].symbol,0,0,0,0);}
break;
case 14:
#line 89 "parser.y"
	{yyval.tree = create(LIT_CHAR,yystack.l_mark[0].symbol,0,0,0,0);}
break;
case 15:
#line 91 "parser.y"
	{yyval.tree = create(KW_BYTE,0,0,0,0,0);}
break;
case 16:
#line 92 "parser.y"
	{yyval.tree = create(KW_SHORT,0,0,0,0,0);}
break;
case 17:
#line 93 "parser.y"
	{yyval.tree = create(KW_LONG,0,0,0,0,0);}
break;
case 18:
#line 94 "parser.y"
	{yyval.tree = create(KW_FLOAT,0,0,0,0,0);}
break;
case 19:
#line 95 "parser.y"
	{yyval.tree = create(KW_DOUBLE,0,0,0,0,0);}
break;
case 20:
#line 97 "parser.y"
	{yyval.tree = create(FDEF,0,yystack.l_mark[-5].tree,yystack.l_mark[-4].tree,yystack.l_mark[-2].tree,yystack.l_mark[0].tree);}
break;
case 22:
#line 100 "parser.y"
	{yyval.tree = 0;}
break;
case 23:
#line 102 "parser.y"
	{yyval.tree = create(',',0,create(FPAR,0,yystack.l_mark[-3].tree,yystack.l_mark[-2].tree,0,0),yystack.l_mark[0].tree,0,0);}
break;
case 24:
#line 103 "parser.y"
	{yyval.tree = create(FPAR,0,yystack.l_mark[-1].tree,yystack.l_mark[0].tree,0,0);}
break;
case 26:
#line 106 "parser.y"
	{yyval.tree = 0;}
break;
case 27:
#line 108 "parser.y"
	{yyval.tree = create(',',0,yystack.l_mark[-2].tree,yystack.l_mark[0].tree,0,0);}
break;
case 29:
#line 111 "parser.y"
	{yyval.tree = create('{',0,yystack.l_mark[-1].tree,0,0,0);}
break;
case 30:
#line 112 "parser.y"
	{yyval.tree = create('{',0,0,0,0,0);}
break;
case 31:
#line 114 "parser.y"
	{yyval.tree = create(';',0,yystack.l_mark[-2].tree,yystack.l_mark[0].tree,0,0);}
break;
case 32:
#line 115 "parser.y"
	{yyval.tree = create(';',0,yystack.l_mark[-1].tree,0,0,0);}
break;
case 34:
#line 118 "parser.y"
	{yyval.tree = create ('=',0,yystack.l_mark[-2].tree,yystack.l_mark[0].tree,0,0);}
break;
case 35:
#line 119 "parser.y"
	{yyval.tree = create ('#',0,yystack.l_mark[-4].tree,yystack.l_mark[-2].tree,yystack.l_mark[0].tree,0);}
break;
case 36:
#line 120 "parser.y"
	{yyval.tree = create(KW_READ,0,yystack.l_mark[0].tree,0,0,0);}
break;
case 37:
#line 121 "parser.y"
	{yyval.tree = create(KW_PRINT,0,yystack.l_mark[0].tree,0,0,0);}
break;
case 38:
#line 122 "parser.y"
	{yyval.tree = create(KW_RETURN,0,yystack.l_mark[0].tree,0,0,0);}
break;
case 39:
#line 123 "parser.y"
	{yyval.tree = create(KW_WHEN,0,yystack.l_mark[-3].tree,yystack.l_mark[0].tree,0,0);}
break;
case 40:
#line 124 "parser.y"
	{yyval.tree = create(KW_ELSE,0,yystack.l_mark[-5].tree,yystack.l_mark[-2].tree,yystack.l_mark[0].tree,0);}
break;
case 41:
#line 125 "parser.y"
	{yyval.tree = create(KW_WHILE,0,yystack.l_mark[-2].tree,yystack.l_mark[0].tree,0,0);}
break;
case 42:
#line 126 "parser.y"
	{yyval.tree = create(KW_FOR,0,yystack.l_mark[-6].tree,yystack.l_mark[-4].tree,yystack.l_mark[-2].tree,yystack.l_mark[0].tree);}
break;
case 43:
#line 127 "parser.y"
	{yyval.tree = 0;}
break;
case 44:
#line 129 "parser.y"
	{yyval.tree = create(' ', 0, yystack.l_mark[-1].tree, yystack.l_mark[0].tree,0,0);}
break;
case 47:
#line 133 "parser.y"
	{yyval.tree = create(LIT_STRING,yystack.l_mark[0].symbol,0,0,0,0);}
break;
case 48:
#line 135 "parser.y"
	{yyval.tree = create('+',0,yystack.l_mark[-2].tree,yystack.l_mark[0].tree,0,0);}
break;
case 49:
#line 136 "parser.y"
	{yyval.tree = create('-',0,yystack.l_mark[-2].tree,yystack.l_mark[0].tree,0,0);}
break;
case 50:
#line 137 "parser.y"
	{yyval.tree = create('*',0,yystack.l_mark[-2].tree,yystack.l_mark[0].tree,0,0);}
break;
case 51:
#line 138 "parser.y"
	{yyval.tree = create('/',0,yystack.l_mark[-2].tree,yystack.l_mark[0].tree,0,0);}
break;
case 53:
#line 140 "parser.y"
	{yyval.tree = create(FCALL,0,yystack.l_mark[-3].tree,yystack.l_mark[-1].tree,0,0);}
break;
case 54:
#line 141 "parser.y"
	{yyval.tree = create('[',0,yystack.l_mark[-3].tree,yystack.l_mark[-1].tree,0,0);}
break;
case 55:
#line 142 "parser.y"
	{yyval.tree = create('<',0,yystack.l_mark[-2].tree,yystack.l_mark[0].tree,0,0);}
break;
case 56:
#line 143 "parser.y"
	{yyval.tree = create('>',0,yystack.l_mark[-2].tree,yystack.l_mark[0].tree,0,0);}
break;
case 57:
#line 144 "parser.y"
	{yyval.tree = create('!',0,yystack.l_mark[0].tree,0,0,0);}
break;
case 58:
#line 145 "parser.y"
	{yyval.tree = create(OPERATOR_LE,0,yystack.l_mark[-2].tree,yystack.l_mark[0].tree,0,0);}
break;
case 59:
#line 146 "parser.y"
	{yyval.tree = create(OPERATOR_GE,0,yystack.l_mark[-2].tree,yystack.l_mark[0].tree,0,0);}
break;
case 60:
#line 147 "parser.y"
	{yyval.tree = create(OPERATOR_EQ,0,yystack.l_mark[-2].tree,yystack.l_mark[0].tree,0,0);}
break;
case 61:
#line 148 "parser.y"
	{yyval.tree = create(OPERATOR_NE,0,yystack.l_mark[-2].tree,yystack.l_mark[0].tree,0,0);}
break;
case 62:
#line 149 "parser.y"
	{yyval.tree = create(OPERATOR_AND,0,yystack.l_mark[-2].tree,yystack.l_mark[0].tree,0,0);}
break;
case 63:
#line 150 "parser.y"
	{yyval.tree = create(OPERATOR_OR,0,yystack.l_mark[-2].tree,yystack.l_mark[0].tree,0,0);}
break;
case 65:
#line 152 "parser.y"
	{yyval.tree = create('(',0,yystack.l_mark[-1].tree,0,0,0);}
break;
#line 1187 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
