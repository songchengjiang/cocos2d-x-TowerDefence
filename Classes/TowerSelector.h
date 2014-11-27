#ifndef  _TOWER_SELECTOR_H_
#define  _TOWER_SELECTOR_H_

#include "cocos2d.h"

enum TowerType
{
	ARROW_TOWER = 0,
	ATTACK_TOWER,
	MAGIC_TOWER,
	ANOTHER
};

class TowerSelector :
	public cocos2d::Layer
{
public:

	virtual bool init() override;
	CREATE_FUNC(TowerSelector);

	std::function<void(TowerSelector *ts, TowerType tType)> createTowerCallback;

private:

	bool onOneTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onOneTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

private:
	TowerType _selectedType;
};
#endif