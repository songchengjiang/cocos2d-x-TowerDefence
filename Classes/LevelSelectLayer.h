#ifndef  _LEVEL_SELECT_LAYER_H_
#define  _LEVEL_SELECT_LAYER_H_

#include "cocos2d.h"
class LevelSelectLayer : public cocos2d::Layer
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	CREATE_FUNC(LevelSelectLayer);

	bool onOneTouchBegan(cocos2d::Touch *touch, cocos2d::Event  *event);
	void onOneTouchMoved(cocos2d::Touch *touch, cocos2d::Event  *event);
	void onOneTouchEnded(cocos2d::Touch *touch, cocos2d::Event  *event);
	void addPage(cocos2d::Node *page);

private:

	int _pageNum;
	int _curPage;
	cocos2d::Vec2 _touchDownPoint;
	cocos2d::Vec2 _touchUpPoint;
	cocos2d::Vec2 _touchCurPoint;
	float WINDOW_WIDTH;
	float WINDOW_HEIGHT;
	void goToCurrNode();
};

#endif

