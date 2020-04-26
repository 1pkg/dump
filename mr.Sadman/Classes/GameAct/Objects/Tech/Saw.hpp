#ifndef __TECH_SAW_HPP__
#define __TECH_SAW_HPP__

#include "GameAct/Objects/Object.hpp"
 
/* FINISHED */

namespace GameAct
{

namespace Tech
{

class Saw
	: public Object
{
public:

	Saw();

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

	cocos2d::Vec2 rotatePoint( cocos2d::Vec2 point, cocos2d::Vec2 center, float angle ) const;

	float _lenth;
	float _time;
	Object * _decorator;
};

}

}

#endif
