#include "Cache.hpp"

#include "ThirdParty/Functions/StringFunctions.hpp"
#include "ThirdParty/Decrypter/aescpp.h"
#include "ThirdParty/BodyReader/BodyReader.hpp"
#include "ThirdParty/Audio/AudioPlayer.hpp"

#include <spine/SkeletonAnimation.h>

#include "Director.hpp"
#include "GameAct/Act.hpp"
#include "GameAct/Levels/Level.hpp"

namespace Resources
{

cocos2d::Node *
Cache::getObjectRepresentation( const std::string & objName ) const
{
	if( _objects.find( objName ) == _objects.end() )
		return nullptr;

	auto & representation = _objects.at( objName ).representation;
	auto & spriteData = representation.sprite;
	if( !spriteData.empty() )
	{
		cocos2d::Image * image = const_cast< Cache * >( this )->getImage( toString( _lab ) + objName, spriteData.data(), spriteData.size() );
		auto texture = cocos2d::Director::getInstance()->getTextureCache()->addImage( image, toString( _lab ) + objName );

		return cocos2d::Sprite::createWithTexture( texture );
	}
	else
	{
		auto & skeleton = representation.skeleton;
		auto & images = skeleton.images;
		std::vector< std::string > aliases;
		for( unsigned int i = 0; i < images.size(); ++i )
		{
			cocos2d::Image * image = const_cast< Cache * >( this )->getImage( toString( _lab ) + objName, images[i].data(), images[i].size() );
			std::string alias = toString( _lab ) + objName + ThirdParty::toString( i + 1 );
			auto texture = cocos2d::Director::getInstance()->getTextureCache()->addImage( image, alias );
			aliases.push_back( alias );
		}
		/*auto skeletonskel = spine::SkeletonAnimation::createWithData( skeleton.data.data(), skeleton.data.size(), skeleton.atlas.data(), skeleton.atlas.size(), aliases );
		auto layer = ::Director::getInstance().getGameAct()->getLevel()->getLayer();
		auto nodeskeletonskel =  (cocos2d::Node *) skeletonskel;
		nodeskeletonskel->setPosition( 350.0f, 350.0f );
		layer->addChild( nodeskeletonskel, 3 );
		skeletonskel->updateWorldTransform();
		skeletonskel->addAnimation( 0, "fire", true );*/
		return spine::SkeletonAnimation::createWithData( skeleton.data.data(), skeleton.data.size(), skeleton.atlas.data(), skeleton.atlas.size(), aliases );
	}
}

cocos2d::PhysicsBody *
Cache::getObjectBody( const std::string & objName, const std::string & bodyName ) const
{
	if( _objects.find( objName ) == _objects.end() || _objects.at( objName ).bodies.find( bodyName ) == _objects.at( objName ).bodies.end() )
		return nullptr;

	auto sprite = getObjectRepresentation( objName );
	auto & bodyData = _objects.at( objName ).bodies.at( bodyName );
	return ThirdParty::BodyReader::getInstance().getBody( bodyData.data(), bodyData.size(), sprite, bodyName );
}

cocos2d::Animate *
Cache::getObjectAnimation( const std::string & objName, const std::string & animName ) const
{
	if( _objects.find( objName ) == _objects.end() || _objects.at( objName ).anims.find( animName ) == _objects.at( objName ).anims.end() )
		return nullptr;

	const auto & animDataDur = _objects.at( objName ).anims.at( animName );
	auto & animData = animDataDur.first;
	cocos2d::Vector< cocos2d::SpriteFrame* > animFrames;
	int i = 1;
	std::for_each(
		animData.begin(),
		animData.end(),
		[ this, objName, animName, &i, &animFrames ]( const UnitedResourcesData & imageData )
		{
			cocos2d::Image * image = const_cast< Cache * >( this )-> getImage( objName + animName + ThirdParty::toString( i ), imageData.data(), imageData.size() ) ;
			auto texture = cocos2d::Director::getInstance()->getTextureCache()->addImage( image, toString( _lab ) + objName + animName + ThirdParty::toString( i++ ) );

			auto size = texture->getContentSize();
			auto frame = cocos2d::SpriteFrame::createWithTexture( texture, cocos2d::Rect( 0.0, 0.0, size.width, size.height ) );
			animFrames.pushBack( frame );
		}
	);

	auto animation = cocos2d::Animation::createWithSpriteFrames( animFrames, animDataDur.second );
	return cocos2d::Animate::create( animation );
}

ThirdParty::Audio *
Cache::getObjectAudio( const std::string & objName, const std::string & audioName ) const
{
	if( _objects.find( objName ) == _objects.end() || _objects.at( objName ).audios.find( audioName ) == _objects.at( objName ).audios.end() )
		return nullptr;

	auto data = _objects.at( objName ).audios.at( audioName );
	auto alias = toString( _lab ) + '_' + objName + '_' + audioName;

	return ThirdParty::AudioPlayer::getInstance().playAudio( alias, (const char*) data.data(), data.size() );
}

const std::vector< ObjectInfo > &
Cache::getChunkInfo( int chunkIndex ) const
{
	return _level.at( chunkIndex );
}

unsigned int
Cache::getChunksCount() const
{
	return _level.size();
}

std::string
Cache::getLevelName() const
{
	return _levelName;
}

LevelOrientation
Cache::getLevelOrientation() const
{
	return _levelOrientation;
}

cocos2d::Size
Cache::getLevelSize() const
{
	return _levelSize;
}

cocos2d::Vec2
Cache::getLevelGravity() const
{
	return _levelGravity;
}

void
Cache::restart( Lab lab, int levelIndex )
{
	const std::string KEY = "361755848554586A619A1AFD7160A7D3127A77C41701736B626706828F038BB0";

	bool objsEmpty = _objects.empty();

	if( objsEmpty || _lab != lab )
	{
		_lab = lab;
		ThirdParty::AudioPlayer::getInstance().clear();

		parseResources( Lab::Shared, KEY );
		if( lab != Lab::United )
		{
			parseResources( lab, KEY );
			parseDefaults( lab, KEY );
		}
		else
		{
			parseResources( Lab::Biological, KEY ), parseResources( Lab::Chemical, KEY ), parseResources( Lab::Physical, KEY ), parseResources( Lab::HistoricalGeographical, KEY ), parseResources( Lab::Literary, KEY );
			parseDefaults( Lab::Biological, KEY ), parseDefaults( Lab::Chemical, KEY ), parseDefaults( Lab::Physical, KEY ), parseDefaults( Lab::HistoricalGeographical, KEY ), parseDefaults( Lab::Literary, KEY );
		}
	}

	if( objsEmpty )
		parseCharacter( KEY );	

	if( _level.empty() || _levelIndex != levelIndex )
	{
		parseLevel( lab, levelIndex, KEY );
		_levelIndex = levelIndex;
	}
}

Cache &
Cache::getInstance()
{
	static Cache cache;
	return cache;
}

Cache::~Cache()
{
	for( auto imgIt : _imagePool )
		delete imgIt.second;

	_imagePool.clear();	
}

cocos2d::Image *
Cache::getImage( const std::string alias, const unsigned char * data, unsigned int size )
{
	auto imgIt = _imagePool.find( alias );

	cocos2d::Image * image;
	if( imgIt == _imagePool.end() )
	{
		image = new cocos2d::Image();
		image->initWithImageData( data, size );
		_imagePool.insert( { alias, image } );
	}
	else
		image = imgIt->second;

	return image;
}

void
Cache::parseResources( Lab lab, const std::string & KEY )
{
	#ifdef COCOS2D_DEBUG

	std::string resPath = "Debug/Act/Objects/" + toString( lab ) + "/resources.xml";

	#else

	std::string resPath = "Release/Act/Objects/" + toString( lab ) + "/ev.xxx";

	#endif

	UnitedResourcesData resData = readFile( resPath );
	UnitedResourcesData resources = decryptFile( resData, KEY );

	std::string resDataCpy( ( char * ) resources.data(), resources.size() );
	rapidxml::xml_document<> docObjects;
	docObjects.parse<0>( const_cast< char * >( resDataCpy.data() ) );

	rapidxml::xml_node< char > * nodeRes = docObjects.first_node()->first_node();
	ObjRes res;
	std::string objName;
	do
	{
		res = ObjRes();
		objName = nodeRes->first_attribute()->value();

		auto resNode = nodeRes->first_node();
		do
		{
			parseResNode( resNode, res, lab, objName, KEY );
		}while( resNode = resNode->next_sibling() );
	
	}while( _objects.insert( { objName, res } ), nodeRes = nodeRes->next_sibling() );
}

void
Cache::parseDefaults( Lab lab, const std::string & KEY )
{
	#ifdef COCOS2D_DEBUG

	std::string defaultsPath = "Debug/Act/Levels/" + toString( lab ) + "/defaults.xml";

	#else

	std::string defaultsPath = "Release/Act/Levels/" + toString( lab ) + "/ev.xxx";

	#endif

	UnitedResourcesData defaultsData = readFile( defaultsPath );
	UnitedResourcesData defaults = decryptFile( defaultsData, KEY );

	std::string defaultsDataCpy( ( char * ) defaults.data(), defaults.size() );
	rapidxml::xml_document<> docDefaults;
	docDefaults.parse<0>( const_cast< char * >( defaultsDataCpy.data() ) );

	rapidxml::xml_node< char > * nodeDefaults = docDefaults.first_node()->first_node();
	ObjectInfo info;
	do
	{
		info = ObjectInfo();

		auto atribute = nodeDefaults->first_attribute();
		do
		{
			parseObjAttribute( atribute, info );
		}while( atribute = atribute->next_attribute() );
	
	}while( _defInfo.insert( { info.name, info } ), nodeDefaults = nodeDefaults->next_sibling() );
}

void
Cache::parseCharacter( const std::string & KEY )
{
	std::vector< std::string > parts = { "Hip", "Head", "Arm", "Hand", "Leg", "Foot" };
	for( auto part : parts )
	{
		#ifdef COCOS2D_DEBUG

		std::string partPath = "Debug/Act/Character/" + part + "/Rpr/sprite.png";

		#else

		std::string partPath = "Release/Act/Character/" + part + "/Rpr/ev.xxx";

		#endif

		#ifdef COCOS2D_DEBUG

		std::string partBdsDefPath = "Debug/Act/Character/" + part + "/Bds/Def/body.json";

		#else

		std::string partBdsDefPath = "Release/Act/Character/" + part + "/Bds/Def/ev.xxx";

		#endif

		ObjRes partRes;

		UnitedResourcesData partSprite = readFile( partPath );
		partRes.representation.sprite = decryptFile( partSprite, KEY );

		UnitedResourcesData partDefBody = readFile( partBdsDefPath );
		partRes.bodies.insert( { "Def", decryptFile( partDefBody, KEY ) } );

		_objects.insert( { part, partRes } );
	}
}

void
Cache::parseLevel( Lab lab, int levelIndex, const std::string & KEY )
{
	#ifdef COCOS2D_DEBUG

	std::string mapPath = "Debug/Act/Levels/" + toString( lab ) + "/level" + ThirdParty::toString( levelIndex ) + ".xml";

	#else

	std::string mapPath = "Release/Act/Levels/" + toString( lab ) + "/ev" + ThirdParty::toString( levelIndex ) + ".xxx";

	#endif

	UnitedResourcesData mapData = readFile( mapPath );
	UnitedResourcesData map = decryptFile( mapData, KEY );

	std::string mapDataCpy( ( char * ) map.data(), map.size() );
	rapidxml::xml_document<> docMap;
	docMap.parse<0>(  const_cast< char * >( mapDataCpy.data() ) );

	auto levelAttr = docMap.first_node()->first_attribute();
	do
	{
		parseLevelAttribute( levelAttr );
	}while( levelAttr = levelAttr->next_attribute() );
		
	rapidxml::xml_node< char > * nodeMap = docMap.first_node()->first_node();
	std::vector< ObjectInfo > chinfo;
	do
	{
		rapidxml::xml_node< char > * chunkMap = nodeMap->first_node();
		chinfo = std::vector< ObjectInfo >();
		if( !chunkMap ) continue;

		ObjectInfo info;
		do
		{
			auto atribute = chunkMap->first_attribute();
			info = _defInfo.at( atribute->value() );
			do
			{
				parseObjAttribute( atribute, info );
			}while( atribute = atribute->next_attribute() );

			rapidxml::xml_node< char > * slavNodeObjs = chunkMap->first_node();
			if( slavNodeObjs )
			{
				ObjectInfo slaveinfo;
				do
				{
					auto atributeSlave = slavNodeObjs->first_attribute();
					slaveinfo = _defInfo.at( atributeSlave->value() );
					do
					{
						parseObjAttribute( atributeSlave, slaveinfo );
					}while( atributeSlave = atributeSlave->next_attribute() );
				}while( info.slaves.push_back( slaveinfo ), slavNodeObjs = slavNodeObjs->next_sibling() );
			}
		}while( chinfo.push_back( info ), chunkMap = chunkMap->next_sibling() );
	}while( _level.push_back( chinfo ), nodeMap = nodeMap->next_sibling() );
}

void
Cache::parseResNode( rapidxml::xml_node< char > * node, ObjRes & res, Lab lab, const std::string & objName, const std::string & key ) const
{
	std::string type = node->name();

	if( type == "representation" )
	{
		std::string representationType = node->first_attribute()->value();
		if( representationType == "sprite")
		{
			#ifdef COCOS2D_DEBUG

			std::string spriteRepresentationPath = "Debug/Act/Objects/" + toString( lab ) + "/" + objName + "/Rpr/sprite.png";

			#else

			std::string spriteRepresentationPath = "Release/Act/Objects/" + toString( lab ) + "/" + objName + "/Rpr/ev.xxx";

			#endif

			auto spriteRepresentation = readFile( spriteRepresentationPath );
			res.representation.sprite = decryptFile( spriteRepresentation, key );
		}
		else
		{
			int imagesCount = atoi( node->first_attribute()->next_attribute()->value() );
			#ifdef COCOS2D_DEBUG

			std::string dataSkeletonRepresentationPath = "Debug/Act/Objects/" + toString( lab ) + "/" + objName + "/Rpr/skeleton.json";
			std::string atlasSkeletonRepresentationPath = "Debug/Act/Objects/" + toString( lab ) + "/" + objName + "/Rpr/skeleton.atlas";
			std::vector< std::string > imageSkeletonRepresentationPaths;
			imageSkeletonRepresentationPaths.push_back( "Debug/Act/Objects/" + toString( lab ) + "/" + objName + "/Rpr/skeleton.png" );
			for( int i = 2; i <= imagesCount; ++i )
				imageSkeletonRepresentationPaths.push_back( "Debug/Act/Objects/" + toString( lab ) + "/" + objName + "/Rpr/skeleton" + ThirdParty::toString( i ) + ".png" );

			#else

			std::string dataSkeletonRepresentationPath = "Release/Act/Objects/" + toString( lab ) + "/" + objName + "/Rpr/eve.xxx";
			std::string atlasSkeletonRepresentationPath = "Release/Act/Objects/" + toString( lab ) + "/" + objName + "/Rpr/eva.xxx";
			std::vector< std::string > imageSkeletonRepresentationPaths;
			for( int i = 1; i <= imagesCount; ++i )
				imageSkeletonRepresentationPaths.push_back( "Release/Act/Objects/" + toString( lab ) + "/" + objName + "/Rpr/ev" +  ThirdParty::toString( i ) + ".xxx" );

			#endif

			auto dataSkeletonRepresentation = readFile( dataSkeletonRepresentationPath );
			res.representation.skeleton.data = decryptFile( dataSkeletonRepresentation, key );

			auto atlasSkeletonRepresentation = readFile( atlasSkeletonRepresentationPath );
			res.representation.skeleton.atlas = decryptFile( atlasSkeletonRepresentation, key );

			for( auto imageSkeletonRepresentationPath : imageSkeletonRepresentationPaths)
			{
				auto imageSkeletonRepresentation = readFile( imageSkeletonRepresentationPath );
				res.representation.skeleton.images.push_back( decryptFile( imageSkeletonRepresentation, key ) );
			}
		}

	}

	if( type == "physic" )
	{
		rapidxml::xml_node< char > * bodyNode = node->first_node();
		do
		{
			std::string bodyName = bodyNode->first_attribute()->value();

			#ifdef COCOS2D_DEBUG

			std::string bodyPath = "Debug/Act/Objects/" + toString( lab ) + "/" + objName + "/Bds/" + bodyName + "/body.json";

			#else

			std::string bodyPath = "Release/Act/Objects/" + toString( lab ) + "/" + objName + "/Bds/" + bodyName + "/ev.xxx";

			#endif

			auto body = readFile( bodyPath );
			res.bodies.insert( { bodyName, decryptFile( body, key ) } );
		
		}while( bodyNode = bodyNode->next_sibling() );
	}
	
	if( type == "animation" )
	{
		rapidxml::xml_node< char > * animNode = node->first_node();
		do
		{
			std::string animName = animNode->first_attribute()->value();

			std::vector< UnitedResourcesData > anim;
			int size = atoi( animNode->first_attribute()->next_attribute()->value() );
			float duration = atof( animNode->first_attribute()->next_attribute()->next_attribute()->value() );
			for( int i = 1; i <= size; ++i )
			{
				#ifdef COCOS2D_DEBUG

				std::string animPath = "Debug/Act/Objects/" + toString( lab ) + "/" + objName + "/Anm/" + animName + "/sprite" + ThirdParty::toString( i ) + ".png";

				#else

				std::string animPath = "Release/Act/Objects/" + toString( lab ) + "/" + objName + "/Anm/" + animName + "/ev" + ThirdParty::toString( i ) + ".xxx";

				#endif

				auto animData = readFile( animPath );
				anim.push_back( decryptFile( animData, key ) );
			}
			res.anims.insert( { animName, { anim, duration } } );
		
		}while( animNode = animNode->next_sibling() );
	}

	if( type == "audio" )
	{
		rapidxml::xml_node< char > * audioNode = node->first_node();
		do
		{
			std::string audioName = audioNode->first_attribute()->value();

			#ifdef COCOS2D_DEBUG

			std::string audioPath = "Debug/Act/Objects/" + toString( lab ) + "/" + objName + "/Snd/" + audioName + "/audio.wav";

			#else

			std::string audioPath = "Release/Act/Objects/" + toString( lab ) + "/" + objName + "/Snd/" + audioName + "/ev.xxx";

			#endif

			auto sound = readFile( audioPath );
			res.audios.insert( { audioName, decryptFile( sound, key ) } );
		
		}while( audioNode = audioNode->next_sibling() );
	}
}

void
Cache::parseObjAttribute(rapidxml::xml_attribute< char > * objAttr, ObjectInfo & info )
{
	std::string name = objAttr->name();

	if( name == "name" )
		info.name = objAttr->value();

	if( name == "position" )
	{
		std::string posit = objAttr->value();
		int decP = posit.find(';');
		float x =  atof( posit.substr( 0, decP ).data() );
		float y =  atof( posit.substr( decP + 1, posit.length() - decP - 1 ).data() );
		info.position = cocos2d::Vec2( x, y );
	}

	if( name == "size" )
	{
		std::string size = objAttr->value();
		int decS = size.find(';');
		float width =  atof( size.substr( 0, decS ).data() );
		float height =  atof( size.substr( decS + 1, size.length() - decS - 1 ).data() );
		info.size = cocos2d::Vec2( width, height );
	}

	if( name == "rotation" )
		info.angle = atof( objAttr->value() );

	if( name == "scale" )
	{
		std::string scale = objAttr->value();
		int decS = scale.find(';');
		float width =  atof( scale.substr( 0, decS ).data() );
		float height =  atof( scale.substr( decS + 1, scale.length() - decS - 1 ).data() );
		info.scale = cocos2d::Vec2( width, height );
	}

	if( name == "zindex" )
		info.zIndex = atoi( objAttr->value() );

	if( name == "mask" )
		info.mask = atoi( objAttr->value() );

	if( name == "collide" )
		info.collideMask = atoi( objAttr->value() );

	if( name == "contact" )
		info.contactMask = atoi( objAttr->value() );

	if( name == "additional" )
		info.additionalParam = objAttr->value();

	if( name == "action" )
		info.initAction = objAttr->value();
}

void
Cache::parseLevelAttribute( rapidxml::xml_attribute< char > * levelAttr )
{
	std::string name = levelAttr->name();

	if( name == "name" )
		_levelName = levelAttr->value();

	if( name == "orientation" )
	{
		std::string orientation = levelAttr->value();
		_levelOrientation = levelOrientationFromString( orientation );
	}

	if( name == "size" )
	{
		std::string size = levelAttr->value();
		std::string width = ThirdParty::readToken( size );
		std::string height = ThirdParty::readToken( size );
		_levelSize = cocos2d::Vec2( atof( width.data() ), atof( height.data() ) );
	}

	if( name == "gravity" )
	{
		std::string gravity = levelAttr->value();
		std::string x = ThirdParty::readToken( gravity );
		std::string y = ThirdParty::readToken( gravity );
		_levelGravity = cocos2d::Vec2( atof( x.data() ), atof( y.data() ) );
	}
}

UnitedResourcesData
Cache::readFile( const std::string & fileName ) const
{
	auto content = cocos2d::FileUtils::getInstance()->getDataFromFile( fileName );

	return UnitedResourcesData( content.getBytes(), content.getSize() );
}

UnitedResourcesData
Cache::readBlock( UnitedResourcesData & data, unsigned int blockSize ) const
{
	UnitedResourcesData result;
	if( data.size() < blockSize )
	{
		result = data;
		data = UnitedResourcesData();
	}
	else
	{
		result = UnitedResourcesData( data.data(), blockSize );
		data.move( blockSize );
	}

	return result;
}

UnitedResourcesData
Cache::decryptFile( UnitedResourcesData & data, const std::string & key ) const
{
	#ifdef COCOS2D_DEBUG

	return data;

	#else

	unsigned int i = 0, by = 0;
	char ch, keyc[32];
	char * cp = const_cast< char* >( key.data() );
	while(i < 64 && *cp)        // the maximum key length is 32 bytes and
    {                           // hence at most 64 hexadecimal digits
        ch = toupper(*cp++);    // process a hexadecimal digit
        if(ch >= '0' && ch <= '9')
            by = (by << 4) + ch - '0';
        else if(ch >= 'A' && ch <= 'F')
            by = (by << 4) + ch - 'A' + 10;

        // store a key byte for each pair of hexadecimal digits
        if(i++ & 1)
            keyc[i / 2 - 1] = by & 0xff;
    }

	AESdecrypt decrypt;
	decrypt.key( (unsigned char*)keyc, i / 2 );

	const int blockLen = 16;

	unsigned char dbuf[3 * blockLen], buf[blockLen];
    unsigned long len, wlen = blockLen;

    // When ciphertext stealing is used, we three ciphertext blocks so
    // we use a buffer that is three times the block length.  The buffer
    // pointers b1, b2 and b3 point to the buffer positions of three
    // ciphertext blocks, b3 being the most recent and b1 being the
    // oldest. We start with the IV in b1 and the block to be decrypted
    // in b2.

	unsigned int lenthAll = data.size();
	UnitedResourcesData block = readBlock( data, 2 * blockLen );
	len = block.size();
	memcpy( dbuf, block.data(), len );

    if( len < 2 * blockLen ) // the original file is less than one block in length
    {
        len -= blockLen;
        // decrypt from position len to position len + BLOCK_LEN
        decrypt.decrypt(dbuf + len, dbuf + len);

        // undo the CBC chaining
        for(i = 0; i < len; ++i)
            dbuf[i] ^= dbuf[i + blockLen];

        return UnitedResourcesData( dbuf, len );
    }
    else
    {   unsigned char *b1 = dbuf, *b2 = b1 + blockLen, *b3 = b2 + blockLen, *bt;
		UnitedResourcesData res( lenthAll );

        for( ; ; )  // while some ciphertext remains, prepare to decrypt block b2
        {
            // read in the next block to see if ciphertext stealing is needed
			UnitedResourcesData block = readBlock( data, blockLen );
			len = block.size();
			memcpy( b3, block.data(), len );

            // decrypt the b2 block
            decrypt.decrypt(b2, buf);

            if(len == 0 || len == blockLen)    // no ciphertext stealing
            {
                // unchain CBC using the previous ciphertext block in b1
                for(i = 0; i < blockLen; ++i)
                    buf[i] ^= b1[i];
            }
            else    // partial last block - use ciphertext stealing
            {
                wlen = len;

                // produce last 'len' bytes of plaintext by xoring with
                // the lowest 'len' bytes of next block b3 - C[N-1]
                for(i = 0; i < len; ++i)
                    buf[i] ^= b3[i];

                // reconstruct the C[N-1] block in b3 by adding in the
                // last (BLOCK_LEN - len) bytes of C[N-2] in b2
                for(i = len; i < blockLen; ++i)
                    b3[i] = buf[i];

                // decrypt the C[N-1] block in b3
                decrypt.decrypt(b3, b3);

                // produce the last but one plaintext block by xoring with
                // the last but two ciphertext block
                for(i = 0; i < blockLen; ++i)
                    b3[i] ^= b1[i];

                 res.append( b3, blockLen );
            }

            res.append( buf, wlen );

			if(len != blockLen)
			{
				res.toFit();
                return res;
			}

            // advance the buffer pointers
            bt = b1, b1 = b2, b2 = b3, b3 = bt;
        }
    }

	#endif
}

}