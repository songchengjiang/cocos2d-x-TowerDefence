#include "AttackTower.h"
#include "GameManager.h"
USING_NS_CC;

bool AttackTower::init()
{
	if (!BaseTower::init()) return false;

	setScope(150);
	setLethality(5);
	setShootIntervalTime(1);

	auto multiDirTower = Sprite::createWithSpriteFrameName("attackTower.png");
	this->addChild(multiDirTower);
	this->setContentSize(multiDirTower->getContentSize());

	scheduleUpdate();
	schedule(schedule_selector(AttackTower::shootBullet), this->getShootIntervalTime());
	return true;
}

void AttackTower::shootBullet(float dt)
{
	if (!_nearestMonster) return;

	auto targetPos = _nearestMonster->getPosition();
	auto deltaPos = targetPos - this->getPosition();

	auto bullet = AttackBullet::create();
	bullet->setOrigin(Vec2(this->getPosition().x, this->getPosition().y + this->getContentSize().height / 4.0f));
	bullet->setDirection(deltaPos);
	bullet->fillBulletTo(this);
	bullet->shoot();
}

void AttackTower::update( float deltaTime )
{
	_nearestMonster = nullptr;
	for (auto iter : GameManager::getInstance()->monsterList)
	{
		auto target = iter;
		if ((target->getPosition() - this->getPosition()).lengthSquared() < this->getScope() * this->getScope()){
			_nearestMonster = target;
			break;
		}
	}
	//scheduleOnce(schedule_selector(MagicTower::shootBullet), this->getShootIntervalTime());
}

bool AttackBullet::init()
{
	if (!BaseBullet::init()) return false;
	Size size = Director::getInstance()->getWinSize();

	auto arrow = Sprite::createWithSpriteFrameName("bullet1.png");
	this->setContentSize(arrow->getContentSize());
	this->addChild(arrow);

	setVelocity(100.0f);
	setShootRange(size.width);
	setOrigin(Vec2::ZERO);
	setDirection(Vec2::ZERO);

	return true;
}
