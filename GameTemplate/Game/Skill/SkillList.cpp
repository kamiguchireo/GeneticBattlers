#include "stdafx.h"
#include "SkillList.h"
#include "SkillDataLoad.h"
#include "SkillAttack.h"
#include "SkillHeal.h"
#include "SkillBuff.h"
#include "SkillMagic.h"
#include "SkillDebuff.h"

SkillList* SkillList::m_instance = nullptr;


SkillList::SkillList()
{
	if (m_instance != nullptr)
	{
		std::abort();
	}

	m_instance = this;

	m_skillData = NewGO<SkillDataLoad>(0);
}

SkillList::~SkillList()
{
	m_instance = nullptr;

	DeleteGO(m_skillData);
}

SkillBase * SkillList::NewSkillData(int table, int no)
{
	SkillBase* useSkill = nullptr;
	switch (table)
	{
	case 0:
		useSkill = NewSkillAttack(no);
		break;

	case 1:
		useSkill = NewSkillHeal(no);
		break;

	case 2:
		useSkill = NewSkillBuff(no);
		break;

	case 3:
		useSkill = NewSkillDebuff(no);
		break;

	default:
		break;
	}
	return useSkill;
}

SkillBase * SkillList::NewSkillAttack(int no)
{
	auto* attackSkill = NewGO<SkillAttack>(0);
	attackSkill->InitSkill(m_skillData->GetSkillAttack(no));
	switch (no)
	{
	case 0:
		//attackSkill->InitSkill(L"�ʏ�U��", 1.0f, 30.0f, 0.95f, 0);
		attackSkill->SetEffect(L"Assets/effect/attack.efk",en_PosTarget);
		break;
	case 1:
		//attackSkill->InitSkill(L"���U��", 1.8f, 50.0f, 0.85f, 1);
		attackSkill->SetEffect(L"Assets/effect/attack2.efk", en_PosTarget);
		break;
	default:
		DeleteGO(attackSkill);
		return nullptr;
		break;
	}
	return attackSkill;
}

SkillBase * SkillList::NewSkillHeal(int no)
{
	auto* healSkill = NewGO<SkillHeal>(0);
	healSkill->InitSkill(m_skillData->GetSkillHeal(no));
	switch (no)
	{
	case 0:
		//healSkill->InitSkill(L"�q�[��", 0.7f, 30.0f, 1.0f, 100);
		healSkill->SetEffect(L"Assets/effect/heal.efk",en_PosTarget);
		break;

	case 1:
		//healSkill->InitSkill(L"�n�C�q�[��", 1.3f, 50.0f, 1.0f, 101);
		healSkill->SetEffect(L"Assets/effect/healS.efk",en_PosTarget);
		break;

	case 2:
		healSkill->SetEffect(L"Assets/effect/heal.efk", en_PosTarget);
		healSkill->SetIsWide(true);
		break;

	default:
		DeleteGO(healSkill);
		return nullptr;
		break;
	}
	return healSkill;
}

SkillBase * SkillList::NewSkillBuff(int no)
{
	auto* buffSkill = NewGO<SkillBuff>(0);
	buffSkill->InitSkill(m_skillData->GetSkillBuff(no));
	switch (no)
	{
	case 0:
		//buffSkill->InitSkill(L"�X�N���g", 2.0f, 50.0f, 1.0f, 200);
		buffSkill->SetStatusBuff(en_buff_DEF);
		buffSkill->SetEffect(L"Assets/effect/BuffDef.efk", en_PosTarget);
		break;

	case 1:
		//buffSkill->InitSkill(L"�X�J��", 1.5f, 60.0f, 1.0f, 201);
		buffSkill->SetStatusBuff(en_buff_DEF);
		buffSkill->SetEffect(L"Assets/effect/BuffDef.efk", en_PosTarget);
		buffSkill->SetIsWide(true);
		break;
	case 2:
		buffSkill->SetStatusBuff(en_buff_ATK);
		buffSkill->SetEffect(L"Assets/effect/BuffAtk.efk", en_PosTarget);
		break;
	default:
		DeleteGO(buffSkill);
		return nullptr;
		break;
	}
	return buffSkill;
}

SkillBase * SkillList::NewSkillDebuff(int no)
{
	//�f�o�t�X�L���̐����B
	auto* debuffSkill = NewGO<SkillDebuff>(0);
	//�f�[�^�擾�B
	debuffSkill->InitSkill(m_skillData->GetSkillDebuff(no));
	switch (no)
	{
	case 0:
		debuffSkill->SetStatusDebuff(en_buff_DEF);
		debuffSkill->SetEffect(L"Assets/effect/DebuffDef.efk", en_PosTarget);
		break;

	case 1:
		debuffSkill->SetStatusDebuff(en_buff_DEX);
		debuffSkill->SetEffect(L"Assets/effect/DebuffDex.efk", en_PosTarget);
		break;
	default:
		DeleteGO(debuffSkill);
		return nullptr;
		break;
	}
	return debuffSkill;
}

//SkillBase * SkillList::NewSkillMagic(int no)
//{
//	return nullptr;
//}


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

