#include "Director.hpp"
#include "GameAct/Act.hpp"

#include "ThirdParty/Audio/AudioPlayer.hpp"

Director &
Director::getInstance()
{
	static Director director;
	return director;
}

GameAct::Act *
Director::getGameAct() const
{
	return _gameAct.get();
}

void
Director::restartAct( Resources::Lab lab, int levelIndex, cocos2d::Layer * layer, cocos2d::PhysicsWorld * physicWorld )
{
	layer->schedule( std::bind( &ThirdParty::AudioPlayer::update, &ThirdParty::AudioPlayer::getInstance() ), "AudioSheduler" );

	_gameAct.reset( GameAct::Act::create( lab, levelIndex, layer, physicWorld ) );
	_gameAct->initialize();
}

void
Director::finishAct()
{
	_gameAct.reset( nullptr );
}