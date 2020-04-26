#ifndef __GAME_ACT_EDGE_HPP__
#define __GAME_ACT_EDGE_HPP__

#include "GameAct/Objects/Object.hpp"

namespace GameAct
{


class Edge
	: public Object
{
public:
/* Interactors overriding*/

	void interact( Character * character ) override;

public:

	void initialize() override;

	std::string getName() const override;

	void runInteraction( Object * object ) override;

};

}

#endif
