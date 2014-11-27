#ifndef  _GAME_MANAGER_H_
#define  _GAME_MANAGER_H_

#include "cocos2d.h"
#include "BaseTower.h"
#include "BaseMonster.h"

class GameManager
{
public:

	static GameManager* getInstance();

	std::vector<BaseBullet *> bulletList;
	std::vector<BaseMonster *> monsterList;
	std::vector<cocos2d::Vec2> walkPathList;

	void clear();

private:

	GameManager(){};
};

#endif
