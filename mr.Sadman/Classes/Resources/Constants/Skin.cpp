#include "Skin.hpp"

namespace Resources
{

std::string toString( Skin skin )
{
	switch ( skin )
	{
		case Skin::Sadman:
			return "Sadman";
		break;

		case Skin::Lolipop:
			return "Lolipop";
		break;

		case Skin::Nazi:
			return "Nazi";
		break;

		case Skin::Robo:
			return "Robo";
		break;

		default:
			return "";
		break;
	}
}

Skin skinFromString( const std::string & str )
{
	if( str == "Lolipop" )
		return Skin::Lolipop;

	if( str == "Nazi" )
		return Skin::Nazi;

	if( str == "Robo" )
		return Skin::Robo;

	if( str == "Sadman" )
		return Skin::Sadman;
}

}
