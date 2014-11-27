#include "LevelSelectScene.h"
#include "UIScene.h"
#include "LevelSelectLayer.h"
#include "LevelPage.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion; 

#define LAYER_NUMBER (3)

LevelSelectScene* LevelSelectScene::_instance = nullptr;

LevelSelectScene *LevelSelectScene::getInstance()
{
	if(_instance != NULL){
		return _instance;
	}
	return  NULL;
}

bool LevelSelectScene::init()  
{
	if (!Scene::init())
	{
		return false;
	}
	_instance = this;

	Size size = Director::getInstance()->getWinSize();

	LevelSelectLayer* scrollView = LevelSelectLayer::create();

	for (int i=0; i<LAYER_NUMBER; ++i) {
		if (0==i) {
			auto page = LevelPage::create("selectLevelBg.png", i);
			page->setTag(i);
			scrollView->addPage(page);
		}else if(1==i){
			auto page = LevelPage::create("selectLevelBg1.png", i);
			page->setTag(i);
			scrollView->addPage(page);
		}else if(2==i){
			auto page = LevelPage::create("selectLevelBg2.png", i);
			page->setTag(i);
			scrollView->addPage(page);
		}
	}          

	Sprite* spritebg =Sprite::create("playbg.png");
	spritebg->setPosition(Point(size.width / 2,size.height / 2));
	addChild(spritebg);

	auto closeItem = MenuItemImage::create(
		"btn_back.png",
		"btn_back_press.png",
		CC_CALLBACK_1(LevelSelectScene::menuCloseCallback, this));
	closeItem->setPosition(Point(40, 40));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);

	this->addChild(scrollView);

	auto selectHouse =Sprite::create("House.png");
	selectHouse->setPosition(Point(size.width / 5 * 4, size.height / 5));
	addChild(selectHouse);

	auto width = Sprite::createWithSpriteFrameName("page_mark2.png")->getContentSize().width;
	auto posX = (size.width - width * LAYER_NUMBER) / 2;
	for(int i =0; i < LAYER_NUMBER; i++)
	{
		Sprite* sprite =Sprite::createWithSpriteFrameName("page_mark2.png");
		sprite->setPosition(Point(posX + i * width, size.height / 7));
		addChild(sprite);
	}

	Sprite* spriteMark =Sprite::createWithSpriteFrameName("page_mark1.png");
	spriteMark->setPosition(Point(posX , size.height / 7));
	spriteMark->setTag(888);
	addChild(spriteMark);

	ParticleSystem* m_emitter1 = ParticleSystemQuad::create("snow.plist");
	m_emitter1->retain();
	ParticleBatchNode *batch = ParticleBatchNode::createWithTexture(m_emitter1->getTexture());
	batch->addChild(m_emitter1);
	m_emitter1->setPosition(Point(size.width/2, size.height));
	addChild(batch, 10);
	m_emitter1->release();

	return true;
}  

void LevelSelectScene::menuCloseCallback(Ref* pSender)
{  
	//SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
	CCDirector::getInstance()->replaceScene(CCTransitionFade::create(0.5, UIScene::createScene()));  
}