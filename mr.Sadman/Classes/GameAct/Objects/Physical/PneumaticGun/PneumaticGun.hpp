#ifndef __GAME_ACT_PHYSICAL_PNEUMATIC_GUN_HPP__
#define __GAME_ACT_PHYSICAL_PNEUMATIC_GUN_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

class Stream;

namespace Physical
{

class PneumaticGun
	: public Object
{
public:

	PneumaticGun();

	void initialize() override;

	std::string getResourcesName() const override;

	void setPosition( cocos2d::Vec2 position ) override;
	void setSize( cocos2d::Size size ) override;
	void setAdditionalParam( std::string additionalParam ) override;
	void setRotation( float angle ) override;

	void hide() override;
	void show() override;

	void attachToChunk( Chunk & chunk, int zIndex ) override;

	void runAction( const std::string & action ) override;

private:

	float _angle;
	
	int _zindex;

	Stream * _wind;

	float _time;
	std::vector<std::string> _shells;
};

}

}

#endif
