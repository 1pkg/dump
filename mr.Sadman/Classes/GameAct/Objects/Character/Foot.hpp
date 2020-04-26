#ifndef __GAME_ACT_CHARACTER_PARTS_FOOT_HPP__
#define __GAME_ACT_CHARACTER_PARTS_FOOT_HPP__

#include "GameAct/Objects/SubTypes/CharacterPart.hpp"

namespace GameAct
{

namespace CharacterParts
{

class Foot
	: public CharacterPart
{
public:

	std::string getResourcesName() const override;
};

}

}

#endif
