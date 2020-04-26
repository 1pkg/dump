#ifndef __GAME_ACT_OBJECTS_FACTORY_HPP__
#define __GAME_ACT_OBJECTS_FACTORY_HPP__

#include "Resources/Forward.hpp"

#include "ThirdParty/noncopyable.hpp"

#include <string>

namespace GameAct
{

class Object;

class ObjectsFactory :
	public ThirdParty::noncopyable
{
public:
	
	static ObjectsFactory * create( Resources::Lab lab );

	virtual ~ObjectsFactory();

	Object * create( const std::string & name ) const;

protected:

	virtual Object * createObject(const std::string & name ) const; 
};

}

#endif
