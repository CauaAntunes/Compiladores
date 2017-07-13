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
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union{ char* symbol; AST* tree;} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
