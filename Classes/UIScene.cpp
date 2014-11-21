#include "UIScene.h"
#include "PlayerLayer.h"

USING_NS_CC;
Scene* UIScene::createScene()
{
	auto scene = Scene::create();
	scene->addChild(UIScene::create());
	return scene;
}

bool UIScene::init()
{
	if (!Layer::init()) return false;

	Size size = CCDirector::getInstance()->getWinSize();  

	auto sprite = Sprite::create("playbg.png");
	sprite->setPosition(Vec2(size.width / 2.0f, size.height / 2.0f));
	this->addChild(sprite, -1);

	auto title = Sprite::createWithSpriteFrameName("title.png");
	title->setPosition(Vec2(size.width / 3.0f, size.height / 3.0f * 2.0f));
	this->addChild(title);
	auto move = JumpBy::create(1.0f, Vec2(0.0f, 0.0f), 10.0f, 1);
	title->runAction(RepeatForever::create(move));

	auto startItem = MenuItemImage::create("start_1.png", "start_2.png", CC_CALLBACK_1(UIScene::menuStartCallback, this));
	startItem->setPosition(Point((size.width -  startItem->getContentSize().width)/ 2, size.height / 6));
	startItem->setAnchorPoint(Point(0, 0));
	auto menu = Menu::create(startItem, nullptr);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	auto starSprite = Sprite::createWithSpriteFrameName("star.png");
	starSprite->setScale(0.7f);
	this->addChild(starSprite);

	auto emitter = ParticleSystemQuad::create("button.plist");
	emitter->retain();
	ParticleBatchNode *batch = ParticleBatchNode::createWithTexture(emitter->getTexture());
	batch->addChild(emitter);
	starSprite->setPosition(Point(startItem->getPosition().x, startItem->getPosition().y));

	emitter->setPosition(Point(startItem->getPosition().x, startItem->getPosition().y ));
	auto path = PathFun( 1, startItem->getContentSize().height, startItem->getContentSize().width /*+ starSprite->getContentSize().width*/);
	starSprite->runAction(path);
	emitter->runAction(path->clone());
	addChild(batch);

	return true;
}

void UIScene::menuStartCallback( Ref* pSender )
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.2f, PlayerLayer::createScene()));
}

RepeatForever* UIScene::PathFun( float controlX, float controlY, float w )
{
	ccBezierConfig bezier1;
	bezier1.controlPoint_1 = Point(-controlX, 0);
	bezier1.controlPoint_2 = Point(-controlX, controlY);
	bezier1.endPosition = Point(0, controlY);
	auto bezierBy1 = BezierBy::create(0.6f, bezier1);

	auto move1 = MoveBy::create(0.7f, Point(w, 0));

	ccBezierConfig bezier2;
	bezier2.controlPoint_1 = Point(controlX, 0);
	bezier2.controlPoint_2 = Point(controlX, -controlY);
	bezier2.endPosition = Point(0, -controlY);
	auto bezierBy2 = BezierBy::create(0.6f, bezier2);
	auto move2 = MoveBy::create(0.7f, Point(-w, 0));
	auto path = RepeatForever::create(Sequence::create(bezierBy1, move1, bezierBy2, move2, NULL));
	return path;
}
