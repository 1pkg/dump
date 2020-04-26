#ifndef __GAME_ACT_PHYSICAL_MACHINE_GUN_HPP__
#define __GAME_ACT_PHYSICAL_MACHINE_GUN_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

class Stream;

namespace Physical
{

class MachineGun
	: public Object
{
public:

	MachineGun();

	std::string getName() const override;

	void setPosition( cocos2d::Vec2 position ) override;
	void setSize( cocos2d::Size size ) override;
	void setAdditionalParam( std::string additionalParam ) override;
	void setRotation( float angle ) override;
	void setScale( cocos2d::Vec2 scale ) override;
	
	void hide() override;

	void attachToChunk( Chunk & chunk, int zIndex ) override;
	void runAction( const std::string & action ) override;

private:

	float _angle;

	float _lenth;

	Stream * _bullets;
};

}

}

#endif
