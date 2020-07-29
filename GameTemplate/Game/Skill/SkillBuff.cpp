#include "stdafx.h"
#include "SkillBuff.h"

void SkillBuff::SkillSetting()
{
	//�G�t�F�N�g�̍Đ��B
	skillEffect = NewGO<prefab::CEffect>(0);
	skillEffect->Play(L"Assets/effect/chant1.efk");
	CVector3 effectPos = GetEffectPos(en_PosUser);
	skillEffect->SetPosition(effectPos);
	//skillEffect->SetScale(CVector3::One() * 50.0f);

	//�A�j���[�V�����̍Đ��B
	m_user->AnimationMagic();
}

void SkillBuff::Update()
{
	if (m_target->IsDead()) {
		DeleteGO(this);
		return;
	}

	if (!skillEffect->IsPlay()) {
		if (m_effectPaths.size() > m_playEffectNum)
		{
			if (!m_isWide)
			{
				skillEffect = NewGO<prefab::CEffect>(0);
				skillEffect->Play(m_effectPaths[m_playEffectNum]);
				CVector3 efPos = GetEffectPos(m_effectPosFlag[m_playEffectNum]);
				skillEffect->SetPosition(efPos);
			}
			else
			{
				auto list = m_target->GetTeamMenber();

				for (int i = 0; i < list.size(); i++)
				{
					//�����o�[�S�Ă��^�[�Q�b�g����B
					m_target = list[i];
					skillEffect = NewGO<prefab::CEffect>(0);
					skillEffect->Play(m_effectPaths[m_playEffectNum]);
					CVector3 efPos = GetEffectPos(m_effectPosFlag[m_playEffectNum]);
					skillEffect->SetPosition(efPos);
				}
			}

			m_playEffectNum++;
		}
		else
		{
			//���ʒl�B
			int res = 0;
			//�o�t��������B
			if (!m_isWide) {
				//���ʎ��Ԃ��v�Z�B
				float result = static_cast<float>(m_user->GetStatusManager().GetStatus().MAT * 5.0f);
				res = static_cast<int>(m_target->Monster_Buff(m_status, skillPower, result));
			}
			else {	//�S�̂ɂ�����B
				res = WideBuff();
			}

			//���ʒl���L�^�B
			m_user->SetDamageResult(res);
			//�N�[���^�C���̐ݒ�B
			m_user->SetCoolTime(coolTime);

			skillEffect = nullptr;
			DeleteGO(this);
		}
	}
}

int SkillBuff::WideBuff()
{
	//���ʎ��Ԃ̌v�Z�B
	float result = static_cast<float>(m_user->GetStatusManager().GetStatus().MAT * 5.0f);
	//�`�[�������o�[���擾�B
	auto list = m_target->GetTeamMenber();

	int res = 0;
	for (int i = 0; i < list.size(); i++) {
		//�S�̂Ƀo�t��������B
		res += static_cast<int>(list[i]->Monster_Buff(m_status, skillPower, result));
	}
	res /= static_cast<int>(list.size());		//�㏸�l�̕��ς��Ƃ�B

	return res;
}
