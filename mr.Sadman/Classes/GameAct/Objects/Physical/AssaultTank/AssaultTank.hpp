#ifndef __GAME_ACT_PHYSICAL_ASSAULT_TANK_HPP__
#define __GAME_ACT_PHYSICAL_ASSAULT_TANK_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

namespace Physical
{

class AssaultTank
	: public Object
{
public:

	void initialize() override;

	std::string getResourcesName() const override;

	void setAdditionalParam( std::string additionalParam ) override;
	void setRotation( float angle ) override;

	void attachToChunk( Chunk & chunk, int zIndex ) override;

	void runAction( const std::string & action ) override;

private:

	float _angle;
	
	int _zindex;

	float _time;

	unsigned int _current;
	std::vector<std::string> _shells;
};

}

}

#endif
