#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include "HW4-expr.h"
#include "Expression.h"
#include "MyItr.h"

#ifndef	GLOBAL_H
	#define GLOBAL_H
	

char* toChars( std::string s );
std::vector<std::string> tokenize_string( std::string s, const char * delimiter  );
std::vector<std::string> intercept_cols( std::vector<std::string> vs1, std::vector<std::string> vs2 );
bool compare_without_star( std::string s1, std::string s2 );
int get_col_pos(std::vector<std::string> header, std::string col );
std::string join_headers( std::string header1, std::string header2 );
std::string join_tuples( std::string s1, std::string s2 );
bool is_number(std::string s); 
std::string construct_tbl_path( std::string table_name );


bool IN( std::string col, std::vector<std::string> vals, std::string header, std::string tuple );
int get_col_pos( std::string col, std::string header );
int arithmetic( expression * ep, std::string header, std::string row );
bool AND( expression * ep, std::string header, std::string tuple );
bool OR( expression * ep, std::string header, std::string tuple );
bool comparison( expression * ep, std::string header, std::string tuple );
bool string_comparison( expression * ep, std::string header, std::string row  );
bool num_comparison( expression * ep, std::string header, std::string row );
std::ifstream::pos_type filesize(const char* filename);
std::string construct_tbl_path( std::string table_name );
std::string construct_sta_path( std::string table_name );
std::string get_entry( std::string header, std::string tuple, std::string col );
std::string get_entry( std::string tuple, int pos );
bool parsetreeDistinct(expression *ep);
bool isDistinct(expr e);
std::unordered_map<std::string, std::vector<std::string>* > get_hash( MyItr * itr, std::vector<std::string> keys );


	#endif 