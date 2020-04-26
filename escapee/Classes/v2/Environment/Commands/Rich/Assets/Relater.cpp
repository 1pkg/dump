#include "Relater.hpp"
#include <cocos2d.h>

namespace Environment
{

namespace Commands
{

namespace Rich
{

namespace Assets
{

Relater::Relater(supps::Command<structs::Buffer, const std::string &> * fetcher)
	: _featcher(fetcher)
{
}

structs::Buffer
Relater::execute(const std::string & object, const std::string & type)
{
	std::string file = cocos2d::FileUtils::getInstance()->fullPathForFilename(object + '/' + type);
	return _featcher->execute(file);
}

}

}

}

}