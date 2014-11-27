#include "BaseTower.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion; 

USING_NS_CC;

BaseTower::BaseTower()
	: _nearestMonster(nullptr)
{

}

bool BaseTower::searchTarget()
{
	_nearestMonster = nullptr;
	float scope = this->getScope() * this->getScope();
	for (auto iter : GameManager::getInstance()->monsterList)
	{
		auto target = iter;
		float lenSqr = (target->getPosition() - this->getPosition()).lengthSquared();
		if (lenSqr < scope){
			_nearestMonster = target;
			scope = lenSqr;
		}
	}

	return _nearestMonster == nullptr? false: true;
}

void BaseBullet::setOrigin( const cocos2d::Vec2 &origin )
{
	_origin = origin;
}

const cocos2d::Vec2& BaseBullet::getOrigin() const
{
	return _origin;
}

void BaseBullet::setDirection( const cocos2d::Vec2 &direction )
{
	_direction = direction;
	_direction.normalize();
}

const cocos2d::Vec2& BaseBullet::getDirection() const
{
	return _direction;
}

void BaseBullet::setVelocity( float velocity )
{
	_velocity = velocity;
}

float BaseBullet::getVelocity()
{
	return _velocity;
}

BaseBullet::BaseBullet()
	: _velocity(0.0f)
{

}

void BaseBullet::setShootRange( float range )
{
	_shootRange = range;
}

float BaseBullet::getShootRange()
{
	return _shootRange;
}

bool BaseBullet::isOutOfBound()
{
	if ((_shootRange * _shootRange) < (this->getPosition() - _origin).lengthSquared())
		return true;
	return false;
}

void BaseBullet::shoot(bool rotByDir)
{
	if (this->getParent()){
		this->setPosition(_origin);
		if (rotByDir)
			this->setRotation(CC_RADIANS_TO_DEGREES(-atan2f(_direction.y, _direction.x)));
		auto endPos = _origin + _direction * _shootRange;
		this->runAction(Sequence::create(MoveTo::create(_shootRange / _velocity, endPos), CallFunc::create(CC_CALLBACK_0(BaseBullet::removeBullet, this)), nullptr));
		GameManager::getInstance()->bulletList.push_back(this);

		SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
	}
}

void BaseBullet::removeBullet()
{
	this->stopAllActions();
	auto iter = std::find(GameManager::getInstance()->bulletList.begin(), GameManager::getInstance()->bulletList.end(), this);
	if (iter != GameManager::getInstance()->bulletList.end())
		GameManager::getInstance()->bulletList.erase(iter);
	this->removeFromParent();
}

void BaseBullet::fillBulletTo(cocos2d::Node *node)
{
	node->addChild(this);
}

bool BaseBullet::hitTarget( cocos2d::Node *target )
{
	Vec2 bInWorldPos = this->convertToWorldSpace(Vec2(-this->getContentSize().width / 2.0f, -this->getContentSize().height / 2.0f));
	Vec2 tInWorldPos = target->convertToWorldSpace(Vec2(-target->getContentSize().width / 2.0f, -target->getContentSize().height / 2.0f));

	Rect bRect(bInWorldPos.x, bInWorldPos.y, this->getContentSize().width, this->getContentSize().height);
	Rect tRect(tInWorldPos.x, tInWorldPos.y, target->getContentSize().width, target->getContentSize().height);
	if (bRect.intersectsRect(tRect)) 
		return true;
	return false;
}
