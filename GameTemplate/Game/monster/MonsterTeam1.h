#pragma once
#include "monster/MonsterBase.h"
#include "Skill/SkillList.h"

class MonsterTeam1 : public MonsterBase
{
public:
	MonsterTeam1();
	~MonsterTeam1();
	bool Start();

	bool ACTScoring() 
	{
		m_status.ClearATB();
		m_UI->SetScaling(0.0f);
		DeleteGO("sLog");
		return true; 
	};

private:
	const char* GetDefaultDataPath()
	{
		return "Assets/AIData/DefaultData/EnemyData.bin";		//ネットではないときのAI。
	}

	//行動の状態遷移の列挙。
	enum ActionState {
		en_state_Tame,
		en_state_Attack,
		en_state_Return,
		en_state_Num
	};

};

