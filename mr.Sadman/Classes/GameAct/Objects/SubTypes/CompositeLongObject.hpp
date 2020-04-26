#ifndef __GAME_ACT_COMPOSITE_LONG_OBJECT_HPP__
#define __GAME_ACT_COMPOSITE_LONG_OBJECT_HPP__

#include "LongObject.hpp"

namespace GameAct
{

class CompositeLongObject
	: public LongObject
{
public:

	void initialize() override;

	cocos2d::Size getSize() const override;
	cocos2d::Size getContentSize() const override;
	cocos2d::Vec2 getPosition() const override;

	cocos2d::PhysicsBody * getBody() const override;
	ThirdParty::Audio * getAudio() const override;

	bool isComposed() const override;

	void setPosition( cocos2d::Vec2 position ) override;
	void setSize( cocos2d::Size size ) override;
	void setAdditionalParam( std::string additionalParam ) override;
	void setRotation( float angle ) override;
	void setScale( cocos2d::Vec2 scale ) override; 
	void setMask( int mask ) override;
	void setColideMask( int colideMask ) override;
	void setContactMask( int contactMask ) override;

	void hide() override;
	void show() override;

	std::vector< LongObject * > getObjects();

	void attachToLevel( Level & level, int zIndex ) override;

protected:

	LongObject * getHip() const;

	std::vector< LongObject * > _objects;
};

}

#endif
