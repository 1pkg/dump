#include "Policy.hpp"

namespace Resources
{

std::string toString( Policy policy )
{
	switch ( policy )
	{
		case Policy::Locked:
			return "Locked";
		break;

		case Policy::Opened:
			return "Opened";
		break;

		default:
			return "";
		break;
	}
}

Policy policyFromString( const std::string & str )
{
	if( str == "Opened" )
		return Policy::Opened;

	if( str == "Locked" )
		return Policy::Locked;

	throw std::exception();
}

}