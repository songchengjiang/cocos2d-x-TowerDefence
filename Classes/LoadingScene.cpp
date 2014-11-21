#include "LoadingScene.h"
#include "ResourceLoader.h"
#include "UIScene.h"
#include "PlayerLayer.h"

USING_NS_CC;

cocos2d::Scene* LoadingScene::createScene()
{
	auto scene = Scene::create();
	scene->addChild(LoadingScene::create());
	return scene;
}

bool LoadingScene::init()
{
	if (!Layer::init()) return false;

	createProcessBar();
	ResourceLoader::getInstance()->preLoadingAsync();

	scheduleUpdate();
	return true;
}

void LoadingScene::createProcessBar()
{
	Size size = Director::getInstance()->getWinSize();
	auto bg = Sprite::create("load.png");
	bg->setPosition(size.width / 2.0f, size.height / 2.0f);
	this->addChild(bg);

	_processBar = ProgressTimer::create(Sprite::create("loadBar.png"));
	_processBar->setType(ProgressTimer::Type::BAR);
	_processBar->setMidpoint(Vec2(0.0f, 0.5f));
	_processBar->setBarChangeRate(Vec2(1, 0));
	_processBar->setPercentage(0.0f);
	_processBar->setAnchorPoint(Vec2(0.5f, 0.5f));
	_processBar->setPosition(bg->getContentSize().width / 2.0f, bg->getContentSize().height / 6.0f);
	bg->addChild(_processBar);
}

void LoadingScene::update( float deltaTime )
{
	float precent = (float)ResourceLoader::getInstance()->getLoadedResourceCount() / (float) ResourceLoader::getInstance()->getTotalResourceCount() * 100.0f;
	_processBar->setPercentage(precent);

	if (ResourceLoader::getInstance()->getLoadedResourceCount() == ResourceLoader::getInstance()->getTotalResourceCount())
	{
		auto ts = TransitionFade::create(0.2f, PlayerLayer::createScene());
		Director::getInstance()->replaceScene(ts);
	}
}
