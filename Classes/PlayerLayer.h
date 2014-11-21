#ifndef  _PLAYER_LAYER_H_
#define  _PLAYER_LAYER_H_


#include "cocos2d.h"

class PlayerLayer :
	public cocos2d::Layer
{
public:

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	CREATE_FUNC(PlayerLayer);

private:

	void initPath(cocos2d::TMXTiledMap *map);

private:
	std::vector<cocos2d::Vec2> _pathList;
};

#endif

