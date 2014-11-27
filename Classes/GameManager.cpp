#include "GameManager.h"

USING_NS_CC;

GameManager* GameManager::getInstance()
{
	static GameManager gm;
	return &gm;
}

void GameManager::clear()
{
	bulletList.clear();
	monsterList.clear();
	walkPathList.clear();
}
