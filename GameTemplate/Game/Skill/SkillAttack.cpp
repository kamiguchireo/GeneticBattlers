#include "stdafx.h"
#include "SkillAttack.h"

void SkillAttack::SkillSetting()
{
	//�G�t�F�N�g�̍Đ��B
	skillEffect = NewGO<prefab::CEffect>(0);
	skillEffect->Play(m_effectPaths[m_playEffectNum]);
	CVector3 effectPos = CreateEffectPosition(m_effectPosFlag[m_playEffectNum]);
	skillEffect->SetPosition(effectPos);
	CQuaternion effectRot = CreateEffectRotation(m_effectPosFlag[m_playEffectNum]);
	skillEffect->SetRotation(m_user->GetRotation());
	//skillEffect->SetScale(CVector3::One() * 20.0f);

	m_playEffectNum++;

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
		if (m_effectPaths.size() > m_playEffectNum)
		{
			skillEffect = NewGO<prefab::CEffect>(0);
			skillEffect->Play(m_effectPaths[m_playEffectNum]);
			CVector3 efPos = CreateEffectPosition(m_effectPosFlag[m_playEffectNum]);
			skillEffect->SetPosition(efPos);

			m_playEffectNum++;
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
