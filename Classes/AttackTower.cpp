#include "AttackTower.h"
#include "GameManager.h"
USING_NS_CC;

bool AttackTower::init()
{
	if (!BaseTower::init()) return false;

	setScope(60);
	setShootIntervalTime(1);

	auto multiDirTower = Sprite::createWithSpriteFrameName("attackTower.png");
	this->addChild(multiDirTower);
	this->setContentSize(multiDirTower->getContentSize());

	scheduleUpdate();
	//schedule(schedule_selector(AttackTower::shootBullet), this->getShootIntervalTime());
	return true;
}

void AttackTower::shootBullet(float dt)
{
	if (!_nearestMonster) return;

	auto targetPos = _nearestMonster->getPosition();
	auto deltaPos = targetPos - this->getPosition();

	auto bullet = AttackBullet::create();
	bullet->setOrigin(Vec2(0.0f, this->getContentSize().height / 4.0f));
	bullet->setDirection(deltaPos);
	bullet->fillBulletTo(this);
	bullet->shoot();
}

void AttackTower::update( float deltaTime )
{
	if (!searchTarget()) return;

	scheduleOnce(schedule_selector(AttackTower::shootBullet), this->getShootIntervalTime());
}

bool AttackBullet::init()
{
	if (!BaseBullet::init()) return false;
	Size size = Director::getInstance()->getWinSize();

	auto arrow = Sprite::createWithSpriteFrameName("bullet1.png");
	this->setContentSize(arrow->getContentSize());
	this->addChild(arrow);

	setVelocity(100.0f);
	setLethality(1);
	setShootRange(size.width);
	setOrigin(Vec2::ZERO);
	setDirection(Vec2::ZERO);

	return true;
}
