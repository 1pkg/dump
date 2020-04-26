#include "Director.hpp"
#include "CharacterPart.hpp"

namespace GameAct
{

void
CharacterPart::initialize()
{
	LongObject::initialize();

	auto body = getBody();

	body->setDynamic( true );

	setMask( 0x4 );
	setContactMask( 0x2 );
}

}