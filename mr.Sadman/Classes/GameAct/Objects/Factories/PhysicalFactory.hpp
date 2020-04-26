#ifndef __GAME_ACT_PHYSICAL_FACTORY_HPP__
#define __GAME_ACT_PHYSICAL_FACTORY_HPP__

#include "ObjectsFactory.hpp"

namespace GameAct
{

class PhysicalFactory :
	public ObjectsFactory
{
public:

	Object * createObject( const std::string & name ) const override;
};

}

#endif
