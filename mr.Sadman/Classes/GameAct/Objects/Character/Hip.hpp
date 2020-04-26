#ifndef __GAME_ACT_CHARACTER_PARTS_HIP_HPP__
#define __GAME_ACT_CHARACTER_PARTS_HIP_HPP__

#include "GameAct/Objects/SubTypes/CharacterPart.hpp"

namespace GameAct
{

namespace CharacterParts
{

class Hip
	: public CharacterPart
{
public:
/* Interactor overriding*/

	void stopInteract( Shared::Edge * edge );

public:

	void initialize() override;

	std::string getResourcesName() const override;

	void separateContact( Object * object ) override;
};

}

}

#endif
