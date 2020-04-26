#ifndef __GAME_ACT_PHYSICAL_TESLA_PILLARS_HPP__
#define __GAME_ACT_PHYSICAL_TESLA_PILLARS_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

namespace Physical
{

class TeslaPillars
	: public Object
{
public:

	void initialize() override;

	std::string getResourcesName() const override;
	
	void setAdditionalParam( std::string additionalParam ) override;

	void runAction( const std::string & action ) override;

private:

	void setBlickBody();
	void setDefBody();

	float _time;
};

}

}

#endif
