#include "ObjectsFactory.hpp"
#include "GameAct/Objects/Object.hpp"

#include "BiologicalFactory.hpp"
#include "ChemicalFactory.hpp"
#include "PhysicalFactory.hpp"
#include "HistoricalGeographicalFactory.hpp"
#include "LiteraryFactory.hpp"

#include "GameAct/Objects/Shared/Edge/Edge.hpp"

#include "GameAct/Objects/Shared/Electricity/Electricity.hpp"
#include "GameAct/Objects/Shared/Explosion/Explosion.hpp"
#include "GameAct/Objects/Shared/Fire/Fire.hpp"
#include "GameAct/Objects/Shared/Magnetism/Magnetism.hpp"
#include "GameAct/Objects/Shared/Radiation/Radiation.hpp"
#include "GameAct/Objects/Shared/Wind/Wind.hpp"

#include "GameAct/Objects/Character/Character.hpp"

namespace GameAct
{

Object *
ObjectsFactory::createObject(const std::string & name ) const
{
	// Others

	if( name == "Edge" )
		return new Shared::Edge();

	// Streams

	if( name == "Electricity" )
		return new Shared::Electricity();

	if( name == "Explosion" )
		return new Shared::Explosion();

	if( name == "Explosion" )
		return new Shared::Explosion();

	if( name == "Fire" )
		return new Shared::Fire();

	if( name == "Magnetism" )
		return new Shared::Magnetism();

	if( name == "Radiation" )
		return new Shared::Radiation();

	if( name == "Wind" )
		return new Shared::Wind();

	// Character

	if ( name == "Character" )
		return new Character();

	if ( name == "Hip" )
		return new CharacterParts::Hip();

	if ( name == "Head" )
		return new CharacterParts::Head();

	if ( name == "Arm" )
		return new CharacterParts::Arm();

	if ( name == "Hand" )
		return new CharacterParts::Hand();

	if ( name == "Leg" )
		return new CharacterParts::Leg();

	if ( name == "Foot" )
		return new CharacterParts::Foot();

	return nullptr;
}

ObjectsFactory::~ObjectsFactory()
{
}

Object *
ObjectsFactory::create( const std::string & name ) const
{
	Object * obj = createObject( name );
	if( obj )
		obj->initialize();
	return obj;
}

ObjectsFactory *
ObjectsFactory::create( Resources::Lab lab )
{
	switch( lab )
	{
		case Resources::Lab::Biological:
			return new BiologicalFactory();
		break;

		case Resources::Lab::Chemical:
			return new ChemicalFactory();
		break;

		case Resources::Lab::Physical:
			return new PhysicalFactory();
		break;

		case Resources::Lab::HistoricalGeographical:
			return new HistoricalGeographicalFactory();
		break;

		case Resources::Lab::Literary:
			return new LiteraryFactory();
		break;

		default:
			return nullptr;
		break;
	}
}

}
