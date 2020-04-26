#include "Trampoline.hpp"
#include "Resources/Cache/Cache.hpp"

namespace GameAct
{

namespace Physical
{

void
Trampoline::initialize()
{
	Object::initialize();

	getBody()->setDynamic( true );
}

std::string
Trampoline::getResourcesName() const
{
	return "Trampoline";
}

void
Trampoline::runAction( const std::string & action )
{
	if( action == "Jump" || action == "On" )
	{
		auto size = getSize();
		setSize( _representation->getContentSize() );
		auto animation = Resources::Cache::getInstance().getObjectAnimation( getResourcesName(), "Jump" );
		_representation->runAction( animation );
		setSize( size );

		Resources::Cache::getInstance().getObjectAudio( getResourcesName(), "Jump" );

		return;
	}

	Object::runAction( action );
}

}

}