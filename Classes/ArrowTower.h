#ifndef  _ARROW_TOWER_H_
#define  _ARROW_TOWER_H_

#include "cocos2d.h"
#include "BaseTower.h"

class ArrowTower :
	public BaseTower
{
public:

	CREATE_FUNC(ArrowTower);
	virtual bool init() override;
	virtual void update(float deltaTime) override;
	virtual void shootBullet(float dt) override;

private:
	cocos2d::Sprite *_rotateArrow;
};

class ArrowBullet :
	public BaseBullet
{
public:

	CREATE_FUNC(ArrowBullet);
	virtual bool init() override;
};

#endif