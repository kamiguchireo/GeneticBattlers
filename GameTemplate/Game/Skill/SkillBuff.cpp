#include "stdafx.h"
#include "SkillBuff.h"

void SkillBuff::SkillSetting()
{
	//�G�t�F�N�g�̍Đ��B
	PlaySkill();

	//�A�j���[�V�����̍Đ��B
	m_user->AnimationMagic();
}

void SkillBuff::Update()
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
			m_isPlay = false;
			//���ʒl�B
			int res = 0;
			//�o�t��������B
			if (!m_isWide) {
				//���ʎ��Ԃ��v�Z�B
				//float result = static_cast<float>(m_user->GetStatusManager().GetStatus().MAT * 5.0f);
				res = m_target->MonsterBuffAndDebuff(m_status, skillPower, BUFF_TIME);
			}
			else {	//�S�̂ɂ�����B
				res = WideBuff();
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

int SkillBuff::WideBuff()
{
	//�`�[�������o�[���擾�B
	auto list = m_target->GetTeamMenber();

	int res = 0;
	for (int i = 0; i < list.size(); i++) {
		//�S�̂Ƀo�t��������B
		res += list[i]->MonsterBuffAndDebuff(m_status, skillPower, BUFF_TIME);
	}
	res /= static_cast<int>(list.size());		//�㏸�l�̕��ς��Ƃ�B

	return res;
}
