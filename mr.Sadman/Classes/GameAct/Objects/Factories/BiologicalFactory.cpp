#include "BiologicalFactory.hpp"

namespace GameAct
{

Object * 
BiologicalFactory::createObject( const std::string & name ) const
{
	return ObjectsFactory::createObject( name );
}

}
