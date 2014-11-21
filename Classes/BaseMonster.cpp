#include "BaseMonster.h"
USING_NS_CC;

void BaseMonster::setMovePath( const std::vector<cocos2d::Vec2> &path )
{
	_movePath = path;
}

BaseMonster::BaseMonster()
	: _currentPosition(0)
	, _entity(nullptr)
{

}
