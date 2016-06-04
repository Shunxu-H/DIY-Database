#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20130925

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0


#ifndef YYSTYPE
typedef int YYSTYPE;
#endif

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

#define IDENT 257
#define NUMBER 258
#define STRING 259
#define NUL 260
#define SELECT 261
#define AS 262
#define FROM 263
#define WHERE 264
#define GROUP 265
#define BY 266
#define HAVING 267
#define ORDER 268
#define ASC 269
#define DESC 270
#define INSERT 271
#define INTO 272
#define VALUES 273
#define UPDATE 274
#define SET 275
#define DELETE 276
#define CREATE 277
#define TABLE 278
#define DESCRIBE 279
#define SHOW 280
#define TABLES 281
#define DROP 282
#define PRIMARY 283
#define KEY 284
#define NOTEQ 285
#define GEQ 286
#define LEQ 287
#define AND 288
#define OR 289
#define QUIT 290
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,    0,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    2,    5,    6,    6,    6,    6,    6,
    6,    6,   10,   10,   11,   11,    8,    8,    8,    4,
   14,   14,   16,   16,   15,   15,   18,   18,   19,   17,
   17,   20,   20,   21,   21,   21,   21,   21,   21,   12,
   12,   22,   22,   13,   13,    3,    3,    3,    3,    3,
    3,    7,    7,   23,   23,   23,    9,    9,    9,    9,
    9,    9,    9,    9,    9,    9,    9,    9,
};
static const short yylen[] = {                            2,
    0,    2,    3,    8,    5,    2,    9,    6,    7,    3,
    3,    4,    2,    1,    1,    1,    3,    5,    5,    3,
    3,    1,    4,    3,    1,    3,    1,    1,    1,    8,
    0,    2,    0,    2,    0,    3,    1,    3,    1,    0,
    3,    1,    3,    1,    2,    2,    1,    2,    2,    1,
    3,    3,    1,    1,    3,    1,    1,    1,    3,    3,
    3,    1,    3,    1,    2,    3,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,
};
static const short yydefred[] = {                         1,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    2,    0,   13,    0,   28,   29,    0,   53,    0,
   16,   22,    0,   50,    0,   14,    0,    0,    0,    0,
    0,    0,    3,    6,    0,    0,    0,    0,    0,   68,
   71,   72,   77,   78,   67,   69,   70,   73,   74,   75,
   76,    0,    0,    0,    0,    0,    0,    0,   10,   11,
    0,   24,    0,    0,   20,   21,   15,   52,   27,    0,
   17,   54,    0,   51,    0,    0,    0,    0,    0,   12,
   23,    0,    0,    0,    0,    0,    0,    0,    5,    0,
    0,    0,    0,   62,    0,   19,   18,    0,   55,    0,
    0,   56,   57,   58,    0,    0,    8,    0,   65,    0,
    0,    0,    0,    0,    0,    0,    0,   66,    9,   63,
   39,    0,   37,    0,    0,   30,    4,   59,   60,   61,
    0,    0,    0,    7,   38,    0,    0,    0,   42,   45,
   46,   48,   49,    0,   43,
};
static const short yydgoto[] = {                          1,
   12,   27,  105,   13,   19,   20,   93,   21,   52,   22,
   64,   23,   73,   87,  101,  114,  126,  122,  123,  138,
  139,   24,   94,
};
static const short yysindex[] = {                         0,
 -125,  -49,   32, -255, -210, -206, -212, -210, -188, -204,
   40,    0,   53,    0,   74,    0,    0,    5,    0,   16,
    0,    0,    2,    0, -210,    0, -157, -210, -210,   66,
   68, -210,    0,    0,   39,   74,   82,  -34, -128,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   61, -210,   32, -249, -128, -130,  116,    0,    0,
   84,    0,   55,  103,    0,    0,    0,    0,    0,    5,
    0,    0,  -29,    0,  122,  101,  117,   64, -128,    0,
    0,   64,  144,  -12,   64, -210,  -79, -207,    0,   64,
   22, -109,  109,    0,   55,    0,    0,   55,    0,  -78,
  -80,    0,    0,    0,  120,   28,    0,  -95,    0,  131,
 -128, -128,   64,  -76,  134, -153,   64,    0,    0,    0,
    0,  150,    0,   55,  -71,    0,    0,    0,    0,    0,
   49, -128,  -81,    0,    0,  -88,  -86,  152,    0,    0,
    0,    0,    0,  -81,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   -6,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -41,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  127,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -36,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  -25,    0,    0,    0,
    0,  128,    0,    0,  129,    0,    0,  -27,    0,    0,
  -19,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  -16,    0,    0,    0,    0,    0,    0,
    0,    1,    0,    3,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   78,   89,   54,    0,    0,
    0,    0,    0,    0,    0,
};
static const short yygindex[] = {                         0,
    0,  113,    0,   69,   47,   50,    0,  145,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   70,    0,
   56,  147,   87,
};
#define YYTABLESIZE 344
static const short yytable[] = {                         27,
   27,   27,   27,   27,   31,   27,   66,   50,   48,   14,
   49,    3,   51,   32,   86,   35,   25,   27,   27,   27,
   27,   33,   31,   75,   40,   47,   45,   46,   97,   50,
   48,   32,   49,   35,   51,   27,   27,   15,   27,   33,
   27,   36,   40,   34,   18,   54,   26,   47,   45,   46,
  102,  103,  104,   27,   27,   27,   28,   50,   48,   36,
   49,   34,   51,   50,   48,   29,   49,   38,   51,   50,
   48,   18,   49,   32,   51,   47,   45,   46,   18,   62,
  107,   47,   45,   46,   63,   68,   37,   47,   45,   46,
   50,   48,   31,   49,   41,   51,   50,   48,   33,   49,
   70,   51,   77,   18,  128,  129,  130,  134,   47,   45,
   46,   34,   41,   35,   47,   45,   46,   56,   44,   84,
   30,   44,   65,   76,   59,   92,   60,   91,   67,   47,
    2,   95,   47,   78,   98,    3,   44,   55,   83,  106,
   57,   58,   80,   81,   61,    4,   82,   47,    5,  110,
    6,    7,  111,    8,    9,   79,   10,   92,  121,   89,
  115,   88,  124,  116,   11,   72,  131,   25,   64,   26,
   25,   64,   26,  108,  109,   67,  136,   90,  121,  137,
  140,  141,  142,  143,   96,  100,  113,  112,  118,  119,
  137,  125,  127,  132,  133,  144,   71,  120,   99,  145,
   74,  135,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   27,   27,    0,   27,   27,    0,   31,    0,
   31,   31,    0,    0,   85,    0,    0,   32,    0,   32,
   32,   35,   35,   27,   27,   27,   27,   27,   33,    0,
   40,   41,   42,   43,   44,   27,   15,    0,    0,    0,
    0,   36,   16,   17,   53,    3,    0,   36,   36,    0,
   34,    0,   40,   41,   42,   43,   44,   39,   27,   27,
   27,   27,   27,    0,    0,    0,    0,    0,   15,   16,
   17,  117,    0,    0,    0,   36,   16,   17,    0,    0,
   40,   41,   42,   43,   44,    0,   40,   41,   42,   43,
   44,    0,   40,   41,   42,   43,   44,   69,   16,   17,
   36,   16,   17,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   40,   41,   42,   43,   44,    0,   40,
   41,   42,   43,   44,
};
static const short yycheck[] = {                         41,
   42,   43,   44,   45,   41,   47,   41,   42,   43,   59,
   45,  261,   47,   41,   44,   41,  272,   59,   60,   61,
   62,   41,   59,  273,   41,   60,   61,   62,   41,   42,
   43,   59,   45,   59,   47,   42,   43,   44,   45,   59,
   47,   41,   59,   41,   40,   44,  257,   60,   61,   62,
  258,  259,  260,   60,   61,   62,  263,   42,   43,   59,
   45,   59,   47,   42,   43,  278,   45,   18,   47,   42,
   43,   40,   45,  278,   47,   60,   61,   62,   40,   41,
   59,   60,   61,   62,   35,   39,   18,   60,   61,   62,
   42,   43,  281,   45,   41,   47,   42,   43,   59,   45,
   40,   47,   56,   40,  258,  259,  260,   59,   60,   61,
   62,   59,   59,   40,   60,   61,   62,  275,   41,   70,
    8,   44,   41,   55,   59,   79,   59,   78,  257,   41,
  256,   82,   44,  264,   85,  261,   59,   25,   70,   90,
   28,   29,   59,   41,   32,  271,   44,   59,  274,   41,
  276,  277,   44,  279,  280,   40,  282,  111,  112,   59,
   41,   40,  113,   44,  290,   53,  117,   41,   41,   41,
   44,   44,   44,  283,  284,  257,  258,   61,  132,  133,
  269,  270,  269,  270,   41,  265,  267,  266,  284,   59,
  144,  268,   59,   44,  266,   44,   52,  111,   86,  144,
   54,  132,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  264,  265,   -1,  267,  268,   -1,  265,   -1,
  267,  268,   -1,   -1,  264,   -1,   -1,  265,   -1,  267,
  268,  267,  268,  285,  286,  287,  288,  289,  268,   -1,
  285,  286,  287,  288,  289,  262,  263,   -1,   -1,   -1,
   -1,  257,  258,  259,  263,  261,   -1,  267,  268,   -1,
  268,   -1,  285,  286,  287,  288,  289,  262,  285,  286,
  287,  288,  289,   -1,   -1,   -1,   -1,   -1,  257,  258,
  259,  264,   -1,   -1,   -1,  257,  258,  259,   -1,   -1,
  285,  286,  287,  288,  289,   -1,  285,  286,  287,  288,
  289,   -1,  285,  286,  287,  288,  289,  257,  258,  259,
  257,  258,  259,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  285,  286,  287,  288,  289,   -1,  285,
  286,  287,  288,  289,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 290
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,
"';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"IDENT","NUMBER","STRING","NUL","SELECT","AS","FROM","WHERE",
"GROUP","BY","HAVING","ORDER","ASC","DESC","INSERT","INTO","VALUES","UPDATE",
"SET","DELETE","CREATE","TABLE","DESCRIBE","SHOW","TABLES","DROP","PRIMARY",
"KEY","NOTEQ","GEQ","LEQ","AND","OR","QUIT",
};
static const char *yyrule[] = {
"$accept : program",
"program :",
"program : program sql_command",
"program : program QUIT ';'",
"sql_command : INSERT INTO tablename VALUES '(' data_list ')' ';'",
"sql_command : INSERT INTO tablename select_expr ';'",
"sql_command : select_expr ';'",
"sql_command : UPDATE tablename SET colname '=' expr WHERE expr ';'",
"sql_command : DELETE FROM tablename WHERE expr ';'",
"sql_command : CREATE TABLE tablename '(' column_decls ')' ';'",
"sql_command : DESCRIBE tablename ';'",
"sql_command : SHOW TABLES ';'",
"sql_command : DROP TABLE tablename ';'",
"sql_command : error ';'",
"tablename : IDENT",
"colname : IDENT",
"expr : value",
"expr : expr bin_op value",
"expr : expr bin_op '(' expr ')'",
"expr : expr bin_op '(' select_expr ')'",
"expr : '(' select_expr ')'",
"expr : '(' expr ')'",
"expr : fcall",
"fcall : IDENT '(' fncargs ')'",
"fcall : IDENT '(' ')'",
"fncargs : expr",
"fncargs : fncargs ',' expr",
"value : IDENT",
"value : NUMBER",
"value : STRING",
"select_expr : SELECT projection FROM join whereclause groupclause havingclause orderclause",
"whereclause :",
"whereclause : WHERE expr",
"havingclause :",
"havingclause : HAVING expr",
"groupclause :",
"groupclause : GROUP BY grouplist",
"grouplist : groupspec",
"grouplist : grouplist ',' groupspec",
"groupspec : colname",
"orderclause :",
"orderclause : ORDER BY orderlist",
"orderlist : orderspec",
"orderlist : orderlist ',' orderspec",
"orderspec : NUMBER",
"orderspec : NUMBER ASC",
"orderspec : NUMBER DESC",
"orderspec : colname",
"orderspec : colname ASC",
"orderspec : colname DESC",
"projection : outcol",
"projection : projection ',' outcol",
"outcol : expr AS colname",
"outcol : colname",
"join : tablename",
"join : join ',' tablename",
"data_list : NUMBER",
"data_list : STRING",
"data_list : NUL",
"data_list : data_list ',' NUMBER",
"data_list : data_list ',' STRING",
"data_list : data_list ',' NUL",
"column_decls : column_decl",
"column_decls : column_decls ',' column_decl",
"column_decl : colname",
"column_decl : colname KEY",
"column_decl : colname PRIMARY KEY",
"bin_op : '='",
"bin_op : NOTEQ",
"bin_op : '>'",
"bin_op : '<'",
"bin_op : GEQ",
"bin_op : LEQ",
"bin_op : '+'",
"bin_op : '-'",
"bin_op : '*'",
"bin_op : '/'",
"bin_op : AND",
"bin_op : OR",

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
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 244 "HW4-sql.y"
yyerror(char *str)
{
	printf("Line %d: %s\n", linenum, str);
	return 1;
}


#line 391 "y.tab.c"

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
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

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

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
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
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
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

    yyerror("syntax error");

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
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
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
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
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
case 3:
#line 42 "HW4-sql.y"
	{ return 0; }
break;
case 4:
#line 46 "HW4-sql.y"
	{ evalexpr(optimize(compile(makeexpr(OP_INSERTROW, 2, yystack.l_mark[-5], yystack.l_mark[-2])))); yyval=0; }
break;
case 5:
#line 49 "HW4-sql.y"
	{ printf("Multi-row insert not implemented yet\n"); }
break;
case 6:
#line 52 "HW4-sql.y"
	{ print_relation(evalexpr(optimize(compile(yystack.l_mark[-1])))); }
break;
case 7:
#line 55 "HW4-sql.y"
	{ printf("UPDATE not implemented yet\n"); }
break;
case 8:
#line 58 "HW4-sql.y"
	{ printf("DELETE not implemented yet\n"); }
break;
case 9:
#line 61 "HW4-sql.y"
	{ evalexpr(optimize(compile(makeexpr(OP_CREATETABLE, 2, yystack.l_mark[-4], yystack.l_mark[-2])))); yyval=0; }
break;
case 10:
#line 64 "HW4-sql.y"
	{ printf("DESCRIBE not implemented yet\n"); }
break;
case 11:
#line 68 "HW4-sql.y"
	{ printf("SHOW TABLES not implemented yet\n"); }
break;
case 12:
#line 72 "HW4-sql.y"
	{ printf("DROP TABLE not implemented yet\n"); }
break;
case 14:
#line 79 "HW4-sql.y"
	{
		  yyval = makeexpr(OP_TABLENAME, 1, yystack.l_mark[0], 0);
		}
break;
case 15:
#line 85 "HW4-sql.y"
	{
		  yyval = makeexpr(OP_COLNAME, 1, yystack.l_mark[0], 0);
		}
break;
case 17:
#line 92 "HW4-sql.y"
	{ yyval = makeexpr(yystack.l_mark[-1], 2, yystack.l_mark[-2], yystack.l_mark[0]); }
break;
case 18:
#line 94 "HW4-sql.y"
	{ yyval = makeexpr(yystack.l_mark[-3], 2, yystack.l_mark[-4], yystack.l_mark[-1]); }
break;
case 19:
#line 96 "HW4-sql.y"
	{ yyval = makeexpr(yystack.l_mark[-3], 2, yystack.l_mark[-4], yystack.l_mark[-1]); }
break;
case 20:
#line 98 "HW4-sql.y"
	{ yyval = yystack.l_mark[-1]; }
break;
case 21:
#line 100 "HW4-sql.y"
	{ yyval = yystack.l_mark[-1]; }
break;
case 22:
#line 102 "HW4-sql.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 23:
#line 106 "HW4-sql.y"
	{ yyval = makeexpr(OP_FCALL, 2, makeexpr(OP_FNAME, 1, yystack.l_mark[-3], 0), yystack.l_mark[-1]); }
break;
case 24:
#line 108 "HW4-sql.y"
	{ yyval = makeexpr(OP_FCALL, 2, makeexpr(OP_FNAME, 1, yystack.l_mark[-2], 0), 0); }
break;
case 25:
#line 112 "HW4-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], 0); }
break;
case 26:
#line 114 "HW4-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], yystack.l_mark[-2]); }
break;
case 27:
#line 119 "HW4-sql.y"
	{ yyval = makeexpr(OP_COLNAME, 1, yystack.l_mark[0], 0); }
break;
case 28:
#line 121 "HW4-sql.y"
	{ yyval = makeexpr(OP_NUMBER, 1, yystack.l_mark[0], 0); }
break;
case 29:
#line 123 "HW4-sql.y"
	{ yyval = makeexpr(OP_STRING, 1, yystack.l_mark[0], 0); }
break;
case 30:
#line 127 "HW4-sql.y"
	{ yyval = yystack.l_mark[-4];
		  if(yystack.l_mark[-3]) yyval = makeexpr(OP_SELECTION, 2, yyval, yystack.l_mark[-3]);
		  if(yystack.l_mark[-2]) yyval = makeexpr(OP_GROUP, 2, yyval, yystack.l_mark[-2]);
		  yyval = makeexpr(OP_PROJECTION, 2, yyval, yystack.l_mark[-6]);
		  if(yystack.l_mark[-1]) yyval = makeexpr(OP_SELECTION, 2, yyval, yystack.l_mark[-1]);
		  if(yystack.l_mark[0]) yyval = makeexpr(OP_SORT, 2, yyval, yystack.l_mark[0]);
		}
break;
case 31:
#line 136 "HW4-sql.y"
	{ yyval = 0; }
break;
case 32:
#line 137 "HW4-sql.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 33:
#line 140 "HW4-sql.y"
	{ yyval = 0; }
break;
case 34:
#line 141 "HW4-sql.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 35:
#line 144 "HW4-sql.y"
	{ yyval = 0; }
break;
case 36:
#line 146 "HW4-sql.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 37:
#line 150 "HW4-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], 0); }
break;
case 38:
#line 152 "HW4-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], yystack.l_mark[-2]); }
break;
case 40:
#line 158 "HW4-sql.y"
	{ yyval = 0; }
break;
case 41:
#line 160 "HW4-sql.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 42:
#line 164 "HW4-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], 0); }
break;
case 43:
#line 166 "HW4-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], yystack.l_mark[-2]); }
break;
case 44:
#line 170 "HW4-sql.y"
	{ yyval = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_NUMBER, 1, yystack.l_mark[0], 0), 0); }
break;
case 45:
#line 172 "HW4-sql.y"
	{ yyval = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_NUMBER, 1, yystack.l_mark[-1], 0), 0); }
break;
case 46:
#line 174 "HW4-sql.y"
	{ yyval = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_NUMBER, 1, yystack.l_mark[-1], 0), makeexpr(OP_NULL, 0, 0, 0)); }
break;
case 47:
#line 176 "HW4-sql.y"
	{ yyval = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_COLNAME, 1, yystack.l_mark[0], 0), 0); }
break;
case 48:
#line 178 "HW4-sql.y"
	{ yyval = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_COLNAME, 1, yystack.l_mark[-1], 0), 0); }
break;
case 49:
#line 180 "HW4-sql.y"
	{ yyval = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_COLNAME, 1, yystack.l_mark[-1], 0), makeexpr(OP_NULL, 0, 0, 0)); }
break;
case 50:
#line 184 "HW4-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], 0); }
break;
case 51:
#line 186 "HW4-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], yystack.l_mark[-2]); }
break;
case 52:
#line 190 "HW4-sql.y"
	{ yyval = makeexpr(OP_OUTCOLNAME, 2, yystack.l_mark[-2], yystack.l_mark[0]); }
break;
case 53:
#line 192 "HW4-sql.y"
	{ yyval = makeexpr(OP_OUTCOLNAME, 2, yystack.l_mark[0], yystack.l_mark[0]); }
break;
case 54:
#line 196 "HW4-sql.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 55:
#line 198 "HW4-sql.y"
	{ yyval = makeexpr(OP_PRODUCT, 2, yystack.l_mark[-2], yystack.l_mark[0]); }
break;
case 56:
#line 202 "HW4-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, makeexpr(OP_NUMBER, 1, yystack.l_mark[0], 0), 0); }
break;
case 57:
#line 204 "HW4-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, makeexpr(OP_STRING, 1, yystack.l_mark[0], 0), 0); }
break;
case 58:
#line 206 "HW4-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, makeexpr(OP_NULL,0,0, 0), 0); }
break;
case 59:
#line 208 "HW4-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, makeexpr(OP_NUMBER, 1, yystack.l_mark[0], 0), yystack.l_mark[-2]); }
break;
case 60:
#line 210 "HW4-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, makeexpr(OP_STRING, 1, yystack.l_mark[0], 0), yystack.l_mark[-2]); }
break;
case 61:
#line 212 "HW4-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, makeexpr(OP_NULL, 0, 0, 0), yystack.l_mark[-2]); }
break;
case 62:
#line 216 "HW4-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], 0); }
break;
case 63:
#line 218 "HW4-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], yystack.l_mark[-2]); }
break;
case 64:
#line 222 "HW4-sql.y"
	{ yyval = makeexpr(OP_COLUMNDEF, 2, yystack.l_mark[0], 0); }
break;
case 65:
#line 224 "HW4-sql.y"
	{ yyval = makeexpr(OP_COLUMNDEF, 2, yystack.l_mark[-1], makeexpr(OP_STRING, 1, (int)"KEY", 0)); }
break;
case 66:
#line 226 "HW4-sql.y"
	{ yyval = makeexpr(OP_COLUMNDEF, 2, yystack.l_mark[-2], makeexpr(OP_STRING, 1, (int)"PRIMARY", 0)); }
break;
case 67:
#line 229 "HW4-sql.y"
	{ yyval = OP_EQUAL; }
break;
case 68:
#line 230 "HW4-sql.y"
	{ yyval = OP_NOTEQ; }
break;
case 69:
#line 231 "HW4-sql.y"
	{ yyval = OP_GT; }
break;
case 70:
#line 232 "HW4-sql.y"
	{ yyval = OP_LT; }
break;
case 71:
#line 233 "HW4-sql.y"
	{ yyval = OP_GEQ; }
break;
case 72:
#line 234 "HW4-sql.y"
	{ yyval = OP_LEQ; }
break;
case 73:
#line 235 "HW4-sql.y"
	{ yyval = OP_PLUS; }
break;
case 74:
#line 236 "HW4-sql.y"
	{ yyval = OP_BMINUS; }
break;
case 75:
#line 237 "HW4-sql.y"
	{ yyval = OP_TIMES; }
break;
case 76:
#line 238 "HW4-sql.y"
	{ yyval = OP_DIVIDE; }
break;
case 77:
#line 239 "HW4-sql.y"
	{ yyval = OP_AND; }
break;
case 78:
#line 240 "HW4-sql.y"
	{ yyval = OP_OR; }
break;
#line 899 "y.tab.c"
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
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
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
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
