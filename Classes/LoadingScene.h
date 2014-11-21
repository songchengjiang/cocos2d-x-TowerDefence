#ifndef  _LOADING_SCENE_H_
#define  _LOADING_SCENE_H_

#include "cocos2d.h"
class LoadingScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	CREATE_FUNC(LoadingScene);

	virtual void update(float deltaTime) override;

private:

	void createProcessBar();

private:

	cocos2d::ProgressTimer *_processBar;
};

#endif

