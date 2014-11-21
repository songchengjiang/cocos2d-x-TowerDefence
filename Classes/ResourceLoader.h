#ifndef  _RESOURCE_LOADER_H_
#define  _RESOURCE_LOADER_H_

#include "cocos2d.h"

class ResourceLoader
{
public:

	static ResourceLoader* getInstance();
	ResourceLoader(void);
	~ResourceLoader(void);
	bool preLoadingAsync();
	void initSearchPaths();
	
	unsigned int getTotalResourceCount();
	unsigned int getLoadedResourceCount();
	const std::vector<std::string>& GetResourceList() const;

private:

	void loadingCallBack(cocos2d::Texture2D *texture);

private:
	unsigned int _totalResCount;
	unsigned int _loadedResCount;
	std::vector<std::string> _resNameList;
};

#endif
