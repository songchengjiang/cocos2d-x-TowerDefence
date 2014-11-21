#ifndef  _GAME_MANAGER_H_
#define  _GAME_MANAGER_H_

#include "cocos2d.h"
#include "BaseTower.h"
#include "BaseMonster.h"

class GameManager
{
public:

	static GameManager* getInstance();

	cocos2d::Vector<BaseBullet *> bulletList;
	cocos2d::Vector<BaseMonster *> monsterList;

private:

	GameManager(){};
};

#endif
