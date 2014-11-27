#ifndef  _LEVEL_SELECT_SCENE_H_
#define  _LEVEL_SELECT_SCENE_H_

#include "cocos2d.h"
class LevelSelectScene : public cocos2d::Scene
{
public:

	virtual bool init();  
	CREATE_FUNC(LevelSelectScene);
	void menuCloseCallback(Ref* pSender);
	static LevelSelectScene *getInstance();

private:

	static LevelSelectScene *_instance;
};

#endif

