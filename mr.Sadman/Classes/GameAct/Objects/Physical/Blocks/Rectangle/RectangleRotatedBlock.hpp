#ifndef __GAME_ACT_PHYSICAL_RECTANGLE_ROTATED_BLOCK_HPP__
#define __GAME_ACT_PHYSICAL_RECTANGLE_ROTATED_BLOCK_HPP__

#include "RectangleStaticBlock.hpp"

namespace GameAct
{

namespace Physical
{

class RectangleRotatedBlock
	: public RectangleStaticBlock
{
public:

	void setPosition( cocos2d::Vec2 position ) override;
	void setAdditionalParam( std::string additionalParam ) override;
	void setRotation( float angle ) override;

	void runAction( const std::string & action ) override;

private:

	cocos2d::Vec2 rotatePoint( cocos2d::Vec2 point, cocos2d::Vec2 center, float angle ) const;

	cocos2d::Vec2 _position;

	float _angle;

	float _lenth;
	float _time;
};

}

}

#endif
