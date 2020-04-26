#ifndef __GAME_ACT_SHARED_EDGE_HPP__
#define __GAME_ACT_SHARED_EDGE_HPP__

#include "GameAct/Objects/SubTypes/Area.hpp"

namespace GameAct
{

namespace Shared
{

class Edge
	: public Area
{
public:
/* Interactor overriding*/

	void stopInteract( CharacterParts::Hip * character ) override;

public:

	void initialize() override;

	std::string getResourcesName() const override;

	void separateContact( Object * object ) override;
};

}

}

#endif
