#include "RockMonster.h"
#include "AnimationLoader.h"
USING_NS_CC;

bool RockMonster::init()
{
	if (!BaseMonster::init()) return false;

	_entity = Sprite::createWithSpriteFrameName("enemyRight1_1.png");
	this->addChild(_entity);
	this->setContentSize(_entity->getContentSize());

	auto animRight = AnimationLoader::getInstance()->createAnimation("enemyRight1", 4, 0.1f);
	auto animLeft = AnimationLoader::getInstance()->createAnimation("enemyLeft1", 4, 0.1f);
	auto animExplode = AnimationLoader::getInstance()->createAnimation("explode1", 6, 0.15f);
	AnimationCache::getInstance()->addAnimation(animRight, "RockMonterMoveRight");
	AnimationCache::getInstance()->addAnimation(animLeft, "RockMonterMoveLeft");
	AnimationCache::getInstance()->addAnimation(animExplode, "RockMonterDead");

	setMoveVelocity(10.0f);
	return true;
}

void RockMonster::born()
{
	if (_movePath.empty()) return;
	_currentPosition = 0;
	this->setPosition(_movePath.at(_currentPosition));
	playMoveAnimations();
}

void RockMonster::move()
{
	++_currentPosition;
	if (_currentPosition >= _movePath.size()){
		stop();
		return;
	}
	auto currentPos = this->getPosition();
	auto nextPos = _movePath.at(_currentPosition);
	auto deltaPos = (currentPos - nextPos).length();
	this->runAction(Sequence::create(MoveTo::create(deltaPos / getMoveVelocity(), nextPos), CallFunc::create(CC_CALLBACK_0(RockMonster::move, this)), nullptr));
}

void RockMonster::stop()
{
	stopMoveAnimations();
	this->stopAllActions();
}

void RockMonster::dead()
{
	stop();
	_entity->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("RockMonterDead")), CallFunc::create(CC_CALLBACK_0(RockMonster::removeFromParent, this)), nullptr));
}

void RockMonster::playMoveAnimations()
{
	auto currentPos = this->getPosition();
	auto nextPos = _movePath.at(_currentPosition);

	if (nextPos.x > currentPos.x)
		_entity->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("RockMonterMoveRight")), CallFunc::create(CC_CALLBACK_0(RockMonster::playMoveAnimations, this)), nullptr));
	else
		_entity->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("RockMonterMoveLeft")), CallFunc::create(CC_CALLBACK_0(RockMonster::playMoveAnimations, this)), nullptr));
}

void RockMonster::stopMoveAnimations()
{
	_entity->stopAllActions();
}
