#include "Serializer.hpp"

#include "ThirdParty/Functions/StringFunctions.hpp"

#include <cocos2d.h>

#include <fstream>

namespace Resources
{

Serializer &
Serializer::getInstance()
{
	static Serializer instance;
	return instance;
}

Serializer::Serializer()
{
	const std::string KEY = "E397CC908B984D8B01B876FDCC91AFE7";

	std::string path = cocos2d::FileUtils::getInstance()->getWritablePath() + "ev.xxx";

	std::ifstream fin( path );
	bool isStartUp = !fin.is_open();
	fin.close();

	sqlite3_open( path.data(), & _connection );
	if( isStartUp )
		startupInit();
	sqlite3_key( _connection, KEY.data(), 32 );
}

Serializer::~Serializer()
{
	sqlite3_close( _connection );
}

void
Serializer::startupInit()
{
	const std::string KEY = "E397CC908B984D8B01B876FDCC91AFE7";

	// Worlds initialize
	std::string query =
		std::string( "CREATE TABLE 'Worlds'(\n" ) +
		"name TEXT PRIMARY KEY NOT NULL,\n" +
		"description TEXT PRIMARY KEY NOT NULL,\n" +
		"totalLevelsCount INT NOT NULL,\n" +
		"finishedLevelsCount INT NOT NULL,\n" +
		"totalWorldPrice INT NOT NULL,\n" +
		"policy TEXT NOT NULL);";		
	sqlite3_exec( _connection, query.data(), nullptr, nullptr, nullptr );

	// Skins initialize
	query =
		std::string( "CREATE TABLE 'Skins'(\n" ) +
		"name TEXT PRIMARY KEY NOT NULL,\n" +
		"description TEXT PRIMARY KEY NOT NULL,\n" +
		"colecteable INT NOT NULL,\n" +
		"policy TEXT NOT NULL);";
	sqlite3_exec( _connection, query.data(), nullptr, nullptr, nullptr );

	// levels initialize
	query =
		std::string( "CREATE TABLE 'Levels'(\n" ) +
	   "name TEXT PRIMARY KEY NOT NULL,\n" +
	   "world TEXT NOT NULL,\n" +
	   "levelIndex INT NOT NULL,\n" +
	   "totalRewardsCount INT NOT NULL,\n" +
	   "colectedRewardCount INT NOT NULL,\n" +
	   "policy TEXT NOT NULL);";		
	sqlite3_exec( _connection, query.data(), nullptr, nullptr, nullptr );

	// game initialize
	query =
		std::string( "CREATE TABLE 'Game'(\n" ) +
		"version FLOAT PRIMARY KEY NOT NULL,\n" +
		"totalMagicBeansCount INT NOT NULL,\n" +
		"policy TEXT NOT NULL);";	
	sqlite3_exec( _connection, query.data(), nullptr, nullptr, nullptr );

	sqlite3_rekey( _connection, KEY.data(), 32 );
}

std::vector< Data::LabInfo >
Serializer::selectLabsData()
{
	std::vector< Data::LabInfo > labsData;

	sqlite3_stmt *stmt;
	sqlite3_prepare( _connection, "SELECT name, description, totalLevelsCount, finishedLevelsCount, totalWorldPrice, policy from 'Worlds'", -1, &stmt, nullptr );
	while ( sqlite3_step( stmt ) == SQLITE_ROW )
	{
		Data::LabInfo info;
		info.name = (char * ) sqlite3_column_text( stmt, 0 );
		info.description = (char * ) sqlite3_column_text( stmt, 1 );
		info.totalLevelsCount = sqlite3_column_int( stmt, 2 );
		info.finishedLevelsCount = sqlite3_column_int( stmt, 3 );
		info.totalWorldPrice = sqlite3_column_int( stmt, 4 );
		info.policy = policyFromString( (char * ) sqlite3_column_text( stmt, 5 ) );

		labsData.push_back( info );
	}
	sqlite3_finalize( stmt );

	return labsData;
}

std::vector< Data::LevelInfo >
Serializer::selectLevelsData()
{
	std::vector< Data::LevelInfo > levelsInfo;

	sqlite3_stmt *stmt;
	std::string query = "SELECT name, world, index, totalRewardsCount, colectedRewardCount, policy from 'Levels'";
	sqlite3_prepare( _connection, query.data(), -1, &stmt, nullptr );
	while ( sqlite3_step( stmt ) == SQLITE_ROW )
	{
		Data::LevelInfo info;
		info.name = (char * ) sqlite3_column_text( stmt, 0 );
		info.lab = labFromString( (char * ) sqlite3_column_int( stmt, 1 ) );
		info.index = sqlite3_column_int( stmt, 2 );
		info.totalRewardsCount = sqlite3_column_int( stmt, 3 );
		info.colectedRewardCount = sqlite3_column_int( stmt, 4 );
		info.policy = policyFromString( (char * ) sqlite3_column_text( stmt, 5 ) );

		levelsInfo.push_back( info );
	}
	sqlite3_finalize( stmt );

	return levelsInfo;
}

Data::GameInfo
Serializer::selectGameData()
{
	Data::GameInfo gameData;

	sqlite3_stmt *stmt;
	sqlite3_prepare( _connection, "SELECT version, totalMagicBeansCount, policy from 'Game'", -1, &stmt, nullptr );
	gameData.version = sqlite3_column_double( stmt, 0 );
	gameData.totalMagicBeansCount = sqlite3_column_int( stmt, 1 );
	gameData.policy = policyFromString( (char * ) sqlite3_column_text( stmt, 2 ) );
	sqlite3_finalize( stmt );

	return gameData;
}

void
Serializer::updateLabsData( const std::vector< Data::LabInfo > & data )
{
	sqlite3_exec( _connection, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr );
	for( auto info : data)
	{
		std::string query =
			std::string( "UPDATE 'Worlds'\n" ) +
			"SET finishedLevelsCount = '" + ThirdParty::toString( info.finishedLevelsCount ) + "'\n" +
			"SET policy = '" + toString( info.policy ) + "'\n" +
			"WHERE name = '" + info.name + "'\n";
		
		sqlite3_exec( _connection, query.data(), nullptr, nullptr, nullptr );
	}
	sqlite3_exec( _connection, "END TRANSACTION;", nullptr, nullptr, nullptr );
}

void
Serializer::updateLevelsData( const std::vector< Data::LevelInfo > & data )
{
	sqlite3_exec( _connection, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr );
	for( auto info : data )
	{
	std::string query =
		std::string( "UPDATE 'Levels'\n" ) +
		"SET policy = '" +  toString( info.policy ) + "'\n" +
		"SET colectedRewardCount = '" +  ThirdParty::toString( info.colectedRewardCount ) + "'\n" +
		"WHERE world = '" + toString( info.lab ) + "' AND index = '" + ThirdParty::toString( info.index ) + "'\n";
		
	sqlite3_exec( _connection, query.data(), nullptr, nullptr, nullptr );
	}
	sqlite3_exec( _connection, "END TRANSACTION;", nullptr, nullptr, nullptr );
}

void
Serializer::updateGameData( const Data::GameInfo & data )
{
	std::string query =
		std::string( "UPDATE 'Game'\n" ) +
		"SET totalMagicBeansCount = '" + ThirdParty::toString( data.totalMagicBeansCount ) + "'\n" +
		"SET policy = '" + toString( data.policy ) + "'\n" +
		"WHERE version = '" + ThirdParty::toString( data.version ) + "'\n";
		
	sqlite3_exec( _connection, query.data(), nullptr, nullptr, nullptr );
}

}