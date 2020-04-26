#include "Generator.hpp"
#include "Registry.hpp"
#include "../Scores/Score.hpp"
#include "Resources/Constants.hpp"

namespace GameAct
{

namespace Objects
{

bool
Generator::handle(const Interfaces::IObserverable * obsable)
{
	const Scores::Score * score = dynamic_cast<const Scores::Score *>(obsable);
	if(!score)
		return false;

	_bypassing = Resources::Constants::GENERATOR_DEFAULT_BYPASSING + (int)(score->getDistance() / Resources::Constants::SCORE_DIVIDED_KOEFICIENT);

	return true;
}

Generator::Generator(Registry * registry)
	: _registry(registry), _bypassing(Resources::Constants::GENERATOR_DEFAULT_BYPASSING)
{
}

void
Generator::update()
{
	std::vector<Interfaces::IObject::Type> rolled = roll();
	for(Interfaces::IObject::Type type : rolled)
	{
		std::unique_ptr<Interfaces::IObjectView> objectView = create(type);
		if(objectView)
			_registry->_objects.insert(std::move(objectView));
	}
}

std::unique_ptr<Interfaces::IObjectView>
Generator::create(Interfaces::IObject::Type type) const
{
	switch ( type )
	{
		default:
			return std::unique_ptr<Interfaces::IObjectView>();
	}
}

std::vector<Interfaces::IObject::Type>
Generator::roll() const
{
	std::vector<Interfaces::IObject::Type> result;
	int overallProbability = 1000;

	for(int i = 0; i < _bypassing; ++i)
	{
		int currentProbability = 0;
		for(auto pair : _odds)
		{
			currentProbability += (int)(pair.second * 100.0f);
			int roll = cocos2d::RandomHelper::random_int(1, overallProbability);
			if(roll <= currentProbability)
			{
				result.push_back(pair.first);
				break;
			}
		}
	}
	
	return result;
}

}

}