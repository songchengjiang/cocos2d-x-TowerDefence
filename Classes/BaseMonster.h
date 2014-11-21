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

protected:
	BaseMonster();

protected:
	std::vector<cocos2d::Vec2> _movePath;
	unsigned int _currentPosition;
	cocos2d::Sprite *_entity;
};

#endif