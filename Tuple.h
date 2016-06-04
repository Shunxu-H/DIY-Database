#include <vector>
#include <fstream>

#ifndef TUPLE_H
  #define TUPLE_H


enum Datatype { NUM, STRING };

struct Tuple
{
	Datatype datatype;
	union value
	{
		int num;
		char* str;
	}value;

	std::vector<std::streampos> offset;
	// bool isDirty;

	Tuple(){};
	Tuple( const char* _value, std::streampos _offset );
	Tuple( const int _value, std::streampos _offset );
	Tuple( const char* _value, std::vector<std::streampos>  _offset );
	Tuple( const int _value, std::vector<std::streampos>  _offset );

	void insert( std::streampos _offset );

	bool operator == ( const Tuple rhs )const;
	bool operator <= ( const Tuple rhs )const;
	bool operator >= ( const Tuple rhs )const;
	bool operator > ( const Tuple rhs )const;
	bool operator < ( const Tuple rhs )const;
};

  #endif