#include "Score.hpp"
#include "../Objects/Character.hpp"
#include "Resources/Constants.hpp"

namespace GameAct
{

namespace Scores
{

void
Score::nortify() const
{
	for(Interfaces::IObserver * obs : _observers)
		obs->handle(this);
}

bool
Score::handle(const Interfaces::IObserverable * obsable)
{
	const Objects::Character * character = dynamic_cast<const Objects::Character*>(obsable);
	if(!character)
		return false;

	_height = character->getBoundingBox().origin.y;

	_distance += Resources::Constants::SCENE_SPEED;

	nortify();

	return true;
}


Score::Score()
	: _distance(0.0f)
{
}

float
Score::getHeight() const
{
	return _height;
}

float
Score::getDistance() const
{
	return _distance;
}

}

}