#include "StringFunctions.hpp"

#include <stdio.h>
#include <stdlib.h>

namespace ThirdParty
{

std::string toString( int i )
{
	char buf[128] = { 0 };
	::sprintf( buf, "%d", i );
	return buf;
}

std::string toString( unsigned int ui )
{
	char buf[128] = { 0 };
	::sprintf( buf, "%d", ui );
	return buf;
}

std::string toString( float f )
{
	char buf[128] = { 0 };
	::sprintf( buf, "%e", f );
	return buf;
}

std::string toString( double d )
{
	char buf[128] = { 0 };
	::sprintf( buf, "%e", d );
	return buf;
}

std::string readToken( std::string & str, char separator )
{
	std::string result;

	int sep = str.find( separator );

	if( sep == str.npos )
	{
		result = str;
		str.clear();
	}
	else
	{
		result = str.substr( 0, sep );
		str.erase( 0, sep + 1 );
	}

	return result;
}

}