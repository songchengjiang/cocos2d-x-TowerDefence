#ifndef  _ANIMATION_LOADER_H_
#define  _ANIMATION_LOADER_H_

#include "cocos2d.h"

class AnimationLoader
{
public:

	static AnimationLoader* getInstance();
	cocos2d::Animation* createAnimation(const std::string &animName, int frameCount, float interval);
};

#endif
