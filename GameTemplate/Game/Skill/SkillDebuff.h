#pragma once
#include "SkillBase.h"

class SkillDebuff :public SkillBase
{
public:
	void SkillSetting();
	void Update();

	//�G�ɑ΂��Ďg�����B
	bool IsAttack() override
	{
		return true;
	}
	//���@���ǂ����B
	bool IsMagic() override
	{
		return true;
	}

	void SetStatusDebuff(StatusBuff status)
	{
		m_status = status;
	}
private:
	const float DEBUFF_TIME = 100.0f;		//�f�o�t�̌��ʎ���
private:
	int WideDebuff();

	StatusBuff m_status = en_buff_ATK;
};
