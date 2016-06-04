#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include "Rewriter.h"
#include "HW4-expr.h"
#include "Expression.h"
#include "Executor.h"
#include "Tables.h"

using namespace std;
typedef basic_string<char> string;

extern Executor executor;

/* ============== codes for Rewiter ================*/

Rule::Rule(string _precondition, string _then)
{
	precondition  = _precondition;
	then = _then;
}

int Rule::construct_node( expression ** leftnode, expression ** rightnode )
{
	int arg[4];
	int haspreplaced[4];
	//cout << *itr << endl;
	itr++; // get ride of the first '('
	for( int i = 0; i < 4; i++ )
	{
	//cout << *itr ;
		string cur_str = *itr;
		if ( (*itr).compare( "(" ) == 0 )
		{
			arg[i] =  construct_node( leftnode, rightnode );
			continue;
		}
		else
		{
			arg[i] = atoi (cur_str.c_str());
		}
		itr++;
		//cout << *itr << endl;
	}
	
	itr++; // get ride of the ')'

	int to_return = makeexpr( arg[0], arg[1], arg[2], arg[3] );
	for( int i = 0; i < 4; i++ )
	{
		if( arg[i] == -1 )
		{
			((expression *)cvt_itoe( to_return ))->values[0].ep = *leftnode;
		}
		else if ( arg[i] == -2 )
		{
			((expression *)cvt_itoe( to_return ))->values[1].ep = *rightnode;
		}
	}
	//if ( arg[2] == -1 )
	//ebuf[i-MAXNODE].values[0].ep = ( expression * ) e;

	//cout << *itr << endl;
	return to_return;
}

bool Rule::has_index( expression * ep )
{
	//cout << "!" << ep->values[0].ep->values[0].name << endl;
	bool has_index = false;
	expression * condition = ep->values[1].ep;
	Table * tbl = executor.get_table( string ( ep->values[0].ep->values[0].name ) );

	if ( !tbl )
		return false;

	if ( condition->values[0].ep->func == OP_COLNAME )
	{
		//cout << condition->values[0].ep->values[0].name << endl;
		has_index = tbl->has_index( string ( condition->values[0].ep->values[0].name ) );
	}
	else if ( condition->values[1].ep->func == OP_COLNAME )
		has_index = tbl->has_index( string ( condition->values[1].ep->values[0].name ) );

	return has_index;
}

bool Rule::apply_rule( expr * e )
{
	expression * ep = ( expression * ) *e;

	if ( precondition.compare( "*1" ) == 0 && ep->func == OP_SELECTION && has_index( ep )  )
		;
	// check if the func is in our library
	else if( ep->func != atoi( precondition.c_str() )  )
		return false;

	// if yes, then apply rule
	expression * leftnode = ep->values[0].ep;
	expression * rightnode = ep->values[1].ep;

	// tokenize then
	char s[then.size() + 1];
	strcpy( s, then.c_str() );
	//cout << s << endl;
	char * token = strtok( s, " " );
	vector<string> vs;
	while( token )
	{
		//cout << token << endl;
		vs.push_back( string( token ) );
		token = strtok( NULL, " " );
	}

	itr = vs.begin();
	*e = (expr) cvt_itoe( construct_node( &leftnode, &rightnode ) );
	return true;
}

/* ============== codes for Rewiter ================*/
Rewriter::Rewriter()
{


	// read in all the rules
	ifstream fs;
	fs.open( "rules.txt" );
	if( !fs.is_open() )
	{
		cerr << "ERROR openning files in Rewiter(). " << endl;
		return;
	}
	string line;
	while ( getline ( fs, line ))
	{
		string precondition = line;
		getline( fs, line );
		string then = line;
		//cout << precondition << " " << then << endl;
		rules.push_back( new Rule( precondition, then ) );
	}

}

void Rewriter::rewrite( expr * e )
{
	expression * ep = ( expression * ) *e;
	for ( int i = 0; i < rules.size(); i++ )
	{
		//cout << ep->func << endl;
		if( rules[i]->apply_rule( e ) )
			break;
	}

}

