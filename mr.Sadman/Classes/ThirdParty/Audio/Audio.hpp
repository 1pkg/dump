#ifndef __THIRD_PARTY_AUDIO_HPP__
#define __THIRD_PARTY_AUDIO_HPP__

#include "FMOD/fmod.hpp"

namespace ThirdParty
{

class Audio
{
public:

	Audio( FMOD::Channel * channel );
	~Audio();

	void pause();
	void resume();

	bool isPlaying() const;
	bool isLooped() const;

	void release();

	void setVolume( float volume );
	void setLoop( bool loop );

private:

	FMOD::Channel * _channel;
};

}

#endif