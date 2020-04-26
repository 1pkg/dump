#ifndef __GAME_ACT_PHYSICAL_TRIANGLE_STATIC_BLOCK_HPP__
#define __GAME_ACT_PHYSICAL_TRIANGLE_STATIC_BLOCK_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

namespace Physical
{

class TriangleStaticBlock
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
