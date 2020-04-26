#ifndef __RESOURCES_WORLD_HPP__
#define __RESOURCES_WORLD_HPP__

#include <string>

namespace Resources
{

enum class World
{
	Tech,
	Fairy,
	Inferno, // ???
	// ???
};

std::string toString( World world ); // return Worlds in string representation

World worldFromString( const std::string & str );

}

#endif