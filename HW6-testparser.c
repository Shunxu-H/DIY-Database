#include "unistd.h"
#include "string.h"
#include "stdio.h"
#include "errno.h"

int linenum;
extern int initfreen;

#include "HW6-expr.h"

#define YYERROR_VERBOSE
#include "y.tab.c"
#include "lex.yy.c"

void init_op_map();
char *op_name(int);

int initfreen, freen;

main()
{
	register i;

	init_op_map();

	while((i=yyparse())>0) printf("Syntax error, resyncing\n");
	printf("QUITting...\n");

}

insert_row()
{
	printf(":insert_row called\n");
}

define_table()
{
	printf(":define_table called\n");
}

print_relation(e)
{
	return 0;
}

evalexpr(x)
{
	print_e(x,0);
	return x;
}

compile(x)
{
	return x;
}

optimize(x)
{
	return x;
}

typedef
struct expression {
	int func;
	int count;
	union values {
		char *name;
		char *data;
		int num;
		struct expression *ep;
	} values[2];
} *esp;

expr *
makearray(expr e)
{
	esp *epp, ep = e;
	int i, size = listlen(e);
	
	if(size < 0) {
		printf("::Bad list structure\n");
		exit(0);
	}
	epp = malloc(size * sizeof (struct expression *));
	
	for(i=size-1; i>=0; i--) {
		epp[i] = ep->values[0].ep;
		ep = ep->values[1].ep;
	}

	return (expr *)epp;
}

makeexpr(int op, int cnt, int arg1, int arg2)
{
	esp ep;
	int i, size;

	//printf(":make_expr called with %d %d %x %x\n", op, cnt, arg1, arg2);

	ep = malloc(sizeof (struct expression));

	ep->func = op;
	ep->count = cnt;
	ep->values[0].num = arg1;
	ep->values[1].num = arg2;

	//printf("::returning %x\n", ep);
	return (int)ep;
}

listlen(expr e)
{
	esp ep = e;
	int i;

	for(i=0; ep; i++) {
		if(ep->func != OP_RLIST) return -1;		/* Not a list element */
		ep = ep->values[1].ep;
	}
	return i;
}

print_e(expr e, int lev)
{
	struct expression *ep = e;
	register int i, slev=lev;

	if(!ep) { printf("() "); return; }
	switch(ep->func) {

	/* Literals */
	case 257:	printf("$%d ", ep->values[0].num); return;
	case OP_NUMBER:	printf("%d ", ep->values[0].num); return;
	case OP_STRING:	printf("%s ", ep->values[0].data); return;
	case OP_NULL:	printf("NULL "); return;

	/* Names */
	case OP_COLNAME:
			printf("COLUMN:%s ", ep->values[0].name); return;
	case OP_TABLENAME:
			printf("TABLE:%s ", ep->values[0].name); return;
	case OP_FNAME:
			printf("FUNC:%s ", ep->values[0].name); return;

	/* Relational operators */
	case OP_PROJECTROW:
			printf("(PROJECT1 \n"); break;
	case OP_PROJECTION:
			printf("(PROJECT \n"); break;
	case OP_SELECTROW:
			printf("(SELECT1 \n"); break;
	case OP_SELECTION:
			printf("(SELECT \n"); break;
	case OP_PRODUCT:
			printf("(PRODUCT \n"); break;
	case OP_SORT:
			printf("(SORT \n"); break;
	case OP_GROUP:
			printf("(GROUP \n"); break;
	case OP_DELTA:
			printf("(DELTA \n"); break;
	case OP_CREATETABLE:
			printf("(CREATETABLE \n"); break;
	case OP_INSERTROW:
			printf("(INSERTROW \n"); break;
	case OP_GETNEXT:
			printf("(GETNEXT \n"); break;
	case OP_ITERATE:
			printf("(ITERATE \n"); break;
	
	case OP_PLUS:	printf("(+ \n"); break;
	case OP_BMINUS:	printf("(- \n"); break;
	case OP_TIMES:	printf("(* \n"); break;
	case OP_DIVIDE:	printf("(/ \n"); break;

	case OP_AND:	printf("(AND \n"); break;
	case OP_OR:	printf("(OR \n"); break;
	case OP_NOT:	printf("(! \n"); break;
	case OP_GT:	printf("(> \n"); break;
	case OP_LT:	printf("(< \n"); break;
	case OP_EQUAL:	printf("(== \n"); break;
	case OP_NOTEQ:	printf("(<> \n"); break;
	case OP_GEQ:	printf("(>= \n"); break;
	case OP_LEQ:	printf("(<= \n"); break;

	case OP_SORTSPEC:
			printf("(SORTSPEC \n"); break;

	case OP_COLUMNDEF:
			printf("(COLSPEC \n"); break;

	case OP_OUTCOLNAME:
			printf("(AS \n"); break;

	case OP_RLIST:	printf("(RLIST ");
			print_e(ep->values[0].ep, lev+7);
			putchar('\n');
			for(i=0;i<lev;i++) putchar(' ');
			print_e(ep->values[1].ep, lev);
			putchar(')');
			return;
	default:	printf("(%s \n", op_name(ep->func)); break;
	}
	lev += 2;
	for(i=0; i<lev; i++) putchar(' ');
	for(i=0; i<ep->count; i++) {
		print_e(ep->values[i].ep, lev+2); putchar(' ');
	}
	putchar('\n');
	for(i=0; i<slev; i++) putchar(' ');
	putchar(')');
}

#define IMPLEMENTED	1
/***********************************************************************************************/
/* Structures to allow conversion of number to name and vice-versa *****************************/
/***********************************************************************************************/
struct opmap {
	char *name;
	int	flag;
} opmap[256];

char opnamebuf[MAXDATA];
char *
op_name(int op_num)
{
	if(op_num < 1 || op_num > OP_EOF) {
		return "INVALID";
	}
	if(opmap[op_num].name)
		return opmap[op_num].name;
	else
		sprintf(opnamebuf,"OP_%d", op_num);
	return opnamebuf;
}

int
opnum(char *str)
{
	int i;
	for(i=1;i<256;i++) {
		if(!opmap[i].name) continue;
		if(!strcmp(opmap[i].name,str)) return i;
	}
	return 0;
}

/***********************************************************************************************/
/* Initialize the operator map *****************************************************************/
/***********************************************************************************************/
void
init_op_map()
{
	register int i;

	i = OP_SELECTION; opmap[i].name = "SELECTION";		
	i = OP_PROJECTION; opmap[i].name = "PROJECTION";		
	i = OP_PRODUCT; opmap[i].name = "PRODUCT";		
	i = OP_GROUP; opmap[i].name = "GROUP";		
	i = OP_DELTA; opmap[i].name = "DELTA";		
	i = OP_SORT; opmap[i].name = "SORT";		
	i = OP_SORTSPEC; opmap[i].name = "SORTSPEC";		
	i = OP_INSERT; opmap[i].name = "INSERT";		
	i = OP_DELETE; opmap[i].name = "DELETE";		
	i = OP_UPDATE; opmap[i].name = "UPDATE";		
	i = OP_OPEN; opmap[i].name = "OPEN";		
	i = OP_GETNEXT; opmap[i].name = "GETNEXT";		
	i = OP_CLOSE; opmap[i].name = "CLOSE";		
	i = OP_PROJECTROW; opmap[i].name = "PROJECTROW";	 opmap[i].flag = IMPLEMENTED;
	i = OP_SELECTROW; opmap[i].name = "SELECTROW";		 opmap[i].flag = IMPLEMENTED;
	i = OP_INSERTROW; opmap[i].name = "INSERTROW";		 opmap[i].flag = IMPLEMENTED;
	i = OP_DELETEROW; opmap[i].name = "DELETEROW";		 opmap[i].flag = IMPLEMENTED;
	i = OP_ROW; opmap[i].name = "ROW";			 opmap[i].flag = IMPLEMENTED;
	i = OP_FETCH1; opmap[i].name = "FETCH1";		 opmap[i].flag = IMPLEMENTED;
	i = OP_EQUAL; opmap[i].name = "EQUAL";			 opmap[i].flag = IMPLEMENTED;
	i = OP_NOTEQ; opmap[i].name = "NOTEQ";			 opmap[i].flag = IMPLEMENTED;
	i = OP_LEQ; opmap[i].name = "LEQ";			 opmap[i].flag = IMPLEMENTED;
	i = OP_GEQ; opmap[i].name = "GEQ";			 opmap[i].flag = IMPLEMENTED;
	i = OP_LT; opmap[i].name = "LT";			 opmap[i].flag = IMPLEMENTED;
	i = OP_GT; opmap[i].name = "GT";			 opmap[i].flag = IMPLEMENTED;
	i = OP_PLUS; opmap[i].name = "PLUS";			 opmap[i].flag = IMPLEMENTED;
	i = OP_BMINUS; opmap[i].name = "BMINUS";		 opmap[i].flag = IMPLEMENTED;
	i = OP_TIMES; opmap[i].name = "TIMES";			 opmap[i].flag = IMPLEMENTED;
	i = OP_DIVIDE; opmap[i].name = "DIVIDE";		 opmap[i].flag = IMPLEMENTED;
	i = OP_UMINUS; opmap[i].name = "UMINUS";		
	i = OP_AND; opmap[i].name = "AND";			 opmap[i].flag = IMPLEMENTED;
	i = OP_OR; opmap[i].name = "OR";			 opmap[i].flag = IMPLEMENTED;
	i = OP_NOT; opmap[i].name = "NOT";		
	i = OP_FCALL; opmap[i].name = "FCALL";		
	i = OP_STREQUAL; opmap[i].name = "STREQUAL";		 opmap[i].flag = IMPLEMENTED;
	i = OP_STRNOTEQ; opmap[i].name = "STRNOTEQ";		 opmap[i].flag = IMPLEMENTED;
	i = OP_STRLEQ; opmap[i].name = "STRLEQ";		 opmap[i].flag = IMPLEMENTED;
	i = OP_STRGEQ; opmap[i].name = "STRGEQ";		 opmap[i].flag = IMPLEMENTED;
	i = OP_STRLT; opmap[i].name = "STRLT";			 opmap[i].flag = IMPLEMENTED;
	i = OP_STRGT; opmap[i].name = "STRGT";			 opmap[i].flag = IMPLEMENTED;
	i = OP_STRCONCAT; opmap[i].name = "STRCONCAT";		
	i = OP_ATOI; opmap[i].name = "ATOI";			 opmap[i].flag = IMPLEMENTED;
	i = OP_ITOA; opmap[i].name = "ITOA";			 opmap[i].flag = IMPLEMENTED;
	i = OP_STXN; opmap[i].name = "STXN";		
	i = OP_COMMIT; opmap[i].name = "COMMIT";		
	i = OP_CLOSEALL; opmap[i].name = "CLOSEALL";		
	i = OP_SET; opmap[i].name = "SET";		
	i = OP_TABLENAME; opmap[i].name = "TABLENAME";		 opmap[i].flag = IMPLEMENTED;
	i = OP_COLNAME; opmap[i].name = "COLNAME";		 opmap[i].flag = IMPLEMENTED;
	i = OP_OUTCOLNAME; opmap[i].name = "OUTCOLNAME";		
	i = OP_COLUMNDEF; opmap[i].name = "COLUMNDEF";		
	i = OP_CREATETABLE; opmap[i].name = "CREATETABLE";	 opmap[i].flag = IMPLEMENTED;
	i = OP_FNAME; opmap[i].name = "FNAME";			 opmap[i].flag = IMPLEMENTED;
	i = OP_RLIST; opmap[i].name = "RLIST";		
	i = OP_STRING; opmap[i].name = "STRING";		 opmap[i].flag = IMPLEMENTED;
	i = OP_NUMBER; opmap[i].name = "NUMBER";		 opmap[i].flag = IMPLEMENTED;
	i = OP_NULL; opmap[i].name = "NULL";			 opmap[i].flag = IMPLEMENTED;

	i = OP_ITERATE; opmap[i].name = "ITERATE";		 opmap[i].flag = IMPLEMENTED;

}
