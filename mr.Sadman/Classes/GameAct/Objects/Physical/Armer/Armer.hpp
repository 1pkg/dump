#ifndef __GAME_ACT_PHYSICAL_ARMER_HPP__
#define __GAME_ACT_PHYSICAL_ARMER_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

namespace Physical
{

class Armer
	: public Object
{
public:

	void initialize() override;

	std::string getResourcesName() const override;

	void setAdditionalParam( std::string additionalParam ) override;

	void runAction( const std::string & action ) override;

private:

	void setOffBody();
	void setOnBody();

	bool _stateLogical;
};

}

}

#endif
