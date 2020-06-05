#pragma once
#include "Skill/SkillList.h"


class BattleManager
{
public:
	BattleManager() {};
	~BattleManager() {};

private:
	typedef std::vector<MonsterBase*> MonsterList;

	/// <summary>
	/// アクティブタイムの加算。
	/// </summary>
	void ActiveTimeUpdate();
	/// <summary>
	/// 行動させる。
	/// </summary>
	void MonsterAction();
	/// <summary>
	/// 評価させる。
	/// </summary>
	void MonsterScoring();

	//バトルの処理切り替え
	enum BattleState {
		enState_ATB,
		enState_ACT,
		enState_Scoring
	};
	//モンスターのポインタ。
	MonsterList m_monsterTeam;
	MonsterList m_monsterEnemy;
	MonsterList m_monsterACTList;	//!<行動中のリスト。
	MonsterBase* m_monsterACT = nullptr;	//!<現在行動中のモンスター。
	SkillList skillList;					//!<スキルリスト。
	BattleState m_battleState = enState_ATB;
};

