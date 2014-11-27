#include "LevelLoader.h"

USING_NS_CC;

LevelLoader::LevelLoader()
{
}


LevelLoader::~LevelLoader(void)
{
}

LevelLoader* LevelLoader::getInstance()
{
	static LevelLoader ll;
	return &ll;
}

bool LevelLoader::loadLevelsInfo( const std::string &levelPlist )
{
	std::string fullPath = FileUtils::getInstance()->fullPathForFilename(levelPlist);
	ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);
	if (dict.empty()) return false;

	_resource = dict["resources"].asValueMap();
	_level = dict["levelInfo"].asValueMap();

	_money =   _level["money"].asFloat();

	ValueMap& groupDict = _level["group"].asValueMap();

	_groupNum = groupDict.size();
	_curGroupNum = 0;

	for (auto iter = groupDict.begin(); iter != groupDict.end(); ++iter)
	{
		ValueMap& group = iter->second.asValueMap();
		std::string spriteFrameName = iter->first;

		LevelMonsterGroup lmg;
		lmg.monsterNum[0] = group["type1Num"].asInt();
		lmg.monsterNum[1] = group["type2Num"].asInt();
		lmg.monsterNum[2] = group["type3Num"].asInt();
		lmg.monsterHP[0] = group["type1Hp"].asInt();
		lmg.monsterHP[1] = group["type2Hp"].asInt();
		lmg.monsterHP[2] = group["type3Hp"].asInt();

		_monsterGroup.push_back(lmg);
	}

	_curMapName =   _resource["map"].asString();
	_curBgName =   _resource["image"].asString();

	return true;
}
