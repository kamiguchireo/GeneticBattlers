#pragma once

struct Status;

class CStatusBase;
class SkillDataLoad;

/// <summary>
/// スキル効果計算クラス。
/// </summary>

class SkillCalculator
{
public:
	SkillCalculator();
	~SkillCalculator();

	//スキルの処理を計算する。
	int SkillCalculation(CStatusBase* user, CStatusBase* target,int SkillNo);
	int SkillCalculation(CStatusBase* user, std::vector<CStatusBase*> targets, int SkillNo);

private:
	//関数。
	int AttackCalculation(CStatusBase* user, CStatusBase* target, int SkillNo);		//攻撃スキル。
	int HealCalculation(CStatusBase* user, CStatusBase* target, int SkillNo);		//回復スキル。
	int BuffCalculation(CStatusBase* user, CStatusBase* target, int SkillNo);		//バフスキル。
	int DebuffCalculation(CStatusBase* user, CStatusBase* target, int SkillNo);		//デバフスキル。

	SkillDataLoad* m_skillData = nullptr;	//スキル情報を持つのクラス
	const float BUFF_TIME = 100.0f;		//ステータス変化の基本効果時間。
};

