#ifndef  _ATTACK_TOWER_H_
#define  _ATTACK_TOWER_H_

#include "cocos2d.h"
#include "BaseTower.h"

class AttackTower :
	public BaseTower
{
public:

	CREATE_FUNC(AttackTower);
	virtual bool init() override;
	virtual void update(float deltaTime) override;
	virtual void shootBullet(float dt) override;
};

class AttackBullet :
	public BaseBullet
{
public:

	CREATE_FUNC(AttackBullet);
	virtual bool init() override;
};

#endif