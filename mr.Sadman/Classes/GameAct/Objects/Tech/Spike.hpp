#ifndef __TECH_SPIKE_HPP__
#define __TECH_SPIKE_HPP__

#include "GameAct/Objects/Object.hpp"

/* FINISHED */

namespace GameAct
{

namespace Tech
{

class Spike
	: public Object
{
public:
	
	Spike();

	std::string getName() const override;

	void setPosition( cocos2d::Vec2 position ) override;
	void setSize( cocos2d::Size size ) override;
	void setAdditionalParam( std::string additionalParam ) override;
	void setDirection( Direction direction ) override;

	void hide() override;
	void show() override;

	void attachToChunk( Chunk & chunk, int zIndex ) override;
	void runAction( const std::string & action ) override;

private:

	float _lenth;
	float _time;
	Object * _decorator;
};

}

}

#endif
