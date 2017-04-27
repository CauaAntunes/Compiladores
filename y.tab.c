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
    9,   10,   10,   11,   11,   11,   11,   12,   12,   13,
   13,    8,    8,    8,    8,    8,    8,    8,    8,    8,
    8,    8,   15,   15,   16,   16,   14,   14,   14,   14,
   14,   14,   14,   14,   14,   14,   14,   14,   14,   14,
   14,   14,   14,   14,
};
static const YYINT yylen[] = {                            2,
    3,    2,    1,    1,    4,    7,    2,    0,    1,    1,
    1,    1,    1,    1,    1,    1,    6,    1,    0,    4,
    2,    1,    0,    3,    3,    1,    1,    3,    2,    3,
    2,    1,    3,    5,    2,    2,    2,    6,    8,    5,
    9,    0,    2,    1,    1,    1,    3,    3,    3,    3,
    1,    4,    4,    3,    3,    2,    3,    3,    3,    3,
    3,    3,    1,    3,
};
static const YYINT yydefred[] = {                         0,
   12,   13,   14,   15,   16,    0,    0,    0,    3,    4,
    0,    0,    0,    0,    0,    1,    0,    9,   10,   11,
    0,    5,    0,    0,   18,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   17,   32,
    0,    6,   20,    0,    0,    0,   35,    0,    0,    0,
   63,    0,   46,    0,   36,    0,    0,    0,   29,    0,
    0,    7,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   43,    0,    0,    0,   28,    0,    0,    0,    0,
    0,    0,    0,   22,   64,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   30,    0,
   40,    0,   53,    0,    0,   52,    0,    0,    0,   24,
   25,    0,    0,   39,    0,   41,
};
static const YYINT yydgoto[] = {                          7,
    8,    9,   10,   11,   51,   42,   24,   60,   25,   93,
   94,   40,   61,   54,   55,   56,
};
static const YYINT yysindex[] = {                      -127,
    0,    0,    0,    0,    0,  -51,    0,  -48,    0,    0,
 -258, -218, -127,  -16,  -89,    0, -218,    0,    0,    0,
 -244,    0, -230,    7,    0,  -37,   17,  292, -194, -218,
   23,   24,   26, -208,   25,   47,  -17,  282,    0,    0,
 -194,    0,    0,   25,   25, -205,    0,  -23,   25,   25,
    0,  476,    0,  476,    0,   47,   25,   25,    0,   19,
  -49,    0,  371,  395,   20,   25, -170,  419,  476,   25,
   25,   25,   25,   25,   25,   25,   25,   25,   25,   25,
   25,    0,  476,  306,  292,    0, -181,  292,   25,  470,
   46,   48,   50,    0,    0,  476,  476,  476,  476,  476,
  476,  447,  447,  -59,  -59,  476,  476,   25,    0,  292,
    0,  328,    0, -170, -170,    0,  476, -166,   25,    0,
    0,  292,  433,    0,  292,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   94,    0,    0,    0,   59,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   61,   44,   45,    0,
    0,    0,    0,    0,    0,    0,    0,   44,    0,    0,
   45,    0,    0,    0,    0,    0,    0,  -33,    0,    0,
    0,  -54,    0,  123,    0,  -53,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   71,    0,   78,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -46,    0,  -55,    0,    0,  -44,    0,    0,
   72,   73,    0,    0,    0,   83,  105,  114,  144,  168,
  192,   34,   56,  -10,   12,  223,  247,    0,    0,  -44,
    0,    0,    0,    0,    0,    0,  -43,   62,    0,    0,
    0,  -44,    0,    0,  -44,    0,
};
static const YYINT yygindex[] = {                       107,
    0,    0,    0,    8,   21,   81,    0,   18,   95,    0,
  -93,    0,   41,  540,   85,    0,
};
#define YYTABLESIZE 752
static const YYINT yytable[] = {                         51,
   80,   21,   81,   42,   37,   44,   12,   51,   51,   51,
   13,   51,   33,   51,   42,   34,   67,   58,   14,   15,
  120,  121,   49,   17,   23,   51,   51,   51,   51,   49,
   49,   49,   49,   26,   49,   22,   49,   23,    1,    2,
    3,    4,    5,   57,   50,   39,   27,   28,   49,   41,
   49,   50,   50,   50,   50,   29,   50,   50,   50,   51,
   30,   41,   44,   45,   49,   46,   48,   66,   47,   31,
   50,   65,   50,   48,   48,   86,   48,   85,   48,   50,
   89,  110,   49,   18,   19,   20,   49,   92,   47,  114,
  116,  115,   48,    2,   48,   47,   47,  122,   47,   19,
   47,   21,   42,    8,   50,  111,   91,   18,   19,   20,
   56,   23,   26,   27,   47,   57,   47,   56,   56,   16,
   38,   62,   57,   57,   43,  109,   48,  118,    0,    1,
    2,    3,    4,    5,   92,   92,   56,   58,   56,  124,
   82,   57,  126,   57,   58,   58,   59,    0,   47,    6,
    0,    0,    0,   59,   59,   45,    0,    0,    0,    0,
    0,    0,   45,   58,    0,   58,    0,    0,    0,    0,
   56,    0,   59,    0,   59,   57,   60,    0,    0,    0,
    0,   45,    0,   60,   60,    0,    0,    0,   18,   19,
   20,    0,    0,    0,    0,    0,    0,   58,    0,    0,
   61,    0,   60,    0,   60,    0,   59,   61,   61,   37,
   44,   70,   71,   72,   73,   74,   75,   33,    0,   42,
   34,    0,    0,    0,   62,    0,   61,    0,   61,    0,
   51,   62,   62,   51,    0,    0,   60,   51,   51,   51,
   51,   51,   51,   51,   51,   51,   51,   51,    0,    0,
   62,    0,   62,   49,    0,   54,   49,    0,    0,    0,
   61,    0,   54,   54,    0,    0,   49,   49,   49,   49,
   49,    0,    0,    0,    0,   50,    0,    0,   50,   55,
    0,   54,    0,   54,   62,    0,   55,   55,   50,   50,
   50,   50,   50,    0,    0,    0,    0,   48,    0,    0,
   48,   48,   18,   19,   20,   55,    0,   55,    0,    0,
   48,   48,   48,   48,   48,   54,    0,    0,    0,   47,
    0,    0,   47,   48,   18,   19,   20,   53,    0,    0,
    0,    0,   47,   47,   47,   47,   47,    0,    0,   55,
    0,   56,    0,    0,   56,    0,   57,   78,   77,   57,
   76,    0,   79,    0,   56,   56,   56,   56,   56,   57,
   57,   57,   57,   57,    0,   80,  108,   81,   58,   78,
   77,   58,   76,    0,   79,    0,    0,   59,    0,    0,
   59,   58,   58,   58,   58,   58,   45,   80,    0,   81,
   59,   59,   59,   59,   59,    0,    0,    0,    0,   45,
   45,   45,   45,   45,   38,    0,   59,   60,    0,    0,
   60,   87,   78,   77,   38,   76,    0,   79,    0,    0,
   60,   60,   60,   60,   60,    0,    0,    0,    0,    0,
   80,   61,   81,    0,   61,   88,   78,   77,    0,   76,
    0,   79,    0,    0,   61,   61,   61,   61,   61,    0,
    0,    0,    0,    0,   80,   62,   81,    0,   62,   95,
   78,   77,    0,   76,    0,   79,    0,    0,   62,   62,
   62,   62,   62,  125,   78,   77,    0,   76,   80,   79,
   81,    0,    0,    0,    0,    0,   54,    0,   78,   54,
    0,    0,   80,   79,   81,    0,    0,    0,    0,   54,
   54,   54,   54,   54,    0,    0,   80,    0,   81,    0,
   55,   78,   77,   55,   76,    0,   79,   78,   77,    0,
   76,    0,   79,   55,   55,   55,   55,   55,    0,   80,
    0,   81,    0,    0,    0,   80,    0,   81,    0,    0,
    0,    0,    0,   31,    0,    0,   32,   33,    0,   34,
   35,   36,    0,   31,    0,    0,   32,   33,   37,   34,
   35,   36,  113,    0,    0,    0,    0,    0,   37,    0,
    0,    0,    0,    0,   52,    0,   70,   71,   72,   73,
   74,   75,    0,   63,   64,    0,    0,    0,   68,   69,
    0,    0,    0,    0,  119,    0,   83,   84,   70,   71,
   72,   73,   74,   75,    0,   90,    0,    0,    0,   96,
   97,   98,   99,  100,  101,  102,  103,  104,  105,  106,
  107,    0,    0,    0,    0,    0,    0,    0,  112,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   70,   71,   72,   73,   74,   75,  117,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  123,    0,
    0,    0,    0,    0,    0,   70,   71,   72,   73,   74,
   75,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   70,
   71,   72,   73,   74,   75,    0,    0,    0,    0,    0,
    0,    0,    0,   70,   71,   72,   73,   74,   75,    0,
    0,    0,    0,    0,    0,    0,    0,   70,   71,   72,
   73,   74,   75,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   70,   71,   72,   73,   74,   75,   70,   71,   72,   73,
   74,   75,
};
static const YYINT yycheck[] = {                         33,
   60,   91,   62,   59,   59,   59,   58,   41,   42,   43,
   59,   45,   59,   47,   59,   59,   40,   35,  277,   12,
  114,  115,   33,   40,   17,   59,   60,   61,   62,   40,
   41,   42,   43,  278,   45,   15,   47,   30,  257,  258,
  259,  260,  261,   61,   33,   28,  277,   41,   59,   29,
   61,   40,   41,   42,   43,   93,   45,   33,   47,   93,
   44,   41,   40,   40,   40,   40,   33,   91,  277,  125,
   59,  277,   61,   40,   41,  125,   43,   59,   45,   33,
   61,  263,   93,  278,  279,  280,   40,   67,   33,   44,
   41,   44,   59,    0,   61,   40,   41,  264,   43,   41,
   45,   41,   59,   59,   93,   88,  277,  278,  279,  280,
   33,   41,   41,   41,   59,   33,   61,   40,   41,   13,
   59,   41,   40,   41,   30,   85,   93,  110,   -1,  257,
  258,  259,  260,  261,  114,  115,   59,   33,   61,  122,
   56,   59,  125,   61,   40,   41,   33,   -1,   93,  277,
   -1,   -1,   -1,   40,   41,   33,   -1,   -1,   -1,   -1,
   -1,   -1,   40,   59,   -1,   61,   -1,   -1,   -1,   -1,
   93,   -1,   59,   -1,   61,   93,   33,   -1,   -1,   -1,
   -1,   59,   -1,   40,   41,   -1,   -1,   -1,  278,  279,
  280,   -1,   -1,   -1,   -1,   -1,   -1,   93,   -1,   -1,
   33,   -1,   59,   -1,   61,   -1,   93,   40,   41,  264,
  264,  271,  272,  273,  274,  275,  276,  264,   -1,  264,
  264,   -1,   -1,   -1,   33,   -1,   59,   -1,   61,   -1,
  264,   40,   41,  267,   -1,   -1,   93,  271,  272,  273,
  274,  275,  276,  277,  278,  279,  280,  281,   -1,   -1,
   59,   -1,   61,  264,   -1,   33,  267,   -1,   -1,   -1,
   93,   -1,   40,   41,   -1,   -1,  277,  278,  279,  280,
  281,   -1,   -1,   -1,   -1,  264,   -1,   -1,  267,   33,
   -1,   59,   -1,   61,   93,   -1,   40,   41,  277,  278,
  279,  280,  281,   -1,   -1,   -1,   -1,  264,   -1,   -1,
  267,  277,  278,  279,  280,   59,   -1,   61,   -1,   -1,
  277,  278,  279,  280,  281,   93,   -1,   -1,   -1,  264,
   -1,   -1,  267,  277,  278,  279,  280,  281,   -1,   -1,
   -1,   -1,  277,  278,  279,  280,  281,   -1,   -1,   93,
   -1,  264,   -1,   -1,  267,   -1,  264,   42,   43,  267,
   45,   -1,   47,   -1,  277,  278,  279,  280,  281,  277,
  278,  279,  280,  281,   -1,   60,   61,   62,  264,   42,
   43,  267,   45,   -1,   47,   -1,   -1,  264,   -1,   -1,
  267,  277,  278,  279,  280,  281,  264,   60,   -1,   62,
  277,  278,  279,  280,  281,   -1,   -1,   -1,   -1,  277,
  278,  279,  280,  281,  123,   -1,  125,  264,   -1,   -1,
  267,   41,   42,   43,  123,   45,   -1,   47,   -1,   -1,
  277,  278,  279,  280,  281,   -1,   -1,   -1,   -1,   -1,
   60,  264,   62,   -1,  267,   41,   42,   43,   -1,   45,
   -1,   47,   -1,   -1,  277,  278,  279,  280,  281,   -1,
   -1,   -1,   -1,   -1,   60,  264,   62,   -1,  267,   41,
   42,   43,   -1,   45,   -1,   47,   -1,   -1,  277,  278,
  279,  280,  281,   41,   42,   43,   -1,   45,   60,   47,
   62,   -1,   -1,   -1,   -1,   -1,  264,   -1,   42,  267,
   -1,   -1,   60,   47,   62,   -1,   -1,   -1,   -1,  277,
  278,  279,  280,  281,   -1,   -1,   60,   -1,   62,   -1,
  264,   42,   43,  267,   45,   -1,   47,   42,   43,   -1,
   45,   -1,   47,  277,  278,  279,  280,  281,   -1,   60,
   -1,   62,   -1,   -1,   -1,   60,   -1,   62,   -1,   -1,
   -1,   -1,   -1,  262,   -1,   -1,  265,  266,   -1,  268,
  269,  270,   -1,  262,   -1,   -1,  265,  266,  277,  268,
  269,  270,   93,   -1,   -1,   -1,   -1,   -1,  277,   -1,
   -1,   -1,   -1,   -1,   35,   -1,  271,  272,  273,  274,
  275,  276,   -1,   44,   45,   -1,   -1,   -1,   49,   50,
   -1,   -1,   -1,   -1,  267,   -1,   57,   58,  271,  272,
  273,  274,  275,  276,   -1,   66,   -1,   -1,   -1,   70,
   71,   72,   73,   74,   75,   76,   77,   78,   79,   80,
   81,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   89,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  271,  272,  273,  274,  275,  276,  108,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  119,   -1,
   -1,   -1,   -1,   -1,   -1,  271,  272,  273,  274,  275,
  276,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  271,
  272,  273,  274,  275,  276,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  271,  272,  273,  274,  275,  276,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  271,  272,  273,
  274,  275,  276,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  271,  272,  273,  274,  275,  276,  271,  272,  273,  274,
  275,  276,
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
"input : TK_IDENTIFIER ',' input",
"input : litinit ',' input",
"input : TK_IDENTIFIER",
"input : litinit",
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
