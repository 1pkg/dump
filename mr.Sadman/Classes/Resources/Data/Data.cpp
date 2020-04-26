#include "Data.hpp"
#include "Serializer.hpp"

#include "ThirdParty/Functions/StringFunctions.hpp"

namespace Resources
{

Data &
Data::getInstance()
{
	static Data data;
	return data;
}

Data::Data()
{
	auto labs = Serializer::getInstance().selectLabsData();
	for( auto lab : labs )	
		_labsData.insert( { lab.name, { lab, Status::NON } } );

	auto levels = Serializer::getInstance().selectLevelsData();
	for( auto level : levels )
		_levelsData.insert( { toString( level.lab ) + '_' + ThirdParty::toString( level.index ), { level, Status::NON } } );

	_gameData = { Serializer::getInstance().selectGameData(), Status::NON };
}

Data::~Data()
{
	std::vector< LevelInfo > levels;
	for( auto level : _levelsData )
	{
		if( level.second.second == Status::MODIFIED )
			levels.push_back( level.second.first );
	}
	Serializer::getInstance().updateLevelsData( levels );

	std::vector< LabInfo > labs;
	for( auto lab : _labsData )
	{
		if( lab.second.second == Status::MODIFIED )
			labs.push_back( lab.second.first );
	}
	Serializer::getInstance().updateLabsData( labs );

	if( _gameData.second == Status::MODIFIED )
		Serializer::getInstance().updateGameData( _gameData.first );
}

const Data::LabInfo &
Data::getLabInfo( Lab lab ) const
{
	return _labsData.at( toString( lab ) ).first;
}

const Data::LevelInfo &
Data::getLevelInfo( Lab lab, int levelIndex ) const
{
	return _levelsData.at( toString( lab ) + ThirdParty::toString( levelIndex ) ).first;
}

const Data::GameInfo &
Data::getGameInfo() const
{
	return _gameData.first;
}

void 
Data::setLabsInfo( Lab lab, const LabInfo & worldInfo )
{
	auto data = _labsData.find( toString( lab ) );
	data->second = { worldInfo, Status::MODIFIED };
}

void
Data::setLevelInfo( Lab lab, int levelIndex, const LevelInfo & levelInfo )
{
	auto data = _levelsData.find( toString( lab ) + ThirdParty::toString( levelIndex ) );
	data->second = { levelInfo, Status::MODIFIED };

	auto worldInfo = getLabInfo( lab );
	//worldInfo.totalLevelsCount = countFinishedLevelsCount( lab );
	setLabsInfo( lab, worldInfo );
}

void
Data::setGameInfo( const GameInfo & gameInfo )
{
	_gameData = { gameInfo, Status::MODIFIED };
}

}