#include "Direction.hpp"

namespace Resources
{

float toDegree( Direction direction )
{
	switch ( direction )
	{
		case Direction::Left:
			return 180.0f;
		break;

		case Direction::Right:
			return 0.0f;
		break;

		case Direction::Top:
			return -90.0f;
		break;

		case Direction::Bottom:
			return 90.0f;
		break;

		case Direction::D45:
			return -135.0f;
		break;

		case Direction::D135:
			return -45.0f;
		break;

		case Direction::D225:
			return 45.0f;
		break;

		case Direction::D315:
			return 135.0f;
		break;

		case Direction::Circle:
			return 360.0f;
		break;

		default:
			return 0.0f;
		break;
	}
}

std::string toString( Direction direction )
{
	switch ( direction )
	{
		case Direction::Left:
			return "Left";
		break;

		case Direction::Right:
			return "Right";
		break;

		case Direction::Top:
			return "Top";
		break;

		case Direction::Bottom:
			return "Bottom";
		break;

		case Direction::D45:
			return "45";
		break;

		case Direction::D135:
			return "135";
		break;

		case Direction::D225:
			return "225";
		break;

		case Direction::D315:
			return "315";
		break;

		case Direction::Circle:
			return "Circle";
		break;

		default:
			return "";
		break;
	}
}

Direction directionFromString( const std::string & str )
{
	if( str == "Left" )
		return Direction::Left;

	if( str == "Right" )
		return Direction::Right;

	if( str == "Top" )
		return Direction::Top;

	if( str == "Bottom" )
		return Direction::Bottom;

	if( str == "45" )
		return Direction::D45;

	if( str == "135" )
		return Direction::D135;

	if( str == "225" )
		return Direction::D225;

	if( str == "315" )
		return Direction::D315;

	if( str == "Circle" )
		return Direction::Circle;
}

}