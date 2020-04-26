#ifndef __GAME_ACT_CHARACTER_HEAD_HPP__
#define __GAME_ACT_CHARACTER_HEAD_HPP__

#include "GameAct/Objects/SubTypes/CharacterPart.hpp"

namespace GameAct
{

namespace CharacterParts
{

class Head
	: public CharacterPart
{
public:

	std::string getResourcesName() const override;
};

}

}

#endif
