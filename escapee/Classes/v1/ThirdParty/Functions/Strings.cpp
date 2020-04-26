#include "Strings.hpp"

#include <stdio.h>
#include <stdlib.h>

namespace ThirdParty
{

namespace Functions
{

namespace Strings
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

}

}

}