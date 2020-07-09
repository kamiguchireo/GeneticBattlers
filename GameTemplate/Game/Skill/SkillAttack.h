#pragma once
#include "SkillBase.h"

class SkillAttack : public SkillBase
{
public:
	void SkillSetting();
	void Update();

	bool IsMagic()override
	{
		return false;
	}
	bool IsAttack()override
	{
		return true;
	}
private:
};

