#include "MagicTower.h"
#include "GameManager.h"
USING_NS_CC;

bool MagicTower::init()
{
	if (!BaseTower::init()) return false;

	setScope(100);
	setShootIntervalTime(4);

	auto multiDirTower = Sprite::createWithSpriteFrameName("multiDirTower.png");
	this->addChild(multiDirTower);
	this->setContentSize(multiDirTower->getContentSize());

	scheduleUpdate();
	//schedule(schedule_selector(MagicTower::shootBullet), this->getShootIntervalTime());
	return true;
}

void MagicTower::shootBullet(float dt)
{
	if (!_nearestMonster) return;

	auto targetPos = _nearestMonster->getPosition();
	auto deltaPos = targetPos - this->getPosition();

	for (unsigned int i = 0; i < 6; ++i)
	{
		auto bullet = MagicBullet::create();
		bullet->setOrigin(Vec2(0.0f, this->getContentSize().height / 4.0f));
		bullet->setDirection(Vec2(cosf(CC_DEGREES_TO_RADIANS(60.0f * i)), sinf(CC_DEGREES_TO_RADIANS(60.0f * i))));
		bullet->fillBulletTo(this);
		bullet->shoot();
	}
}

void MagicTower::update( float deltaTime )
{
	if (!searchTarget()) return;

	scheduleOnce(schedule_selector(MagicTower::shootBullet), this->getShootIntervalTime());
}

bool MagicBullet::init()
{
	if (!BaseBullet::init()) return false;
	Size size = Director::getInstance()->getWinSize();

	auto arrow = Sprite::createWithSpriteFrameName("bullet.png");
	this->setContentSize(arrow->getContentSize());
	this->addChild(arrow);

	setVelocity(100.0f);
	setLethality(5);
	setShootRange(size.width);
	setOrigin(Vec2::ZERO);
	setDirection(Vec2::ZERO);

	return true;
}
