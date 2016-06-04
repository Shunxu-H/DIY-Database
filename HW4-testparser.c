#include <iostream>
#include "unistd.h"
#include "string.h"
#include "stdio.h"
#include "errno.h"

int linenum;

#include "HW4-expr.h"

#define YYERROR_VERBOSE
#include "lex.yy.cc"

#include "HW4-sql.tab.cc"

int main()
{
	register i;

	while((i=yyparse())>0) printf("Syntax error, resyncing\n");
	printf("QUITting...\n");

	return 0;
}

void insert_row()
{
	printf(":insert_row called\n");
}

void define_table()
{
	printf(":define_table called\n");
}

void print_relation(expr e)
{
	return;
	//return 0;
}

expr evalexpr(expr x)
{
	print_e(x,0);
	return x;
}

expr compile(expr x)
{
	return x;
}

expr optimize(expr x)
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

expr makearray(expr e)
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

	return epp;
}

int makeexpr(int op, int cnt, int arg1, int arg2)
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

int listlen(expr e)
{
	esp ep = e;
	int i;

	for(i=0; ep; i++) {
		if(ep->func != OP_RLIST) return -1;		/* Not a list element */
		ep = ep->values[1].ep;
	}
	return i;
}

void print_e(expr e, int lev)
{
	struct expression *ep = e;
	register int i, slev=lev;

	if(!ep) { printf("() "); return; }
	switch(ep->func) {

	/* Literals */
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
	case OP_PROJECTION:
			printf("(PROJECT \n"); break;
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

	case OP_OUTCOLNAME:
			printf("(AS \n"); break;

	case OP_RLIST:	printf("(RLIST \n"); break;
	default:	printf("(%d \n", ep->func); break;
	}
	lev += 2;
	for(i=0; i<lev; i++) putchar(' ');
	print_e(ep->values[0].ep, lev+2); putchar(' ');
	print_e(ep->values[1].ep, lev+2); 
	putchar('\n');
	for(i=0; i<slev; i++) putchar(' ');
	putchar(')');
}

