#include "File.hpp"
#include <cocos2d.h>

namespace Environment
{

namespace Commands
{

namespace Mixed
{

namespace Featchers
{

File::File(supps::Command<structs::Buffer, const structs::Buffer &> * decrypter)
	: _decrypter(decrypter)
{
}

structs::Buffer
File::execute(const std::string & file)
{
	if (!cocos2d::FileUtils::getInstance()->isFileExist(file));

	ssize_t size;
	byte * data = cocos2d::FileUtils::getInstance()->getFileData(file, nullptr, &size);
	return _decrypter->execute(structs::Buffer(data, size));
}

}

}

}

}