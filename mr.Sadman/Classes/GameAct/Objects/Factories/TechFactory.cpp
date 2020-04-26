#include "TechFactory.hpp"
//#include "GameAct/Objects/Tech/Block.hpp"
//#include "GameAct/Objects/Tech/Barrel.hpp"
//#include "GameAct/Objects/Tech/Gear.hpp"
#include "GameAct/Objects/Tech/StaticSpike.hpp"
#include "GameAct/Objects/Tech/Spike.hpp"
//#include "GameAct/Objects/Tech/MachineGun.hpp"
//#include "GameAct/Objects/Tech/Bullets.hpp"
//#include "GameAct/Objects/Tech/FlameThrower.hpp"
//#include "GameAct/Objects/Tech/Flame.hpp"
#include "GameAct/Objects/Tech/Cannon.hpp"
//#include "GameAct/Objects/Tech/CannonOneOff.hpp"
#include "GameAct/Objects/Tech/Ball.hpp"
#include "GameAct/Objects/Tech/StaticSaw.hpp"
#include "GameAct/Objects/Tech/Saw.hpp"
#include "GameAct/Objects/Tech/Line.hpp"
//#include "GameAct/Objects/Tech/Electricity.hpp"
//#include "GameAct/Objects/Tech/Radiation.hpp"
//#include "GameAct/Objects/Tech/Gum.hpp"
#include "GameAct/Objects/Tech/Impeller.hpp"
#include "GameAct/Objects/Tech/Wind.hpp"
//#include "GameAct/Objects/Tech/WindDecorate.hpp"
//#include "GameAct/Objects/Tech/Dynamite.hpp"
//#include "GameAct/Objects/Tech/Explosion.hpp"
//#include "GameAct/Objects/Tech/Mine.hpp"

namespace GameAct
{

Object * 
TechFactory::createObject( const std::string & name ) const
{
	// Blocks 

	/*if( name == "Block" )
		return new Tech::Block( "" );

	if( name == "Block_Gear" )
		return new Tech::Block( "Gear" );

	if( name == "Block_Electricity" )
		return new Tech::Block( "Electricity" );

	if( name == "Block_Radiation" )
		return new Tech::Block( "Radiation" );

	if( name == "Block_Gum" )
		return new Tech::Block( "Gum" );

	if( name == "Block_WindTop" )
		return new Tech::Block( "WindDecorateTop" );

	if( name == "Block_WindBottom" )
		return new Tech::Block( "WindDecorateBottom" );

	if( name == "Block_WindLeft" )
		return new Tech::Block( "WindDecorateLeft" );

	if( name == "Block_WindRight" )
		return new Tech::Block( "WindDecorateRight" );

	// Barrels

	if( name == "Barrel" )
		return new Tech::Barrel( "" );

	if( name == "Barrel_Dynamite" )
		return new Tech::Barrel( "Dynamite" );

	// Shells
	*/
	if( name == "Ball" )
		return new Tech::Ball();
	/*
	if( name == "Mine" )
		return new Tech::Mine();*/

	// Saws

	if( name == "StaticSaw" )
		return new Tech::StaticSaw();

	if( name == "Saw" )
		return new Tech::Saw();

	// Impellers

	if( name == "Impeller" )
		return new Tech::Impeller();

	// Spikes

	if( name == "StaticSpike" )
		return new Tech::StaticSpike();

	if( name == "Spike" )
		return new Tech::Spike();

	// Machines

	/*if( name == "MachineGunRight" )
		return new Tech::MachineGun( Direction::Right );

	if( name == "MachineGunLeft" )
		return new Tech::MachineGun( Direction::Left );

	if( name == "FlameThrowerRight" )
		return new Tech::FlameThrower( Direction::Right );

	if( name == "FlameThrowerLeft" )
		return new Tech::FlameThrower( Direction::Left );*/

	if( name == "Cannon" )
		return new Tech::Cannon();

	/*if( name == "CannonRight_Mine" )
		return new Tech::Cannon( Direction::Right, "Mine" );

	if( name == "CannonLeft_Mine" )
		return new Tech::Cannon( Direction::Left, "Mine" );

	if( name == "CannonOneOffRight_Ball" )
		return new Tech::CannonOneOff( Direction::Right, "Ball" );

	if( name == "CannonOneOffLeft_Ball" )
		return new Tech::CannonOneOff( Direction::Left, "Ball" );

	// Streams

	/*if( name == "BulletsLeft" )
		return new Tech::Bullets( Direction::Left );

	if( name == "BulletsRight" )
		return new Tech::Bullets( Direction::Right );

	if( name == "FlameLeft" )
		return new Tech::Flame( Direction::Left );

	if( name == "FlameRight" )
		return new Tech::Flame( Direction::Right );*/

	if( name == "Wind" )
		return new Tech::Wind();

	/*if( name == "Explosion" )
		return new Tech::Explosion();

	// Decorators

	if( name == "Gear" )
		return new Tech::Gear();

	if( name == "WindDecorateTop" )
		return new Tech::WindDecorate( Direction::Top );

	if( name == "WindDecorateBottom" )
		return new Tech::WindDecorate( Direction::Bottom );

	if( name == "WindDecorateRight" )
		return new Tech::WindDecorate( Direction::Right );

	if( name == "WindDecorateLeft" )
		return new Tech::WindDecorate( Direction::Left );

	if( name == "Electricity" )
		return new Tech::Electricity();

	if( name == "Radiation" )
		return new Tech::Radiation();

	if( name == "Gum" )
		return new Tech::Gum();*/

	if( name == "Line" )
		return new Tech::Line();

/*	if( name == "Dynamite" )
		return new Tech::Dynamite();*/

	return ObjectsFactory::createObject( name );

}

}
