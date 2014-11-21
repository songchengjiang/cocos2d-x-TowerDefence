#ifndef  _UI_SCENE_H_
#define  _UI_SCENE_H_

#include "cocos2d.h"
class UIScene :
	public cocos2d::Layer
{
public:

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	CREATE_FUNC(UIScene);

private:

	void menuStartCallback(Ref* pSender);
	cocos2d::RepeatForever* PathFun(float controlX, float controlY, float w);

};

#endif

