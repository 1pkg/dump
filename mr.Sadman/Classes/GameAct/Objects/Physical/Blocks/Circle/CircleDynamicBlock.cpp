#include "CircleDynamicBlock.hpp"

namespace GameAct
{

namespace Physical
{

void
CircleDynamicBlock::initialize()
{
	CircleStaticBlock::initialize();

	getBody()->setDynamic( true );
}

}

}