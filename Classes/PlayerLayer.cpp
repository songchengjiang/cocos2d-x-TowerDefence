#include "PlayerLayer.h"
#include "FireMonster.h"
#include "IceMonster.h"
#include "RockMonster.h"
#include "AttackTower.h"
#include "MagicTower.h"
#include "ArrowTower.h"
#include "GameManager.h"

USING_NS_CC;

cocos2d::Scene* PlayerLayer::createScene()
{
	auto scene = Scene::create();
	scene->addChild(PlayerLayer::create());
	return scene;
}

bool PlayerLayer::init()
{
	if (!Layer::init()) return false;
	Size size = Director::getInstance()->getWinSize();

	auto bg = Sprite::create("playbg.png");
	bg->setPosition(Vec2(size.width / 2.0f, size.height / 2.0f));
	this->addChild(bg, -2);

	auto map = TMXTiledMap::create("map.tmx");
	auto bgLayer = map->getLayer("bg");
	bgLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
	bgLayer->setPosition(Vec2(size.width / 2.0f, size.height / 2.0f));

	this->addChild(map, -1);

	initPath(map);

	auto fm = FireMonster::create();
	fm->setMovePath(_pathList);
	fm->born();
	fm->move();
	this->addChild(fm);
	GameManager::getInstance()->monsterList.pushBack(fm);

	auto im = IceMonster::create();
	im->setMovePath(_pathList);
	im->born();
	im->move();
	this->addChild(im);
	GameManager::getInstance()->monsterList.pushBack(im);

	auto rm = RockMonster::create();
	rm->setMovePath(_pathList);
	rm->born();
	rm->move();
	this->addChild(rm);
	GameManager::getInstance()->monsterList.pushBack(rm);

	//auto at = ArrowTower::create();
	//at->setPosition(Vec2(size.width / 2.0f, size.height / 2.0f));
	//this->addChild(at);

	//auto mt = MagicTower::create();
	//mt->setPosition(Vec2(size.width / 3.0f, size.height / 2.0f));
	//this->addChild(mt);

	auto att = AttackTower::create();
	att->setPosition(Vec2(size.width / 4.0f, size.height / 2.0f));
	this->addChild(att);

	return true;
}

void PlayerLayer::initPath(cocos2d::TMXTiledMap *map)
{
	Size size = Director::getInstance()->getWinSize();
	auto offset = (map->getContentSize().width - size.width) / 2.0f;
	auto objects = map->getObjectGroup("obj");
	int count = 0;
	auto point = objects->getObject(std::to_string(count));
	while (point.begin() != point.end())
	{
		float x = point.at("x").asFloat() - offset;
		float y = point.at("y").asFloat();
		_pathList.push_back(Vec2(x, y));
		++count;
		point = objects->getObject(std::to_string(count));
	}
}
