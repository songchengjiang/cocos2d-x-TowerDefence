#include "BaseMonster.h"
USING_NS_CC;

#define HP_BAR_TAG 0x0001

void BaseMonster::setMovePath( const std::vector<cocos2d::Vec2> &path )
{
	_movePath = path;
}

BaseMonster::BaseMonster()
	: _currentPosition(0)
	, _entity(nullptr)
	, _moveVelocity(0.0f)
	, _maxHp(0)
	, _currHp(0)
	, _hpBar(nullptr)
{

}

void BaseMonster::createAndSetHpBar()
{
	auto hpBgSprite = Sprite::createWithSpriteFrameName("hpBg1.png");
	hpBgSprite->setPosition(Point(_entity->getContentSize().width / 2, _entity->getContentSize().height ));
	_entity->addChild(hpBgSprite, 0, HP_BAR_TAG);
	// 2
	_hpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("hp1.png"));
	_hpBar->setType(ProgressTimer::Type::BAR);
	_hpBar->setMidpoint(Point(0, 0.5f));
	_hpBar->setBarChangeRate(Point(1, 0));
	_hpBar->setPercentage(100.0f);
	_hpBar->setPosition(Point(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 3 * 2 ));
	hpBgSprite->addChild(_hpBar);
}

void BaseMonster::updateHpBar()
{
	float persent = (float)_currHp / (float)_maxHp * 100.0f;
	if (persent < 0.0f) persent = 0.0f; 
	_hpBar->setPercentage(persent);
}

void BaseMonster::removeHpBar()
{
	_entity->removeChildByTag(HP_BAR_TAG);
}
