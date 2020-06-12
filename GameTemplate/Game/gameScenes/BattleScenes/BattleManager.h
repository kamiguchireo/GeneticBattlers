#pragma once
#include "Skill/SkillList.h"

class BattleScenes;

struct ACTMonsterInfo {
	MonsterBase* actMonster = nullptr;
	bool isEnemy = false;
};

class BattleManager
{
public:
	BattleManager();
	~BattleManager();

	//戦闘処理。
	void BattleUpdate();
	//味方のチームをセット。
	void PushBackTeams(MonsterBase* monster)
	{
		m_monsterTeam.push_back(monster);
	}
	//敵のチームをセット。
	void PushBackEnemys(MonsterBase* enemy)
	{
		m_monsterEnemy.push_back(enemy);
	}
	//それぞれに味方チームを知らせる。
	void SetTeams();
	/// <summary>
	/// バトルシーンのポインタ設定。
	/// </summary>
	/// <param name="p">ポインタ。</param>
	void SetScenePointa(BattleScenes* p)
	{
		m_scenes = p;
	}

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
	//HPでソートを行う。
	void SortTeams();

	//バトルの処理切り替え
	enum BattleState {
		enState_ATB,
		enState_ACT,
		enState_Scoring
	};
	BattleScenes* m_scenes = nullptr;
	//モンスターのポインタ。
	MonsterList m_monsterTeam;
	MonsterList m_monsterEnemy;
	std::vector <ACTMonsterInfo> m_monsterACTList;	//!<行動中のリスト。
	ACTMonsterInfo m_monsterACT;					//!<現在行動中のモンスター。
	SkillList skillList;							//!<スキルリスト。
	SkillBase* m_usingSkill = nullptr;				//現在使用中のスキル。
	BattleState m_battleState = enState_ATB;
};

