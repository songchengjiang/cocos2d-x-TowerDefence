#ifndef  _BASE_MONSTER_H_
#define  _BASE_MONSTER_H_

#include "cocos2d.h"
class BaseMonster :
	public cocos2d::Layer
{
public:

	void setMovePath(const std::vector<cocos2d::Vec2> &path);
	virtual void born() = 0;
	virtual void move() = 0;
	virtual void stop() = 0;
	virtual void dead() = 0;

	CC_SYNTHESIZE(float, _moveVelocity, MoveVelocity);
	CC_SYNTHESIZE(int, _maxHp, MaxHp);
	CC_SYNTHESIZE(int, _currHp, CurrHp);
	CC_SYNTHESIZE_READONLY(cocos2d::ProgressTimer*, _hpBar, HpBar);
	void updateHpBar();

	std::function<void(BaseMonster *)> MonsterPassCallback;

protected:
	BaseMonster();
	void createAndSetHpBar();
	void removeHpBar();
protected:
	std::vector<cocos2d::Vec2> _movePath;
	unsigned int _currentPosition;
	cocos2d::Sprite *_entity;
};

#endif