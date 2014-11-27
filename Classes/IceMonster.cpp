#include "IceMonster.h"
#include "AnimationLoader.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion; 

USING_NS_CC;

bool IceMonster::init()
{
	if (!BaseMonster::init()) return false;

	_entity = Sprite::createWithSpriteFrameName("enemyRight2_1.png");
	this->addChild(_entity);
	this->setContentSize(_entity->getContentSize());

	auto animRight = AnimationLoader::getInstance()->createAnimation("enemyRight2", 4, 0.1f);
	auto animLeft = AnimationLoader::getInstance()->createAnimation("enemyLeft2", 4, 0.1f);
	auto animExplode = AnimationLoader::getInstance()->createAnimation("explode2", 6, 0.15f);
	AnimationCache::getInstance()->addAnimation(animRight, "IceMonterMoveRight");
	AnimationCache::getInstance()->addAnimation(animLeft, "IceMonterMoveLeft");
	AnimationCache::getInstance()->addAnimation(animExplode, "IceMonterDead");

	setMoveVelocity(40.0f);
	setMaxHp(5);
	setCurrHp(5);

	createAndSetHpBar();
	return true;
}

void IceMonster::born()
{
	if (_movePath.empty()) return;
	_currentPosition = 0;
	this->setPosition(_movePath.at(_currentPosition));
	playMoveAnimations();
	GameManager::getInstance()->monsterList.push_back(this);
}

void IceMonster::move()
{
	++_currentPosition;
	if (_currentPosition >= _movePath.size()){
		MonsterPassCallback(this);
		return;
	}
	auto currentPos = this->getPosition();
	auto nextPos = _movePath.at(_currentPosition);
	auto deltaPos = (currentPos - nextPos).length();
	this->runAction(Sequence::create(MoveTo::create(deltaPos / getMoveVelocity(), nextPos), CallFunc::create(CC_CALLBACK_0(IceMonster::move, this)), nullptr));
}

void IceMonster::stop()
{
	stopMoveAnimations();
	this->stopAllActions();
}

void IceMonster::dead()
{
	stop();
	removeHpBar();
	_entity->setAnchorPoint(Point(0.5f, 0.25f));
	_entity->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("IceMonterDead")), CallFunc::create(CC_CALLBACK_0(IceMonster::removeFromParent, this)), nullptr));
	auto iter = std::find(GameManager::getInstance()->monsterList.begin(), GameManager::getInstance()->monsterList.end(), this);
	GameManager::getInstance()->monsterList.erase(iter);
	SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/enemy0_down.mp3").c_str(), false);
}

void IceMonster::playMoveAnimations()
{
	auto currentPos = this->getPosition();
	auto nextPos = _movePath.at(_currentPosition);

	if (nextPos.x > currentPos.x)
		_entity->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("IceMonterMoveRight")), CallFunc::create(CC_CALLBACK_0(IceMonster::playMoveAnimations, this)), nullptr));
	else
		_entity->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("IceMonterMoveLeft")), CallFunc::create(CC_CALLBACK_0(IceMonster::playMoveAnimations, this)), nullptr));
}

void IceMonster::stopMoveAnimations()
{
	_entity->stopAllActions();
}
