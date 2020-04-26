#include "Armer.hpp"
#include "Resources/Cache/Cache.hpp"

namespace GameAct
{

namespace Physical
{

void
Armer::initialize()
{
	Object::initialize();

	auto body =  Resources::Cache::getInstance().getObjectBody( getResourcesName(), "Off" );
	_representation->setPhysicsBody( body );
	body->setDynamic( false );

	_status = "Off";
}

std::string
Armer::getResourcesName() const
{
	return "Armer";
}

void
Armer::setAdditionalParam( std::string additionalParam )
{
	std::string stateLogical = ThirdParty::readToken( additionalParam );
	_stateLogical = atoi( stateLogical.data() ) == 1;

	Object::setAdditionalParam( additionalParam );
}

void
Armer::runAction( const std::string & action )
{
	if( action == "Switch" )
	{
		_status = _status == "On"
		? "Off"
		: "On";
		_stateLogical = ! _stateLogical;

		std::string actionRepresentation = _status;
		std::string actionLogical =
			_stateLogical ?
			"On" :
			"Off";

		auto size = getSize();
		setSize( _representation->getContentSize() );
		auto animation = Resources::Cache::getInstance().getObjectAnimation( getResourcesName(), actionRepresentation );

		auto switchIt = [ this, actionLogical ] ()
		{
			for( auto obj : _slaves )
				obj->runAction( actionLogical );		
		};

		auto setBody = actionRepresentation == "Off"
		? std::bind( &Armer::setOffBody, this )
		: std::bind( &Armer::setOnBody, this );

		auto action = cocos2d::Sequence::create( animation, cocos2d::CallFunc::create( switchIt ), cocos2d::CallFunc::create( setBody ), nullptr );
		_representation->runAction( action );
		setSize( size );

		Resources::Cache::getInstance().getObjectAudio( getResourcesName(), "Switch" );

		return;
	}

	Object::runAction( action );
}

void
Armer::setOffBody()
{
	auto size = getSize();
	setSize( _representation->getContentSize() );
	getBody()->removeFromWorld();
	_representation->setPhysicsBody( Resources::Cache::getInstance().getObjectBody( getResourcesName(), "Off" ) );
	getBody()->setDynamic( false );
	setSize( size );
}

void
Armer::setOnBody()
{
	auto size = getSize();
	setSize( _representation->getContentSize() );
	getBody()->removeFromWorld();
	_representation->setPhysicsBody( Resources::Cache::getInstance().getObjectBody( getResourcesName(), "On" ) );
	getBody()->setDynamic( false );
	setSize( size );
}

}

}