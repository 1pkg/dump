#ifndef __RESOURCES_LAB_HPP__
#define __RESOURCES_LAB_HPP__

#include <string>

namespace Resources
{

enum class Lab
{
	Shared,
	Biological = 1,
	Chemical,
	Physical,
	HistoricalGeographical,
	Literary,
	United
};

std::string toString( Lab lab ); // return Worlds in string representation

Lab labFromString( const std::string & str );

}

#endif