#ifndef  _BASE_TOWER_H_
#define  _BASE_TOWER_H_

#include "cocos2d.h"
#include "BaseMonster.h"

class BaseTower :
	public cocos2d::Layer
{
	CC_SYNTHESIZE(int, _scope, Scope);
	CC_SYNTHESIZE(int, _lethality, Lethality);
	CC_SYNTHESIZE(float, _shootIntervalTime, ShootIntervalTime);

	virtual void shootBullet(float dt) = 0;

protected:

	BaseTower();

protected:
	BaseMonster *_nearestMonster;
};

class BaseBullet :
	public cocos2d::Layer
{
public:

	void setOrigin(const cocos2d::Vec2 &origin);
	const cocos2d::Vec2& getOrigin() const;
	void setDirection(const cocos2d::Vec2 &direction);
	const cocos2d::Vec2& getDirection() const;
	void setVelocity(float velocity);
	float getVelocity();
	void setShootRange(float range);
	float getShootRange();
	bool isOutOfBound();

	void fillBulletTo(cocos2d::Node *node);
	void shoot();
	bool hitTarget(cocos2d::Node *target);

protected:

	BaseBullet();

	void removeBullet();

protected:

	cocos2d::Vec2 _origin;
	cocos2d::Vec2 _direction;
	float _velocity;
	float _shootRange;
};

#endif