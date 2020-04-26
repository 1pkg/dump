#ifndef __THIRD_PARTY_AUDIO_PLAYER_HPP__
#define __THIRD_PARTY_AUDIO_PLAYER_HPP__

#include "Audio.hpp"

#include <string>
#include <unordered_map>
#include <unordered_set>

namespace ThirdParty
{

class AudioPlayer
{
public:

	static AudioPlayer & getInstance();
	~AudioPlayer();

	Audio * playAudio( const std::string & alias, const char * buffer, unsigned int size, float volume = 1.0f, bool looped = false );
	void releaseAudio( Audio * audio );

	void update();
	void clear();

private:

	FMOD::Sound * preloadSound( const char * buffer, unsigned int size );

	AudioPlayer();

	std::unordered_map< std::string, FMOD::Sound * > _sounds;
	std::unordered_set< Audio * > _audios;

	FMOD::System * system;
};

}

#endif