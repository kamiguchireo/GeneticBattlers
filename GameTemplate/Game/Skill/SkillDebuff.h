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

	void SetStatusDebuff(StatusBuff status)
	{
		m_status = status;
	}

private:
	int WideDebuff();

	StatusBuff m_status = en_buff_ATK;
};

