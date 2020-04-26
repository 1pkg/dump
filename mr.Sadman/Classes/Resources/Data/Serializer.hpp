#ifndef __RESOURCES_SERIALIZER_HPP__
#define __RESOURCES_SERIALIZER_HPP__

#include "Data.hpp"

#include "ThirdParty/noncopyable.hpp"
#include "ThirdParty/Sqllite/sqlite3.h"

#include <vector>
#include <unordered_map>

namespace Resources
{

class Serializer
	: public ThirdParty::noncopyable
{
public:

	~Serializer();

	static Serializer & getInstance();

	std::vector< Data::LabInfo > selectLabsData();
	std::vector< Data::LevelInfo > selectLevelsData();
	Data::GameInfo selectGameData();

	void updateLabsData( const std::vector< Data::LabInfo > & data );
	void updateLevelsData( const std::vector< Data::LevelInfo > & data );
	void updateGameData( const Data::GameInfo & data );

private:

	Serializer();
	void startupInit();
	void addStartData();

	sqlite3 * _connection;
};

}

#endif
