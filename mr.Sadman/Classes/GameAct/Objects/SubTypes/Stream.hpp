#ifndef __GAME_ACT_STREAM_HPP__
#define __GAME_ACT_STREAM_HPP__

#include "Area.hpp"

namespace GameAct
{

class Stream
	: public Area
{
public:

	~Stream();

	void initialize() override;

	void setPosition( cocos2d::Vec2 position ) override;
	void setRotation( float angle ) override;

	void hide() override;
	void show() override;
	virtual void showFor( float duration );

	void attachToChunk( Chunk & chunk, int zIndex ) override;

protected:

	float _angle;

	cocos2d::ParticleSystemQuad * _particle;
};

}

#endif
