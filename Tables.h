
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <vector>
#include <map>
#include "Global.h"
#include "HW4-expr.h"
#include "MyItr.h"
#include "Btree.h"
#include "Expression.h"

#ifndef TABLES_H
  #define TABLES_H
  
using namespace std;


char* toChars( string s );
class Tables;
class Executor;

class Table{
  string name;
  vector<string> cols;
  map<string, BTree*> keys;
  //string p_keys;
  MyItr * myItr;
  friend class Tables;
  friend class Executor;

public:
  Table(){};
  Table(string _name,  vector<string> _cols, MyItr * itr );
  Table(string _name, string _firstRow );
  bool operator == ( Table rhs );
  bool operator == ( string rhs );
  bool has_index( std::string col );
  bool has_index( std::vector<std::string> col );
  MyItr * index_find( int op, string key_to_btree, Tuple tuple );
  MyItr * index_fetch( std::vector<std::streampos> offsets ); 
  void build_keys( std::vector<std::string> key_list );
  bool is_number(std::string s);  
  bool has_index_file(string col);
  void build_key_from_file( string col );
  std::string get_idx_path ( string col );
  void dump_tree( string col, BTreeNode * node );
  void delete_associate();
  int update_btree( std::string key_to_btree, std::string tuple, streampos offset ); // return distinct count of the btree after insertion.
  //Tuple build_tuple( std::string tuple);

  bool AND( expression * ep, string tuple );
  bool OR( expression * ep, string tuple );
  bool comparison( expression * ep, string tuple );
  bool num_comparison( expression * cond, string row );
  bool string_comparison( expression * ep, string row  );
  int arithmetic( expression * ep, string row );
  //bool comparison(  )
  std::string get_entry( std::string tuple, int pos ); // get the attributes at the location specified by pos
  std::string get_entry( std::string tuple, std::string col ); // get the attributes at the location specified by col
  int get_col_pos( string col );
  int get_colCnt();
  std::string get_path();
  bool hasCol( std::string col_name );
  MyItr * get_itr();
  void print_table();
  void print_keys();
  void deleterow( streampos pos, std::string tuple, std::string col );
};



class Tables {

protected:
  vector<Table*> tables;
  Table DOE;
  bool isTBLfile( string filename );

public:
  Tables();
  ~Tables(){};

  std::string getCurDir();
  bool hasTable ( std::string _tname );
  int get_colCnt( std::string t_name );
  bool existingDir( string dir_name );
  Table * get_table( std::string table_name );
  void add_table( std::string table_name, std::string _firstRow );
  void print_tables();
  void print_keys();
  void load_tables( std::string t_name );
  MyItr * get_itr( std::string tname );
  void add_table ( std::string table_name, std::string first_row, MyItr * itr );

};







  #endif