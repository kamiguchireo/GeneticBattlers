#pragma once
#include "SkillBase.h"

class SkillAttack : public SkillBase
{
public:
	bool Start();
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

