#pragma once
#include "SkillBase.h"

class SkillMagic : public SkillBase
{
	bool Start();
	void Update();

	bool IsMagic()
	{
		return true;
	}

	bool IsAttack()
	{
		return true;
	}
};

