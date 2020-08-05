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

	if (!skillEffect->IsPlay())
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
				//�񕜗ʂ̌v�Z�B
				int result = static_cast<int>(m_user->GetStatusManager().GetStatus().MAT * skillPower);
				res = m_target->Healing(result);

			}
			else
			{
				res = WideHeal();
			}
			//���ʒl���L�^�B
			m_user->SetDamageResult(res);
			//�N�[���^�C���̐ݒ�B
			m_user->SetCoolTime(coolTime);

			m_isPlay = false;
			skillEffect = nullptr;
			DeleteGO(this);
		}
	}
}

int SkillHeal::WideHeal()
{
	//�񕜗ʂ̌v�Z
	float result = static_cast<float>(m_user->GetStatusManager().GetStatus().MAT * skillPower);
	//�`�[�������o�[���擾�B
	auto list = m_target->GetTeamMenber();

	int res = 0;
	for (int i = 0; i < list.size(); i++) {
		//�S�̂Ƀo�t��������B
		res += list[i]->Healing(static_cast<int>(result));
	}
	res /= static_cast<int>(list.size());		//�㏸�l�̕��ς��Ƃ�B

	return res;
}
