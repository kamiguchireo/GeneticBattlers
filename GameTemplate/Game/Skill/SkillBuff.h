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
	/// �S�̂Ƀo�t���|����
	/// </summary>
	/// <returns>���ʒl</returns>
	int WideBuff();

	StatusBuff m_status = en_buff_ATK;
};

