#ifndef __RESOURCES_AUDIO_FILE_HPP__
#define __RESOURCES_AUDIO_FILE_HPP__

#include "ThirdParty\noncopyable.hpp"

#include <string>
#include <stdio.h>

namespace Resources
{

class UnitedResourcesData;

class /*[[deprecated("It's strongly recomended use memory buffer, instead of real file")]]*/ AudioFile
	: ThirdParty::noncopyable
{
public:

	AudioFile( const std::string & alias, const UnitedResourcesData & data );
	~AudioFile();

private:

	std::string _alias;
};

}

#endif