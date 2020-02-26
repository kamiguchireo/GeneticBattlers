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

	//通常行動。
	const int typeNum = 2;
	SkillTable typeList[typeNum];
	auto attack = NewGO<Attack>(0);
	attack->InitSkill("通常攻撃", 1.0f, 30.0f, 0.95f, 0);
	attack->SetEffect(L"Assets/effect/test.efk");
	typeList[0].push_back(attack);
	auto doublAttack = NewGO<DoubleAttack>(0);
	doublAttack->InitSkill("ダブルアタック", 1.0f, 50.0f, 0.85f, 1);
	typeList[0].push_back(doublAttack);

	//回復魔法。
	auto heal = NewGO<Heal>(0);
	heal->InitSkill("ヒール", 1.0f, 30.0f, 1.0f, 100, en_elements_Empty, true);
	typeList[1].push_back(heal);


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

//通常攻撃。
bool Attack::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	static int skilltime = 0;
	if(skillEffect == nullptr){
		skillEffect = NewGO<prefab::CEffect>(0);
		//skillEffect->Play(L"Assets/effect/test.efk");
		skillEffect->Play(effectPath);
		skillEffect->SetPosition(attack->GetPosition() + CVector3::AxisY()*20.0f);
		skillEffect->SetRotation(attack->GetRotation());
		skillEffect->SetScale(CVector3::One() * 20.0f);
		skilltime = 0;
	}
	else if (skilltime > 20) {
		int damage = DamageCalcuration(attack, target);

		target->Damage(damage);
		attack->SetCoolTime(coolTime);

		skillEffect = nullptr;

		return true;
	}

	skilltime++;

	return false;
}

//ダブルアタック。
bool DoubleAttack::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	static int skilltime = 0;
	if (skillEffect == nullptr) {
		skillEffect = NewGO<prefab::CEffect>(0);
		skillEffect->Play(L"Assets/effect/test.efk");
		skillEffect->SetPosition(attack->GetPosition() + CVector3::AxisY()*20.0f);
		CQuaternion qRot;
		qRot.SetRotationDeg(CVector3::AxisY(), 90.0f);
		qRot.Multiply(attack->GetRotation());
		skillEffect->SetRotation(qRot);
		skillEffect->SetScale(CVector3::One() * 20.0f);
		skilltime = 0;
	}
	else if (skilltime > 20) {
		int damage = DamageCalcuration(attack, target);

		target->Damage(damage);

		damage = DamageCalcuration(attack, target);

		target->Damage(damage);
		attack->SetCoolTime(coolTime);

		skillEffect = nullptr;

		return true;
	}

	skilltime++;

	return false;
}


//ヒール。
bool Heal::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	int result = attack->GetStatus().MAT * skillPower;

	target->Healing(result);

	return false;
}
