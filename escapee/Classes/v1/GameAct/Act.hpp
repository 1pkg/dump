#ifndef __GAME_ACT_ACT_HPP__
#define __GAME_ACT_ACT_HPP__

#include "Interfaces/IViewPort.hpp"
#include "Interfaces/IObject.hpp"

#include <cocos2d.h>

namespace GameAct
{

namespace Contours
{
	class Kit;
}

namespace Objects
{
	class Interactor;

	class Registry;

	class Character;
}

namespace Colors
{
	class Pallete;
}

namespace Scores
{
	class Score;
}

class Act : public Interfaces::INoncopyable
{
public:

	void restart(cocos2d::Layer * layer);

	Contours::Kit * getKit() const;

	Colors::Pallete * getPallete() const;

	Objects::Interactor * getInteractor() const;
	Objects::Registry * getRegistry() const;

	Objects::Character * getCharacter() const;

	Scores::Score * getScore() const;

	cocos2d::Layer * getLayer();

public:
	
	static Act & getInstance();

private:

	std::unique_ptr<Contours::Kit> _kit;

	std::unique_ptr<Colors::Pallete> _pallete;
	std::unique_ptr<Interfaces::IViewPort> _palleteView;

	std::unique_ptr<Objects::Interactor> _interactor;
	std::unique_ptr<Objects::Registry> _interactorView;

	std::unique_ptr<Objects::Character> _characterView;

	std::unique_ptr<Scores::Score> _score;
	std::unique_ptr<Interfaces::IViewPort> _scoreView;

	cocos2d::Layer * _layer;
};

}

#endif