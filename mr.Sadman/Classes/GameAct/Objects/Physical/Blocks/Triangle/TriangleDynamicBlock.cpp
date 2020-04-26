#include "TriangleDynamicBlock.hpp"

namespace GameAct
{

namespace Physical
{

void
TriangleDynamicBlock::initialize()
{
	TriangleStaticBlock::initialize();

	getBody()->setDynamic( true );
}

}

}