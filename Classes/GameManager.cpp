#include "GameManager.h"

USING_NS_CC;

GameManager* GameManager::getInstance()
{
	static GameManager gm;
	return &gm;
}