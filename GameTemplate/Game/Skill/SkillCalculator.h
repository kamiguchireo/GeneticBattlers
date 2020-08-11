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

	int SkillCalculation(CStatusBase* user, CStatusBase* target,int SkillNo);
	int SkillCalculation(CStatusBase* user, std::vector<CStatusBase*> targets, int SkillNo);

private:
	int AttackCalculation(CStatusBase* user, CStatusBase* target, int SkillNo);
	int HealCalculation(CStatusBase* user, CStatusBase* target, int SkillNo);
	int BuffCalculation(CStatusBase* user, CStatusBase* target, int SkillNo);
	int DebuffCalculation(CStatusBase* user, CStatusBase* target, int SkillNo);

	SkillDataLoad* m_skillData = nullptr;
	const float BUFF_TIME = 100.0f;		//ステータス変化の基本効果時間。
};

