#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "Global.h"
#include "Expression.h"
#include "HW4-expr.h"



//extern Executor executor;


// set<string> tablesInTree;

char* toChars( std::string s ) {

  char *c = new char[s.size() + 1];
  c[s.size()] = '\0';
  memcpy( c, s.c_str(), s.size() );
}


std::vector<std::string> tokenize_string( std::string s, const char * delimiter  )
{
  char * ss = toChars( s );
  char * token;
  std::vector<std::string> to_return;

  token = strtok( ss, delimiter );
  while ( token )
  {
    to_return.push_back( std::string( token ) );
    token = strtok( NULL, delimiter );
  }

  return to_return;

}

bool compare_without_star( std::string s1, std::string s2 )
{
  std::string ss1;
  std::string ss2;
  if ( s1[0] == '*' )
    ss1 = s1.substr( 1, s1.size() );
  else 
    ss1 = s1;

  if ( s2[0] == '*' )
    ss2 = s2.substr( 1, s2.size() );
  else 
    ss2 = s2;

  return ss1.compare( ss2 ) == 0;

}

std::vector<std::string> intercept_cols( std::vector<std::string> vs1, std::vector<std::string> vs2 )
{
  std::vector<std::string> to_return;
  for( int i = 0; i < vs1.size(); i++ )
  {
    for( int j = 0; j < vs2.size(); j++ )
    {
      if ( compare_without_star( vs1[i], vs2[j] ))
      {
        to_return.push_back( vs1[i] );
      }
    }
  }
  return to_return;
}

int get_col_pos(std::vector<std::string> header, std::string col ){

  int i = 0;
  if( col[0] == '*' || col[0] == '&' )
    col = col.substr( 1, col.size() );

  for ( std::vector<std::string>::iterator itr = header.begin() ; itr != header.end(); itr++ )
  {

    if ( compare_without_star( *itr, col ) ){
      return i;
    }
    i++;
  }

  return -1;
  
}

std::string join_headers( std::string header1, std::string header2 )
{
  std::vector<std::string> vs1 = tokenize_string( header1, "\t" );
  std::vector<std::string> vs2 = tokenize_string( header2, "\t" );
  std::vector<std::string> intercept = intercept_cols( vs1, vs2 );
  std::string header;


  for ( int i = 0; i < vs1.size(); i++ )
  {
    int j = 0;
    for ( j = 0; j < intercept.size(); j++ )
    {
      if ( compare_without_star( vs1[i], intercept[j] ))
        break;
    }
    if ( j == intercept.size() )
    {
      if ( vs1[i][0] == '*' )
        header.append( vs1[i].substr( 1, vs1[i].size() ) );
      else
        header.append( vs1[i] );
      header.push_back( '\t' );
    } // current col_name is not in intercept,
  }

  for ( int i = 0; i < intercept.size(); i++)
  {
      if ( intercept[i][0] == '*' )
        header.append( intercept[i].substr( 1, vs1[i].size() ) );
      else
        header.append( intercept[i] );

      header.push_back( '\t' );
  }

  for ( int i = 0; i < vs2.size(); i++ )
  {
    int j = 0;
    for ( j = 0; j < intercept.size(); j++ )
    {
      if ( compare_without_star( vs2[i], intercept[j] ))
        break;
    }

    if ( j == intercept.size() )
    {
      if ( vs2[i][0] == '*' )
        header.append( vs2[i].substr( 1, vs2[i].size() ) );
      else
        header.append( vs2[i] );

      header.push_back( '\t' );
    } // j reach the end, current std::string is not in intercept
  }

  return header;

}


bool is_number(std::string s){
  //scan();
  std::string::const_iterator it = s.begin();
  while ( it != s.end() && isdigit( *it ) )
    it++;
  return !s.empty() && it == s.end();
}

int get_col_pos( std::string col, std::string header ){

  std::vector<std::string> vh = tokenize_string( header, "\t" );
  int i = 0;
  if( col[0] == '*' || col[0] == '&' )
    col = col.substr( 1, col.size() );

  for ( std::vector<std::string>::iterator itr = vh.begin() ; itr != vh.end(); itr++ )
  {
    //std::cout << *itr << " " << col << std::endl;
    if ( compare_without_star(*itr, col ) ){
      return i;
    }
    i++;
  }

  return -1;
  
}

int arithmetic( expression * ep, std::string header, std::string row )
{
  if ( !ep )
  {
    std::cout << "error in Table::arithmetic()" << std::endl;
    return 0;
  }

  std::vector<std::string> cols = tokenize_string( header, "\t" );

  expression* node[2];
  node[0] = ep->values[0].ep;
  node[1] = ep->values[1].ep;
  int v_lhs = 0;
  int v_rhs = 0;
  int ops[2];

  // tokenize row
  std::vector<std::string> row_v;
  char *s = toChars( row );
  char *token;

  token = strtok( s, "\t" );
  while ( token )
  {
    row_v.push_back( std::string( token ) );
    token = strtok ( NULL, "\t" );
  }
  if ( row_v.size() != cols.size() )
    return false;

  // see if nodes are number or std::string, 
  // if it is std::string, we need to find the actual value in database
  for ( int i = 0; i < 2; i++ )
  {

    if ( node[i]->func != OP_COLNAME && node[i]->func != OP_NUMBER )
      return arithmetic( node[i], header, row );
    else if ( node[i]->func == OP_NUMBER ) 
    {
      ops[i] = node[i]->values[0].num;
    }
    else if ( node[i]->func == OP_COLNAME )
    {
      int pos = get_col_pos( node[i]->values[0].data, header );
      if ( pos < 0 )
      {
        std::cout << "column does not exist!" << std::endl;
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
              std::cout << "OPERATOR NOT SUPPORTED! " << std::endl;
              return false;
              break;

  }
}

bool IN( std::string col, std::vector<std::string> vals, std::string header, std::string tuple )
{
  for( int i = 0; i < vals.size(); i++ )
  {
    std::string cur_entry = get_entry( header, tuple, col );
    //cout << header << " " << vals[i] << endl;
    if( cur_entry.compare( vals[i] ) == 0 )
      return true;
  }
  return false;
}

bool AND( expression * ep, std::string header, std::string tuple )
{
  bool lhs = false;
  bool rhs = false;
  if ( ep->values[0].ep->func == OP_AND )
    lhs = AND ( ep->values[0].ep, header, tuple );
  else if ( ep->values[0].ep->func == OP_OR )
    lhs = OR ( ep->values[0].ep, header, tuple );
  else
    lhs = comparison ( ep->values[0].ep, header, tuple );

  if ( ep->values[1].ep->func == OP_AND )
    rhs = AND ( ep->values[1].ep, header, tuple );
  else if ( ep->values[1].ep->func == OP_OR )
    rhs = OR ( ep->values[1].ep, header, tuple );
  else
    rhs = comparison ( ep->values[1].ep, header, tuple );

  return lhs && rhs;
}

bool OR( expression * ep, std::string header, std::string tuple )
{
  bool lhs = false;
  bool rhs = false;

  if ( ep->values[0].ep->func == OP_AND )
    lhs = AND ( ep->values[0].ep, header, tuple );
  else if ( ep->values[0].ep->func == OP_OR )
    lhs = OR ( ep->values[0].ep, header, tuple );
  else
    lhs = comparison ( ep->values[0].ep, header, tuple );

  if ( ep->values[1].ep->func == OP_AND )
    rhs = AND ( ep->values[1].ep, header, tuple );
  else if ( ep->values[1].ep->func == OP_OR )
    rhs = OR ( ep->values[1].ep, header, tuple );
  else
    rhs = comparison ( ep->values[1].ep, header, tuple );

  return lhs || rhs;
}


bool comparison( expression * ep, std::string header, std::string tuple )
{
  if ( !ep )
    return false;
  //if ( ep->func  )
  if( ep->values[0].ep->func == OP_STRING || 
        ep->values[1].ep->func == OP_STRING )
      {
        //cout << "here" << std::endl;
        return string_comparison( ep, header, tuple );
      }
      else
      {
        return num_comparison( ep, header, tuple );
          
      }
}

bool string_comparison( expression * ep, std::string header, std::string row  )
{
//cout << "here " << std::endl;
  if ( !ep )
    return false;


  std::vector<std::string> cols = tokenize_string( header, "\t" );

  //cout << "what?" << std::endl;
  expression* node[2];
  node[0] = ep->values[0].ep;
  node[1] = ep->values[1].ep;
  std::string ops[2];

  std::vector<std::string> row_v;
  char *s = toChars( row );
  char *token;

  token = strtok( s, "\t" );
  while ( token )
  {
    row_v.push_back( std::string( token ) );
    token = strtok ( NULL, "\t" );
  }
  if ( row_v.size() != cols.size() )
    return false;

  // see if nodes are number or std::string, 
  // if it is std::string, we need to find the actual value in database
  for ( int i = 0; i < 2; i++ )
  {
    if ( node[i]->func == OP_STRING )
    {
      ops[i] = std::string( node[i]->values[0].data );
      //cout << "!" << ops[i] << std::endl;
    }
    else if ( node[i]->func == OP_COLNAME )
    {
      //cout <<  node[i]->values[i].name << std::endl;
      int pos = get_col_pos( node[i]->values[i].name, header );
      if ( pos < 0 )
      {
        std::cout << "column does not exist!" << std::endl;
        return false;
      }

      ops[i] = std::string( row_v[pos] );

    }
  }

  switch( ep->func ){

    case OP_EQUAL:  return  (ops[0].compare( ops[1] ) == 0 ); break;
    case OP_NOTEQ:  return  (ops[0].compare( ops[1] ) != 0 ); break;
    case OP_LEQ:    return  (ops[0].compare( ops[1] ) <= 0 ); break;
    case OP_GEQ:    return  (ops[0].compare( ops[1] ) >= 0 ); break;
    case OP_LT:     return  (ops[0].compare( ops[1] ) < 0 ); break;
    case OP_GT:     return  (ops[0].compare( ops[1] ) > 0 ); break;
    default : 
              std::cout << "OPERATOR ON std::string NOT SUPPORTED! " << std::endl;
              return false;
              break;

  }
}

bool num_comparison( expression * ep, std::string header, std::string row )
{
  if ( !ep )
    return false;

  std::vector<std::string> cols = tokenize_string( header, "\t" );

  expression* node[2];
  node[0] = ep->values[0].ep;
  node[1] = ep->values[1].ep;
  int v_lhs = 0;
  int v_rhs = 0;
  int ops[2];

  // tokenize row
  std::vector<std::string> row_v;
  char *s = toChars( row );
  char *token;

  token = strtok( s, "\t" );
  while ( token )
  {
    row_v.push_back( std::string( token ) );
    token = strtok ( NULL, "\t" );
  }
  if ( row_v.size() != cols.size() )
    return false;

  // see if nodes are number or std::string, 
  // if it is std::string, we need to find the actual value in database
  for ( int i = 0; i < 2; i++ )
  {
    if ( node[i]->func != OP_COLNAME && node[i]->func != OP_NUMBER )
    {
      ops[i] = arithmetic( node[i], header, row );
    }

    else if ( node[i]->func == OP_NUMBER ) 
    {
      ops[i] = node[i]->values[0].num;
    }
    else if ( node[i]->func == OP_COLNAME )
    {
      int pos = get_col_pos( std::string( node[i]->values[0].name ), header );
      if ( pos < 0 )
      {
        std::cout << "column does not exist!" << std::endl;
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
              std::cout << "OPERATOR NOT SUPPORTED! " << std::endl;
              return false;
              break;

  }
}

std::ifstream::pos_type filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
}

std::string construct_tbl_path( std::string table_name )
{
  std::string path( "./data/" );
  path.append( table_name );
  path.append( ".tbl" );

  return path;
}

std::string construct_sta_path( std::string table_name )
{
  std::string path( "./data/" );
  path.append( table_name );
  path.append( ".sta" );

  return path;
}

std::string get_entry( std::string tuple, int pos )
{
  char * _tuple = toChars( tuple );

  // tokenize
  char * token = strtok ( _tuple, "\t" );
  for ( int i = 0; i < pos; i ++ )
    token = strtok( NULL, "\t" );

  return string( token );

}

std::string get_entry( std::string header, std::string tuple, std::string col )
{
  int pos = get_col_pos( col, header );
  std::string to_return;
  if ( pos == -1 )
  {
    return to_return;
  }

  char * _tuple = toChars( tuple );

  // tokenize
  char * token = strtok ( _tuple, "\t" );
  for ( int i = 0; i < pos; i ++ )
    token = strtok( NULL, "\t" );

  return string( token );

}

bool parsetreeDistinct(expression *ep){

  if(ep->func == OP_PROJECTION &&

     ep->values[1].ep->func == OP_DISTINCT){

    ep->values[1].ep = ep->values[1].ep->values[0].ep;

    return true;

  }

  if(ep->func == OP_PROJECTION &&

     ep->values[1].ep->func == OP_RLIST){

    return parsetreeDistinct(ep->values[1].ep);

  }

  if(ep->func == OP_RLIST &&

     ep->values[1].ep != nullptr &&

     ep->values[1].ep->func == OP_DISTINCT){

    ep->values[1].ep = ep->values[1].ep->values[0].ep;

    return true;

  }

  if(ep->func == OP_RLIST &&

     ep->values[1].ep != nullptr &&

     ep->values[1].ep->func == OP_RLIST){

    return parsetreeDistinct(ep->values[1].ep);

  }

  return false;

}


bool isDistinct(expr e){

  expression *ep = (expression *)e;

  return parsetreeDistinct( ep );

}


typedef std::unordered_map<std::string, std::vector<std::string>* > HashMap;


HashMap get_hash( MyItr * itr, std::vector<std::string> keys )
{
  HashMap hash_map;
  itr->open();
  std::string header = itr->first();

  // load everything to hashTable from this.tuples
    // construct Row for each tuple
  std::string cur_string = itr->get_next();
  while ( !itr->is_last() )
  {
    std::string key;

    for ( unsigned int i = 0; i < keys.size(); i++ )
      key.append( get_entry( header, cur_string,  keys[i] ) );

    HashMap::iterator map_itr = hash_map.find( key );
    if ( map_itr == hash_map.end() )
    {
      std::vector<std::string> * new_list = new std::vector<std::string>();
      new_list->push_back( header );
      new_list->push_back( cur_string );
      hash_map[key] = new_list;
    }
    else
    {
      map_itr->second->push_back( cur_string );
    }

    cur_string = itr->get_next();
  }

  return hash_map;
}
