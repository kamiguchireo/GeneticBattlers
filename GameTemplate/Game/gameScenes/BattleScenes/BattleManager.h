#pragma once
#include "Skill/SkillList.h"

class BattleScenes;

struct ACTMonsterInfo {
	MonsterBase* actMonster = nullptr;
	bool isEnemy = false;
};

namespace job {
	enum JOB {
		enjob_Attacker,
		enjob_Healer,
		enjob_Supotter,
		enjob_Num
	};
}

class BattleManager:public IGameObject
{
public:
	BattleManager();
	~BattleManager();

	bool Start();
	void Update();

	//味方のチームをセット。
	void PushBackTeams(MonsterBase* monster, job::JOB j)
	{
		m_monsterTeam[j] = monster;
	}
	//敵のチームをセット。
	void PushBackEnemys(MonsterBase* enemy, job::JOB j)
	{
		m_monsterEnemy[j] = enemy;
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
	//GIの更新処理と保存をさせる。
	void SaveData()
	{
		//全員分の記録を行う。
		for (auto p : m_monsterTeam) {
			auto GI = p->GetAIManager();
			GI.Save();
		}
	}
	void SetIsBattle(bool flag)
	{
		m_isBattle = flag;
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
	////HPでソートを行う。
	//void SortTeams();

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
	bool m_isBattle = false;
};

