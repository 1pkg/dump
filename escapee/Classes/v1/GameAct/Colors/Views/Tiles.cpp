#include "Tiles.hpp"
#include "../Pallete.hpp"
#include "../Dye.hpp"
#include "Resources/Constants.hpp"

namespace GameAct
{

namespace Colors
{

namespace Views
{

void
Tiles::update(cocos2d::Vec2 delta)
{
	_deltas += delta;

	render();
}

void
Tiles::render() const
{
	std::vector<cocos2d::Color4F> colors = _pallete->getColors();
	cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();

	float xStart = size.width - 20.0f * colors.size();
	float yFull = 14.0f;
	float yMin = 1.0f;

	int i = 0;
	for(cocos2d::Color4F color : colors)
	{
		_nodes[i]->clear();

		Dye & dye = _pallete->getDye(color);
		float yCurrent = (yFull - yMin) / Resources::Constants::DEFAULT_DYE_AMOUNT * dye.getAmount();
		if(yCurrent > 0.0f)
			_nodes[i]->drawSolidRect(cocos2d::Vec2(xStart + 1.0f, yMin + _deltas.y), cocos2d::Vec2(xStart + 14.0f, yCurrent + yMin + _deltas.y), color);
		_nodes[i]->drawRect(cocos2d::Vec2(xStart, 1.0f + _deltas.y), cocos2d::Vec2(xStart + 15.0f, 15.0f + _deltas.y), cocos2d::Color4F::WHITE);
		xStart += 20.0f;

		++i;
	}
}

cocos2d::Rect
Tiles::getBoundingBox() const
{
	std::vector<cocos2d::Color4F> colors = _pallete->getColors();
	cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();

	return cocos2d::Rect(size.width - 20.0f * colors.size(), _deltas.y, size.width * colors.size(), 15.0f);
}

bool
Tiles::handle(const Interfaces::IObserverable * obsable)
{
	const Pallete * pallete = dynamic_cast<const Pallete *>(obsable);
	if(!pallete)
		return false;

	render();

	return true;
}

Tiles::Tiles(Pallete * pallete, cocos2d::Layer * layer)
	: _pallete(pallete), _layer(layer), _listener(cocos2d::EventListenerTouchOneByOne::create())
{
	int count = _pallete->getColors().size();
	for(int i = 0; i < count; ++i)
	{
		cocos2d::DrawNode * node = cocos2d::DrawNode::create();
		_layer->addChild(node, 1000);
		_nodes.push_back(node);
	}

	_listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		std::vector<cocos2d::Color4F> colors = _pallete->getColors();
		cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
		cocos2d::Vec2 location = touch->getLocation();

		int xStart = size.width - 20.0f * colors.size();
		
		for(cocos2d::Color4F color : colors)
		{
			cocos2d::Rect rect(xStart, 0.0f, 15.0f, 15.0f);
			if(rect.containsPoint(location))
			{
				_pallete->setCurrentDye(color);
				return true;
			}
			xStart += 20.0f;
		}
		return false;
	};
	_listener->setSwallowTouches(true);
	_layer->getEventDispatcher()->addEventListenerWithFixedPriority(_listener, 1);

	render();
}

Tiles::~Tiles()
{
	for(cocos2d::DrawNode * node : _nodes)
		node->removeFromParentAndCleanup(true);

	_layer->getEventDispatcher()->removeEventListener(_listener);
}

}

}

}