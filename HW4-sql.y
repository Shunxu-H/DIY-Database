%token	IDENT
%token	NUMBER	
%token	STRING
%token	NUL

%token	SELECT
%token	AS
%token	FROM
%token	WHERE
%token	GROUP
%token	BY
%token	HAVING
%token	ORDER
%token	ASC
%token	DESC
%token	INSERT
%token	INTO
%token	VALUES
%token	UPDATE
%token	SET
%token	DELETE
%token	CREATE
%token	TABLE
%token	DESCRIBE
%token	SHOW
%token	TABLES
%token	DROP
%token	PRIMARY
%token	KEY

%token	NOTEQ
%token	GEQ
%token	LEQ
%token	AND
%token	OR

%token	QUIT

%%
program	:
	|	program sql_command
	|	program QUIT ';'	{ return 0; }
	;

sql_command:	INSERT INTO tablename VALUES '(' data_list ')' ';'
		{ evalexpr(optimize(compile(makeexpr(OP_INSERTROW, 2, $3, $6)))); $$=0; }

	|	INSERT INTO tablename select_expr ';'
		{ printf("Multi-row insert not implemented yet\n"); }

	|	select_expr ';'
		{ print_relation(evalexpr(optimize(compile($1)))); }

	|	UPDATE tablename SET colname '=' expr WHERE expr ';'
		{ printf("UPDATE not implemented yet\n"); }

	|	DELETE FROM tablename WHERE expr ';'
		{ (evalexpr(optimize(compile(makeexpr(OP_DELETE, 2, $3, $5))), 0); }

	|	CREATE TABLE tablename '(' column_decls ')' ';'
		{ evalexpr(optimize(compile(makeexpr(OP_CREATETABLE, 2, $3, $5)))); $$=0; }

	|	DESCRIBE tablename ';'
		{ printf("DESCRIBE not implemented yet\n"); }


	|	SHOW TABLES ';'
		{ printf("SHOW TABLES not implemented yet\n"); }


	|	DROP TABLE tablename ';'
		{ evalexpr(optimize(compile(drop_table(cvt_itoe($3))))); }

	|	error ';'

	;	

tablename:	IDENT	
		{
		  $$ = makeexpr(OP_TABLENAME, 1, $1, 0);
		}
	;

colname	:	IDENT
		{
		  $$ = makeexpr(OP_COLNAME, 1, $1, 0);
		}
	;

expr	:	value
	|	expr bin_op value
		{ $$ = makeexpr($2, 2, $1, $3); }
	|	expr bin_op '(' expr ')'
		{ $$ = makeexpr($2, 2, $1, $4); }
	|	expr bin_op '(' select_expr ')'
		{ $$ = makeexpr($2, 2, $1, $4); }
	|	'(' select_expr ')'
		{ $$ = $2; }
	|	'(' expr ')'
		{ $$ = $2; }
        |       fcall
                { $$ = $1; }
        ;

fcall   :       IDENT '(' fncargs ')'
                { $$ = makeexpr(OP_FCALL, 2, makeexpr(OP_FNAME, 1, $1, 0), $3); }
        |       IDENT '(' ')'
                { $$ = makeexpr(OP_FCALL, 2, makeexpr(OP_FNAME, 1, $1, 0), 0); }
        ;

fncargs :       expr
                { $$ = makeexpr(OP_RLIST, 2, $1, 0); }
        |       fncargs ',' expr
                { $$ = makeexpr(OP_RLIST, 2, $3, $1); }
        ;


value	:	IDENT
		{ $$ = makeexpr(OP_COLNAME, 1, $1, 0); }
	|	NUMBER
		{ $$ = makeexpr(OP_NUMBER, 1, $1, 0); }
	|	STRING
		{ $$ = makeexpr(OP_STRING, 1, $1, 0); }
	;

select_expr:	SELECT projection FROM join whereclause groupclause havingclause orderclause
		{ $$ = $4;
		  if($5) $$ = makeexpr(OP_SELECTION, 2, $$, $5);
		  if($6) $$ = makeexpr(OP_GROUP, 2, $$, $6);
		  $$ = makeexpr(OP_PROJECTION, 2, $$, $2);
		  if($7) $$ = makeexpr(OP_SELECTION, 2, $$, $7);
		  if($8) $$ = makeexpr(OP_SORT, 2, $$, $8);
		}
	;

whereclause:			{ $$ = 0; }
	|	WHERE expr	{ $$ = $2; }
	;

havingclause:			{ $$ = 0; }
	|	HAVING expr	{ $$ = $2; }
	;

groupclause:			{ $$ = 0; }
	|	GROUP BY grouplist
				{ $$ = $3; }
	;

grouplist:	groupspec
				{ $$ = makeexpr(OP_RLIST, 2, $1, 0); }
	|	grouplist ',' groupspec
				{ $$ = makeexpr(OP_RLIST, 2, $3, $1); }
	;

groupspec:	colname
	;

orderclause:			{ $$ = 0; }
	|	ORDER BY orderlist
				{ $$ = $3; }
	;

orderlist:	orderspec
				{ $$ = makeexpr(OP_RLIST, 2, $1, 0); }
	|	orderlist ',' orderspec
				{ $$ = makeexpr(OP_RLIST, 2, $3, $1); }
	;

orderspec:	NUMBER
		{ $$ = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_NUMBER, 1, $1, 0), 0); }
	|	NUMBER ASC
		{ $$ = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_NUMBER, 1, $1, 0), 0); }
	|	NUMBER DESC
		{ $$ = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_NUMBER, 1, $1, 0), makeexpr(OP_NULL, 0, 0, 0)); }
	|	colname
		{ $$ = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_COLNAME, 1, $1, 0), 0); }
	|	colname ASC
		{ $$ = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_COLNAME, 1, $1, 0), 0); }
	|	colname DESC
		{ $$ = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_COLNAME, 1, $1, 0), makeexpr(OP_NULL, 0, 0, 0)); }
	;

projection:	outcol
		{ $$ = makeexpr(OP_RLIST, 2, $1, 0); }
	|	projection ',' outcol
		{ $$ = makeexpr(OP_RLIST, 2, $3, $1); }
	;

outcol	:	expr AS colname
		{ $$ = makeexpr(OP_OUTCOLNAME, 2, $1, $3); }
	|	colname
		{ $$ = makeexpr(OP_OUTCOLNAME, 2, $1, $1); }
	;
		
join	:	tablename
		{ $$ = $1; }
	|	join ',' tablename
		{ $$ = makeexpr(OP_PRODUCT, 2, $1, $3); }
	;

data_list:	NUMBER
		{ $$ = makeexpr(OP_RLIST, 2, makeexpr(OP_NUMBER, 1, $1, 0), 0); }
	|	STRING
		{ $$ = makeexpr(OP_RLIST, 2, makeexpr(OP_STRING, 1, $1, 0), 0); }
	|	NUL
		{ $$ = makeexpr(OP_RLIST, 2, makeexpr(OP_NULL,0,0, 0), 0); }
	|	data_list ',' NUMBER
		{ $$ = makeexpr(OP_RLIST, 2, makeexpr(OP_NUMBER, 1, $3, 0), $1); }
	|	data_list ',' STRING
		{ $$ = makeexpr(OP_RLIST, 2, makeexpr(OP_STRING, 1, $3, 0), $1); }
	|	data_list ',' NUL
		{ $$ = makeexpr(OP_RLIST, 2, makeexpr(OP_NULL, 0, 0, 0), $1); }
	;

column_decls:	column_decl
		{ $$ = makeexpr(OP_RLIST, 2, $1, 0); }
	|	column_decls ',' column_decl
		{ $$ = makeexpr(OP_RLIST, 2, $3, $1); }
	;

column_decl:	colname
		{ $$ = makeexpr(OP_COLUMNDEF, 2, $1, 0); }
	|	colname KEY
		{ $$ = makeexpr(OP_COLUMNDEF, 2, $1, makeexpr(OP_STRING, 1, (int)"KEY", 0)); }
	|	colname PRIMARY KEY
		{ $$ = makeexpr(OP_COLUMNDEF, 2, $1, makeexpr(OP_STRING, 1, (int)"PRIMARY", 0)); }
	;

bin_op	:	'='	{ $$ = OP_EQUAL; }
	|	NOTEQ	{ $$ = OP_NOTEQ; }
	|	'>'	{ $$ = OP_GT; }
	|	'<'	{ $$ = OP_LT; }
	|	GEQ	{ $$ = OP_GEQ; }
	|	LEQ	{ $$ = OP_LEQ; }
	|	'+'	{ $$ = OP_PLUS; }
	|	'-'	{ $$ = OP_BMINUS; }
	|	'*'	{ $$ = OP_TIMES; }
	|	'/'	{ $$ = OP_DIVIDE; }
	|	AND	{ $$ = OP_AND; }
	|	OR	{ $$ = OP_OR; }
	;

%%
yyerror(char *str)
{
	printf("Line %d: %s\n", linenum, str);
	return 1;
}


