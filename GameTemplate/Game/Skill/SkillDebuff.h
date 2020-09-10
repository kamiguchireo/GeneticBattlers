#pragma once
#include "SkillBase.h"

class SkillDebuff :public SkillBase
{
public:
	void SkillSetting();
	void Update();

	//敵に対して使うか。
	bool IsAttack() override
	{
		return true;
	}
	//魔法かどうか。
	bool IsMagic() override
	{
		return true;
	}

private:
	const float DEBUFF_TIME = 100.0f;		//デバフの効果時間
private:
	int WideDebuff();
};

