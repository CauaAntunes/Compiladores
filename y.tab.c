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

#line 5 "parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union{ char* symbol; } YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 32 "y.tab.c"

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
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    1,    1,    2,    2,    6,    6,    5,    5,
    5,    4,    4,    4,    4,    4,    3,    7,    7,    9,
    9,   10,   10,   11,   11,   13,   13,   14,   14,    8,
    8,    8,    8,    8,    8,    8,    8,    8,    8,    8,
   15,   15,   16,   16,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,
};
static const YYINT yylen[] = {                            2,
    3,    2,    1,    1,    4,    7,    2,    0,    1,    1,
    1,    1,    1,    1,    1,    1,    6,    1,    0,    4,
    2,    1,    0,    3,    1,    3,    2,    3,    2,    1,
    3,    5,    2,    2,    2,    6,    8,    5,    9,    0,
    2,    1,    1,    1,    3,    3,    3,    3,    1,    4,
    4,    3,    3,    2,    3,    3,    3,    3,    3,    3,
    1,    3,
};
static const YYINT yydefred[] = {                         0,
   12,   13,   14,   15,   16,    0,    0,    0,    3,    4,
    0,    0,    0,    0,    0,    1,    0,    9,   10,   11,
    0,    5,    0,    0,   18,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   17,   30,
    0,    6,   20,    0,    0,    0,   33,    0,    0,    0,
   61,    0,   44,    0,   34,    0,    0,    0,   27,    0,
    0,    7,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   41,    0,    0,    0,   26,    0,    0,    0,    0,
    0,   22,    0,   62,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   28,    0,   38,
    0,   51,   50,    0,    0,    0,    0,   24,    0,    0,
   37,    0,   39,
};
static const YYINT yydgoto[] = {                          7,
    8,    9,   10,   11,   51,   42,   24,   60,   25,   91,
   92,   54,   40,   61,   55,   56,
};
static const YYINT yysindex[] = {                      -173,
    0,    0,    0,    0,    0,  -57,    0,  -39,    0,    0,
 -273, -129, -173,   -2,  -89,    0, -129,    0,    0,    0,
 -238,    0, -236,   17,    0,  -32,   18,  366, -232, -129,
   23,   25,   26, -209,  -27,    3,  -19,  205,    0,    0,
 -232,    0,    0,  -27,  -27, -208,    0,   -1,  -27,  -27,
    0,  501,    0,  501,    0,    3,  -27,  -27,    0,   11,
  -53,    0,  262,  284,   19,  -27,  -27,  306,  501,  -27,
  -27,  -27,  -27,  -27,  -27,  -27,  -27,  -27,  -27,  -27,
  -27,    0,  501,  452,  366,    0, -172,  366,  -27,  459,
   51,    0,  350,    0,  501,  501,  501,  501,  501,  501,
  469,  469,  -55,  -55,  501,  501,  -27,    0,  366,    0,
  480,    0,    0,  -27,  501, -170,  -27,    0,  366,  328,
    0,  366,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   98,    0,    0,    0,   65,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   67,   50,   53,    0,
    0,    0,    0,    0,    0,    0,    0,   50,    0,    0,
   53,    0,    0,    0,    0,    0,    0,  -33,    0,    0,
    0,  -56,    0,  -15,    0,  -42,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   69,    0,   78,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -40,    0,  -44,    0,    0,  -38,    0,    0,
    0,    0,   73,    0,  100,  122,  144,  166,  373,  395,
   34,   56,  -10,   12,  417,  439,    0,    0,  -38,    0,
    0,    0,    0,    0,  -35,   62,    0,    0,  -38,    0,
    0,  -38,    0,
};
static const YYINT yygindex[] = {                       110,
    0,    0,    0,   90,   35,   83,    0,   -6,   95,    0,
   20,  713,    0,   41,   79,    0,
};
#define YYTABLESIZE 830
static const YYINT yytable[] = {                         49,
   12,   21,   35,   14,   80,   50,   81,   49,   49,   49,
   49,   49,   49,   49,   40,   58,   42,   43,   31,   13,
   40,   39,   47,   32,   43,   49,   49,   49,   49,   47,
   47,   47,   47,   47,   47,   50,   47,   17,   67,   26,
   27,   57,   49,   43,   48,   18,   19,   20,   47,   22,
   47,   48,   48,   48,   48,   48,   48,   28,   48,   49,
   29,   30,   44,   41,   45,   46,   46,   47,   65,   85,
   48,   86,   48,   46,   46,   41,   46,   46,   46,   89,
   29,  110,   47,    1,    2,    3,    4,    5,   45,   66,
  109,  113,   46,  119,   46,   45,   45,    2,   45,   45,
   45,   15,  116,    6,   48,   19,   23,   21,   40,   23,
   54,    8,  121,   25,   45,  123,   45,   54,   54,   23,
   36,   54,   16,   62,   43,  108,   46,    1,    2,    3,
    4,    5,   55,  118,   82,    0,   54,    0,   54,   55,
   55,    0,    0,   55,    0,    0,    0,    0,   45,    0,
    0,    0,    0,    0,   56,    0,    0,    0,   55,    0,
   55,   56,   56,    0,    0,   56,    0,    0,    0,    0,
   54,    0,    0,    0,    0,    0,   57,    0,    0,    0,
   56,    0,   56,   57,   57,    0,    0,   57,   18,   19,
   20,    0,   55,    0,    0,    0,    0,    0,   58,    0,
    0,    0,   57,    0,   57,   58,   58,   35,    0,   58,
    0,    0,    0,    0,   56,   70,   71,   72,   73,   74,
   75,   42,    0,   31,   58,   40,   58,    0,   32,    0,
   49,    0,    0,   49,    0,    0,   57,   49,   49,   49,
   49,   49,   49,   49,   49,   49,   49,   49,   43,   48,
   18,   19,   20,   47,    0,    0,   47,    0,   58,    0,
    0,   43,   43,   43,   43,   43,   47,   47,   47,   47,
   47,    0,    0,    0,    0,   48,    0,    0,   48,   48,
   18,   19,   20,   53,    0,    0,    0,    0,   48,   48,
   48,   48,   48,    0,    0,    0,    0,   46,    0,    0,
   46,    0,   87,   78,   77,    0,   76,    0,   79,    0,
   46,   46,   46,   46,   46,    0,    0,    0,    0,   45,
    0,   80,   45,   81,   88,   78,   77,   38,   76,   59,
   79,    0,   45,   45,   45,   45,   45,    0,    0,    0,
    0,   54,    0,   80,   54,   81,   94,   78,   77,    0,
   76,    0,   79,    0,   54,   54,   54,   54,   54,    0,
    0,    0,    0,   55,    0,   80,   55,   81,  122,   78,
   77,    0,   76,    0,   79,    0,   55,   55,   55,   55,
   55,    0,    0,    0,    0,   56,    0,   80,   56,   81,
    0,   78,   77,  114,   76,    0,   79,    0,   56,   56,
   56,   56,   56,    0,    0,   59,    0,   57,    0,   80,
   57,   81,   59,   59,    0,    0,   59,    0,    0,    0,
   57,   57,   57,   57,   57,    0,    0,   60,    0,   58,
    0,   59,   58,   59,   60,   60,    0,    0,   60,    0,
    0,    0,   58,   58,   58,   58,   58,    0,    0,   52,
    0,    0,    0,   60,    0,   60,   52,   52,    0,    0,
   52,    0,    0,    0,    0,   59,   31,    0,    0,   32,
   33,   53,   34,   35,   36,   52,    0,   52,   53,   53,
    0,   37,   53,    0,    0,    0,    0,   60,   38,    0,
    0,    0,    0,   78,   77,    0,   76,   53,   79,   53,
   78,   77,    0,   76,    0,   79,    0,    0,    0,   52,
   78,   80,  107,   81,    0,   79,    0,    0,   80,    0,
   81,   78,   77,    0,   76,    0,   79,    0,   80,    0,
   81,   53,   70,   71,   72,   73,   74,   75,    0,   80,
    0,   81,   78,   77,    0,   76,    0,   79,    0,    0,
    0,  112,    0,    0,   70,   71,   72,   73,   74,   75,
   80,    0,   81,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   70,   71,   72,   73,
   74,   75,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   70,   71,
   72,   73,   74,   75,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   70,   71,   72,   73,   74,   75,    0,   31,    0,    0,
   32,   33,    0,   34,   35,   36,   59,    0,    0,   59,
    0,    0,   37,    0,    0,    0,    0,    0,    0,   59,
   59,   59,   59,   59,    0,    0,    0,    0,   60,    0,
    0,   60,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   60,   60,   60,   60,   60,    0,    0,    0,    0,
   52,    0,    0,   52,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   52,   52,   52,   52,   52,    0,    0,
    0,    0,   53,    0,    0,   53,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   53,   53,   53,   53,   53,
    0,    0,   70,   71,   72,   73,   74,   75,    0,   70,
   71,   72,   73,   74,   75,    0,    0,    0,    0,   70,
   71,   72,   73,   74,   75,    0,  117,   52,    0,    0,
   70,   71,   72,   73,   74,   75,   63,   64,    0,    0,
    0,   68,   69,    0,    0,    0,    0,    0,    0,   83,
   84,   70,   71,   72,   73,   74,   75,    0,   90,   93,
    0,    0,   95,   96,   97,   98,   99,  100,  101,  102,
  103,  104,  105,  106,    0,    0,    0,    0,    0,    0,
    0,  111,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  115,
    0,    0,    0,    0,    0,    0,   93,    0,    0,  120,
};
static const YYINT yycheck[] = {                         33,
   58,   91,   59,  277,   60,   33,   62,   41,   42,   43,
   44,   45,   40,   47,   59,   35,   59,   33,   59,   59,
   59,   28,   33,   59,   40,   59,   60,   61,   62,   40,
   41,   42,   43,   44,   45,   33,   47,   40,   40,  278,
  277,   61,   40,   59,   33,  278,  279,  280,   59,   15,
   61,   40,   41,   42,   43,   44,   45,   41,   47,   93,
   93,   44,   40,   29,   40,   40,   33,  277,  277,   59,
   59,  125,   61,   40,   41,   41,   43,   44,   45,   61,
  125,   88,   93,  257,  258,  259,  260,  261,   33,   91,
  263,   41,   59,  264,   61,   40,   41,    0,   43,   44,
   45,   12,  109,  277,   93,   41,   17,   41,   59,   41,
   33,   59,  119,   41,   59,  122,   61,   40,   41,   30,
   59,   44,   13,   41,   30,   85,   93,  257,  258,  259,
  260,  261,   33,  114,   56,   -1,   59,   -1,   61,   40,
   41,   -1,   -1,   44,   -1,   -1,   -1,   -1,   93,   -1,
   -1,   -1,   -1,   -1,   33,   -1,   -1,   -1,   59,   -1,
   61,   40,   41,   -1,   -1,   44,   -1,   -1,   -1,   -1,
   93,   -1,   -1,   -1,   -1,   -1,   33,   -1,   -1,   -1,
   59,   -1,   61,   40,   41,   -1,   -1,   44,  278,  279,
  280,   -1,   93,   -1,   -1,   -1,   -1,   -1,   33,   -1,
   -1,   -1,   59,   -1,   61,   40,   41,  264,   -1,   44,
   -1,   -1,   -1,   -1,   93,  271,  272,  273,  274,  275,
  276,  264,   -1,  264,   59,  264,   61,   -1,  264,   -1,
  264,   -1,   -1,  267,   -1,   -1,   93,  271,  272,  273,
  274,  275,  276,  277,  278,  279,  280,  281,  264,  277,
  278,  279,  280,  264,   -1,   -1,  267,   -1,   93,   -1,
   -1,  277,  278,  279,  280,  281,  277,  278,  279,  280,
  281,   -1,   -1,   -1,   -1,  264,   -1,   -1,  267,  277,
  278,  279,  280,  281,   -1,   -1,   -1,   -1,  277,  278,
  279,  280,  281,   -1,   -1,   -1,   -1,  264,   -1,   -1,
  267,   -1,   41,   42,   43,   -1,   45,   -1,   47,   -1,
  277,  278,  279,  280,  281,   -1,   -1,   -1,   -1,  264,
   -1,   60,  267,   62,   41,   42,   43,  123,   45,  125,
   47,   -1,  277,  278,  279,  280,  281,   -1,   -1,   -1,
   -1,  264,   -1,   60,  267,   62,   41,   42,   43,   -1,
   45,   -1,   47,   -1,  277,  278,  279,  280,  281,   -1,
   -1,   -1,   -1,  264,   -1,   60,  267,   62,   41,   42,
   43,   -1,   45,   -1,   47,   -1,  277,  278,  279,  280,
  281,   -1,   -1,   -1,   -1,  264,   -1,   60,  267,   62,
   -1,   42,   43,   44,   45,   -1,   47,   -1,  277,  278,
  279,  280,  281,   -1,   -1,   33,   -1,  264,   -1,   60,
  267,   62,   40,   41,   -1,   -1,   44,   -1,   -1,   -1,
  277,  278,  279,  280,  281,   -1,   -1,   33,   -1,  264,
   -1,   59,  267,   61,   40,   41,   -1,   -1,   44,   -1,
   -1,   -1,  277,  278,  279,  280,  281,   -1,   -1,   33,
   -1,   -1,   -1,   59,   -1,   61,   40,   41,   -1,   -1,
   44,   -1,   -1,   -1,   -1,   93,  262,   -1,   -1,  265,
  266,   33,  268,  269,  270,   59,   -1,   61,   40,   41,
   -1,  277,   44,   -1,   -1,   -1,   -1,   93,  123,   -1,
   -1,   -1,   -1,   42,   43,   -1,   45,   59,   47,   61,
   42,   43,   -1,   45,   -1,   47,   -1,   -1,   -1,   93,
   42,   60,   61,   62,   -1,   47,   -1,   -1,   60,   -1,
   62,   42,   43,   -1,   45,   -1,   47,   -1,   60,   -1,
   62,   93,  271,  272,  273,  274,  275,  276,   -1,   60,
   -1,   62,   42,   43,   -1,   45,   -1,   47,   -1,   -1,
   -1,   93,   -1,   -1,  271,  272,  273,  274,  275,  276,
   60,   -1,   62,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  271,  272,  273,  274,
  275,  276,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  271,  272,
  273,  274,  275,  276,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  271,  272,  273,  274,  275,  276,   -1,  262,   -1,   -1,
  265,  266,   -1,  268,  269,  270,  264,   -1,   -1,  267,
   -1,   -1,  277,   -1,   -1,   -1,   -1,   -1,   -1,  277,
  278,  279,  280,  281,   -1,   -1,   -1,   -1,  264,   -1,
   -1,  267,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  277,  278,  279,  280,  281,   -1,   -1,   -1,   -1,
  264,   -1,   -1,  267,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  277,  278,  279,  280,  281,   -1,   -1,
   -1,   -1,  264,   -1,   -1,  267,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  277,  278,  279,  280,  281,
   -1,   -1,  271,  272,  273,  274,  275,  276,   -1,  271,
  272,  273,  274,  275,  276,   -1,   -1,   -1,   -1,  271,
  272,  273,  274,  275,  276,   -1,  267,   35,   -1,   -1,
  271,  272,  273,  274,  275,  276,   44,   45,   -1,   -1,
   -1,   49,   50,   -1,   -1,   -1,   -1,   -1,   -1,   57,
   58,  271,  272,  273,  274,  275,  276,   -1,   66,   67,
   -1,   -1,   70,   71,   72,   73,   74,   75,   76,   77,
   78,   79,   80,   81,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   89,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  107,
   -1,   -1,   -1,   -1,   -1,   -1,  114,   -1,   -1,  117,
};
#define YYFINAL 7
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 282
#define YYUNDFTOKEN 301
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
"LIT_INTEGER","LIT_REAL","LIT_CHAR","LIT_STRING","TOKEN_ERROR",0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program",
"program : def ';' program",
"program : def ';'",
"def : var",
"def : func",
"var : TK_IDENTIFIER ':' type litinit",
"var : TK_IDENTIFIER ':' type '[' LIT_INTEGER ']' vec",
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
"func : type TK_IDENTIFIER '(' parempty ')' cmd",
"parempty : param",
"parempty :",
"param : type TK_IDENTIFIER ',' param",
"param : type TK_IDENTIFIER",
"inputempty : input",
"inputempty :",
"input : exp ',' input",
"input : exp",
"cmdblock : '{' cmdlist '}'",
"cmdblock : '{' '}'",
"cmdlist : cmd ';' cmdlist",
"cmdlist : cmd ';'",
"cmd : cmdblock",
"cmd : TK_IDENTIFIER '=' exp",
"cmd : TK_IDENTIFIER '#' exp '=' exp",
"cmd : KW_READ TK_IDENTIFIER",
"cmd : KW_PRINT printlist",
"cmd : KW_RETURN exp",
"cmd : KW_WHEN '(' exp ')' KW_THEN cmd",
"cmd : KW_WHEN '(' exp ')' KW_THEN cmd KW_ELSE cmd",
"cmd : KW_WHILE '(' exp ')' cmd",
"cmd : KW_FOR '(' TK_IDENTIFIER '=' exp KW_TO exp ')' cmd",
"cmd :",
"printlist : printable printlist",
"printlist : printable",
"printable : exp",
"printable : LIT_STRING",
"exp : exp '+' exp",
"exp : exp '-' exp",
"exp : exp '*' exp",
"exp : exp '/' exp",
"exp : TK_IDENTIFIER",
"exp : TK_IDENTIFIER '(' inputempty ')'",
"exp : TK_IDENTIFIER '[' exp ']'",
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
