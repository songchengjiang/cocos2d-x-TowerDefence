#include "MonsterGenerator.h"
#include "FireMonster.h"
#include "IceMonster.h"
#include "RockMonster.h"
#include "GameManager.h"
#include "PlayerLayer.h"
#include "LevelLoader.h"

void MonsterGenerator::generateMonsterGroup(int groupIndex, float interval)
{
	_generatedFireMonster = _generatedIceMonster = _generatedRockMonster = 0;
	_currentGroup = groupIndex;
	_oneByOneInterval = interval;

	schedule(schedule_selector(MonsterGenerator::generateMonster), _oneByOneInterval);
}

void MonsterGenerator::generateMonster( float interval )
{
	auto mGroup = LevelLoader::getInstance()->getMonsterGroup();
	if (_generatedFireMonster >= mGroup[_currentGroup].monsterNum[0]
  && _generatedIceMonster >= mGroup[_currentGroup].monsterNum[1]
  && _generatedRockMonster >= mGroup[_currentGroup].monsterNum[2]){
		unschedule(schedule_selector(MonsterGenerator::generateMonster));
		_observer->oneMonsterGroupGenerated(this);
		return;
	}

  if (_generatedFireMonster < mGroup[_currentGroup].monsterNum[0]){
	  auto fm = FireMonster::create();
	  fm->setMovePath(GameManager::getInstance()->walkPathList);
	  fm->setMaxHp(mGroup[_currentGroup].monsterHP[0]);
	  fm->setCurrHp(fm->getMaxHp());
	  fm->born();
	  fm->move();
	  fm->MonsterPassCallback = CC_CALLBACK_1(PlayerLayer::monsterWin, _observer);
	  this->addChild(fm, 10);
	  ++_generatedFireMonster;
  }

  if ((_generatedFireMonster >= mGroup[_currentGroup].monsterNum[0] / 2) && (_generatedIceMonster < mGroup[_currentGroup].monsterNum[1])){
	  auto im = IceMonster::create();
	  im->setMovePath(GameManager::getInstance()->walkPathList);
	  im->setMaxHp(mGroup[_currentGroup].monsterHP[1]);
	  im->setCurrHp(im->getMaxHp());
	  im->born();
	  im->move();
	  im->MonsterPassCallback = CC_CALLBACK_1(PlayerLayer::monsterWin, _observer);
	  this->addChild(im, 10);
	  ++_generatedIceMonster;
  }

  if ((_generatedIceMonster >= mGroup[_currentGroup].monsterNum[1] / 2) && (_generatedRockMonster < mGroup[_currentGroup].monsterNum[2])){
	  auto rm = RockMonster::create();
	  rm->setMovePath(GameManager::getInstance()->walkPathList);
	  rm->setMaxHp(mGroup[_currentGroup].monsterHP[2]);
	  rm->setCurrHp(rm->getMaxHp());
	  rm->born();
	  rm->move();
	  rm->MonsterPassCallback = CC_CALLBACK_1(PlayerLayer::monsterWin, _observer);
	  this->addChild(rm, 10);
	  ++_generatedRockMonster;
  }
}

void MonsterGenerator::setObserver( PlayerLayer *pl )
{
	_observer = pl;
}
