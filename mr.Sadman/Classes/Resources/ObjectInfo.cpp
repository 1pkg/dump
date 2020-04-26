#include "ObjectInfo.hpp"

namespace Resources
{

ObjectInfo::ObjectInfo()
	: name( "" ), position( cocos2d::Vec2() ), size( cocos2d::Size() ), scale( cocos2d::Vec2( 1.0f, 1.0f ) ), angle( 0.0f ), zIndex( 0 ), mask( 0x0 ), collideMask( 0x0 ), contactMask( 0x0 ), additionalParam( "" ), initAction( "" ), slaves( std::vector< ObjectInfo >() )
{
}

}