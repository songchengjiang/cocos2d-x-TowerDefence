#ifndef  _LEVEL_LOADER_H_
#define  _LEVEL_LOADER_H_

#include "cocos2d.h"

struct LevelMonsterGroup
{
	unsigned int monsterNum[3];//fire ice rock
	int monsterHP[3];
};

class LevelLoader
{
public:

	static LevelLoader* getInstance();
	bool loadLevelsInfo(const std::string &levelPlist);


	LevelLoader();
	~LevelLoader();

	CC_SYNTHESIZE_READONLY(int, _money, Money);
	CC_SYNTHESIZE_READONLY(int, _groupNum, GroupNum);
	CC_SYNTHESIZE(int, _curGroupNum, CurGroupNum);
	CC_SYNTHESIZE_READONLY(std::string, _curMapName, CurMapName);
	CC_SYNTHESIZE_READONLY(std::string, _curBgName, CurBgName);
	CC_SYNTHESIZE_READONLY(std::vector<LevelMonsterGroup>, _monsterGroup, MonsterGroup);

private:

	cocos2d::ValueMap _resource;
	cocos2d::ValueMap _level;
};

#endif
