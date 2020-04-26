#ifndef __TECH_CANNON_ONE_OFF_HPP__
#define __TECH_CANNON_ONE_OFF_HPP__

#include "Game/Objects/DynamicObject.hpp"
#include "Game/Objects/Providers/Direction.hpp"

namespace Objects
{

namespace Tech
{

class CannonOneOff : public DynamicObject
{
public:
/* Handle event overriding*/

	void handleEvent( Events::CannonEvent * ev ) override;

public:
/* Interactors overriding*/

public:
/* Object parts overriding*/

	CannonOneOff( Direction direction, const std::string & shell );

	void initialize() override;

	std::string getName() const override;

	void setRotation( float angle ) override;

	void runAction( const std::string & action ) override;

private:

	void onFire();

	static DynamicObject * createShell( const std::string & shell );

private:

	Direction _direction;
	std::string _shell;
	bool _used;
};

}

}

#endif
