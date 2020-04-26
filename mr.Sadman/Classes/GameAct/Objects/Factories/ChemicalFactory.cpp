#include "ChemicalFactory.hpp"

namespace GameAct
{

Object * 
ChemicalFactory::createObject( const std::string & name ) const
{
	return ObjectsFactory::createObject( name );
}

}
