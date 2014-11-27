#include "LevelSelectLayer.h"
#include "PlayerLayer.h"
#include "LevelSelectScene.h"

USING_NS_CC;

#define SHORTEST_SLIDE_LENGTH (20)

bool LevelSelectLayer::init()
{
	if (!Layer::init()) return false;

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(LevelSelectLayer::onOneTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(LevelSelectLayer::onOneTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(LevelSelectLayer::onOneTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	WINDOW_WIDTH = Director::getInstance()->getWinSize().width;  
	WINDOW_HEIGHT = Director::getInstance()->getWinSize().height;
	_pageNum = _curPage = 0;

	return true;
}

bool LevelSelectLayer::onOneTouchBegan( Touch *touch, Event *event )
{
	_touchDownPoint = touch->getLocation();
	_touchCurPoint = _touchDownPoint;
	return true;
}

void LevelSelectLayer::onOneTouchMoved( Touch *touch, Event *event )
{
	Point touchPoint = touch->getLocation();
	auto currX = this->getPositionX() + (touchPoint.x - _touchCurPoint.x);
	Point posPoint = Vec2(currX, getPositionY());
	auto dis= fabsf(touchPoint.x - _touchCurPoint.x);
	if (dis >= SHORTEST_SLIDE_LENGTH ) {
		setPosition(posPoint);
	}
	_touchCurPoint = touchPoint;
}

void LevelSelectLayer::onOneTouchEnded( Touch *touch, Event *event )
{
	_touchUpPoint = touch->getLocation();
	auto dis= _touchUpPoint.getDistance(_touchDownPoint);
	auto sprite1 =Sprite::createWithSpriteFrameName("page_mark1.png");
	auto width = sprite1->getContentSize().width;
	if (dis >= SHORTEST_SLIDE_LENGTH )
	{
		int offset = getPositionX() - _curPage * (-WINDOW_WIDTH);
		if (offset > width) {
			if (_curPage > 0) {
				--_curPage;
				Sprite *sprite =  (Sprite *)LevelSelectScene::getInstance()->getChildByTag(888);
				sprite->setPosition(Point(sprite->getPositionX()-width,sprite->getPositionY()));
			}
		}
		else if (offset < -width) {
			if (_curPage < (_pageNum - 1)) {
				++_curPage;
				Sprite *sprite =  (Sprite *)LevelSelectScene::getInstance()->getChildByTag(888);
				sprite->setPosition(Point(sprite->getPositionX()+width,sprite->getPositionY()));
			}
		}
		goToCurrNode();
	}
}

void LevelSelectLayer::addPage( Node *page )
{
	if (page)
	{
		page->setContentSize(Size(WINDOW_WIDTH, WINDOW_HEIGHT));
		page->setPosition(Point(WINDOW_WIDTH * _pageNum, 0));
		this->addChild(page);
		_pageNum++;
	}
}

void LevelSelectLayer::goToCurrNode()
{
	this->runAction(MoveTo::create(0.4f, Vec2(-_curPage * WINDOW_WIDTH, 0)));
}
