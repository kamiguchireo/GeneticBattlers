#include "stdafx.h"
#include "SkillList.h"
#include "SkillAttack.h"
#include "SkillHeal.h"
#include "SkillBuff.h"
#include "SkillMagic.h"

SkillList* SkillList::m_instance = nullptr;


SkillList::SkillList()
{
	if (m_instance != nullptr)
	{
		std::abort();
	}

	m_instance = this;
}

SkillList::~SkillList()
{
	m_instance = nullptr;
}

SkillBase * SkillList::GetSkillData(int table, int no)
{
	SkillBase* useSkill = nullptr;
	switch (table)
	{
	case 0:
		useSkill = GetSkillAttack(no);
		break;

	case 1:
		useSkill = GetSkillHeal(no);
		break;

	case 2:
		useSkill = GetSkillBuff(no);
		break;

	default:
		break;
	}
	return useSkill;
}

SkillBase * SkillList::GetSkillAttack(int no)
{
	auto* attackSkill = NewGO<SkillAttack>(0);
	switch (no)
	{
	case 0:
		attackSkill->InitSkill(L"�ʏ�U��", 1.0f, 30.0f, 0.95f, 0);
		attackSkill->SetEffect(L"Assets/effect/test.efk",en_PosUser);
		break;
	case 1:
		attackSkill->InitSkill(L"���U��", 1.8f, 50.0f, 0.85f, 1);
		attackSkill->SetEffect(L"Assets/effect/test.efk", en_PosUser);
		break;
	default:
		DeleteGO(attackSkill);
		return nullptr;
		break;
	}
	return attackSkill;
}

SkillBase * SkillList::GetSkillHeal(int no)
{
	auto* healSkill = NewGO<SkillHeal>(0);
	switch (no)
	{
	case 0:
		healSkill->InitSkill(L"�q�[��", 0.7f, 30.0f, 1.0f, 100);
		healSkill->SetEffect(L"Assets/effect/heal.efk",en_PosTarget);
		break;

	case 1:
		healSkill->InitSkill(L"�n�C�q�[��", 1.3f, 50.0f, 1.0f, 101);
		healSkill->SetEffect(L"Assets/effect/healS.efk",en_PosTarget);
		break;

	default:
		DeleteGO(healSkill);
		return nullptr;
		break;
	}
	return healSkill;
}

SkillBase * SkillList::GetSkillBuff(int no)
{
	auto* buffSkill = NewGO<SkillBuff>(0);
	switch (no)
	{
	case 0:
		buffSkill->InitSkill(L"�X�N���g", 2.0f, 50.0f, 1.0f, 200);
		buffSkill->SetStatusBuff(en_buff_DEF);
		break;

	case 1:
		buffSkill->InitSkill(L"�X�J��", 1.5f, 60.0f, 1.0f, 201);
		buffSkill->SetStatusBuff(en_buff_DEF);
		buffSkill->SetIsWide(true);
		break;

	default:
		DeleteGO(buffSkill);
		return nullptr;
		break;
	}
	return buffSkill;
}

SkillBase * SkillList::GetSkillMagic(int no)
{
	return nullptr;
}


////�_�u���A�^�b�N�B
//bool DoubleAttack::UseSkill(MonsterBase * attack, MonsterBase * target)
//{
//	if (skillEffect == nullptr) {
//		//�G�t�F�N�g�̍Đ��B
//		skillEffect = NewGO<prefab::CEffect>(0);
//		skillEffect->Play(L"Assets/effect/test.efk");
//		skillEffect->SetPosition(attack->GetPosition() + CVector3::AxisY()*20.0f);
//		CQuaternion qRot;
//		qRot.SetRotationDeg(CVector3::AxisY(), 90.0f);
//		qRot.Multiply(attack->GetRotation());
//		skillEffect->SetRotation(qRot);
//		skillEffect->SetScale(CVector3::One() * 20.0f);
//	}
//	else if (!skillEffect->IsPlay()) {
//		int res = 0;
//		//�_���[�W�̌v�Z�B
//		int damage = DamageCalcuration();
//		res += target->Damage(damage);
//		//�Q��U���B
//		damage = DamageCalcuration();
//		res += target->Damage(damage);
//		
//		//attack->SetActResult(m_skillNo, res);
//
//		//�N�[���^�C���̐ݒ�B
//		attack->SetCoolTime(coolTime);
//
//		skillEffect = nullptr;
//
//		return true;
//	}
//
//
//	return false;
//}

