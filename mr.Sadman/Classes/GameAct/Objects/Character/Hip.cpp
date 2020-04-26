#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Levels/Level.hpp"
#include "Hip.hpp"
#include "GameAct/Objects/Shared/Edge/Edge.hpp"

namespace GameAct
{

namespace CharacterParts
{

void
Hip::stopInteract( Shared::Edge * edge )
{
	edge->stopInteract( this );
}

void
Hip::initialize()
{
	CharacterPart::initialize();

	//Director::getInstance().getGameAct()->getLevel()->getLayer()->runAction( cocos2d::Follow::create( _representation ) );
}

std::string
Hip::getResourcesName() const
{
	return "Hip";
}

void
Hip::separateContact( Object * object )
{
	object->stopInteract( this );
}

}

}