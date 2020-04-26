#include "CircleStaticBlock.hpp"

namespace GameAct
{

namespace Physical
{

void
CircleStaticBlock::initialize()
{
	Object::initialize();

	auto body = cocos2d::PhysicsBody::createBox( _representation->getContentSize() );
	_representation->setPhysicsBody( body );
	body->setDynamic( false );
}

std::string
CircleStaticBlock::getResourcesName() const
{
	return "CircleBlock";
}

void
CircleStaticBlock::setAdditionalParam( std::string additionalParam )
{
	std::string time = ThirdParty::readToken( additionalParam );
	_time = atof( time.data() );

	Object::setAdditionalParam( additionalParam );
}

void
CircleStaticBlock::runAction( const std::string & action )
{
	if( action == "Apear" || action == "On" )
	{
		auto aper = cocos2d::FadeIn::create( _time );
		auto show = std::bind( &CircleStaticBlock::show, this );
		auto action = cocos2d::Sequence::create( aper, cocos2d::CallFunc::create( show ), nullptr );
		_representation->runAction( action );

		return;
	}

	if( action == "Disapear" || action == "Off" )
	{

		auto disaper = cocos2d::FadeOut::create( _time );
		auto hide = std::bind( &CircleStaticBlock::hide, this );
		auto action = cocos2d::Sequence::create( disaper, cocos2d::CallFunc::create( hide ), nullptr );
		_representation->runAction( action );

		return;
	}

	Object::runAction( action );
}

}

}