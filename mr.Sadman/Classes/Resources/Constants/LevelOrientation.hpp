#ifndef __RESOURCES_LEVEL_ORIENTATION_HPP__
#define __RESOURCES_LEVEL_ORIENTATION_HPP__

#include <string>
#include <stdio.h>

namespace Resources
{

enum class LevelOrientation
{
	Vertical,
	Horizontal
};

std::string toString( LevelOrientation orientation );

LevelOrientation levelOrientationFromString( const std::string & str );

}

#endif