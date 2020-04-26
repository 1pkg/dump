#ifndef __GAME_ACT_PHYSICAL_MOVED_SAW_HPP__
#define __GAME_ACT_PHYSICAL_MOVED_SAW_HPP__

#include "StaticSaw.hpp"

namespace GameAct
{

namespace Physical
{

class MovedSaw
	: public StaticSaw
{
public:

	MovedSaw();
	
	void setPosition( cocos2d::Vec2 position ) override;
	void setSize( cocos2d::Size size ) override;
	void setAdditionalParam( std::string additionalParam ) override;
	void setRotation( float angle ) override;

	void hide() override;
	void show() override;

	void attachToChunk( Chunk & chunk, int zIndex ) override;
	void runAction( const std::string & action ) override;

private:

	cocos2d::Vec2 _postion;

	float _angle;

	float _lenth;
	float _time;

	Object * _pivot;
};

}

}

#endif
