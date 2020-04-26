#ifndef __GAME_ACT_CHARACTER_PART_HPP__
#define __GAME_ACT_CHARACTER_PART_HPP__

#include "GameAct/Objects/SubTypes/LongObject.hpp"

namespace GameAct
{

class Character;

class CharacterPart
	: public LongObject
{
public:
/* Interactors overriding*/

public:

	void initialize() override;

protected:

	Character * _character;

};

}

#endif
