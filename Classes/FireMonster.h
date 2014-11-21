#ifndef  _FIRE_MONSTER_H_
#define  _FIRE_MONSTER_H_

#include "BaseMonster.h"

class FireMonster :
	public BaseMonster
{
public:
	CREATE_FUNC(FireMonster);

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