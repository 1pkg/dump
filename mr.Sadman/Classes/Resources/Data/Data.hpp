#ifndef __RESOURCES_DATA_HPP__
#define __RESOURCES_DATA_HPP__

#include "Resources/Forward.hpp"

#include "ThirdParty/noncopyable.hpp"

#include <string>
#include <unordered_map>

namespace Resources
{

class Data
	: public ThirdParty::noncopyable
{
public:

	struct LabInfo
	{
		std::string name;
		std::string description;

		unsigned int totalLevelsCount;
		unsigned int finishedLevelsCount;

		int totalWorldPrice;

		Policy policy;
	};

	struct LevelInfo
	{
		std::string name;

		Lab lab;
		unsigned int index;

		unsigned int totalRewardsCount;
		unsigned int colectedRewardCount;

		Policy policy;
	};

	struct GameInfo
	{
		double version;

		unsigned int totalMagicBeansCount;

		Policy policy;
	};

public:

	static Data & getInstance();
	~Data();

	const LabInfo & getLabInfo( Lab lab ) const;
	const LevelInfo & getLevelInfo( Lab lab, int levelIndex ) const;
	const GameInfo & getGameInfo() const;

	void setLabsInfo( Lab lab, const LabInfo & worldInfo );
	void setLevelInfo( Lab lab, int levelIndex, const LevelInfo & levelInfo );
	void setGameInfo( const GameInfo & gameInfo );

private:

	Data();

	enum class Status
	{
		MODIFIED,
		NON
	};

	std::unordered_map< std::string, std::pair< LabInfo, Status > > _labsData;
	std::unordered_map< std::string, std::pair< LevelInfo, Status > > _levelsData;
	std::pair< GameInfo, Status > _gameData;
};

}

#endif
