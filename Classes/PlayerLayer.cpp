#include "PlayerLayer.h"
#include "FireMonster.h"
#include "IceMonster.h"
#include "RockMonster.h"
#include "AttackTower.h"
#include "MagicTower.h"
#include "ArrowTower.h"
#include "GameManager.h"
#include "MonsterGenerator.h"
#include "LevelLoader.h"
#include "SimpleAudioEngine.h"
#include "LevelSelectScene.h"

USING_NS_CC;
using namespace CocosDenshion; 

#define MAP_TAG 0x0001
#define TOWER_SELECTOR_TAG 0x0002

#define MONEY_LABEL_TAG 0x0010
#define PLAYER_LABEL_TAG 0x0020
#define MONSTER_GROUP_LABEL_TAG 0x0030

#define MONSTER_GENERATOR_TAG 0x0040

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

	//LevelLoader::getInstance()->loadLevelsInfo("levelInfo_0.plist");

	initLevelInfo();
	initToolBar();

	auto levelloader = LevelLoader::getInstance();
	auto bg = Sprite::create(levelloader->getCurBgName());
	bg->setPosition(Vec2(size.width / 2.0f, size.height / 2.0f));
	this->addChild(bg, -2);

	auto map = TMXTiledMap::create(levelloader->getCurMapName());
	auto bgLayer = map->getLayer("bg");
	bgLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
	bgLayer->setPosition(Vec2(size.width / 2.0f, size.height / 2.0f));
	this->addChild(map, -1, MAP_TAG);

	initPath(map);

	auto touchListenser = EventListenerTouchOneByOne::create();
	touchListenser->onTouchBegan = CC_CALLBACK_2(PlayerLayer::onOneTouchBegan, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListenser, this);

	auto mg = MonsterGenerator::create();
	this->addChild(mg, 10, MONSTER_GENERATOR_TAG);
	mg->generateMonsterGroup(levelloader->getCurGroupNum(), 5.0f);
	mg->setObserver(this);
	_oneMonsterGroupGenerated = false;

	SimpleAudioEngine::getInstance()->playBackgroundMusic(FileUtils::getInstance()->fullPathForFilename("sound/music.mp3").c_str(), true);
	//_backGroundMusicID = SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/music.mp3").c_str(), true);

	scheduleUpdate();
	return true;
}

void PlayerLayer::initPath(cocos2d::TMXTiledMap *map)
{
	Size size = Director::getInstance()->getWinSize();
	auto offset = (map->getContentSize().width - size.width) / 2.0f;
	auto objects = map->getObjectGroup("obj");
	int count = 0;
	char str[16];
	sprintf(str, "%d", count);
	auto point = objects->getObject(str);
	while (point.begin() != point.end())
	{
		float x = point.at("x").asFloat() - offset;
		float y = point.at("y").asFloat();
		GameManager::getInstance()->walkPathList.push_back(Vec2(x, y));
		++count;
		sprintf(str, "%d", count);
		point = objects->getObject(str);
	}
}

void PlayerLayer::update( float deltaTime )
{
	collisionDetection();

	if (_oneMonsterGroupGenerated && GameManager::getInstance()->monsterList.empty()){

		int cur = LevelLoader::getInstance()->getCurGroupNum();
		if (++cur < LevelLoader::getInstance()->getGroupNum()){
			LevelLoader::getInstance()->setCurGroupNum(cur);
			MonsterGenerator *mg = static_cast<MonsterGenerator *>(this->getChildByTag(MONSTER_GENERATOR_TAG));
			mg->generateMonsterGroup(cur, 5.0f);
			updateMonsterGroup(1);
		}
		else{
			//Level Over
			GameManager::getInstance()->clear();
			Director::getInstance()->replaceScene(CCTransitionFade::create(0.5, LevelSelectScene::create()));
		}
		_oneMonsterGroupGenerated = false;
	}
}

void PlayerLayer::collisionDetection()
{
	std::vector<BaseBullet *> needRemovedBullets;
	std::vector<BaseMonster *> needRemovedMonster;

	for (unsigned int bt = 0; bt < GameManager::getInstance()->bulletList.size(); ++bt){
		for (unsigned int ms = 0; ms < GameManager::getInstance()->monsterList.size(); ++ms){
			BaseBullet *bullet = GameManager::getInstance()->bulletList[bt];
			BaseMonster *monster = GameManager::getInstance()->monsterList[ms];
			if (bullet->hitTarget(monster))
			{
				needRemovedBullets.push_back(bullet);
				//GameManager::getInstance()->bulletList.erase(GameManager::getInstance()->bulletList.begin() + bt);

				if (monster->getCurrHp() > 0){
					int monsterHP = monster->getCurrHp() - bullet->getLethality();
					monster->setCurrHp(monsterHP);
					monster->updateHpBar();
					if (monsterHP <= 0){
						needRemovedMonster.push_back(monster);
						//GameManager::getInstance()->monsterList.erase(GameManager::getInstance()->monsterList.begin() + ms);
					}
				}
				break;
			}
		}
	}

	for (auto iter : needRemovedBullets){
		iter->removeBullet();
	}

	for (auto iter : needRemovedMonster){
		iter->dead();
		updateMoney(50);
	}
}

bool PlayerLayer::onOneTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event )
{
	this->removeChildByTag(TOWER_SELECTOR_TAG);
	Vec2 tileLoc;
	if (canPutTower(touch, tileLoc)){
		auto ts = TowerSelector::create();
		ts->setPosition(tileLoc);
		ts->createTowerCallback = CC_CALLBACK_2(PlayerLayer::createTower, this);
		this->addChild(ts, 0, TOWER_SELECTOR_TAG);
		return true;
	}
	else{
		auto tips = Sprite::createWithSpriteFrameName("no.png");
		tips->setPosition(tileLoc);
		this->addChild(tips);
		tips->runAction(Sequence::create(DelayTime::create(0.8f),
			CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
			NULL));
	}
	return false;
}

bool PlayerLayer::canPutTower( cocos2d::Touch *touch, Vec2 &touchTileLoc)
{
	Size size = Director::getInstance()->getWinSize();
	auto map = static_cast<cocos2d::TMXTiledMap *>(this->getChildByTag(MAP_TAG));
	auto offset = (map->getContentSize().width - size.width) / 2.0f;
	auto bgLayer = map->getLayer("bg");

	auto location = touch->getLocation();
	auto inMap = convertToMapTile(location);
	int gid = bgLayer->getTileGIDAt(inMap);
	auto tileWidth = map->getContentSize().width / map->getMapSize().width;
	auto tileHeight = map->getContentSize().height / map->getMapSize().height;
	touchTileLoc = Point((inMap.x * tileWidth) + tileWidth/2 - offset, map->getContentSize().height - (inMap.y * tileHeight) - tileHeight/2);

	bool touchValue = false;
	auto finder = std::find(_filledVec.begin(), _filledVec.end(), touchTileLoc);
	if (map->getPropertiesForGID(gid).getType() == Value::Type::MAP && finder == _filledVec.end()){
		auto tileAttri = map->getPropertiesForGID(gid).asValueMap();
		touchValue = tileAttri.at("canTouch").asBool();
	}
	return touchValue;
}

cocos2d::Vec2 PlayerLayer::convertToMapTile( const Vec2 &inWorld )
{
	auto map = static_cast<cocos2d::TMXTiledMap *>(this->getChildByTag(MAP_TAG));
	Size size = Director::getInstance()->getWinSize();
	auto offset = (map->getContentSize().width - size.width) / 2.0f;

	int x = (inWorld.x + offset) / map->getContentSize().width * map->getMapSize().width;
	int y = map->getMapSize().height - inWorld.y / map->getContentSize().height * map->getMapSize().height;
	return Vec2(x, y);
}

void PlayerLayer::createTower( TowerSelector *ts, TowerType tType )
{
	bool noEnoughMoney = false;
	switch (tType)
	{
	case ARROW_TOWER:
		{
			if (_money >= 200){
				auto at = ArrowTower::create();
				at->setPosition(ts->getPosition());
				this->addChild(at);
				_filledVec.push_back(ts->getPosition());
				updateMoney(-200);
			}
			else{
				noEnoughMoney = true;
			}
		}
		break;
	case ATTACK_TOWER:
		{
			if (_money >= 150){
				auto att = AttackTower::create();
				att->setPosition(ts->getPosition());
				this->addChild(att);
				_filledVec.push_back(ts->getPosition());
				updateMoney(-150);
			}
			else{
				noEnoughMoney = true;
			}
		}
		break;
	case MAGIC_TOWER:
		{
			if (_money >= 500){
				auto mt = MagicTower::create();
				mt->setPosition(ts->getPosition());
				this->addChild(mt);
				_filledVec.push_back(ts->getPosition());
				updateMoney(-500);
			}
			else{
				noEnoughMoney = true;
			}
		}
		break;
	case ANOTHER:
	default:
		break;
	}

	if (noEnoughMoney){
		auto tips = Sprite::createWithSpriteFrameName("nomoney_mark.png");
		tips->setPosition(ts->getPosition());
		this->addChild(tips);
		tips->runAction(Sequence::create(DelayTime::create(0.5f),
			CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
			NULL));
	}
}

void PlayerLayer::initToolBar()
{
	char str[16];
	auto size = Director::getInstance()->getWinSize();
	auto toolLayer = Layer::create();
	this->addChild(toolLayer);
	// 工具栏背景图片
	_toolBar = Sprite::createWithSpriteFrameName("toolbg.png");
	_toolBar->setAnchorPoint(Point(0.5f, 1));
	_toolBar->setPosition (Point(size.width / 2, size.height));
	toolLayer->addChild(_toolBar);   
	// 金币数
	auto moneyLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
	moneyLabel->setPosition(Point(_toolBar->getContentSize().width / 8, _toolBar->getContentSize().height / 2));
	moneyLabel->setAnchorPoint(Point(0, 0.5f));
	sprintf(str, "%d", _money);
	moneyLabel->setString(str);
	_toolBar->addChild(moneyLabel, 0, MONEY_LABEL_TAG);   
	// 玩家血量条
	auto playHpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("playhp.png"));
	playHpBar->setType(ProgressTimer::Type::BAR);
	playHpBar->setMidpoint(Point(0, 0.4f));
	playHpBar->setBarChangeRate(Point(1, 0));
	playHpBar->setPercentage(_playerHp);
	playHpBar->setPosition(Point(_toolBar->getContentSize().width / 5 *4  , _toolBar->getContentSize().height / 2));
	_toolBar->addChild(playHpBar, 0, PLAYER_LABEL_TAG);
	// 玩家得分标尺  
	auto star = Sprite::createWithSpriteFrameName("playstar.png");
	star->setPosition(Point(_toolBar->getContentSize().width / 5 *4 , _toolBar->getContentSize().height / 2));
	_toolBar->addChild(star);    
	// 当前波数
	auto groupLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
	groupLabel->setPosition(Point(_toolBar->getContentSize().width / 8 * 3, _toolBar->getContentSize().height / 2 ));
	groupLabel->setAnchorPoint(Point(0.5f , 0.5f));
	sprintf(str, "%d", _currentMonsterGroup);
	groupLabel->setString(str);
	_toolBar->addChild(groupLabel, 0, MONSTER_GROUP_LABEL_TAG);
	// 总波数
	auto groupTotalLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
	groupTotalLabel->setPosition(Point(_toolBar->getContentSize().width / 2 , _toolBar->getContentSize().height / 2 ));
	groupTotalLabel->setAnchorPoint(Point(0.5f , 0.5f));
	sprintf(str, "%d", _totalMonsterGroup);
	groupTotalLabel->setString(str);
	_toolBar->addChild(groupTotalLabel);

	// back
	Sprite *backItem1 = CCSprite::createWithSpriteFrameName("playbutton1.png");
	Sprite *backItem2 = CCSprite::createWithSpriteFrameName("playbutton2.png");
	MenuItemSprite *pPauseItem = MenuItemSprite::create(backItem1, backItem2, CC_CALLBACK_1(PlayerLayer::menuBackCallback, this));
	pPauseItem->setPosition(Point(_toolBar->getContentSize().width - backItem1->getContentSize().width/2, _toolBar->getContentSize().height / 2));
	pPauseItem->setAnchorPoint(Point(0, 0.4f));
	Menu* pMenu = Menu::create(pPauseItem, NULL);
	pMenu->setPosition(Point::ZERO);
	_toolBar->addChild(pMenu);
}

void PlayerLayer::initLevelInfo()
{
	_money = LevelLoader::getInstance()->getMoney();
	_totalMonsterGroup = LevelLoader::getInstance()->getGroupNum();
	_currentMonsterGroup = 1;
	_playerHp = 100.0f;
}

void PlayerLayer::updateMoney( int delta )
{
	_money += delta;
	auto label = static_cast<Label *>(_toolBar->getChildByTag(MONEY_LABEL_TAG));
	char str[16];
	sprintf(str, "%d", _money);
	label->setString(str);
}

void PlayerLayer::updatePlayerHp( float delta )
{
	_playerHp += delta;
	if (_playerHp < 0.0f) _playerHp = 0.0f;

	auto label = static_cast<ProgressTimer *>(_toolBar->getChildByTag(PLAYER_LABEL_TAG));
	label->setPercentage(_playerHp);
}

void PlayerLayer::updateMonsterGroup( int delta )
{
	_currentMonsterGroup += delta;
	auto label = static_cast<Label *>(_toolBar->getChildByTag(MONSTER_GROUP_LABEL_TAG));
	char str[16];
	sprintf(str, "%d", _currentMonsterGroup);
	label->setString(str);
}

void PlayerLayer::monsterWin( BaseMonster *bm )
{
	bm->dead();
	updatePlayerHp(-10.0f);
	if (_playerHp <= 0.0f){
		//fail
		GameManager::getInstance()->clear();
		Director::getInstance()->replaceScene(CCTransitionFade::create(0.5, LevelSelectScene::create()));
	}
}

void PlayerLayer::oneMonsterGroupGenerated(MonsterGenerator *mg)
{
	_oneMonsterGroupGenerated = true;
}

void PlayerLayer::menuBackCallback( Ref* pSender )
{
	//SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
	GameManager::getInstance()->clear();
	Director::getInstance()->replaceScene(CCTransitionFade::create(0.5, LevelSelectScene::create()));
}

PlayerLayer::~PlayerLayer()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	//SimpleAudioEngine::getInstance()->stopEffect(_backGroundMusicID);
}
