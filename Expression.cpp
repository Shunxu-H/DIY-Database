#include "Expression.h"
#include "Executor.h"
#include "Global.h"

#define MAXNODE 20000

bool has_distinct = false;

int linenum;
int freen = 0;
	expr cvt_itoe(int);
int yylex();
int yyerror(char const *);
int makestrexpr(char *), makename(int, char*), setname(int, int), makenum(int);
expr compile(expr), evalexpr(expr), optimize(expr);
void print_relation(expr);
int drop_table( expr e );
int update_table( int table_name, int col_eq, int condition );


expression ebuf[MAXNODE];

#include "HW4-sql.ypp.tab.c"
#include "lex.yy.cc"
#include "Rewriter.h"

yyFlexLexer *t = new yyFlexLexer;

Executor executor;
Rewriter rewriter;
bool _yyparse()
{
	return yyparse();
}

int yylex()
{
	return t->yylex();
}

expr cvt_itoe(int i)
{
	expr e;

	//printf("::cvt_itoe called with %d\n", i);
	
	if( i < 0 ) return 0;
	if(!i) return 0;
	if(i<MAXNODE) {
		printf("Messed up index - too low\n");
		return 0;
	}
	if(i > MAXNODE+MAXNODE) {
		printf("Messed up index - too high\n");
		return 0;
	}
	e = (expr)(ebuf + (i-MAXNODE));
	return e;
}


/* Utility to convert a list into an array **********************************/
expr *
makearray(expr e)
{
	expression **epp, *ep = (expression *)e;
	int i, size = listlen(e);
	
	if(size==0) return 0;
	if(size < 0) {
		printf("::Bad list structure\n");
		exit(0);
	}
	epp = (expression **)malloc(size * sizeof (struct expression *));
	
	for(i=size-1; i>=0; i--) {
		if(!ep || ep->func != OP_RLIST) {
			printf("::Not a list element\n");
			return 0;
		}
		epp[i] = ep->values[0].ep;
		ep = ep->values[1].ep;
	}

	return (expr *)epp;
}


/* yyparse wants an int (YYSTYPE) and supplies ints, so this has to be ******/
int makeexpr(int op, int cnt, int arg1, int arg2)
{
	expression *ep;
	int i, size;

	//printf(":make_expr called with %d %d %d %d\n", op, cnt, arg1, arg2);

	/* yyparse wants integers not pointers, and on CSIF machines they are incompatible */
	/* So allocate from an array, and return a modified index */
	if(freen<MAXNODE) {
		ep = ebuf + (freen++);
	} else {
		printf("Out of expression nodes\n");
		return 0;
	}
	ep->func = op;
	ep->count = cnt;
	ep->values[0].ep = (expression *)cvt_itoe(arg1);
	switch(ep->func) {
	default:	ep->values[1].ep = (expression *)cvt_itoe(arg2);
			break;
	case OP_COLUMNDEF:
			ep->values[1].num = arg2;
			break;
	}

	//printf("::returning %d\n", (ep-ebuf)+MAXNODE);
	//cout << "!" <<(ep-ebuf)+MAXNODE << endl;
	return (ep-ebuf)+MAXNODE;
}


int makenum(int v)
{
	int i = makeexpr(OP_NUMBER,1,0,0);
	ebuf[i-MAXNODE].count = 1;
	ebuf[i-MAXNODE].values[0].num = v;
	return i;
}

int makestrexpr(char *str)
{
	int i = makeexpr(OP_STRING,1,0,0);
	ebuf[i-MAXNODE].count = 1;
	ebuf[i-MAXNODE].values[0].data = str;
	return i;
}

int makename(int op, char*str)
{
	int i = makeexpr(op,1,0,0);

	//printf("makename called with %d %s\n", op, str);
	ebuf[i-MAXNODE].count = 1;
	ebuf[i-MAXNODE].values[0].name = str;
	//printf("::makename: returning %d\n", i);
	return i;
}

int setname(int op, int ei)
{
	expression *ep;
	//printf("::setname called with %d %d\n", op, ei);
	ep = (expression *)cvt_itoe(ei);
	if(!ep) return 0;
	//printf("::Setname: name=%s\n", ep->values[0].name);
	ep->func=op;
	return ei;
}

int listlen(expr e)
{
	expression *ep = (expression *)e;
	int i;

	for(i=0; ep; i++) {
		if(ep->func != OP_RLIST) return -1;		/* Not a list element */
		ep = ep->values[1].ep;
	}
	return i;
}


int drop_table( expr e )
{
	//int makeexpr(int op, int cnt, int arg1, int arg2)
	expression * ep = ( expression * ) e;
	int i = makeexpr( 101, 1, 0, 0 );
	ebuf[i-MAXNODE].count = 1;
	ebuf[i-MAXNODE].values[0].ep = ( expression * ) e;
	return i;
}

int update_table( int table_name, int change, int condition )
{
	//update_table( $2, makeexpre(OP_EQUAL, 2, $4, $6), $8  );
	int i1 = makeexpr( OP_IF, 2, condition, change);
	int i = makeexpr( OP_UPDATETABLE, 2, table_name, i1 );
	return i;
}

void print_e(expr e, int lev)
{
	expression *ep = (expression *)e;
	register int i, slev=lev;

	if(!ep) { printf("() "); return; }
	switch(ep->func) {

	/* Literals */
	case OP_NUMBER:	printf("%d OP_NUMBER", ep->values[0].num); return;
	case OP_STRING:	printf("%s OP_STRING", ep->values[0].data); return;
	case OP_NULL:	printf("NULL "); return;

	/* Names */
	case OP_COLNAME:
			printf("COLUMN:%s OP_COLNAME", ep->values[0].name); return;
	case OP_TABLENAME:			printf("TABLE:%s OP_TABLENAME", ep->values[0].name); return;
	case OP_FNAME:
			printf("FUNC:%s OP_FNAME", ep->values[0].name); return;
	case OP_COLUMNDEF:
			printf("(COLSPEC ");
			printf("%s ", ep->values[1].num==1?"KEY":ep->values[1].num==3?"PRIMARY":"");
			print_e(ep->values[0].ep, lev+2);
			putchar(')');
			return;


	/* Relational operators */
	case OP_PROJECTION:
			printf("(PROJECT \n"); break;
	case OP_SELECTION:
			printf("(SELECT \n"); break;
	case OP_PRODUCT:
			printf("(PRODUCT \n"); break;
	case OP_DROPTABLE:
			printf("(DROPTABLE \n"); break;
	case OP_DELETE:
			printf("(DELETEROW(S) \n"); break;
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
	case OP_ITERATE:
			printf("(ITERATE \n"); break;
	case OP_SELECTROW:
			printf("(SELECTROW \n"); break;
	case OP_PROJECTROW:
			printf("(PROJECTROW \n"); break;
	case OP_GETNEXT:
			printf("(GETNEXT \n"); break;
	case OP_SET:
			printf("(SET \n"); break;
	case OP_UPDATETABLE:
			printf("(UPDATETABLE \n"); break;
	case OP_INDEXSELECT:
			printf("(INDEXSELECT \n"); break;
	case OP_DISTINCT:
			printf("(DISTINCT \n"); break;


	
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


	case OP_IF:	printf("(IF \n"); break;


	case OP_SORTSPEC:
			printf("(SORTSPEC \n"); break;

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

/**********************************************************************/
/* Dummy routines that need to be filled out for HW4 ******************/
/* Move to another module and fully define there **********************/
/**********************************************************************/

void rewrite_projection( expr *e )
{
	expression *ep = (expression *)*e;
	expression *get_next, *projectrow, *iterate;
	//cout << ep->values[0].ep->values[0].ep->func << endl;
	expression *R = ep->values[0].ep;
	expression *anything = ep->values[1].ep;

// makeexpr(int op, int cnt, int arg1, int arg2)
	get_next = (expression *)cvt_itoe( makeexpr( OP_GETNEXT, 0, 0, 0 ) );

	// make projectrow
	projectrow = (expression *)cvt_itoe( makeexpr( OP_PROJECTROW, 2, 0,0 ) );
	((expression*)projectrow)->values[0].ep = get_next;
	((expression*)projectrow)->values[1].ep = anything;

	// make iterate
	iterate = (expression *)cvt_itoe( makeexpr( OP_ITERATE, 2, 0, 0) );
	iterate->values[0].ep = R;
	iterate->values[1].ep = projectrow;
	*e = iterate;

	//return iterate;

}

void rewrite_selection( expr *e )
{
	expression *ep = (expression *)*e;
	expression *get_next, *selectrow, *iterate;
	expression *R = ep->values[0].ep;
	expression *anything = ep->values[1].ep;

// makeexpr(int op, int cnt, int arg1, int arg2)
	get_next = (expression *)cvt_itoe( makeexpr( OP_GETNEXT, 0, 0, 0 ) );

	// make selectrow
	selectrow = (expression *)cvt_itoe( makeexpr( OP_SELECTROW, 2, 0,0 ) );
	((expression*)selectrow)->values[0].ep = get_next;
	((expression*)selectrow)->values[1].ep = anything;

	// make iterate
	iterate = (expression *)cvt_itoe( makeexpr( OP_ITERATE, 2, 0, 0) );
	iterate->values[0].ep = R;
	iterate->values[1].ep = selectrow;
	*e = iterate;
	//return iterate;

}


void _compile( expression **e )
{

	expression *ep = (expression *)*e;


	if(!ep) { return; }
	switch(ep->func) {

	/* Literals */
	case OP_NUMBER:	return;
	case OP_STRING:	return;
	case OP_NULL:	return;

	/* Names */
	case OP_COLNAME:
			return;
	case OP_TABLENAME: return;
	case OP_FNAME: return;
	case OP_COLUMNDEF:
			_compile(&(ep->values[0].ep));
			return;


	/* Relational operators */
	case OP_PROJECTION:
			rewriter.rewrite( (void**)e );
			 break;
			//printf("(PROJECT \n"); break;
	case OP_SELECTION:
			//cout << " calling the function " << endl;
			rewriter.rewrite( (void**)e ); break;
			//printf("(SELECT \n"); break;
	case OP_PRODUCT:break;
	case OP_SORT:
	break;
	case OP_GROUP: break;
	case OP_DELTA: break;
	case OP_CREATETABLE: break;
	case OP_INSERTROW: break;
	case OP_ITERATE:break;
	case OP_SELECTROW:break;
	case OP_PROJECTROW: break;
	case OP_GETNEXT:break;
	case OP_DELETE:
			rewriter.rewrite( (void**)e ); break;

	
	case OP_PLUS:	break;
	case OP_BMINUS:	break;
	case OP_TIMES:	break;
	case OP_DIVIDE:	break;

	case OP_AND:	break;
	case OP_OR:		break;
	case OP_NOT:	break;
	case OP_GT:		break;
	case OP_LT:		break;
	case OP_EQUAL:	break;
	case OP_NOTEQ:	break;
	case OP_GEQ:	break;
	case OP_LEQ:	break;

	case OP_SORTSPEC:break;

	case OP_OUTCOLNAME:break;

	case OP_RLIST:	 break;
	default:		 break;
	}
	_compile(&((*e)->values[0].ep)); 
	_compile(&((*e)->values[1].ep)); 
	//putchar('\n');

}

expr compile(expr e)
{
	has_distinct = isDistinct( e );
	_compile( ((expression**)&e) );
	return e;

}

expr evalexpr(expr e)
{

	//print_e(e, 0);
	executor.execute(e);

	//print_e(e, 0);
	return e;
}

expr optimize(expr e)
{
	return e;
}

void print_relation(expr e)
{

}


int main(int argc, char * argv[])
{
	if ( argc == 2 && argv[1] )
		executor.print_keys();

    while (true) {
        if (!_yyparse())  {
            break;
        }
	cout << "Syntax error, resyncing...\n";
    }
    cout << "QUITting...\n";
    return 0;
}
