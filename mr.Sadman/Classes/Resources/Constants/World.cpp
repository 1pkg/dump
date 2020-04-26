#include "World.hpp"

namespace Resources
{

std::string toString( World world )
{
	switch ( world )
	{
		case World::Tech:
			return "Tech";
		break;

		case World::Fairy:
			return "Fairy";
		break;

		case World::Inferno:
			return "Inferno";
		break;

		default:
			return "";
		break;
	}
}

World worldFromString( const std::string & str )
{
	if( str == "Tech" )
		return World::Tech;

	if( str == "Fairy" )
		return World::Fairy;

	if( str == "Inferno" )
		return World::Inferno;
}

}