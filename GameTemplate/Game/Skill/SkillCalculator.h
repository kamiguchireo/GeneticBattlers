#pragma once

struct Status;
struct SkillData;

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
	/// <summary>
	/// MPが足りているかどうか。
	/// </summary>
	/// <param name="user">使用者のステータス。</param>
	/// <param name="SkillNo">使用するスキル番号。</param>
	/// <returns>使用可能かどうか。trueで使用可能,falseでMPが足りていない。</returns>
	bool IsAvailableSkill(CStatusBase* user, const int SkillNo);

private:
	//関数。
	int AttackCalculation(CStatusBase* user, CStatusBase* target, SkillData& skill);		//攻撃スキル。
	int HealCalculation(CStatusBase* user, CStatusBase* target, SkillData& skill);		//回復スキル。
	int BuffCalculation(CStatusBase* user, CStatusBase* target, SkillData& skill);		//バフスキル。
	int DebuffCalculation(CStatusBase* user, CStatusBase* target, SkillData& skill);		//デバフスキル。

	SkillDataLoad* m_skillData = nullptr;	//スキル情報を持つのクラス
	const float BUFF_TIME = 100.0f;		//ステータス変化の基本効果時間。
};

