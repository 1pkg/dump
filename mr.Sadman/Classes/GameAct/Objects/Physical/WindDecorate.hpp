#ifndef __TECH_WIND_DECORATE_HPP__
#define __TECH_WIND_DECORATE_HPP__

#include "Game/Objects/DecorateObject.hpp"
#include "Game/Objects/Providers/Direction.hpp"

namespace Objects
{

class StaticObject;

namespace Tech
{

class WindDecorate : public DecorateObject
{
public:
/* Handle event overriding*/

public:
/* Interactors overriding*/

public:
/* Object parts overriding*/

	WindDecorate( Direction direction );

	void initialize() override;

	std::string getName() const override;

	void setPosition( cocos2d::Vec2 position ) override;
	void setSize( cocos2d::Size size ) override;

	void hide() override;
	void show() override;

	void attachToChunk( Levels::Chunk & chunk, int zIndex ) override;
	void runAction( const std::string & action ) override;

private:

	static StaticObject * createWind( Direction direction );

	Direction _direction;
	StaticObject * _wind;
};

}

}

#endif
