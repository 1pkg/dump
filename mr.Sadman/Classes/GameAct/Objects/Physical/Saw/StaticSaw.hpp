#ifndef __GAME_ACT_PHYSICAL_STATIC_SAW_HPP__
#define __GAME_ACT_PHYSICAL_STATIC_SAW_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

namespace Physical
{

class StaticSaw
	: public Object
{
public:

	void initialize() override;

	std::string getResourcesName() const override;
	
	void setAdditionalParam( std::string additionalParam ) override;

	void runAction( const std::string & action ) override;

private:

	float _time;
};

}

}

#endif
