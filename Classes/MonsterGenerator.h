#ifndef  _MONSTER_GENERATOR_H_
#define  _MONSTER_GENERATOR_H_

#include "cocos2d.h"

class PlayerLayer;
class MonsterGenerator
	: 	public cocos2d::Layer
{
public:

	void setObserver(PlayerLayer *pl);
	void generateMonsterGroup(int groupIndex, float interval);

	CREATE_FUNC(MonsterGenerator);

private:

	void generateMonster(float interval);

private:

	PlayerLayer *_observer;
	float _oneByOneInterval;
	unsigned int _generatedFireMonster;
	unsigned int _generatedIceMonster;
	unsigned int _generatedRockMonster;
	int _currentGroup;
};

#endif

