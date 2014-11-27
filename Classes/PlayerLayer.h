#ifndef  _PLAYER_LAYER_H_
#define  _PLAYER_LAYER_H_


#include "cocos2d.h"
#include "TowerSelector.h"

class BaseMonster;
class MonsterGenerator;
class PlayerLayer :
	public cocos2d::Layer
{
public:

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	virtual void update(float deltaTime) override;

	//callback by MonsterGenerator
	void monsterWin(BaseMonster *bm);
	void oneMonsterGroupGenerated(MonsterGenerator *mg);

	CREATE_FUNC(PlayerLayer);

	~PlayerLayer();

private:

	void generateOneMonsterGroup(unsigned int total, float interval);

	void initLevelInfo();
	void initToolBar();
	bool onOneTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void createTower(TowerSelector *ts, TowerType tType);
	void initPath(cocos2d::TMXTiledMap *map);
	void collisionDetection();
	bool canPutTower(cocos2d::Touch *touch, cocos2d::Vec2 &touchTileLoc);
	cocos2d::Vec2 convertToMapTile(const cocos2d::Vec2 &inWorld);

	void updateMoney(int delta);
	void updatePlayerHp(float delta);
	void updateMonsterGroup(int delta);

	void menuBackCallback(Ref* pSender);

private:
	std::vector<cocos2d::Vec2> _filledVec; 
	cocos2d::Sprite *_toolBar;


	int _money;
	int _totalMonsterGroup;
	int _currentMonsterGroup;
	float _playerHp;

	bool _oneMonsterGroupGenerated;

	unsigned int _backGroundMusicID;
};

#endif

