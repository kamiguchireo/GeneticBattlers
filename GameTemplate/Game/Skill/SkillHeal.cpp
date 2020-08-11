#include "stdafx.h"
#include "SkillHeal.h"

void SkillHeal::SkillSetting()
{
	//�G�t�F�N�g�̍Đ��B
	PlaySkill();

	//�A�j���[�V�����̍Đ��B
	m_user->AnimationMagic();
}

void SkillHeal::Update()
{
	if (m_target->IsDead()) {
		m_target = nullptr;
		m_user = nullptr;
		m_isPlay = false;
		DeleteGO(this);
		return;
	}

	if (!m_skillEffect->IsPlay())
	{
		if (m_playSkillPaths.m_effectPaths.size() > m_playEffectNum)
		{
			PlaySkill();
		}
		else
		{
			int res = 0;
			if (!m_isWide)
			{
				//�񕜁B
				res = m_calculator.SkillCalculation(m_user->GetStatusManager(), m_target->GetStatusManager(), m_skillNo);
			}
			else
			{
				res = WideHeal();
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

int SkillHeal::WideHeal()
{
	//�`�[�������o�[���擾�B
	auto list = m_target->GetTeamMenber();

	int res = 0;
	for (int i = 0; i < list.size(); i++) {
		//�񕜁B
		res = m_calculator.SkillCalculation(m_user->GetStatusManager(), list[i]->GetStatusManager(), m_skillNo);
	}
	res /= static_cast<int>(list.size());		//���ς��Ƃ�B

	return res;
}
