#ifndef __GAME_ACT_PHYSICAL_LUKE_HPP__
#define __GAME_ACT_PHYSICAL_LUKE_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

namespace Physical
{

class Luke
	: public Object
{
public:

	void initialize() override;

	std::string getResourcesName() const override;

	void runAction( const std::string & action ) override;

private:

	void setOpenBody();
	void setLockBody();
};

}

}

#endif
