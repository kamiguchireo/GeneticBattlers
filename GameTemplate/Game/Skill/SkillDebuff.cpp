#include "stdafx.h"
#include "SkillDebuff.h"

void SkillDebuff::SkillSetting()
{
	//�G�t�F�N�g�̍Đ��B
	PlaySkill();

	//�A�j���[�V�����̍Đ��B
	m_user->AnimationMagic();
}

void SkillDebuff::Update()
{
	if (m_target->IsDead()) {
		m_target = nullptr;
		m_user = nullptr;
		m_isPlay = false;
		DeleteGO(this);
		return;
	}

	if (!m_skillEffect->IsPlay()) {
		if (m_playSkillPaths.m_effectPaths.size() > m_playEffectNum)
		{
			PlaySkill();
		}
		else
		{
			//���ʒl�B
			int res = 0;
			//�o�t��������B
			if (!m_isWide) {
				//���ʎ��Ԃ��v�Z�B
				//float result = static_cast<float>(m_user->GetStatusManager().GetStatus().HEAL * 5.0f);
				res = m_calculator.SkillCalculation(m_user->GetStatusManager(), m_target->GetStatusManager(), m_skillNo);
			}
			else {	//�S�̂ɂ�����B
				res = WideDebuff();
			}

			//���ʒl���L�^�B
			m_user->SetDamageResult(res);
			////�N�[���^�C���̐ݒ�B
			//m_user->SetCoolTime(coolTime);

			m_isPlay = false;
			m_skillEffect = nullptr;
			m_sound = nullptr;
			DeleteGO(this);
		}
	}
}

void SkillDebuff::SetStatusChange(int status)
{
	switch (status)
	{
	case en_buff_ATK:
		SetStatusDebuff(en_buff_ATK);
		break;
	case en_buff_DEF:
		SetStatusDebuff(en_buff_DEF);
		break;
	case en_buff_MAT:
		SetStatusDebuff(en_buff_MAT);
		break;
	case en_buff_MDF:
		SetStatusDebuff(en_buff_MDF);
		break;
	case en_buff_DEX:
		SetStatusDebuff(en_buff_DEX);
		break;
	default:
		break;
	}
}

int SkillDebuff::WideDebuff()
{
	//�`�[�������o�[���擾�B
	auto list = m_target->GetTeamMenber();

	int res = 0;
	for (int i = 0; i < list.size(); i++) {
		//�S�̂Ƀf�o�t��������B
		res = m_calculator.SkillCalculation(m_user->GetStatusManager(), list[i]->GetStatusManager(), m_skillNo);
	}
	res /= static_cast<int>(list.size());		//�㏸�l�̕��ς��Ƃ�B

	return res;
}
