#include "stdafx.h"
#include "SkillList.h"
#include "monster/MonsterBase.h"

SkillList*SkillList::m_instance = nullptr;

SkillList::SkillList()
{
	if (m_instance != nullptr)
	{
		std::abort();
	}

	m_instance = this;

	//�ʏ�s���B
	const int typeNum = 2;
	SkillTable typeList[typeNum];
	auto attack = NewGO<Attack>(0);		//�ʏ�U���B
	attack->InitSkill("�ʏ�U��", 1.0f, 30.0f, 0.95f, 0);
	attack->SetEffect(L"Assets/effect/test.efk");
	typeList[0].push_back(attack);
	auto doublAttack = NewGO<DoubleAttack>(0);		//�_�u���A�^�b�N�B
	doublAttack->InitSkill("�_�u���A�^�b�N", 1.0f, 50.0f, 0.85f, 1);
	typeList[0].push_back(doublAttack);

	//�񕜖��@�B
	auto heal = NewGO<Heal>(0);		//�q�[���B
	heal->InitSkill("�q�[��", 1.0f, 30.0f, 1.0f, 100, en_elements_Empty, true);
	typeList[1].push_back(heal);
	auto hiheal = NewGO<Heal>(0);	//�n�C�q�[���B
	hiheal->InitSkill("�n�C�q�[��", 2.0f, 50.0f, 1.0f, 101, en_elements_Empty, true);
	typeList[1].push_back(hiheal);

	for (int i = 0; i < typeNum; i++)
	{
		m_skillList.push_back(typeList[i]);
	}
}

SkillList::~SkillList()
{
	for (SkillTable table : m_skillList)
	{
		for (SkillBase* SB : table)
		{
			DeleteGO(SB);
		}
	}

	m_instance = nullptr;
}

//�ʏ�U���B
bool Attack::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	if(skillEffect == nullptr){
		skillEffect = NewGO<prefab::CEffect>(0);
		//skillEffect->Play(L"Assets/effect/test.efk");
		skillEffect->Play(effectPath);
		skillEffect->SetPosition(attack->GetPosition() + CVector3::AxisY()*20.0f);
		skillEffect->SetRotation(attack->GetRotation());
		skillEffect->SetScale(CVector3::One() * 20.0f);
	}
	else if (!skillEffect->IsPlay()) {
		int damage = DamageCalcuration(attack, target);

		target->Damage(damage);
		attack->SetCoolTime(coolTime);

		skillEffect = nullptr;

		return true;
	}

	return false;
}

//�_�u���A�^�b�N�B
bool DoubleAttack::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	if (skillEffect == nullptr) {
		skillEffect = NewGO<prefab::CEffect>(0);
		skillEffect->Play(L"Assets/effect/test.efk");
		skillEffect->SetPosition(attack->GetPosition() + CVector3::AxisY()*20.0f);
		CQuaternion qRot;
		qRot.SetRotationDeg(CVector3::AxisY(), 90.0f);
		qRot.Multiply(attack->GetRotation());
		skillEffect->SetRotation(qRot);
		skillEffect->SetScale(CVector3::One() * 20.0f);
	}
	else if (!skillEffect->IsPlay()) {
		int damage = DamageCalcuration(attack, target);

		target->Damage(damage);

		damage = DamageCalcuration(attack, target);

		target->Damage(damage);
		attack->SetCoolTime(coolTime);

		skillEffect = nullptr;

		return true;
	}


	return false;
}


//�q�[���B
bool Heal::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	if (skillEffect == nullptr) {
		skillEffect = NewGO<prefab::CEffect>(0);
		skillEffect->Play(L"Assets/effect/chant1.efk");
		skillEffect->SetPosition(attack->GetPosition() + CVector3::AxisY()*20.0f);
		skillEffect->SetScale(CVector3::One() * 50.0f);
	}
	else if (!skillEffect->IsPlay()) {
		int result = attack->GetStatus().MAT * skillPower;

		target->Healing(result);
		attack->SetCoolTime(coolTime);

		skillEffect = nullptr;

		return true;
	}

	return false;
}
