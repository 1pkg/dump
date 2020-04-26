#include "AudioFile.hpp"
#include "UnitedResourcesData.hpp"

#include <cocos2d.h>

#include <fstream>

namespace Resources
{

AudioFile::AudioFile( const std::string & alias, const UnitedResourcesData & data )
	: _alias( alias )
{
	FILE * file = nullptr;
	if( !( file = fopen( alias.data(), "wb" ) ) )
		throw std::exception();
	fwrite( ( char* ) data.data(), 1, data.size(), file );
	fclose( file );
}

AudioFile::~AudioFile()
{
	cocos2d::FileUtils::getInstance()->removeFile( _alias );
}

}