#ifndef __TECH_GUM_HPP__
#define __TECH_GUM_HPP__

#include "Game/Objects/DecorateObject.hpp"

namespace Objects
{

namespace Tech
{

class Gum : public DecorateObject
{
public:
/* Handle event overriding*/

public:
/* Interactors overriding*/

public:
/* Object parts overriding*/

	void initialize() override;

	std::string getName() const override;
};

}

}

#endif
