#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <vector>
#include <errno.h>
#include <cstdio>
#include "Btree.h"
#include "Tables.h"
#include "MyItr.h"
#include "Tuple.h"
#include "Global.h"
#include "HW4-expr.h"
#include "Expression.h"

// after the table is created, all the tables are gone
// fix it
int LOAD_CNT = 100;
typedef basic_string<char> string;


/*
Table::Table(string _name, vector<string> _cols, MyItr * _myItr )
{
  name = _name;
  cols = _cols;
  myItr = _myItr;
  //rows = content;
}
*/
Table::Table(string _name, string first_row)
{

  string line;
  name.assign( _name );
  vector<string> key_list;
  //cout << first_row << endl;
  char* s = toChars( first_row );
  char* token;
  token = strtok ( s, "\t" );
  while ( token ){
    if ( token[0] == '*' )
    {
      key_list.push_back( string( token + 1 ) );
      cols.push_back( string( token + 1 ) );  
    }
    else
      cols.push_back( string( token ) );

   token = strtok ( NULL, "\t" );
  }

  if ( key_list.size() > 0 )
    build_keys( key_list );
  //cout << "!" << _name << endl;
  myItr = new MyItr( _name, 10 );
}

// 
string Table::get_entry( string tuple, int pos )
{
  char _tuple[tuple.size() + 1];
  strcpy( _tuple, tuple.c_str() );

  // tokenize
  char * token = strtok ( _tuple, "\t" );
  for ( int i = 0; i < pos; i ++ )
    token = strtok( NULL, "\t" );

  return string( token );

}

string Table::get_entry( string tuple, std::string col )
{
  int pos = get_col_pos( col );
  std::string to_return;
  if ( pos == -1 )
  {
    return to_return;
  }

  char _tuple[tuple.size() + 1];
  strcpy( _tuple, tuple.c_str() );

  // tokenize
  char * token = strtok ( _tuple, "\t" );
  for ( int i = 0; i < pos; i ++ )
    token = strtok( NULL, "\t" );

  return string( token );

}

bool Table::has_index_file(string col)
{
  // construct name
  string path ( "./data/" );
  path.append( name + string( "." ) + col + string( ".idx" ) );
  //cout << path << endl;
  ifstream fs( path.c_str() );
  if ( !fs.is_open() )
  {
    return false;
  }

  fs.close();
  return true;
}

void Table::build_key_from_file( string col )
{
  fstream fs( get_idx_path( col ) );

  if( !fs.is_open( ) )
  {
    cerr << "ERROR open file in Table::build_key_from_file(). " << endl;
    return;
  }

  BTree * btree = new BTree( 5, 6 );

  string line;
  while ( getline( fs, line ) )
  {
    char s[line.size() + 1];
    strcpy( s, line.c_str() );
    int type = 0;
    char * c_type;
    int n_type;

    char * token = strtok ( s, " " );
    type = atoi( token );
    token = strtok( NULL, " " );

    if ( type == NUM )
      n_type = atoi( token );
    else
    {
      c_type = new char[strlen( token )];
      strcpy( c_type, token  );
    }

    token = strtok( NULL, " " );

    vector<streampos> vp;
    while( token )
    {
      vp.push_back( atoi( token ) );
      token = strtok( NULL, " " );
    }


    if ( type == NUM )
      btree->insert( Tuple( n_type, vp  ) );
    else
      btree->insert( Tuple( c_type, vp  ) );
  }


  keys.insert( pair<string, BTree*>( col, btree )  );

  fs.close();



}

string Table::get_idx_path ( string col )
{
  string path ( "./data/" );
  path.append( name + string( "." ) + col + string( ".idx" ) );
  return path;
}

void Table::dump_tree( string col, BTreeNode * node )
{
  ofstream ofs ( get_idx_path( col ).c_str(), std::ofstream::out | std::ofstream::trunc );

  BTreeNode * cur_node = node;
  while ( cur_node )
  {
    Tuple * values = ((LeafNode *)cur_node)->get_values();
    for ( int i = 0; i < cur_node->getCount(); i++ )
    {
      ofs << values[i].datatype << " ";
      if (values[i].datatype == NUM )
        ofs << values[i].value.num << " ";
      else 
        ofs << values[i].value.str << " ";

      for( int j = 0; j < values[i].offset.size(); j++ )
        ofs << values[i].offset[j] << " ";

      ofs << "\n";

    }

    cur_node = cur_node->getRightSibling();
  }


  ofs.close();


}


void Table::delete_associate()
{
  // delete index files
  for ( map<string, BTree*>::iterator itr = keys.begin(); itr != keys.end(); itr++ )
  {
    string path = get_idx_path ( itr->first );
    remove( path.c_str() );
  }

  // remove table
  string path = get_path();
  remove( path.c_str() );
  path = construct_sta_path( name );
  remove( path.c_str() );
}

bool Table::is_number(std::string s){
  //scan();
  std::string::const_iterator it = s.begin();
  while ( it != s.end() && isdigit( *it ) )
    it++;
  return !s.empty() && it == s.end();
}

void Table::build_keys( vector<string> key_list )
{
  // construct file pat
  string path( "./data/" );
  path.append( name );
  path.append( ".tbl" );

  ifstream fs( path.c_str() );
  if ( !fs.is_open() )
  {
    cout << path << endl;
    cerr << "ERROR: file does not exist in Table::build_keys(). " << endl;
    return;
  }

  for ( int i = 0; i < key_list.size(); i++ )
  {
    if( has_index_file( key_list[i] ) )
    {
      build_key_from_file( key_list[i] );
      continue;
    }


    int pos = get_col_pos( key_list[i] );
    
    streampos offset = 0;

    BTree * btree = new BTree ( 5, 6 );
    string line;
    getline( fs, line ); // get rid of the first line

    offset = fs.tellg(); 
    while ( getline ( fs, line ) && line.size() > 0)
    {
      // to ignore the deleted lines
      //cout << line << endl;
      if( line[0] == '@' )
      {
        //cout << line << endl;
        offset = fs.tellg();
        continue;
      }

      string entry = get_entry( line, pos );

      if ( is_number ( entry ) ) 
      {
        Tuple cur_tuple( atoi( entry.c_str() ),  offset );
        btree->insert( cur_tuple );
      }
      else 
      {
        Tuple cur_tuple( entry.c_str() ,  offset );
        btree->insert( cur_tuple );
      }
      offset = fs.tellg();
    }

    keys.insert( pair<string, BTree*>( key_list[i], btree )  );
    fs.clear();
    fs.seekg( fs.beg );

    BTreeNode * node = btree->get_first();
    dump_tree( key_list[i], node );
  }

  fs.close();
}

int Table::update_btree( std::string key_to_btree, std::string tuple, streampos offset )
{ // return distinct count of the btree

  // find the btree
  map<string, BTree*>::iterator map_itr = keys.find( key_to_btree );
  BTree * btree; 

  if ( map_itr == keys.end() )
  {
    cerr << "ERROR: Key does not exist in Table::update_btree()." << endl;
    return -1;
  }

  btree = map_itr->second;

  // get the targeted tuple 
  // construct a tuple
  int pos = get_col_pos( key_to_btree );  
  char * token; 
  char * s = toChars( tuple );

  token = strtok( s, "\t" );
  for ( int i = 0; i < pos; i++ )
    token = strtok( NULL, "\t" );

  Tuple * t;
  string key ( token );

  if ( is_number( key ) )
    t = new Tuple( atoi( key.c_str() ), offset  );
  else
    t = new Tuple( key.c_str(), offset  );

  btree->insert( *t );

  delete( t );

  return btree->get_distinct_cnt();
  // get distinct count 

}


bool Table::operator == ( Table rhs )
{
  return (name.compare( rhs.name ) == 0 );
}

bool Table::operator == ( string rhs )
{
  //cout << name << " " << rhs << endl;
  return ( name.compare( rhs ) == 0 );
}

bool Table::has_index( string col )
{

  for (map<string, BTree*>::iterator itr = keys.begin(); itr != keys.end(); itr++ )
  {
    if ( itr->first.compare( col ) == 0 )
      return true;
  }
  return false;

}

bool Table::has_index( std::vector<std::string> vs )
{

    unsigned int i;
    for ( i = 0; i < vs.size(); i++ )
    {
      map<string, BTree*>::iterator itr;
      for( itr = keys.begin(); itr != keys.end(); itr++ )
        if ( itr->first.compare( vs[i] ) == 0 )
          break;
      if ( itr == keys.end() )
        return false;
    }

  return true;

}

MyItr * Table::index_find(int op, string key_to_btree, Tuple to_find )
{
  //cout << op << endl;
  map<string, BTree*>::iterator map_itr = keys.find( key_to_btree ); 
  MyItr * itr = NULL;
  //tuples.push_back( myItr->first() ); // get the headers

  // if there is not index for the column, should never happen
  if ( map_itr == keys.end() )
  {
    return NULL;
  }

  BTree * btree = map_itr->second;

  if ( op == OP_EQUAL )
  {
    //cout << "euql " << endl;
    BTreeNode * node = btree->find( to_find );
    if ( node == NULL )
      return NULL;

    for ( int i = 0; i < node->getCount(); i++ )
    {
      if ( to_find == ( (LeafNode *) node )->get_values()[i] )
      {
        vector<streampos> offset = ( (LeafNode *) node )->get_values()[i].offset;
        //cout << offset.size() << endl;
        itr = index_fetch( offset );
      }
    }
  }
  else if ( op == OP_LEQ )
  {
    BTreeNode * node = btree->find_leq( to_find );

    if ( node == NULL )
      return NULL;

    BTreeNode * cur_node = node;
    vector<string> tuples;
    myItr->open();
    tuples.push_back( myItr->first() );
    myItr->close();
    itr = new MyItr( name, tuples  );

    while( node )
    {
      for ( int i = node->getCount() - 1;  i >= 0; i-- )
      {
        if ( ( (LeafNode *) node )->get_values()[i] <= to_find)
        {
          vector<streampos> offset = ( (LeafNode *) node )->get_values()[i].offset;
          *itr += *( index_fetch( offset ) );
        }
      }
      node = node->getLeftSibling();
    }
  }
  else if ( op == OP_LT )
  {
    BTreeNode * node = btree->find_leq( to_find );

    if ( node == NULL )
      return NULL;

    BTreeNode * cur_node = node;
    vector<string> tuples;
    myItr->open();
    tuples.push_back( myItr->first() );
    myItr->close();
    itr = new MyItr( name, tuples  );
    //cout << " at least here" << endl;
    while( node )
    {
      for ( int i = node->getCount() - 1; i >= 0; i-- )
      {
        if ( ( (LeafNode *) node )->get_values()[i] < to_find)
        {
          vector<streampos> offset = ( (LeafNode *) node )->get_values()[i].offset;
          *itr += *( index_fetch( offset ) );
        }
      }
      node = node->getLeftSibling();
    }
  }
  else if ( op == OP_GEQ )
  {
    BTreeNode * node = btree->find_geq( to_find );

    if ( node == NULL )
      return NULL;

    BTreeNode * cur_node = node;
    vector<string> tuples;
    myItr->open();
    tuples.push_back( myItr->first() );
    myItr->close();
    itr = new MyItr( name, tuples  );
    //cout << " at least here" << endl;
    while( node )
    {
      for ( int i = 0;  i < node->getCount(); i++ )
      {
        if ( ( (LeafNode *) node )->get_values()[i] >= to_find)
        {
          vector<streampos> offset = ( (LeafNode *) node )->get_values()[i].offset;
          *itr += *( index_fetch( offset ) );
        }
      }
      node = node->getRightSibling();
    }
  }
  else if ( op == OP_GT )
  {
    //cout << "GT" << endl;
    BTreeNode * node = btree->find_geq( to_find );

    if ( node == NULL )
      return NULL;
    
    BTreeNode * cur_node = node;
    vector<string> tuples;
    myItr->open();
    tuples.push_back( myItr->first() );
    myItr->close();
    itr = new MyItr( name, tuples  );
    //cout << " at least here" << endl;
    //cout << node << endl;
    while( node )
    {
      for ( int i = 0;  i < node->getCount(); i++ )
      {
        if ( ( (LeafNode *) node )->get_values()[i] > to_find)
        {
          vector<streampos> offset = ( (LeafNode *) node )->get_values()[i].offset;
          *itr += *( index_fetch( offset ) );
        }
      }
      node = node->getRightSibling();
    }
  }
  else
  {
    cerr << "Error in Table::index_find(): should never be here." << endl;
    return NULL;
  }

  return itr;
}

string Table::get_path()
{
  string path ( "./data/" );
  path.append( name );
  path.append( ".tbl" );

  return path;
}

void Table::deleterow( streampos pos, string tuple, string col )
{
  //cout << col << endl;
  ifstream ifs( get_path( ) );
  string temp_file;
  if( !ifs.is_open() )
  {
    cerr << "ERROR opening file in Executor::deleterow(). " << endl;
    return;
  }

  string s;
  string line;
  while ( ifs.tellg() != pos )
  {
    getline( ifs, line );
    temp_file.append( line + string( "\n")  );
  }
  getline( ifs, line );
  //temp_file.append( line  + string( "\n")  );

  //cout << line << endl;

  // update btree index
  if( has_index( col ) )
  {
    map<string, BTree*>::iterator map_itr = keys.find( col );
    BTree * btree = map_itr->second;

    //construct tuple
    int type;
    string entry( get_entry( line, get_col_pos( col ) ) );

    if( is_number( entry ) )
      btree->remove( Tuple ( atoi( entry.c_str() ), pos )  );
    else 
      btree->remove( Tuple ( entry.c_str(), pos ) );

    dump_tree( col, btree->get_first() );
  }


  line[0] = '@';
  temp_file.append( line + string( "\n")  );

  while ( getline( ifs, line ) )
    temp_file.append( line + string( "\n")  );

  ifs.close();

  // rewrite the whole file
  ofstream ofs ( get_path( ), std::ofstream::out | std::ofstream::trunc );
  if( !ofs.is_open() )
  {
    cerr << "ERROR opening out file in Executor::deleterow(). " << endl;
    return;
  }

  ofs << temp_file;

  ofs.close();
}

MyItr * Table::index_fetch ( vector<streampos> offsets )
{
  //cout << "inddex_ fetch" << endl;
  vector<string> tuples;
  string line;
  string path( get_path() );
  ifstream fs( path );

  if( !fs.is_open() )
    return new MyItr( name, tuples );

  // get the first line, aka headers
  getline ( fs, line );
  tuples.push_back( line );

  // load tuples specified 
  for ( int i = 0; i < offsets.size(); i++ )
  {
    if( offsets[i] == -1 )
      continue;

    fs.clear();
    fs.seekg( offsets[i] );
    getline(fs, line );
    //cout << line << endl;
    tuples.push_back( line );

  }

  fs.close();

  return new MyItr( name, tuples );
}

int Table::arithmetic( expression * ep, string row )
{
  if ( !ep )
  {
    cout << "error in Table::arithmetic()" << endl;
    return 0;
  }

  expression* node[2];
  node[0] = ep->values[0].ep;
  node[1] = ep->values[1].ep;
  int v_lhs = 0;
  int v_rhs = 0;
  int ops[2];

  // tokenize row
  vector<string> row_v;
  char *s = toChars( row );
  char *token;

  token = strtok( s, "\t" );
  while ( token )
  {
    row_v.push_back( string( token ) );
    token = strtok ( NULL, "\t" );
  }
  if ( row_v.size() != cols.size() )
    return false;

  // see if nodes are number or string, 
  // if it is string, we need to find the actual value in database
  for ( int i = 0; i < 2; i++ )
  {

    if ( node[i]->func != OP_COLNAME && node[i]->func != OP_NUMBER )
      return arithmetic( node[i], row );
    else if ( node[i]->func == OP_NUMBER ) 
    {
      ops[i] = node[i]->values[0].num;
    }
    else if ( node[i]->func == OP_COLNAME )
    {
      int pos = get_col_pos( node[i]->values[0].data );
      if ( pos < 0 )
      {
        cout << "column does not exist!" << endl;
        return false;
      }
      ops[i] = atoi( row_v[pos].c_str() );
    }
  }

    // start comparison
  switch( ep->func ){

    case OP_PLUS:     return ops[0] + ops[1]; break;
    case OP_BMINUS:   return ops[0] - ops[1]; break;
    case OP_TIMES:    return ops[0] * ops[1]; break;
    case OP_DIVIDE:   return ops[0] / ops[1]; break;
    case OP_UMINUS:   return -ops[0]; break;
    default : 
              cout << "OPERATOR NOT SUPPORTED! " << endl;
              return false;
              break;

  }
}

bool Table::AND( expression * ep, string tuple )
{
  bool lhs = false;
  bool rhs = false;
  if ( ep->values[0].ep->func == OP_AND )
    lhs = AND ( ep->values[0].ep, tuple );
  else if ( ep->values[0].ep->func == OP_OR )
    lhs = OR ( ep->values[0].ep, tuple );
  else
    lhs = comparison ( ep->values[0].ep, tuple );

  if ( ep->values[1].ep->func == OP_AND )
    rhs = AND ( ep->values[1].ep, tuple );
  else if ( ep->values[1].ep->func == OP_OR )
    rhs = OR ( ep->values[1].ep, tuple );
  else
    rhs = comparison ( ep->values[1].ep, tuple );

  return lhs && rhs;
}

bool Table::OR( expression * ep, string tuple )
{
  bool lhs = false;
  bool rhs = false;

  if ( ep->values[0].ep->func == OP_AND )
    lhs = AND ( ep->values[0].ep, tuple );
  else if ( ep->values[0].ep->func == OP_OR )
    lhs = OR ( ep->values[0].ep, tuple );
  else
    lhs = comparison ( ep->values[0].ep, tuple );

  if ( ep->values[1].ep->func == OP_AND )
    rhs = AND ( ep->values[1].ep, tuple );
  else if ( ep->values[1].ep->func == OP_OR )
    rhs = OR ( ep->values[1].ep, tuple );
  else
    rhs = comparison ( ep->values[1].ep, tuple );

  return lhs || rhs;
}


bool Table::comparison( expression * ep, string tuple )
{
  if ( !ep )
    return false;
  //if ( ep->func  )
  if( ep->values[0].ep->func == OP_STRING || 
        ep->values[1].ep->func == OP_STRING )
      {
        //cout << "here" << endl;
        return string_comparison( ep, tuple );
      }
      else
      {
        return num_comparison( ep, tuple );
          
      }
}

bool Table::string_comparison( expression * ep, string row  )
{
//cout << "here " << endl;
  if ( !ep )
    return false;

  //cout << "what?" << endl;
  expression* node[2];
  node[0] = ep->values[0].ep;
  node[1] = ep->values[1].ep;
  string ops[2];

  vector<string> row_v;
  char *s = toChars( row );
  char *token;

  token = strtok( s, "\t" );
  while ( token )
  {
    row_v.push_back( string( token ) );
    token = strtok ( NULL, "\t" );
  }
  if ( row_v.size() != cols.size() )
    return false;

  // see if nodes are number or string, 
  // if it is string, we need to find the actual value in database
  for ( int i = 0; i < 2; i++ )
  {
    if ( node[i]->func == OP_STRING )
    {
      ops[i] = string( node[i]->values[0].data );
      //cout << "!" << ops[i] << endl;
    }
    else if ( node[i]->func == OP_COLNAME )
    {
      //cout <<  node[i]->values[i].name << endl;
      int pos = get_col_pos( node[i]->values[i].name );
      if ( pos < 0 )
      {
        cout << "column does not exist!" << endl;
        return false;
      }

      ops[i] = string( row_v[pos] );

    }
  }

  switch( ep->func ){

    case OP_EQUAL:  return  (ops[0].compare( ops[1] ) == 0 ); break;
    default : 
              cout << "OPERATOR ON STRING NOT SUPPORTED! " << endl;
              return false;
              break;

  }
}

bool Table::num_comparison( expression * ep, string row )
{
  if ( !ep )
    return false;

  expression* node[2];
  node[0] = ep->values[0].ep;
  node[1] = ep->values[1].ep;
  int v_lhs = 0;
  int v_rhs = 0;
  int ops[2];

  // tokenize row
  vector<string> row_v;
  char *s = toChars( row );
  char *token;

  token = strtok( s, "\t" );
  while ( token )
  {
    row_v.push_back( string( token ) );
    token = strtok ( NULL, "\t" );
  }
  if ( row_v.size() != cols.size() )
    return false;

  // see if nodes are number or string, 
  // if it is string, we need to find the actual value in database
  for ( int i = 0; i < 2; i++ )
  {
    if ( node[i]->func != OP_COLNAME && node[i]->func != OP_NUMBER )
    {
      ops[i] = arithmetic( node[i], row );
    }

    else if ( node[i]->func == OP_NUMBER ) 
    {
      ops[i] = node[i]->values[0].num;
    }
    else if ( node[i]->func == OP_COLNAME )
    {
      int pos = get_col_pos( string( node[i]->values[0].name ) );
      if ( pos < 0 )
      {
        cout << "column does not exist!" << endl;
        return false;
      }
      ops[i] = atoi( row_v[pos].c_str() );
    }
  }

    // start comparison
  switch( ep->func ){

    case OP_EQUAL:  return ops[0] == ops[1]; break;
    case OP_NOTEQ:  return ops[0] != ops[1]; break;
    case OP_LEQ:    return ops[0] <= ops[1]; break;
    case OP_GEQ:    return ops[0] >= ops[1]; break;
    case OP_LT:     return ops[0] < ops[1]; break;
    case OP_GT:     return ops[0] > ops[1]; break;
    default : 
              cout << "OPERATOR NOT SUPPORTED! " << endl;
              return false;
              break;

  }
}

int Table::get_col_pos( string col ){

  int i = 0;
  if( col[0] == '*' || col[0] == '&' )
    col = col.substr( 1, col.size() );

  for ( vector<string>::iterator itr = cols.begin() ; itr != cols.end(); itr++ )
  {

    if ( (*itr).compare( col ) == 0){
      return i;
    }
    i++;
  }

  return -1;
  
}

int Table::get_colCnt()
{

  return cols.size();
}

bool Table::hasCol( std::string col_name ){
  bool hasCol = false;
  for ( vector<string>::iterator it = cols.begin(); it != cols.end(); ++it ){
    if ( it->compare( col_name ) )
    {
      hasCol = true;
      break;
    }
  }
  return hasCol;
}

void Table::print_table(){
  cout << name << ": " << endl;
  for ( int i = 0 ; i < cols.size(); i++ )
    cout << "  " << cols[i] << " ";
  cout << endl;

}

void Table::print_keys()
{
  for (map<string, BTree*>::iterator itr = keys.begin(); itr != keys.end(); itr++ )
  cout << "DEBUG: " << name << "." << itr->first << " has a B-tree index. " << endl;
}

MyItr * Table::get_itr()
{
  return myItr;
}

Tables::Tables(){

  if ( !existingDir( string( "data" ) )){
    if ( !existingDir( "data" ) )
    {
      if ( system( "mkdir data" ) != 0  ){
        cerr << "Error making database directory" << endl;
        exit(1);
      }
      system( "cd data" );
    }
  }
      
    
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir( "./data" )) != NULL ){
      while( (ent = readdir( dir )) != NULL) {
        string file_name( ent->d_name );
        if ( isTBLfile( file_name ) ){
          string first_line;  
        
          ifstream table( toChars( string ( string( "./data/") + string (ent->d_name ) ) ) );
          if( table.is_open() ){
            getline( table, first_line );
            table.close();
          }

          add_table( file_name.substr(0, file_name.size() - 4 ) , first_line );
        }
      }
    }
  }

string Tables::getCurDir(){
  char cwd[2048];
  if ( getcwd( cwd, 2048 ) )
    return string( cwd );
  else
  {
    int error = errno;
    switch ( error )
    {

      case EACCES: write( 1, "Access denied\n", 20 ); break;
      case ERANGE: write( 1, "need to resize MAXPATHNAME\n", 30 ); break;     
      case EFAULT: write( 1, "points to bad address\n", 20);
      default:  write( 1, "undefined error\n", 20); break;
    }

    return string("");
  }
}


bool Tables::existingDir( string dir_name ){
  struct stat buff;

  if ( stat( dir_name.c_str(), &buff) != -1){
    if (  S_ISDIR(buff.st_mode) )
      return true;
  }
  
  return false;
}

bool Tables::isTBLfile( string filename )
{
  size_t DotPos = filename.find_first_of( "." );

  if ( DotPos != string::npos )
  {

    string s = filename.substr(DotPos, filename.size() );
    //cout << s << endl;
    return s.compare( ".tbl" ) == 0;
  }
  else 
    return false;
}



Table * Tables::get_table( std::string table_name )
{

  for( vector<Table*>::iterator it = tables.begin(); it != tables.end(); it++ ){
    if ( **it == table_name ){
      return *it;
    }
  
  }

  return NULL;
}

int Tables::get_colCnt( std::string t_name ){
 //cout << "~"<< t_name << endl;
  for ( vector<Table*>::iterator it = tables.begin(); it != tables.end(); ++it ){
    if ( **it == t_name )
    {
      //cout << "?" << (it)->name << endl;
      return (*it)->get_colCnt();
    }
  }
}

void Tables::add_table( string table_name, string first_row ){
  
  tables.push_back( new Table ( table_name, first_row )  );
}
/*
void Tables::add_table ( std::string table_name, std::string first_row, MyItr * itr )
{

  tables.push_back( new Table( table_name, tokenize_string(first_row, "\t"), itr ) );
}

*/
bool Tables::hasTable( string _tname )
{
  for ( int i = 0; i < tables.size(); i++ )
  {
    if ( *( tables[i] ) == _tname )
    {
      
      return true;
    }
  }
  return false;
}

void Tables::print_tables(){
  if ( tables.size() == 0)
    cout << "no table loaded" << endl;
  for ( int i = 0; i < tables.size(); i++)
    (*tables[i]).print_table();
}

void Tables::print_keys()
{
  for ( int i = 0; i < tables.size(); i++ )
    tables[i]->print_keys();

}

MyItr * Tables::get_itr( string t_name )
{
  Table * table = get_table ( t_name );

  if ( table )
    return table->get_itr();
  else
    return NULL;
}
