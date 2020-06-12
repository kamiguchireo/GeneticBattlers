#include "stdafx.h"
#include "SkillAttack.h"

bool SkillAttack::Start()
{
	//�G�t�F�N�g�̍Đ��B
	skillEffect = NewGO<prefab::CEffect>(0);
	skillEffect->Play(effectPath);
	skillEffect->SetPosition(m_user->GetPosition() + CVector3::AxisY()*20.0f);
	skillEffect->SetRotation(m_user->GetRotation());
	skillEffect->SetScale(CVector3::One() * 20.0f);

	return true;
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
