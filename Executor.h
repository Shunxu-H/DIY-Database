// Executor


#include <iostream>
#include "Tables.h"
#include "Expression.h"
#include "Global.h"
#include "MyItr.h"


#ifndef EXECUTOT_H
  #define EXECUTOT_H

  typedef basic_string<char> string;


 char* toChars( std::string s );
 std::string* toStrings( std::vector<std::string> strings );

class Executor: public Tables {
  char* FAIL;
  MyItr * fail;
  std::vector<std::string> cast_cols;
  std::vector<std::string> requested_cols;
  std::vector<std::string> keys;
  std::vector<std::string> p_keys;
  std::string to_count;
  std::string to_avg;

  int get_colCnt( std::string tname );
  bool existingFile( std::string file_name );
  void print_result(std::vector<std::string> col_headers,  std::vector<int> col_nums, std::vector< std::vector< std::string >> wanted_tuples);
  void calc_max_name_size( std::string tuple, std::vector<int> &max_sizes );

public:
  Executor(){ /*cml.type = UNSET; */}
  char* define_table( std::string table_name, int n_col, std::string* col_names );
  char* insert_row( std::string table_name, int n_val, std::string* values );
  vector<string> Rlist( expr e );
  void outcolname( expr e );
  void execute(expr e);
  void create_table(expr e);
  void insert(expr e );
  void update_max_length( vector<string> reference, vector<int> &max_length_list );
  //vector<string>::iterator make_temp_table( Table tbl, expression * condition );
  MyItr * selectrow( MyItr * itr, expr e );
  MyItr * projectrow( MyItr * itr, expression * ep );
  MyItr * deleterow( MyItr * itr, expression * ep );
  void deleterow( streampos pos );
  MyItr * indexselect( expression * ep );
  MyItr * sort( expression * ep );
  std::string sortspec( expression * ep );
  std::string get_sta_path( std::string table_name );


  void execute_e(expr e, int lev);
  void compile_e(expr e, int lev);
  void execute(expr e, int lev);
  void print_result( MyItr * itr );
  MyItr * iterate( expr e );
  MyItr * product( expression * ep );
  void droptable( expression * ep );
  MyItr * distinct( MyItr * itr );
  MyItr * group( MyItr * itr, expression * ep, expression * to_project );
 };






  #endif