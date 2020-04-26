#ifndef __TECH_BLOCK_HPP__
#define __TECH_BLOCK_HPP__

#include "Game/Objects/StaticObject.hpp"

namespace Objects
{

class DecorateObject;

namespace Tech
{

class Block : public StaticObject
{
public:
/* Handle event overriding*/

public:
/* Interactors overriding*/

	void interact( Ball * ball ) override;

public:
/* Object parts overriding*/

	Block( const std::string & decorator );

	void initialize() override;

	std::string getName() const override;

	void setPosition( cocos2d::Vec2 position ) override;
	void setSize( cocos2d::Size size ) override;

	void hide() override;
	void show() override;

	void attachToChunk( Levels::Chunk & chunk, int zIndex ) override;
	void runInteraction( Object * object ) override;

private:

	static DecorateObject * createDecorator( const std::string & decorator );

	DecorateObject * _decorator;
};

}

}

#endif
