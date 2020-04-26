#ifndef __GAME_ACT_COMPOSITE_OBJECT_HPP__
#define __GAME_ACT_COMPOSITE_OBJECT_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{

class CompositeObject
	: public Object
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

	std::vector< Object * > getObjects();

	void attachToChunk( Chunk & chunk, int zIndex ) override;

protected:

	Object * getHip() const;

	std::vector< Object * > _objects;
};

}

#endif
