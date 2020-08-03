#include "stdafx.h"
#include "SkillHeal.h"

void SkillHeal::SkillSetting()
{
	//�G�t�F�N�g�̍Đ��B
	skillEffect = NewGO<prefab::CEffect>(0);
	skillEffect->Play(L"Assets/effect/chant1.efk");
	CVector3 effectPos = CreateEffectPosition(en_PosUser);
	skillEffect->SetPosition(effectPos);
	//skillEffect->SetScale(CVector3::One() * 50.0f);

	//�A�j���[�V�����̍Đ��B
	m_user->AnimationMagic();
}

void SkillHeal::Update()
{
	if (m_target->IsDead()) {
		m_target = nullptr;
		m_user = nullptr;
		DeleteGO(this);
		return;
	}
	//if (m_healEffect == nullptr
	//	&& !skillEffect->IsPlay()) {
	//	//�G�t�F�N�g�̍Đ��B
	//	m_healEffect = NewGO<prefab::CEffect>(0);
	//	m_healEffect->Play(effectPath);
	//	m_healEffect->SetPosition(m_target->GetPosition() + CVector3::AxisY()*20.0f);
	//	m_healEffect->SetScale(CVector3::One()*80.0f);
	//}
	//else if (m_healEffect != nullptr
	//	&& !m_healEffect->IsPlay()) {
	//	//�񕜗ʂ̌v�Z�B
	//	int result = m_user->GetStatusManager().GetStatus().MAT * skillPower;
	//	int res = m_target->Healing(result);

	//	//���ʒl���L�^�B
	//	m_user->SetDamageResult(res);
	//	//�N�[���^�C���̐ݒ�B
	//	m_user->SetCoolTime(coolTime);

	//	m_healEffect = nullptr;
	//	DeleteGO(this);
	//}
	if (!skillEffect->IsPlay())
	{
		if (m_effectPaths.size() > m_playEffectNum)
		{
			if (!m_isWide)
			{
				skillEffect = NewGO<prefab::CEffect>(0);
				skillEffect->Play(m_effectPaths[m_playEffectNum]);
				CVector3 efPos = CreateEffectPosition(m_effectPosFlag[m_playEffectNum]);
				skillEffect->SetPosition(efPos);
			}
			else
			{
				auto list = m_target->GetTeamMenber();

				for (int i = 0; i < list.size(); i++)
				{
					//�����o�[�S�Ă��^�[�Q�b�g����B
					m_target = list[i];
					if (!m_target->IsDeath())
					{
						skillEffect = NewGO<prefab::CEffect>(0);
						skillEffect->Play(m_effectPaths[m_playEffectNum]);
						CVector3 efPos = CreateEffectPosition(m_effectPosFlag[m_playEffectNum]);
						skillEffect->SetPosition(efPos);
					}
				}
			}

			m_playEffectNum++;
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
