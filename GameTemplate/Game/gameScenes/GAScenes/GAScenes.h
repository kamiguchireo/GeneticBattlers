#pragma once
#include "monster/MonsterData.h"

class SkillCalculator;
class SkillDataLoad;

typedef std::vector<MonsterData*> MonsterList;
typedef std::vector<AIData> AITable;
typedef std::vector<AITable> AIGenetics;

class GAScenes:public IGameObject
{
public:
	GAScenes();
	~GAScenes();
	bool Start()override;
	void Update()override;
private:
	static const int GENETICS_NUM = 100;
	enum Job
	{
		en_Attacker,
		en_Healer,
		en_Supporter,
		en_JobNum
	};

	prefab::SpriteRender* m_sprite = nullptr;
	prefab::FontRender* m_font = nullptr;
	MonsterList m_members;
	MonsterList m_enemys;
	AITable m_myAI[en_JobNum];
	AITable m_enemyAI[en_JobNum];
	AIGenetics m_currentGenetic[en_JobNum];
	std::vector<int> m_winRate;
};

