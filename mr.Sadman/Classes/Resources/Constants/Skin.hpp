#ifndef __RESOURCES_SKIN_HPP__
#define __RESOURCES_SKIN_HPP__

#include <string>

namespace Resources
{

enum class Skin
{
	Sadman,
	Lolipop,
	Robo,
	Nazi
};

std::string toString( Skin skin ); // return Skins in string representation

Skin skinFromString( const std::string & str );

}

#endif
