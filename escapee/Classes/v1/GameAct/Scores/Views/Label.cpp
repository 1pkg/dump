#include "Label.hpp"
#include "../Score.hpp"
#include "Resources/Constants.hpp"

#include "ThirdParty/Functions/Strings.hpp"

namespace GameAct
{

namespace Scores
{

namespace Views
{

void
Label::update(cocos2d::Vec2 delta)
{
	_heightLabel->setPosition(_heightLabel->getPosition() + delta);

	_distanceLabel->setPosition(_distanceLabel->getPosition() + delta);
}

void
Label::render() const
{
	_heightLabel->setString(ThirdParty::Functions::Strings::toString((int)_score->getHeight()));

	_distanceLabel->setString(ThirdParty::Functions::Strings::toString((int)_score->getDistance()));
}

cocos2d::Rect
Label::getBoundingBox() const
{
	cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();

	return cocos2d::Rect(0.0, _heightLabel->getPositionY(), size.width, 15.0f);
}

bool
Label::handle(const Interfaces::IObserverable * obsable)
{
	const Score * score = dynamic_cast<const Score *>(obsable);
	if(!score)
		return false;

	render();

	return true;
}

Label::Label(Score * score, cocos2d::Layer * layer)
	: _score(score), _layer(layer), _heightLabel(cocos2d::Label::createWithSystemFont("", "Arial", 12)), _distanceLabel(cocos2d::Label::createWithSystemFont("", "Arial", 12))
{
	cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
	_layer->addChild(_heightLabel, 100000);
	_heightLabel->setPosition(cocos2d::Vec2(35.0f, size.height - 15.0f));

	_layer->addChild(_distanceLabel, 100000);
	_distanceLabel->setPosition(cocos2d::Vec2(size.width - 35.0f, size.height - 15.0f));

	render();
}

Label::~Label()
{
	_heightLabel->removeFromParentAndCleanup(true);

	_distanceLabel->removeFromParentAndCleanup(true);
}

}

}

}