#include "HistoricalGeographicalFactory.hpp"

namespace GameAct
{

Object * 
HistoricalGeographicalFactory::createObject( const std::string & name ) const
{
	return ObjectsFactory::createObject( name );
}

}
