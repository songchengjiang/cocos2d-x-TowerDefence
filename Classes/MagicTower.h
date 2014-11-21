#ifndef  _MAGIC_TOWER_H_
#define  _MAGIC_TOWER_H_

#include "cocos2d.h"
#include "BaseTower.h"

class MagicTower :
	public BaseTower
{
public:

	CREATE_FUNC(MagicTower);
	virtual bool init() override;
	virtual void update(float deltaTime) override;
	virtual void shootBullet(float dt) override;
};

class MagicBullet :
	public BaseBullet
{
public:

	CREATE_FUNC(MagicBullet);
	virtual bool init() override;
};

#endif