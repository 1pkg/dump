#ifndef __GAME_ACT_OBJECT_HPP__
#define __GAME_ACT_OBJECT_HPP__

#include "Resources/Forward.hpp"
#include "Interactors/Interactor.hpp"

#include "ThirdParty/noncopyable.hpp"
#include "ThirdParty/Functions/StringFunctions.hpp"
#include "ThirdParty/Audio/Audio.hpp"

#include <cocos2d.h>

namespace GameAct
{

class Chunk;

class Object :
	public ThirdParty::noncopyable,
	public Interactor
{
public:

	virtual ~Object();

	virtual void initialize();

	virtual cocos2d::Size getSize() const;
	virtual cocos2d::Size getContentSize() const;
	virtual cocos2d::Vec2 getPosition() const;

	virtual std::string getStatus() const;

	virtual std::string getResourcesName() const = 0;
	virtual cocos2d::PhysicsBody * getBody() const;
	virtual ThirdParty::Audio * getAudio() const;

	virtual bool isComposed() const;
	virtual bool isLongObject() const;

	virtual void setPosition( cocos2d::Vec2 position );
	virtual void setSize( cocos2d::Size size );
	virtual void setAdditionalParam( std::string additionalParam );
	virtual void setRotation( float angle );
	virtual void setScale( cocos2d::Vec2 scale ); 
	virtual void setMask( int mask );
	virtual void setColideMask( int colideMask );
	virtual void setContactMask( int contactMask );

	virtual void addSlave( Object * slave );

	virtual void hide();
	virtual void show();

	virtual void attachToChunk( Chunk & chunk, int zIndex );

	virtual void runAction( const std::string & action );

	virtual bool beginContact( Object * object );
	virtual void stepContact( Object * object );
	virtual void separateContact( Object * object );

protected:

	std::string _status;

	cocos2d::Node * _representation;
	ThirdParty::Audio * _audio;

	std::vector< Object * > _slaves;
	Object * _master;

	Chunk * _chunk;
};

}

#endif
