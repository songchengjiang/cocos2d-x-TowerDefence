#include "BaseTower.h"
#include "GameManager.h"
USING_NS_CC;

BaseTower::BaseTower()
	: _nearestMonster(nullptr)
{

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

void BaseBullet::shoot()
{
	if (this->getParent()){
		this->setPosition(_origin);
		this->setRotation(atan2f(_direction.y, _direction.x));
		auto endPos = _origin + _direction * _shootRange;
		this->runAction(Sequence::create(MoveTo::create(_shootRange / _velocity, endPos), CallFunc::create(CC_CALLBACK_0(BaseBullet::removeBullet, this)), nullptr));
		GameManager::getInstance()->bulletList.pushBack(this);
	}
}

void BaseBullet::removeBullet()
{
	GameManager::getInstance()->bulletList.eraseObject(this);
	this->removeFromParent();
}

void BaseBullet::fillBulletTo(cocos2d::Node *node)
{
	node->addChild(this);
}

bool BaseBullet::hitTarget( cocos2d::Node *target )
{
	Mat4 mat = this->getNodeToWorldTransform();
	auto inWorldPos = mat * Vec4(this->getPosition().x, this->getPosition().y, 0.0f, 1.0f);
	Rect bRect(inWorldPos.x, inWorldPos.y, this->getContentSize().width, this->getContentSize().height);
	Rect tRect(target->getPosition().x, target->getPosition().y, target->getContentSize().width, target->getContentSize().height);
	if (bRect.intersectsRect(tRect)) 
		return true;
	return false;
}
