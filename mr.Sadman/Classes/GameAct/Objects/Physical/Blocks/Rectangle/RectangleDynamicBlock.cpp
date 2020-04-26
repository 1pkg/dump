#include "RectangleDynamicBlock.hpp"

namespace GameAct
{

namespace Physical
{

void
RectangleDynamicBlock::initialize()
{
	RectangleStaticBlock::initialize();

	getBody()->setDynamic( true );
}

void
RectangleDynamicBlock::runAction( const std::string & action )
{
	Object::runAction( action );
}

}

}