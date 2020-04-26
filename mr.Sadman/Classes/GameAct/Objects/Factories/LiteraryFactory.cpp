#include "LiteraryFactory.hpp"

namespace GameAct
{

Object * 
LiteraryFactory::createObject( const std::string & name ) const
{
	return ObjectsFactory::createObject( name );
}

}
