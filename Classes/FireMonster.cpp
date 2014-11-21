#include "FireMonster.h"
#include "AnimationLoader.h"
USING_NS_CC;

bool FireMonster::init()
{
	if (!BaseMonster::init()) return false;

	_entity = Sprite::createWithSpriteFrameName("enemyRight3_1.png");
	this->addChild(_entity);
	this->setContentSize(_entity->getContentSize());

	auto animRight = AnimationLoader::getInstance()->createAnimation("enemyRight3", 4, 0.1f);
	auto animLeft = AnimationLoader::getInstance()->createAnimation("enemyLeft3", 4, 0.1f);
	auto animExplode = AnimationLoader::getInstance()->createAnimation("explode3", 6, 0.15f);
	AnimationCache::getInstance()->addAnimation(animRight, "FireMonterMoveRight");
	AnimationCache::getInstance()->addAnimation(animLeft, "FireMonterMoveLeft");
	AnimationCache::getInstance()->addAnimation(animExplode, "FireMonterDead");

	setMoveVelocity(30.0f);
	return true;
}

void FireMonster::born()
{
	if (_movePath.empty()) return;
	_currentPosition = 0;
	this->setPosition(_movePath.at(_currentPosition));
	playMoveAnimations();
}

void FireMonster::move()
{
	++_currentPosition;
	if (_currentPosition >= _movePath.size()){
		stop();
		return;
	}
	auto currentPos = this->getPosition();
	auto nextPos = _movePath.at(_currentPosition);
	auto deltaPos = (currentPos - nextPos).length();
	this->runAction(Sequence::create(MoveTo::create(deltaPos / getMoveVelocity(), nextPos), CallFunc::create(CC_CALLBACK_0(FireMonster::move, this)), nullptr));
}

void FireMonster::stop()
{
	stopMoveAnimations();
	this->stopAllActions();
}

void FireMonster::dead()
{
	stop();
	_entity->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("FireMonterDead")), CallFunc::create(CC_CALLBACK_0(FireMonster::removeFromParent, this)), nullptr));
}

void FireMonster::playMoveAnimations()
{
	auto currentPos = this->getPosition();
	auto nextPos = _movePath.at(_currentPosition);

	if (nextPos.x > currentPos.x)
		_entity->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("FireMonterMoveRight")), CallFunc::create(CC_CALLBACK_0(FireMonster::playMoveAnimations, this)), nullptr));
	else
		_entity->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("FireMonterMoveLeft")), CallFunc::create(CC_CALLBACK_0(FireMonster::playMoveAnimations, this)), nullptr));
}

void FireMonster::stopMoveAnimations()
{
	_entity->stopAllActions();
}
