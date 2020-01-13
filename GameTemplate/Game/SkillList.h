#pragma once

/// <summary>
/// スキルデータの構造体。
/// 名前。
/// スキルの威力。
/// 消費MP量。
/// </summary>
struct SkillData {
	char skillName[30];
	int skillPower = 1;
	int useMP = 0;
};

class SkillList
{
public:
	SkillList();
	~SkillList();
private:
	std::vector<SkillData>m_skillList;
};

