%%
[a-zA-Z_.$][a-zA-Z0-9_.$]*	{ char buf[10]; int i=0; char *np;
				  for(i=0; i<yyleng && i<9; i++) buf[i]=toupper(yytext[i]); buf[i]=0;
				  if(!strcmp("SELECT", buf)) return SELECT;
				  if(!strcmp("FROM", buf)) return FROM;
				  if(!strcmp("WHERE", buf)) return WHERE;
				  if(!strcmp("AS", buf)) return AS;
				  if(!strcmp("GROUP", buf)) return GROUP;
				  if(!strcmp("BY", buf)) return BY;
				  if(!strcmp("HAVING", buf)) return HAVING;
				  if(!strcmp("ORDER", buf)) return ORDER;
				  if(!strcmp("ASC", buf)) return ASC;
				  if(!strcmp("DESC", buf)) return DESC;
				  if(!strcmp("INSERT", buf)) return INSERT;
				  if(!strcmp("INTO", buf)) return INTO;
				  if(!strcmp("VALUES", buf)) return VALUES;
				  if(!strcmp("DELETE", buf)) return DELETE;
				  if(!strcmp("CREATE", buf)) return CREATE;
				  if(!strcmp("TABLE", buf)) return TABLE;
				  if(!strcmp("DROP", buf)) return DROP;
				  if(!strcmp("QUIT", buf)) return QUIT;
				  if(!strcmp("KEY", buf)) return KEY;
				  if(!strcmp("PRIMARY", buf)) return PRIMARY;
				  if(!strcmp("DISTINCT", buf)) return DISTINCT;
				  if(!strcmp("NULL", buf)) return NUL;
				  if(!strcmp("AND", buf)) return AND;
				  if(!strcmp("OR", buf)) return OR;
				  if(!strcmp("NOT", buf)) return NOT;
				  if(!strcmp("UPDATE", buf)) return UPDATE;
				  if(!strcmp("SET", buf)) return SET;
				  if(!strcmp("IN", buf)) return IN;
				  if(!strcmp("COUNT", buf)) return COUNT;
				  if(!strcmp("AVG", buf)) return AVG;
				  np = (char *)malloc(yyleng+1);
				  for(i=0; i<yyleng; i++) np[i] = tolower(yytext[i]);
					np[i] = '\0';
					yylval = makename(OP_FNAME, np);
					return IDENT;
				}
[0-9]+				{ yylval = makenum(atoi(yytext)); return NUMBER; }
'[^\n']*'			{ yylval = makestrexpr(strcpy((char *)malloc(yyleng+1), yytext)); return STRING; }
'[^'\n]*\n			{ printf("ERROR: Unterminated string in line %d\n", linenum++); }
=				{ return '='; }
\<\>				{ return NOTEQ; }
\<				{ return '<'; }
\>				{ return '>'; }
\<=				{ return LEQ; }
\>=				{ return GEQ; }
\n				{ linenum++; }
[ \t]				{ ; }
\(				{ return '('; }
\)				{ return ')'; }
\+				{ return '+'; }
-				{ return '-'; }
\*				{ return '*'; }
\/				{ return '/'; }
;				{ return ';'; }
,				{ return ','; }
.				{ printf("Warning: Invalid character in line %d ignored\n", linenum); }
%%

int
yyFlexLexer::yywrap()
{
	//printf("::Saw EOF\n");
	return 1;
}
