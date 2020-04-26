#include "Act.hpp"
#include "Contours/Kit.hpp"
#include "Colors/Rainbow.hpp"
#include "Colors/Views/Tiles.hpp"
#include "Objects/Interactor.hpp"
#include "Objects/Registry.hpp"
#include "Objects/Character.hpp"
#include "Scores/Score.hpp"
#include "Scores/Views/Label.hpp"
#include "Resources/Constants.hpp"

namespace GameAct
{

void
Act::restart(cocos2d::Layer * layer)
{
	_layer = layer;

	_kit.reset(new Contours::Kit(layer));

	_pallete.reset(new Colors::Rainbow());
	_palleteView.reset(new Colors::Views::Tiles(_pallete.get(), _layer));
	_pallete->addObserver(_palleteView.get());

	_interactor.reset(new Objects::Interactor());
	_interactorView.reset(new Objects::Registry(_interactor.get(), _layer));

	_characterView.reset(new Objects::Character(_kit->getExpert(), _layer));

	_score.reset(new Scores::Score());
	_scoreView.reset(new Scores::Views::Label(_score.get(), _layer));
	_score->addObserver(_scoreView.get());

	/**/
	_characterView->addObserver(_score.get());

	_characterView->assignView(_palleteView.get());
	_characterView->assignView(_scoreView.get());
}

Contours::Kit *
Act::getKit() const
{
	return _kit.get();
}

Colors::Pallete *
Act::getPallete() const
{
	return _pallete.get();
}

Objects::Interactor *
Act::getInteractor() const
{
	return _interactor.get();
}

Objects::Registry *
Act::getRegistry() const
{
	return _interactorView.get();
}

Objects::Character *
Act::getCharacter() const
{
	return _characterView.get();
}

Scores::Score *
Act::getScore() const
{
	return _score.get();
}

cocos2d::Layer *
Act::getLayer()
{
	return _layer;
}
	
Act &
Act::getInstance()
{
	static Act act;
	return act;
}

}