#include "ResourceLoader.h"
USING_NS_CC;

ResourceLoader::ResourceLoader(void)
	: _totalResCount(0)
	, _loadedResCount(0)
{
	_resNameList.push_back("Play.plist"); _totalResCount++;
	_resNameList.push_back("playbg.png"); _totalResCount++;
	_resNameList.push_back("playbg1.jpg"); _totalResCount++;
	_resNameList.push_back("successfulBg.png"); _totalResCount++;
	_resNameList.push_back("btn_back.png"); _totalResCount++;
	_resNameList.push_back("btn_back_press.png"); _totalResCount++;
	_resNameList.push_back("card_1.png"); _totalResCount++;
	_resNameList.push_back("card_2.png"); _totalResCount++;
	_resNameList.push_back("card_3.png"); _totalResCount++;
	_resNameList.push_back("LevelInfoPanel.png"); _totalResCount++;
	_resNameList.push_back("House.png"); _totalResCount++;
	_resNameList.push_back("selectLevelBg.png"); _totalResCount++;
	_resNameList.push_back("selectLevelBg1.png"); _totalResCount++;
	_resNameList.push_back("selectLevelBg2.png"); _totalResCount++;
	_resNameList.push_back("start_1.png"); _totalResCount++;
	_resNameList.push_back("start_2.png"); _totalResCount++;
}


ResourceLoader::~ResourceLoader(void)
{
}

ResourceLoader* ResourceLoader::getInstance()
{
	static ResourceLoader rl;
	return &rl;
}

bool ResourceLoader::preLoadingAsync()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(_resNameList[0]);
	++_loadedResCount;

	for (unsigned int i = 1; i < _resNameList.size(); ++i){
		Director::getInstance()->getTextureCache()->addImageAsync(_resNameList[i], CC_CALLBACK_1(ResourceLoader::loadingCallBack, this));
	}
	
	return true;
}

unsigned int ResourceLoader::getTotalResourceCount()
{
	return _totalResCount;
}

unsigned int ResourceLoader::getLoadedResourceCount()
{
	return _loadedResCount;
}

void ResourceLoader::initSearchPaths()
{
	std::vector<std::string> searchPath;
	searchPath.push_back("height_864");
	CCFileUtils::getInstance()->setSearchPaths(searchPath);
}

const std::vector<std::string>& ResourceLoader::GetResourceList() const
{
	return _resNameList;
}

void ResourceLoader::loadingCallBack( cocos2d::Texture2D *texture )
{
	++_loadedResCount;
}
