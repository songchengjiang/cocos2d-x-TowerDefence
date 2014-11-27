#include "LevelPage.h"
#include "LevelSelectLayer.h"
#include "SimpleAudioEngine.h" 
#include "LevelLoader.h"
#include "PlayerLayer.h"

USING_NS_CC;
using namespace CocosDenshion; 

#define LEVEL_ROW (3)
#define LEVEL_COL (2)

LevelPage* LevelPage::create(const std::string& bgName, int level)
{
	LevelPage *pRet = new LevelPage();
	if (pRet && pRet->initLevelPage(bgName, level))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool LevelPage::initLevelPage(const std::string& bgName, int level)
{
	if (!Node::init())
	{
		return false;
	}
	auto size = Director::getInstance()->getWinSize();
	auto sprite =Sprite::create(bgName);
	sprite->setPosition(Point(size.width / 2,size.height / 2));
	addChild(sprite,-2);

	Vector<MenuItem*> menuItemVector;
	auto buttonSize = Sprite::create("card_1.png")->getContentSize();
	auto gap = buttonSize.width / 4;
	auto startWidth =( size.width -  LEVEL_ROW* buttonSize.width - (LEVEL_ROW - 1)*gap ) /2 ;
	auto startHeight = ( size.height + (LEVEL_COL - 1) * gap + buttonSize.height * LEVEL_COL ) /2 - buttonSize.height;
	for ( int row = 0; row < LEVEL_COL; row++ )
	{
		auto height = startHeight - ( buttonSize.height + gap ) * row ;
		for ( int col = 0; col < LEVEL_ROW; col++)
		{
			auto width = startWidth + ( buttonSize.width + gap ) * col ;
			auto item = MenuItemImage::create(
				"card_1.png",
				"card_2.png",
				"card_3.png",
				CC_CALLBACK_1(LevelPage::menuStartCallback, this));
			item->setAnchorPoint(Point(0 ,0));
			item->setPosition(Point(width, height));
			item->setTag(row * LEVEL_ROW + col + level * LEVEL_ROW * LEVEL_COL);
			menuItemVector.pushBack( item );
			auto levelNum = UserDefault::getInstance()->getIntegerForKey("levelNum");

			//if(levelNum < row * LEVEL_ROW + col + level * LEVEL_ROW * LEVEL_COL)
			//{
			//	item->setEnabled(false);
			//}
		}
	}
	auto levelMenu = Menu::createWithArray(menuItemVector);
	levelMenu->setPosition(Point::ZERO);
	this->addChild(levelMenu, -1);

	return true;
}

void LevelPage::menuStartCallback(Ref* pSender)
{
	auto button = (MenuItemImage *)pSender;
	//SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);

	char buffer[20] = { 0 };
	sprintf(buffer, "levelInfo_%d.plist", button->getTag());
	std::string strName =  buffer;
	if (LevelLoader::getInstance()->loadLevelsInfo(strName)){
		UserDefault::getInstance()->setStringForKey("nextLevelFile", strName);

		Scene *scene = Scene::create();
		auto layer = PlayerLayer::create();
		scene->addChild(layer);
		auto sence = TransitionFade::create(0.5, scene);

		Director::getInstance()->replaceScene(sence);
	}


}
