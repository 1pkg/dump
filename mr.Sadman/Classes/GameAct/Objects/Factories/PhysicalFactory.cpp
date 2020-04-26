#include "PhysicalFactory.hpp"

#include "GameAct/Objects/Physical/Blocks/Rectangle/RectangleStaticBlock.hpp"
#include "GameAct/Objects/Physical/Blocks/Rectangle/RectangleMovedBlock.hpp"
#include "GameAct/Objects/Physical/Blocks/Rectangle/RectangleRotatedBlock.hpp"
#include "GameAct/Objects/Physical/Blocks/Rectangle/RectangleDynamicBlock.hpp"
#include "GameAct/Objects/Physical/Blocks/Triangle/TriangleStaticBlock.hpp"
#include "GameAct/Objects/Physical/Blocks/Triangle/TriangleRotatedBlock.hpp"
#include "GameAct/Objects/Physical/Blocks/Triangle/TriangleDynamicBlock.hpp"
#include "GameAct/Objects/Physical/Blocks/Circle/CircleStaticBlock.hpp"
#include "GameAct/Objects/Physical/Blocks/Circle/CircleRotatedBlock.hpp"
#include "GameAct/Objects/Physical/Blocks/Circle/CircleDynamicBlock.hpp"

#include "GameAct/Objects/Physical/Armer/Armer.hpp"
#include "GameAct/Objects/Physical/Button/Button.hpp"
#include "GameAct/Objects/Physical/PushPlate/PushPlate.hpp"

#include "GameAct/Objects/Physical/Spring/Spring.hpp"
#include "GameAct/Objects/Physical/Saw/StaticSaw.hpp"
#include "GameAct/Objects/Physical/Saw/MovedSaw.hpp"
#include "GameAct/Objects/Physical/Saw/RotatedSaw.hpp"
#include "GameAct/Objects/Physical/Saw/DynamicSaw.hpp"
#include "GameAct/Objects/Physical/Pendulum/PendulumAlebarda.hpp"
#include "GameAct/Objects/Physical/Pendulum/PendulumSpikedBall.hpp"
#include "GameAct/Objects/Physical/Luke/Luke.hpp"
#include "GameAct/Objects/Physical/Ram/Ram.hpp"
#include "GameAct/Objects/Physical/Ram/RamPiston.hpp"
#include "GameAct/Objects/Physical/Press/Press.hpp"
#include "GameAct/Objects/Physical/Trampoline/Trampoline.hpp"

#include "GameAct/Objects/Physical/PneumaticGun/PneumaticGun.hpp"
#include "GameAct/Objects/Physical/AssaultTank/AssaultTank.hpp"

#include "GameAct/Objects/Physical/Impeller/Impeller.hpp"
#include "GameAct/Objects/Physical/AirGun/AirGun.hpp"
#include "GameAct/Objects/Physical/Pump/Pump.hpp"

#include "GameAct/Objects/Physical/Generator/Generator.hpp"
#include "GameAct/Objects/Physical/TeslaPillars/TeslaPillars.hpp"
#include "GameAct/Objects/Physical/Magnite/Magnite.hpp"
#include "GameAct/Objects/Physical/Reactor/Reactor.hpp"

#include "GameAct/Objects/Physical/Shared/Grenade/Grenade.hpp"
#include "GameAct/Objects/Physical/Shared/GlueBomb/GlueBomb.hpp"

#include "GameAct/Objects/Physical/Shared/Alebarda/Alebarda.hpp"
#include "GameAct/Objects/Physical/Shared/SpikedBall/SpikedBall.hpp"

#include "GameAct/Objects/Physical/Shared/Pivot/Pivot.hpp"


namespace GameAct
{

using namespace Physical;

Object * 
PhysicalFactory::createObject( const std::string & name ) const
{

	// Blocks

	if( name == "RectangleStaticBlock" )
		return new RectangleStaticBlock();

	if( name == "RectangleMovedBlock" )
		return new RectangleMovedBlock();

	if( name == "RectangleRotatedBlock" )
		return new RectangleRotatedBlock();

	if( name == "RectangleDynamicBlock" )
		return new RectangleDynamicBlock();

	if( name == "TriangleStaticBlock" )
		return new TriangleStaticBlock();

	if( name == "TriangleRotatedBlock" )
		return new TriangleRotatedBlock();

	if( name == "TriangleDynamicBlock" )
		return new TriangleDynamicBlock();

	if( name == "CircleStaticBlock" )
		return new CircleStaticBlock();

	if( name == "CircleRotatedBlock" )
		return new CircleRotatedBlock();

	if( name == "CircleDynamicBlock" )
		return new CircleDynamicBlock();

	// Switchers

	if( name == "Armer" )
		return new Armer();

	if( name == "Button" )
		return new Button();

	if( name == "PushPlate" )
		return new PushPlate();

	// Mechanics

	if( name == "Spring" )
		return new Spring();

	if( name == "StaticSaw" )
		return new StaticSaw();

	if( name == "MovedSaw" )
		return new MovedSaw();

	if( name == "RotatedSaw" )
		return new RotatedSaw();

	if( name == "DynamicSaw" )
		return new DynamicSaw();

	if( name == "PendulumAlebarda" )
		return new PendulumAlebarda();

	if( name == "PendulumSpikedBall" )
		return new PendulumSpikedBall();

	if( name == "Luke" )
		return new Luke();

	if( name == "Ram" )
		return new Ram();

	if( name == "RamPiston" )
		return new RamPiston();

	if( name == "Press" )
		return new Press();

	if( name == "Trampoline" )
		return new Trampoline();

	// Guns

	if( name == "PneumaticGun" )
		return new PneumaticGun();

	if( name == "AssaultTank" )
		return new AssaultTank();

	// Wind

	if( name == "Impeller" )
		return new Impeller();

	if( name == "AirGun" )
		return new AirGun();

	if( name == "Pump" )
		return new Pump();

	// Electro - Magite - Nuclear

	if( name == "Generator" )
		return new Generator();

	if( name == "TeslaPillars" )
		return new TeslaPillars();

	if( name == "Magnite" )
		return new Magnite();

	if( name == "Reactor" )
		return new Reactor();

	// Shared

	if( name == "Alebarda" )
		return new Alebarda();

	if( name == "SpikedBall" )
		return new SpikedBall();

	if( name == "Grenade" )
		return new Grenade();

	if( name == "GlueBomb" )
		return new GlueBomb();

	if( name == "Pivot" )
		return new Pivot();

	return ObjectsFactory::createObject( name );
}

}
