#include "Lab.hpp"

namespace Resources
{

std::string toString( Lab world )
{
	switch ( world )
	{
		case Lab::Shared:
			return "Shared";
		break;

		case Lab::Biological:
			return "Biological";
		break;

		case Lab::Chemical:
			return "Chemical";
		break;

		case Lab::Physical:
			return "Physical";
		break;

		case Lab::HistoricalGeographical:
			return "HistoricalGeographical";
		break;

		case Lab::Literary:
			return "Literary";
		break;

		case Lab::United:
			return "Literary";
		break;

		default:
			return "";
		break;
	}
}

Lab labFromString( const std::string & str )
{
	if( str == "Shared" )
		return  Lab::Shared;

	if( str == "Biological" )
		return  Lab::Biological;

	if( str == "Chemical" )
		return Lab::Chemical;

	if( str == "Physical" )
		return  Lab::Physical;

	if( str == "HistoricalGeographical" )
		return Lab::HistoricalGeographical;

	if( str == "Literary" )
		return Lab::Literary;

	if( str == "United" )
		return  Lab::United;

	throw std::exception();
}

}