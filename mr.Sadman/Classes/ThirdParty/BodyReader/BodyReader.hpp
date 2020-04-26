#ifndef __BODY_READER_HPP__
#define  __BODY_READER_HPP__

#include "document.h"

#include <cocos2d.h>

#include <string>
#include <sstream>

USING_NS_CC;

namespace ThirdParty
{

class BodyReader
{
public:

    static BodyReader & getInstance();

    PhysicsBody * getBody( unsigned char* stream, long length, Node* pNode, const std::string& name, PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT );

private:

	void parseJsonFile( const std::string& pFile );

	void parse( unsigned char* buffer, long length );

	BodyReader();

    rapidjson::Document _doc;
};

}

#endif