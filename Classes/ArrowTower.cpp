#include "ArrowTower.h"
#include "GameManager.h"
USING_NS_CC;

bool ArrowTower::init()
{
	if (!BaseTower::init()) return false;

	setScope(70);
	setShootIntervalTime(2);

	auto baseplate = Sprite::createWithSpriteFrameName("baseplate.png");
	this->addChild(baseplate);

	_rotateArrow = Sprite::createWithSpriteFrameName("arrow.png");
	_rotateArrow->setPosition(Vec2(0.0f, baseplate->getContentSize().height / 4.0f));
	this->addChild(_rotateArrow);
	this->setContentSize(Size(baseplate->getContentSize().width > _rotateArrow->getContentSize().width? baseplate->getContentSize().width: _rotateArrow->getContentSize().width
		                                , baseplate->getContentSize().height > _rotateArrow->getContentSize().height? baseplate->getContentSize().height: _rotateArrow->getContentSize().height));

	//schedule(schedule_selector(ArrowTower::shootBullet), this->getShootIntervalTime());
	scheduleUpdate();
	return true;
}

void ArrowTower::shootBullet(float dt)
{
	if (!_nearestMonster) return;

	auto targetPos = _nearestMonster->getPosition();
	auto deltaPos = targetPos - this->getPosition();

	auto bullet = ArrowBullet::create();
	bullet->setOrigin(_rotateArrow->getPosition());
	bullet->setDirection(deltaPos);
	bullet->fillBulletTo(this);
	bullet->shoot(true);
}

void ArrowTower::update( float deltaTime )
{
	if (!searchTarget()) return;

	auto targetPos = _nearestMonster->getPosition();
	auto deltaPos = targetPos - this->getPosition();
	auto rotAngle = atan2f(deltaPos.y, deltaPos.x);
	_rotateArrow->setRotation(CC_RADIANS_TO_DEGREES(-rotAngle));
	scheduleOnce(schedule_selector(ArrowTower::shootBullet), this->getShootIntervalTime());
}

bool ArrowBullet::init()
{
	if (!BaseBullet::init()) return false;
	Size size = Director::getInstance()->getWinSize();

	auto arrow = Sprite::createWithSpriteFrameName("arrowBullet.png");
	this->setContentSize(arrow->getContentSize());
	this->addChild(arrow);

	setVelocity(100.0f);
	setLethality(2);
	setShootRange(size.width);
	setOrigin(Vec2::ZERO);
	setDirection(Vec2::ZERO);

	return true;
}
