#ifndef __RESOURCES_POLICY_HPP__
#define __RESOURCES_POLICY_HPP__

#include <string>
#include <stdio.h>

namespace Resources
{

enum class Policy
{
	Locked,
	Opened,
};

std::string toString( Policy policy );

Policy policyFromString( const std::string & str );

}

#endif