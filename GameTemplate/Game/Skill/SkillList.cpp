#include "stdafx.h"
#include "SkillList.h"
#include "SkillDataLoad.h"
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
		//attackSkill->InitSkill(L"通常攻撃", 1.0f, 30.0f, 0.95f, 0);
		attackSkill->SetEffect(L"Assets/effect/test.efk",en_PosUser);
		break;
	case 1:
		//attackSkill->InitSkill(L"強攻撃", 1.8f, 50.0f, 0.85f, 1);
		attackSkill->SetEffect(L"Assets/effect/test.efk", en_PosUser);
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
		//healSkill->InitSkill(L"ヒール", 0.7f, 30.0f, 1.0f, 100);
		healSkill->SetEffect(L"Assets/effect/heal.efk",en_PosTarget);
		break;

	case 1:
		//healSkill->InitSkill(L"ハイヒール", 1.3f, 50.0f, 1.0f, 101);
		healSkill->SetEffect(L"Assets/effect/healS.efk",en_PosTarget);
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
		//buffSkill->InitSkill(L"スクルト", 2.0f, 50.0f, 1.0f, 200);
		buffSkill->SetStatusBuff(en_buff_DEF);
		break;

	case 1:
		//buffSkill->InitSkill(L"スカラ", 1.5f, 60.0f, 1.0f, 201);
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

SkillBase * SkillList::NewSkillMagic(int no)
{
	return nullptr;
}


////ダブルアタック。
//bool DoubleAttack::UseSkill(MonsterBase * attack, MonsterBase * target)
//{
//	if (skillEffect == nullptr) {
//		//エフェクトの再生。
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
//		//ダメージの計算。
//		int damage = DamageCalcuration();
//		res += target->Damage(damage);
//		//２回攻撃。
//		damage = DamageCalcuration();
//		res += target->Damage(damage);
//		
//		//attack->SetActResult(m_skillNo, res);
//
//		//クールタイムの設定。
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

