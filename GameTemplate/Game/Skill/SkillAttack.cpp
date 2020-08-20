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
	if (!m_skillEffect->IsPlay()) {
		if (m_playSkillPaths.m_effectPaths.size() > m_playEffectNum)
		{
			PlaySkill();
		}
		else
		{
			int res = 0;
			if (!m_isWide) {
				//�_���[�W��^����B
				res = m_calculator.SkillCalculation(m_user->GetStatusManager(), m_target->GetStatusManager(), m_skillNo);
				m_target->Damage(res);
			}
			else {	//�S�̂ɂ�����B
				res = WideAttack();
			}

			//���ʒl���L�^�B
			m_user->SetDamageResult(res);

			m_isPlay = false;
			m_skillEffect = nullptr;
			m_sound = nullptr;
			DeleteGO(this);
		}
	}
}

int SkillAttack::WideAttack()
{
	//�`�[�������o�[���擾�B
	auto list = m_target->GetTeamMenber();

	int res = 0;
	for (int i = 0; i < list.size(); i++) {
		int damage = m_calculator.SkillCalculation(m_user->GetStatusManager(), list[i]->GetStatusManager(), m_skillNo);
		if (!m_target->IsDeath()) {
			m_target->Damage(damage);		//���S���Ă��Ȃ��Ȃ�_���[�W���o�B
		}
		res += damage;
	}
	res /= static_cast<int>(list.size());		//�㏸�l�̕��ς��Ƃ�B

	return res;
}
