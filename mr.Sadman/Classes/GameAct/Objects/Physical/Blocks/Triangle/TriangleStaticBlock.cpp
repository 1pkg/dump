#include "TriangleStaticBlock.hpp"

namespace GameAct
{

namespace Physical
{

void
TriangleStaticBlock::initialize()
{
	Object::initialize();

	getBody()->setDynamic( false );
}

std::string
TriangleStaticBlock::getResourcesName() const
{
	return "TriangleBlock";
}

void
TriangleStaticBlock::setAdditionalParam( std::string additionalParam )
{
	std::string time = ThirdParty::readToken( additionalParam );
	_time = atof( time.data() );

	Object::setAdditionalParam( additionalParam );
}

void
TriangleStaticBlock::runAction( const std::string & action )
{
	if( action == "Apear" || action == "On" )
	{
		auto aper = cocos2d::FadeIn::create( _time );
		auto show = std::bind( &TriangleStaticBlock::show, this );
		auto action = cocos2d::Sequence::create( aper, cocos2d::CallFunc::create( show ), nullptr );
		_representation->runAction( action );

		return;
	}

	if( action == "Disapear" || action == "Off" )
	{

		auto disaper = cocos2d::FadeOut::create( _time );
		auto hide = std::bind( &TriangleStaticBlock::hide, this );
		auto action = cocos2d::Sequence::create( disaper, cocos2d::CallFunc::create( hide ), nullptr );
		_representation->runAction( action );

		return;
	}

	Object::runAction( action );
}

}

}