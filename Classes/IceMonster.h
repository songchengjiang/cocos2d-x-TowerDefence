#ifndef  _ICE_MONSTER_H_
#define  _ICE_MONSTER_H_

#include "BaseMonster.h"

class IceMonster :
	public BaseMonster
{
public:
	CREATE_FUNC(IceMonster);

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