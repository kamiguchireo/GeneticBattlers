#pragma once
#include "Skill/SkillBase.h"

struct SkillData;

class SkillList : public IGameObject
{
public:
	SkillList();
	~SkillList();

	virtual bool UseSkill() { return false; };

private:
	//std::vector<SkillData>m_skillList;
};

