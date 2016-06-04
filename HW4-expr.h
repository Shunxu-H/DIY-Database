/* Relational operators */
#define OP_SELECTION	1
#define OP_PROJECTION	2
#define OP_PRODUCT	3
#define OP_GROUP	4
#define OP_DELTA	5
#define OP_SORT		6
#define OP_SORTSPEC	7
#define OP_INSERT	8
#define OP_DELETE	9
#define OP_DROPTABLE	101
#define OP_UPDATETABLE	102
#define OP_INDEXSELECT	103
#define OP_DISTINCT		104

/* Iteration */
#define OP_ITERATE	10
#define OP_OPEN		11
#define OP_GETNEXT	12
#define OP_CLOSE	13
#define OP_PROJECTROW	14
#define OP_SELECTROW	15
#define OP_INSERTROW	16
#define OP_DELETEROW	17

/* Standard arithmetic */
#define OP_EQUAL	20
#define OP_NOTEQ	21
#define OP_LEQ		22
#define OP_GEQ		23
#define OP_LT		24
#define OP_GT		25
#define	OP_PLUS		26
#define OP_BMINUS	27		/* Subtract */
#define OP_TIMES	28
#define OP_DIVIDE	29
#define OP_UMINUS	30		/* Unary minus, negate */
#define OP_AND		31
#define OP_OR		32
#define OP_NOT		33
#define OP_IN 		35
#define OP_FCALL    34
#define OP_FCOUNT   36
#define OP_FAVG	    37


/* Transaction control */
#define OP_STXN		40
#define OP_COMMIT	41
#define OP_CLOSEALL	42

/* DDL */
#define OP_SET		50
#define OP_TABLENAME	51		/* Reference to a table */
#define OP_COLNAME	52		/* Reference to a column */
#define OP_OUTCOLNAME	53		/* Rename of column (AS operator) */
#define OP_COLUMNDEF	54		/* A column definition (only to say if it is a key or primary key ) */
#define OP_CREATETABLE	55
#define OP_FNAME	56
#define OP_IF		57

/* Composition */
#define OP_RLIST	60		/* List in reverse order */

/* Literals */
#define	OP_STRING	90
#define OP_NUMBER 91
#define OP_NULL		92

typedef void *expr;
expr *makearray(expr rlist);
int listlen(expr rlist);
int makeexpr(int , int , int, int);

