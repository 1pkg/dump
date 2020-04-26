#ifndef __GAME_ACT_PHYSICAL_REACTOR_HPP__
#define __GAME_ACT_PHYSICAL_REACTOR_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

class Stream;

namespace Physical
{

class Reactor
	: public Object
{
public:

	Reactor();

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

	int _zindex;

	float _angle;

	float _radiationLenth;

	Stream * _radiation;
};

}

}

#endif
