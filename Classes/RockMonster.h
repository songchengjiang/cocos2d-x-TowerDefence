#ifndef  _ROCK_MONSTER_H_
#define  _ROCK_MONSTER_H_

#include "BaseMonster.h"

class RockMonster :
	public BaseMonster
{
public:
	CREATE_FUNC(RockMonster);

	virtual bool init() override;
	virtual void born();
	virtual void move();
	virtual void stop();
	virtual void dead();

private:
	void playMoveAnimations();
	void stopMoveAnimations();

};

#endif