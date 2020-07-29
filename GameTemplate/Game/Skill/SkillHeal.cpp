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
			skillEffect = NewGO<prefab::CEffect>(0);
			skillEffect->Play(m_effectPaths[m_playEffectNum]);
			CVector3 efPos = CreateEffectPosition(m_effectPosFlag[m_playEffectNum]);
			skillEffect->SetPosition(efPos);
			//skillEffect->SetScale(CVector3::One() * 80.0f);

			m_playEffectNum++;
		}
		else
		{
			//�񕜗ʂ̌v�Z�B
			int result = static_cast<int>(m_user->GetStatusManager().GetStatus().MAT * skillPower);
			int res = m_target->Healing(result);

			//���ʒl���L�^�B
			m_user->SetDamageResult(res);
			//�N�[���^�C���̐ݒ�B
			m_user->SetCoolTime(coolTime);

			DeleteGO(this);
		}
	}
}
