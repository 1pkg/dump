#ifndef __GAME_ACT_PHYSICAL_PENDULUM_HPP__
#define __GAME_ACT_PHYSICAL_PENDULUM_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

namespace Physical
{

class Pendulum
	: public Object
{
public:

	Pendulum();
	
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

	cocos2d::Vec2 rotatePoint( cocos2d::Vec2 point, cocos2d::Vec2 center, float angle ) const;

	cocos2d::Vec2 _position;

	float _angle;

	float _lenth;
	float _time;

	Object * _pivot;
};

}

}

#endif
