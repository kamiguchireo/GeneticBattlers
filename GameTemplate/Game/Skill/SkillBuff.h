#pragma once
#include "SkillBase.h"

class SkillBuff : public SkillBase
{
public:
	bool Start();
	void Update();

	bool IsMagic()
	{
		return true;
	}
	bool IsAttack()
	{
		return false;
	}

	void SetStatusBuff(StatusBuff status)
	{
		m_status = status;
	}
private:
	/// <summary>
	/// 全体にバフを掛ける
	/// </summary>
	/// <returns>効果値</returns>
	int WideBuff();

	StatusBuff m_status = en_buff_ATK;
};

