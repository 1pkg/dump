#ifndef __TECH_MINE_HPP__
#define __TECH_MINE_HPP__

#include "Game/Objects/SubTypes/Shell.hpp"
#include "Game/Objects/Providers/Direction.hpp"

namespace Objects
{

namespace Tech
{

class Mine : public Shell
{
public:
/* Handle event overriding*/

public:
/* Interactors overriding*/

public:
/* Object parts overriding*/

	std::string getName() const override;

	void attachToChunk( Levels::Chunk & chunk, int zIndex ) override;
	void runAction( const std::string & action ) override;
};

}

}

#endif
