#pragma once
#include "Skill/SkillBase.h"

struct SkillData;

class SkillList
{
public:
	SkillList();
	~SkillList();
private:
	std::vector<SkillData>m_skillList;
};

