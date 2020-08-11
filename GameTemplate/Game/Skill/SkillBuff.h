#pragma once
#include "SkillBase.h"

class SkillBuff : public SkillBase
{
public:
	void SkillSetting();
	void Update();

	bool IsMagic()
	{
		return true;
	}
	bool IsAttack()
	{
		return false;
	}
	void SetStatusChange(int status)override;
	void SetStatusBuff(StatusBuff status)
	{
		m_status = status;
	}
private:
	const float BUFF_TIME = 100.0f;		//�o�t�̌��ʎ��ԁB
private:
	/// <summary>
	/// �S�̂Ƀo�t���|����
	/// </summary>
	/// <returns>���ʒl</returns>
	int WideBuff();

	StatusBuff m_status = en_buff_ATK;
};

