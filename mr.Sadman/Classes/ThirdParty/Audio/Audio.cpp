#include "Audio.hpp"
#include "AudioPlayer.hpp"

namespace ThirdParty
{

Audio::Audio( FMOD::Channel * channel  )
	: _channel( channel )
{
}

Audio::~Audio()
{
	_channel->stop();
}

void
Audio::release()
{
	AudioPlayer::getInstance().releaseAudio( this );
}

void
Audio::pause()
{
	_channel->setPaused( true );
}

void
Audio::resume()
{
	_channel->setPaused( false );
}

bool
Audio::isPlaying() const
{
	bool isPlaying = false;
	_channel->isPlaying( &isPlaying );
	return isPlaying;
}

bool
Audio::isLooped() const
{
	FMOD_MODE * mode = nullptr;
	_channel->getMode( mode );

	return ( (unsigned int) mode & FMOD_LOOP_NORMAL ) != 0;
}

void
Audio::setVolume( float volume )
{
	_channel->setVolume( volume );
}

void
Audio::setLoop( bool loop )
{
	loop
	? _channel->setMode( FMOD_LOOP_NORMAL )
	: _channel->setMode( FMOD_LOOP_OFF );
}

}