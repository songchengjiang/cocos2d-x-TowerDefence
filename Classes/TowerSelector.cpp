#include "TowerSelector.h"

USING_NS_CC;

bool TowerSelector::init()
{
	if (!Layer::init()) return false;

	_selectedType = TowerType::ANOTHER;

	auto sprite = Sprite::createWithSpriteFrameName("towerPos.png");
	sprite->setPosition(Point(0, 0));
	this->addChild(sprite);

	auto sprite1 = Sprite::createWithSpriteFrameName("ArrowTower1.png");
	sprite1->setTag(TowerType::ARROW_TOWER);
	sprite1->setAnchorPoint( Point(0.5f, 0));
	sprite1->setPosition(Point(-sprite->getContentSize().width, sprite->getContentSize().height/2));
	this->addChild(sprite1);

	auto sprite2 = Sprite::createWithSpriteFrameName("AttackTower1.png");
	sprite2->setTag(TowerType::ATTACK_TOWER);
	sprite2->setAnchorPoint( Point(0.5f, 0));
	sprite2->setPosition(Point(0, sprite->getContentSize().height/2));
	this->addChild(sprite2);

	auto sprite3 = Sprite::createWithSpriteFrameName("MultiDirTower1.png");
	sprite3->setTag(TowerType::MAGIC_TOWER);
	sprite3->setAnchorPoint( Point(0.5f, 0));
	sprite3->setPosition(Point(sprite->getContentSize().width, sprite->getContentSize().height/2));
	this->addChild(sprite3);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(TowerSelector::onOneTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(TowerSelector::onOneTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sprite1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sprite2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sprite3);

	return true;
}

bool TowerSelector::onOneTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event )
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());

	Point locationInNode = target->convertTouchToNodeSpace(touch);
	Size size = target->getContentSize();
	Rect rect = Rect(0, 0, size.width, size.height);

	if (rect.containsPoint(locationInNode))
	{
		target->setOpacity(180);
		return true;
	}
	return false;
}

void TowerSelector::onOneTouchEnded( cocos2d::Touch* touch, cocos2d::Event* event )
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	target->setOpacity(255);
	if (createTowerCallback != nullptr)
		createTowerCallback(this, static_cast<TowerType>(target->getTag()));

	this->removeFromParent();
}
