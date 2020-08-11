#pragma once

struct Status;

class StatusBase;
class SkillDataLoad;

/// <summary>
/// スキル効果計算クラス。
/// </summary>

class SkillCalculator
{
public:
	SkillCalculator();
	~SkillCalculator();

	int SkillCalculation(Status& user, Status& target,int SkillNo);
	int SkillCalculation(Status&user, std::vector<Status&>targets, int SkillNo);

private:
	int AttackCalculation(Status& user, Status& target, int SkillNo);
	int HealCalculation(Status& user, Status& target, int SkillNo);
	int BuffCalculation(Status& user, Status& target, int SkillNo);
	int DebuffCalculation(Status& user, Status& target, int SkillNo);

	SkillDataLoad* m_skillData = nullptr;
};

