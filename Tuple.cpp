#include <cstring>
#include <iostream>
#include "Tuple.h"

using namespace std;


Tuple::Tuple( const char * _value, std::streampos _offset )
{
	datatype = STRING;
	value.str = new char[strlen( _value ) + 1];
	strcpy ( value.str, _value );
	offset.push_back( _offset );
}

Tuple::Tuple( const int _value, std::streampos _offset )
{
	datatype = NUM;
	value.num = _value;
	offset.push_back( _offset );
}

Tuple::Tuple( const char* _value, std::vector<std::streampos>  _offset )
{
	datatype = STRING;
	value.str = new char[strlen( _value ) + 1];
	strcpy ( value.str, _value );
	offset = _offset;

}

Tuple::Tuple( const int _value, std::vector<std::streampos>  _offset )
{
	datatype = NUM;
	value.num = _value;
	offset = _offset;
}

void Tuple::insert( std::streampos _offset )
{
	offset.push_back( _offset );
}

bool Tuple::operator == ( const Tuple rhs )const {
	if ( datatype == rhs.datatype )
	{
		if ( datatype == NUM )
		{
			//cout << value.num << " "  << rhs.value.num << endl;
			return value.num == rhs.value.num;
		}
		else 
			return strcmp(value.str,  rhs.value.str ) == 0;
	}
	else
	{
		cout << "INCOMPATIBLE TYPE IN Tuple::operator == () " << endl;
		return false; 
	}
}

bool Tuple::operator <= ( const Tuple rhs )const {
	if ( datatype == rhs.datatype )
	{
		if ( datatype == NUM )
			return value.num <= rhs.value.num;
		else 
			return strcmp(value.str,  rhs.value.str ) <= 0;
	}
	else
	{
		cout << "INCOMPATIBLE TYPE IN Tuple::operator <= () " << endl;
		return false; 
	}
}

bool Tuple::operator >= ( const Tuple rhs )const {
	if ( datatype == rhs.datatype )
	{
		if ( datatype == NUM )
			return value.num >= rhs.value.num;
		else 
			return strcmp(value.str,  rhs.value.str ) >= 0;
	}
	else
	{
		cout << "INCOMPATIBLE TYPE IN Tuple::operator <= () " << endl;
		return false; 
	}
}

bool Tuple::operator > ( const Tuple rhs )const {
	if ( datatype == rhs.datatype )
	{
		if ( datatype == NUM )
			return value.num > rhs.value.num;
		else 
			return strcmp(value.str,  rhs.value.str ) > 0;
	}
	else
	{
		cout << "INCOMPATIBLE TYPE IN Tuple::operator > () " << endl;
		return false; 
	}
}

bool Tuple::operator < ( const Tuple rhs )const {
	if ( datatype == rhs.datatype )
	{
		if ( datatype == NUM )
			return value.num < rhs.value.num;
		else 
			return strcmp(value.str,  rhs.value.str ) < 0;
	}
	else
	{
		cout << "INCOMPATIBLE TYPE IN Tuple::operator > () " << endl;
		return false; 
	}
}
