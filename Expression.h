

#ifndef EXPRESSION_H
	#define EXPRESSION_H
	#include <cstdlib>
	#include <stdio.h>
	#include <iostream>
	#include <string.h>
	using namespace std;
	#include "HW4-expr.h"	


	
  
	/**********************************************************************/
	/* Expression generation code *****************************************/
	/**********************************************************************/
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
	} expression;
	 
	/* yyparse wants integers and CSIF machines have larger pointers than ints */
	/* So need conversion routines between ints and node pointers **************/

	expr cvt_itoe(int i);

	/* Utility to convert a list into an array **********************************/
	expr *makearray(expr e);

	/* yyparse wants an int (YYSTYPE) and supplies ints, so this has to be ******/
	int makeexpr(int op, int cnt, int arg1, int arg2);
	int makenum(int v);
	int makestrexpr(char *str);
	int makename(int op, char*str);
	int setname(int op, int ei);
	int listlen(expr e);
	void print_e(expr e, int lev);


	/**********************************************************************/
	/* Dummy routines that need to be filled out for HW4 ******************/
	/* Move to another module and fully define there **********************/
	/**********************************************************************/
	expr compile(expr e);
	expr evalexpr(expr e);
	expr optimize(expr e);
	void print_relation(expr e);
	int yylex();
	bool _yyparse();



	#endif