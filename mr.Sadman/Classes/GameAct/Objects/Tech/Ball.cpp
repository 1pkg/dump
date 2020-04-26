#include "Ball.hpp"

namespace GameAct
{

namespace Tech
{

void
Ball::initialize()
{
	Shell::initialize();
}

std::string
Ball::getName() const
{
	return "Ball";
}

void
Ball::runInteraction( Object * object )
{
	object->interact( this );
}

}

}