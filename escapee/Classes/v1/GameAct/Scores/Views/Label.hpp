#ifndef __GAME_CAT_SCORES_VIEWS_LABEL_HPP__
#define __GAME_CAT_SCORES_VIEWS_LABEL_HPP__

#include "Interfaces/IViewPort.hpp"

namespace GameAct
{

namespace Scores
{

class Score;

namespace Views
{

class Label : public Interfaces::IViewPort
{
public:

	cocos2d::Rect getBoundingBox() const override;

	void render() const override;

	void update(cocos2d::Vec2 delta) override;

public:

	bool handle(const Interfaces::IObserverable * obsable) override;

public:

	Label(Score * score, cocos2d::Layer * layer);
	~Label();

private:

	Score * _score;

	cocos2d::Layer * _layer;
	cocos2d::Label * _heightLabel;
	cocos2d::Label * _distanceLabel;
};

}

}

}

#endif