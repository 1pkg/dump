#ifndef __GAME_ACT_SCORES_SCORE_HPP__
#define __GAME_ACT_SCORES_SCORE_HPP__

#include "Interfaces/INoncopyable.hpp"
#include "Interfaces/IObserverable.hpp"
#include "Interfaces/IObserver.hpp"

#include <cocos2d.h>

namespace GameAct
{

namespace Scores
{

class Score : public Interfaces::INoncopyable, public Interfaces::IObserverable, public Interfaces::IObserver
{
public:

	void nortify() const override;

public:

	bool handle(const Interfaces::IObserverable * obsable) override;

public:

	Score();

	float getHeight() const;
	float getDistance() const;

private:

	float _height;
	float _distance;
};

}

}

#endif