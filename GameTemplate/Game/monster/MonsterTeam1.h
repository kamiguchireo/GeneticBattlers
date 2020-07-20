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
		DeleteGO("sLog");
		return true; 
	};
	////AIデータを読み込みたい。
	//void Init(const char* filePath)override 
	//{
	//	//デフォルトのデータのファイルを読み込む。
	//	m_GIData.LoadDefault(GetDefaultDataPath());
	//};

	void SetUIPos(const CVector3& pos)
	{
		m_UIpos = pos;
	}

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

	CVector3 m_UIpos = CVector3::Zero();
};

