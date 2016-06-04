#include <cstring>
#include <vector>
#include "HW4-expr.h"
#include "Expression.h"


#ifndef REWRITER_H
	#define REWRITER_H
	
	class Rewriter;

	class Rule
	{
		std::string precondition;
		std::string then;
		std::vector<std::string>::iterator itr;
		friend class Rewriter;
	public:
		Rule(std::string _procondition, std::string _then);
		bool has_index( expression * ep );
		bool apply_rule( expr * e );
		int construct_node( expression ** leftnode, expression ** rightnode );
	};

	class Rewriter 
	{
		std::vector<Rule*> rules;
	public:
		Rewriter(  );
		void rewrite( expr * e );
	};




	#endif 