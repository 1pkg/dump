#ifndef __TECH_MACHINE_GUN_HPP__
#define __TECH_MACHINE_GUN_HPP__

#include "Game/Objects/StaticObject.hpp"
#include "Game/Objects//Providers/Direction.hpp"

namespace Objects
{

namespace Tech
{

class MachineGun: public StaticObject
{
public:
/* Handle event overriding*/

public:
/* Interactors overriding*/

public:
/* Object parts overriding*/

	MachineGun( Direction direction );

	void initialize() override;

	std::string getName() const override;

	void setPosition( cocos2d::Vec2 position ) override;
	void setSize( cocos2d::Size size ) override;
	void setRotation( float angle ) override;
	
	void hide() override;
	void show() override;

	void attachToChunk( Levels::Chunk & chunk, int zIndex ) override;
	void runAction( const std::string & action ) override;

private:

	static StaticObject * createBullets( Direction direction );

	Direction _direction;
	StaticObject * _bullets;
};

}

}

#endif
