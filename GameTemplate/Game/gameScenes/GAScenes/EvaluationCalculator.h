#pragma once
#include "GAScenes.h"

class SkillCalculator;
class SkillDataLoad;

typedef std::vector<MonsterData*> MonsterList;

struct MonsterInfo
{
	MonsterData* actionMonster = nullptr;
	bool IsEnemy = false;
};

/// <summary>
/// 評価値計算機
/// </summary>

class EvaluationCalculator : public IGameObject
{
public:
	EvaluationCalculator();
	~EvaluationCalculator();

	void SetEnemyAI(GA::AITable& ai, GA::Job job);

	/// <summary>
	/// 勝率を計算する。
	/// </summary>
	/// <param name="table">1つの遺伝子</param>
	/// <returns>勝率(%)</returns>
	GA::Evaluation Calculation(GA::AITableList& table);

private:
	bool Battle();

	void ActiveTime();

	//行動を行う。
	void Action();
	//行動を決定する。
	void DisideSkill(int& skill, int& target);
	//ターゲットリスト作成。
	void SetTargetList(int skill);
	//スキルを使う。
	int UseSkill(const int skill,const int target);
	/// <summary>
	/// 状態を更新する。
	/// </summary>
	/// <param name="isWin">戦闘勝利か？</param>
	/// <returns>戦闘が終わったかどうか。</returns>
	bool MonsterStateUpdate(bool& isWin);


	const int LOOP_NUMBER = 20;	//勝率測定の戦闘回数。

	//MonsterList m_members;
	//MonsterList m_enemys;
	MonsterData m_members[GA::en_JobNum];
	MonsterData m_enemys[GA::en_JobNum];

	MonsterInfo monsterACT;			//現在行動中モンスターの情報。
	MonsterList m_targetList;
	std::vector<MonsterInfo> m_actionList;
	std::vector<int> m_resultValueList;			//評価値の可変長配列。
	SkillCalculator* m_skillCalc = nullptr;
	SkillDataLoad* m_skillData = nullptr;
	int m_resultValue = 0;
};

