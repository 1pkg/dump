#include "AudioPlayer.hpp"

namespace ThirdParty
{

AudioPlayer &
AudioPlayer::getInstance()
{
	static AudioPlayer player;
	return player;
}

AudioPlayer::AudioPlayer()
{
	FMOD::System_Create( &system );
	system->init( 32, FMOD_INIT_NORMAL, 0 );
	system->update();
}

AudioPlayer::~AudioPlayer()
{
	clear();
	system->close();
	system->release();
}

FMOD::Sound * AudioPlayer::preloadSound( const char * buffer, unsigned int size )
{
	FMOD_CREATESOUNDEXINFO sndinfo = {0};
	sndinfo.cbsize      = sizeof(sndinfo);
	sndinfo.length      = size;
	FMOD::Sound * sound;
	FMOD_RESULT result = system->createSound( buffer, FMOD_OPENMEMORY, &sndinfo, &sound );
	
	return sound;
}

Audio * AudioPlayer::playAudio( const std::string & alias, const char * buffer, unsigned int size, float volume, bool looped )
{
	if( _audios.size() >= 32 )
		return nullptr;

	FMOD::Sound * sound;
	auto soundIt = _sounds.find( alias );
	sound = soundIt == _sounds.end()
	? preloadSound( buffer, size )
	: soundIt->second;

	FMOD::Channel* channel;
	system->playSound( sound, nullptr, false, &channel );
	Audio * audio = new Audio ( channel );
	_audios.insert( audio );
	audio->setVolume( volume );
	audio->setLoop( looped );
	return audio;
}

void AudioPlayer::releaseAudio( Audio * audio )
{
	_audios.erase( audio );
	delete audio;
}

void AudioPlayer::update()
{
	system->update();
	for( auto it = _audios.begin(); it != _audios.end(); )
	{
		Audio * audio = *it;

		if( !audio->isPlaying() && !audio->isLooped() )
		{
			it = _audios.erase( it );
			delete audio;
		}
		else
			++it;
	}
}

void AudioPlayer::clear()
{
	for( auto sound : _sounds )
		sound.second->release();

	for( auto audio : _audios )
		audio->release();
}

}