#ifndef __GAME_ACT_INTERACTOR_HPP__
#define __GAME_ACT_INTERACTOR_HPP__

#include "BiologicalInteractor.hpp"
#include "ChemicalInteractor.hpp"
#include "PhysicalInteractor.hpp"
#include "HistoricalGeographicalInteractor.hpp"
#include "LiteraryInteractor.hpp"

namespace GameAct
{

namespace Shared
{

class Edge;

}

namespace CharacterParts
{
	class Hip;
	class Head;
	class Arm;
	class Hand;
	class Leg;
	class Foot;
}

class Interactor
	: public Biological::Interactor,
	public Chemical::Interactor,
	public Physical::Interactor,
	public HistoricalGeographical::Interactor,
	public Literary::Interactor
{
public:

	virtual void startInteract( Shared::Edge * obj );
	virtual void stepInteract( Shared::Edge * obj );
	virtual void stopInteract( Shared::Edge * obj );

	virtual void startInteract( CharacterParts::Hip * obj );
	virtual void stepInteract( CharacterParts::Hip * obj );
	virtual void stopInteract( CharacterParts::Hip * obj );
};

}

#endif