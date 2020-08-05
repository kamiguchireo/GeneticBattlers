#include "stdafx.h"
#include "SkillAttack.h"

void SkillAttack::SkillSetting()
{
	//�G�t�F�N�g�̍Đ��B
	PlaySkill();

	//�A�j���[�V�����̍Đ��B
	m_user->AnimationAttack();
}

void SkillAttack::Update()
{
	if (m_target->IsDead()) {
		m_target = nullptr;
		m_user = nullptr;
		m_isPlay = false;
		DeleteGO(this);
		return;
	}
	if (!skillEffect->IsPlay()) {
		if (m_playSkillPaths.m_effectPaths.size() > m_playEffectNum)
		{
			PlaySkill();
		}
		else
		{
			//�_���[�W��^����B
			int damage = DamageCalcuration();
			int res = m_target->Damage(damage);

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
