#ifndef __RESOURCES_DIRECTION_HPP__
#define __RESOURCES_DIRECTION_HPP__

#include <string>

namespace Resources
{

enum class Direction
{
	Right,
	Left,
	Top,
	Bottom,
	D45,
	D135,
	D225,
	D315,
	Circle
};

float toDegree( Direction direction ); // return Direction in degree representation
std::string toString( Direction direction ); // return Direction in string representation

Direction directionFromString( const std::string & str );

}

#endif