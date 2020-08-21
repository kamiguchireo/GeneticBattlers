#include "stdafx.h"
#include "EvaluationCalculator.h"
#include "Skill/SkillCalculator.h"
#include "Skill/SkillDataLoad.h"

using namespace GA;

EvaluationCalculator::EvaluationCalculator()
{
	//味方のステータス設定。
	m_members[en_Attacker].GetStatusManager()->StatusAttaker();
	m_members[en_Healer].GetStatusManager()->StatusHealer();
	m_members[en_Supporter].GetStatusManager()->StatusSupporter();
	//敵のステータス設定。
	m_enemys[en_Attacker].GetStatusManager()->StatusAttaker();
	m_enemys[en_Healer].GetStatusManager()->StatusHealer();
	m_enemys[en_Supporter].GetStatusManager()->StatusSupporter();
	//スキル計算機の実体化。
	m_skillCalc = new SkillCalculator();

	m_skillData = SkillDataLoad::GetInstance();
	if (m_skillData == nullptr)
	{
		m_skillData = NewGO<SkillDataLoad>(0);
	}
}

EvaluationCalculator::~EvaluationCalculator()
{
	if (m_skillCalc != nullptr)
	{
		delete m_skillCalc;
	}
	DeleteGO(m_skillData);
}

void EvaluationCalculator::SetEnemyAI(GA::AITable & ai, GA::Job job)
{
	m_enemys[job].GetAIManager().SetAIData(ai);
}

Evaluation EvaluationCalculator::Calculation(AITableList & table)
{
	//AIをセット。
	m_members[en_Attacker].GetAIManager().SetAIData(table[en_Attacker]);
	m_members[en_Healer].GetAIManager().SetAIData(table[en_Healer]);
	m_members[en_Supporter].GetAIManager().SetAIData(table[en_Supporter]);

	int winCount = 0;		//勝利回数計測。
	m_actionCount = 0;		//行動回数初期化。

	for (int i = 0; i < LOOP_NUMBER; i++)
	{
		//ステータスを元に戻しておく。
		for (auto& data : m_members)
		{
			data.GetStatusManager()->ResetStatus();
		}
		for (auto& data : m_enemys)
		{
			data.GetStatusManager()->ResetStatus();
		}
		//戦闘に勝利したか？
		if (Battle())
		{
			winCount++;
		}
	}

	Evaluation ret;
	//勝率記録。
	ret.winRate = static_cast<int>(static_cast<float>(winCount) / LOOP_NUMBER * 100);
	ret.actionCount = m_actionCount;
	return ret;
}

bool EvaluationCalculator::Battle()
{
	bool battleFlag = false;
	bool IsWin = false;
	while (!battleFlag)
	{
		//行動している。
		if (m_actionList.size() > 0)
		{
			Action();
			battleFlag = MonsterStateUpdate(IsWin);
		}
		else	//行動していない。
		{
			ActiveTime();
		}
	}

	return IsWin;
}

void EvaluationCalculator::ActiveTime()
{
	//味方の更新。
	for (auto& data : m_members)
	{
		if (data.GetStatusManager()->AddATB())
		{
			m_actionList.push_back({ &data,false });
		}
	}
	//敵側の更新。
	for (auto& data : m_enemys)
	{
		if (data.GetStatusManager()->AddATB())
		{
			m_actionList.push_back({ &data,true });
		}
	}
}

void EvaluationCalculator::Action()
{

	monsterACT = m_actionList.front();

	//行動者が死亡している。
	if (monsterACT.actionMonster->GetStatusManager()->IsDeath())
	{
		m_actionList.erase(m_actionList.begin());
		monsterACT = { nullptr,false };		//初期化。

		return;
	}

	if (m_skillData == nullptr)
	{
		m_skillData = SkillDataLoad::GetInstance();
	}

	int skill, target;
	//行動決定の処理。
	DisideSkill(skill, target);

	//ターゲットリスト作成。
	SetTargetList(skill);

	//スキルを使用する。
	UseSkill(skill, target);

	//敵の行動カウント。
	if (monsterACT.IsEnemy)
	{
		m_actionCount++;
	}
	//m_actionCount++;
	//行動終了。
	m_actionList.erase(m_actionList.begin());
	monsterACT = { nullptr,false };		//初期化。
}

void EvaluationCalculator::DisideSkill(int& skill,int& target)
{
	bool ActionFlag = false;

	//行動の決定。
	monsterACT.actionMonster->GetAIManager().ActionDicide(skill, target);
	//ターゲットの死亡確認。
	if (monsterACT.IsEnemy) {		//敵の行動選択。
		if (m_skillData->IsAttackSkill(skill)) {
			ActionFlag = m_members[target].GetStatusManager()->IsDeath();
		}
		else {
			ActionFlag = m_enemys[target].GetStatusManager()->IsDeath();
		}
	}
	else {							//味方の行動選択。
		if (m_skillData->IsAttackSkill(skill)) {
			ActionFlag = m_enemys[target].GetStatusManager()->IsDeath();
		}
		else {
			ActionFlag = m_members[target].GetStatusManager()->IsDeath();
		}
	}
	//ターゲットが死亡しているなら。
	while (ActionFlag)
	{
		//ランダムでターゲットを変更する。
		target = g_random.GetRandomInt() % en_JobNum;
		//ターゲットの死亡確認。
		if (monsterACT.IsEnemy) {		//敵の行動選択。
			if (m_skillData->IsAttackSkill(skill)) {
				ActionFlag = m_members[target].GetStatusManager()->IsDeath();
			}
			else {
				ActionFlag = m_enemys[target].GetStatusManager()->IsDeath();
			}
		}
		else {							//味方の行動選択。
			if (m_skillData->IsAttackSkill(skill)) {
				ActionFlag = m_enemys[target].GetStatusManager()->IsDeath();
			}
			else {
				ActionFlag = m_members[target].GetStatusManager()->IsDeath();
			}
		}
	}
}

void EvaluationCalculator::SetTargetList(int skill)
{
	//配列をリセット。
	m_targetList.clear();
	m_targetList.resize(en_JobNum);

	MonsterList memberList;		//行動者のチーム。
	memberList.resize(en_JobNum);
	MonsterList enemyList;		//行動者の敵対チーム。
	enemyList.resize(en_JobNum);

	//ターゲットリスト作成。
	if (monsterACT.IsEnemy)		//行動者が敵。
	{
		//味方リスト作成。
		memberList[en_Attacker] = &m_enemys[en_Attacker];
		memberList[en_Healer] = &m_enemys[en_Healer];
		memberList[en_Supporter] = &m_enemys[en_Supporter];
		//敵対者のリスト。
		enemyList[en_Attacker] = &m_members[en_Attacker];
		enemyList[en_Healer] = &m_members[en_Healer];
		enemyList[en_Supporter] = &m_members[en_Supporter];
		
	}
	else		//行動者が味方。
	{
		//味方リスト作成。
		memberList[en_Attacker] = &m_members[en_Attacker];
		memberList[en_Healer] = &m_members[en_Healer];
		memberList[en_Supporter] = &m_members[en_Supporter];
		//敵対者のリスト。
		enemyList[en_Attacker] = &m_enemys[en_Attacker];
		enemyList[en_Healer] = &m_enemys[en_Healer];
		enemyList[en_Supporter] = &m_enemys[en_Supporter];
	}
	if (m_skillData->IsAttackSkill(skill))
	{
		//敵側のリスト作成。
		m_targetList = enemyList;
	}
	else
	{
		//味方のリスト作成。
		m_targetList = memberList;
	}
}

void EvaluationCalculator::UseSkill(const int skill,const int target)
{
	//MPが足りているかどうか。
	if (!m_skillCalc->IsAvailableSkill(
		monsterACT.actionMonster->GetStatusManager(),
		skill)){
		//足りていないなら中断。
		return;
	}
	//スキルを使用する。
	SkillData sData = m_skillData->GetSkillData(skill);
	//全体効果のスキルか？
	if (sData.targetNum == en_JobNum)
	{
		//全体に対して使用。
		for (auto& data : m_targetList)
		{
			m_skillCalc->SkillCalculation(
				monsterACT.actionMonster->GetStatusManager(),
				data->GetStatusManager(),
				skill
			);
		}
	}
	else
	{
		//ターゲットに対して使用。
		m_skillCalc->SkillCalculation(
			monsterACT.actionMonster->GetStatusManager(),
			m_targetList[target]->GetStatusManager(),
			skill
		);
	}
}

bool EvaluationCalculator::MonsterStateUpdate(bool& isWin)
{
	int mDeathNum = 0;
	int eDeathNum = 0;

	//状態更新と戦闘終了かどうか判定。
	for (auto& data : m_members)
	{
		//状態更新。
		data.GetStatusManager()->StateUpdate();
		if (data.GetStatusManager()->IsDeath())
		{
			//死亡数をカウント。
			mDeathNum++;
		}
	}
	//全滅しているなら終了。
	if (mDeathNum == en_JobNum)
	{
		isWin = false;
		return true;
	}
	for (auto& data : m_enemys)
	{
		//状態更新。
		data.GetStatusManager()->StateUpdate();
		if (data.GetStatusManager()->IsDeath())
		{
			//死亡数をカウント。
			eDeathNum++;
		}
	}
	//全滅しているなら戦闘終了。
	if (eDeathNum == en_JobNum)
	{
		isWin = true;
		return true;
	}

	return false;
}
