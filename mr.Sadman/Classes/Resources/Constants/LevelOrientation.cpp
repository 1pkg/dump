#include "LevelOrientation.hpp"

namespace Resources
{

std::string toString( LevelOrientation orientation )
{
	switch ( orientation )
	{
		case LevelOrientation::Vertical:
			return "Vertical";
		break;

		case LevelOrientation::Horizontal:
			return "Horizontal";
		break;

		default:
			return "";
		break;
	}
}

LevelOrientation levelOrientationFromString( const std::string & str )
{
	if( str == "Vertical" )
		return LevelOrientation::Vertical;

	if( str == "Horizontal" )
		return LevelOrientation::Horizontal;

	throw std::exception();
}

}