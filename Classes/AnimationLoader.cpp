#include "AnimationLoader.h"

USING_NS_CC;

AnimationLoader* AnimationLoader::getInstance()
{
	static AnimationLoader al;
	return &al;
}

cocos2d::Animation* AnimationLoader::createAnimation( const std::string &animName, int frameCount, float interval )
{
	Vector<SpriteFrame*> animFrames;

	for (int i = 1; i <= frameCount; i++)
	{
		char buffer[20] = { 0 };
		sprintf(buffer, "_%i.png",  i);
		std::string str =  animName + buffer;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	return Animation::createWithSpriteFrames(animFrames, interval);
}
