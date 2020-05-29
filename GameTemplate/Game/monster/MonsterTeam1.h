#pragma once
#include "monster/MonsterBase.h"
#include "Skill/SkillList.h"

class MonsterTeam1 : public MonsterBase
{
public:
	MonsterTeam1();
	~MonsterTeam1();
	bool Start();
	void Update();
	bool Action_good();
	bool Action_usually();
	bool Action_bad();
	/// <summary>
	/// ステートに応じて行動を決める。
	/// </summary>
	bool Action();

	bool BattleAction();
	bool ACTScoring() { return true; };
	void SelectUseSkill(const std::vector<MonsterBase*>& e_team, const std::vector<MonsterBase*>& m_team)override;
	//AIデータを読み込みたい。
	void Init(const char* filePath)override {};

	void SetUIPos(const CVector3& pos)
	{
		m_UIpos = pos;
	}

private:
	const char* GetDefaultDataPath()
	{
		return "Assets/AIData/HealerDefault.bin";
	}
	const char m_filePath[64] = "Assets/AIData/HealerDefault.bin";

	//行動の状態遷移の列挙。
	enum ActionState {
		en_state_Tame,
		en_state_Attack,
		en_state_Return,
		en_state_Num
	};

	CVector3 m_UIpos = CVector3::Zero();
};

