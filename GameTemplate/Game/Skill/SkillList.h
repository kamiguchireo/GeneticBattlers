#pragma once
#include "Skill/SkillBase.h"

struct SkillData;
class MonsterBase;

class SkillList : public IGameObject
{
public:
	SkillList();
	~SkillList();

	//virtual bool UseSkill() { return false; };

private:
	//std::vector<SkillData>m_skillList;
};

class Attack : public SkillBase
{
public:
	Attack() {
		sprintf_s(skillName, "í èÌçUåÇ");
		skillPower = 1.0f;
		useMP = 0;
		m_skillElements = en_elements_Empty;
	}
	bool UseSkill(MonsterBase* attack,MonsterBase* target);
private:
	
};

