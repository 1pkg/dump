#ifndef __THIRD_PARTY_STRING_FUNCTIONS_HPP__
#define __THIRD_PARTY_STRING_FUNCTIONS_HPP__

#include <string>

namespace ThirdParty
{

std::string toString( int i );
std::string toString( unsigned int ui );
std::string toString( float f );
std::string toString( double d );

std::string readToken( std::string & str, char separator = ';' );

}

#endif