#ifndef __GAME_ACT_CHARACTER_PARTS_ARM_HPP__
#define __GAME_ACT_CHARACTER_PARTS_ARM_HPP__

#include "GameAct/Objects/SubTypes/CharacterPart.hpp"

namespace GameAct
{

namespace CharacterParts
{

class Arm
	: public CharacterPart
{
public:

	std::string getResourcesName() const override;
};

}

}

#endif
