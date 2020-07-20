#include "stdafx.h"
#include "SkillAttack.h"

void SkillAttack::SkillSetting()
{
	//�G�t�F�N�g�̍Đ��B
	skillEffect = NewGO<prefab::CEffect>(0);
	skillEffect->Play(m_effectPaths[m_playEffectNum]);
	CVector3 effectPos = GetEffectPos(en_PosUser);
	skillEffect->SetPosition(effectPos);
	skillEffect->SetRotation(m_user->GetRotation());
	//skillEffect->SetScale(CVector3::One() * 20.0f);

	m_playEffectNum++;

	//�A�j���[�V�����̍Đ��B
	m_user->AnimationAttack();
}

void SkillAttack::Update()
{
	if (!skillEffect->IsPlay()) {
		//�_���[�W��^����B
		int damage = DamageCalcuration();
		int res = m_target->Damage(damage);

		//���ʒl���L�^�B
		m_user->SetDamageResult(res);
		//�N�[���^�C���̐ݒ�B
		m_user->SetCoolTime(coolTime);

		skillEffect = nullptr;
		DeleteGO(this);
	}
}
