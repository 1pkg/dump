#ifndef __GAME_CAT_COLORS_VIEWS_TILES_HPP__
#define __GAME_CAT_COLORS_VIEWS_TILES_HPP__

#include "Interfaces/IViewPort.hpp"

namespace GameAct
{

namespace Colors
{

class Pallete;

namespace Views
{

class Tiles : public Interfaces::IViewPort
{
public:

	cocos2d::Rect getBoundingBox() const override;

	void render() const override;

	void update(cocos2d::Vec2 delta) override;

public:

	bool handle(const Interfaces::IObserverable * obsable) override;

public:

	Tiles(Pallete * pallete, cocos2d::Layer * layer);
	~Tiles();

private:

	Pallete * _pallete;

	cocos2d::Vec2 _deltas;

	cocos2d::Layer * _layer;
	cocos2d::EventListenerTouchOneByOne * _listener;
	std::vector<cocos2d::DrawNode *> _nodes;
};

}

}

}

#endif