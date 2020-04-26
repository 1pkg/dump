#ifndef __RESOURCES_CASHE_HPP__
#define __RESOURCES_CASHE_HPP__

#include "Resources/Forward.hpp"

#include "UnitedResourcesData.hpp"

#include "ThirdParty/noncopyable.hpp"
#include "ThirdParty/Rapidxml/rapidxml.hpp"
#include "ThirdParty/Audio/Audio.hpp"

#include <cocos2d.h>

namespace Resources
{

class Cache
	: public ThirdParty::noncopyable
{
public:

	static Cache & getInstance();
	~Cache();

	cocos2d::Node * getObjectRepresentation( const std::string & objName ) const;
	cocos2d::PhysicsBody * getObjectBody( const std::string & objName, const std::string & bodyName = "Def" ) const;
	cocos2d::Animate * getObjectAnimation( const std::string & objName, const std::string & animName ) const;
	ThirdParty::Audio * getObjectAudio( const std::string & objName, const std::string & audioName = "Def" ) const;

	const std::vector< ObjectInfo > & getChunkInfo( int chunkIndex ) const;

	unsigned int getChunksCount() const;
	std::string getLevelName() const;
	LevelOrientation getLevelOrientation() const;
	cocos2d::Size getLevelSize() const;
	cocos2d::Vec2 getLevelGravity() const;

	void restart( Lab lab, int levelIndex );

private:

	cocos2d::Image * getImage( const std::string alias, const unsigned char * data, unsigned int size );

	struct ObjRes
	{
		struct
		{
			struct
			{
				UnitedResourcesData data;
				UnitedResourcesData atlas;
				std::vector< UnitedResourcesData > images;
			}skeleton;
			UnitedResourcesData sprite;
		} representation;

		std::unordered_map< std::string, UnitedResourcesData > bodies;
		std::unordered_map< std::string, std::pair< std::vector< UnitedResourcesData >, float > > anims;
		std::unordered_map< std::string, UnitedResourcesData > audios;
	};

	void parseResources( Lab lab, const std::string & KEY );
	void parseDefaults( Lab lab, const std::string & KEY );
	void parseCharacter( const std::string & KEY );
	void parseLevel( Lab lab, int levelIndex, const std::string & KEY );

	void parseResNode( rapidxml::xml_node< char > * node, ObjRes & res, Lab lab, const std::string & objName, const std::string & key ) const;
	void parseObjAttribute( rapidxml::xml_attribute< char > * objAttr, ObjectInfo & info );
	void parseLevelAttribute( rapidxml::xml_attribute< char > * levelAttr );

	UnitedResourcesData readFile( const std::string & fileName ) const;
	UnitedResourcesData decryptFile( UnitedResourcesData & data, const std::string & key ) const;
	UnitedResourcesData readBlock( UnitedResourcesData & data, size_t blockSize ) const;

private:

	std::unordered_map< std::string, cocos2d::Image * > _imagePool;

	std::unordered_map< std::string, ObjRes > _objects;

	std::unordered_map< std::string, ObjectInfo > _defInfo;

	std::vector< std::vector< ObjectInfo > > _level;

	std::string _levelName;
	LevelOrientation _levelOrientation;
	cocos2d::Size _levelSize;
	cocos2d::Vec2 _levelGravity;

	Lab _lab;
	int _levelIndex;
};

}

#endif