#ifndef  _LEVEL_PAGE_H_
#define  _LEVEL_PAGE_H_

#include "cocos2d.h"
class LevelPage : public cocos2d::Node
{
public:

	bool initLevelPage(const std::string& bgName, int level);
	static LevelPage* create(const std::string& bgName, int level);
	void menuStartCallback(Ref* pSender);
};

#endif

