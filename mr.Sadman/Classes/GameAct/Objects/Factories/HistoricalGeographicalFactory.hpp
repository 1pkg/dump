#ifndef __GAME_ACT_HISTORICAL_GEOGRAPHICAL_FACTORY_HPP__
#define __GAME_ACT_HISTORICAL_GEOGRAPHICAL_FACTORY_HPP__

#include "ObjectsFactory.hpp"

namespace GameAct
{

class HistoricalGeographicalFactory :
	public ObjectsFactory
{
public:

	Object * createObject( const std::string & name ) const override;
};

}

#endif
