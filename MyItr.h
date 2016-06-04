#include <fstream>
#include <cstring>
#include <vector>
#include <iostream>



#ifndef MYITR_H
  #define MYITR_H

  
  class MyItr 
  {
    std::string path;
    std::ifstream fs;
    int load_size;
    std::vector<std::string> tuples;
    std::vector<std::ios_base::streampos> offsets;
    std::vector<std::string>::iterator itr;
    std::vector<std::ios_base::streampos>::iterator offsets_itr;
    std::ios_base::streampos cur_file_pos;
    int offset_cnt;
    int cur_pos;
    bool is_on_disk;

  public:
    std::string filename;
    std::string table1;
    std::string table2;

    std::string EOI;
    MyItr(){cur_pos = 0; tuples.push_back(std::string( "*EOI" ) ); };// {  std::cout << "DONT USE THIS DEFAULT CONSTRUCTOR FOR MyItr() " << std::endl; };
    MyItr( std::string _filename, int lc ); 
    MyItr( std::string _filename, std::vector<std::string> _tuple );
    void operator += ( MyItr &lhs );
    void open(); // open the file
    std::string get_next(); // get the next tuple, if none trying loading it from fd
    std::ios_base::streampos get_cur_pos();
    void close(); // close the file
    bool hasMore( ); // return true if the file has not reach the end.
    bool is_open();
    void load(); // read more lines from the file
    std::string first(); // return the first item in itr
    void print_all();
    int get_col_pos( std::string s );
    void sort( std::string sortkey );
    char * dump_table( std::string table_name );
    MyItr * nested_join( MyItr & rhs );
    MyItr * nested_join( std::string header, std::string tuple);
    bool is_last();
    std::vector<int> get_positions( std::string & tuple, std::vector<std::string> & intercept );
    std::string strings_match( std::string s1, std::vector<int> poses1, std::string s2, std::vector<int> poses2, std::vector<int> & intercept );
    std::string eliminate_intercept( std::vector<std::string> tuple, std::vector<int> poses );
    std::string eliminate_intercept( std::vector<std::string> tuple, std::vector<int> poses, std::string & intercept );
    std::vector<int> get_positions( std::string & tuple, std::vector<std::string> & intercept, std::vector<int> & not_intercept );
    MyItr * hash_join( MyItr & rhs );
    MyItr * cross_product( MyItr &rhs );
    /*
*/
  };




  #endif 