#include "stdafx.h"
#include "SkillList.h"

SkillList*SkillList::m_instance = nullptr;

SkillList::SkillList()
{
	if (m_instance != nullptr)
	{
		std::abort();
	}

	m_instance = this;

	//通常行動。
	const int typeNum = 3;
	SkillTable typeList[typeNum];
	auto attack = NewGO<Attack>(0);		//通常攻撃。
	attack->InitSkill("通常攻撃", 1.0f, 30.0f, 0.95f, 0);
	attack->SetEffect(L"Assets/effect/test.efk");
	typeList[0].push_back(attack);
	auto doublAttack = NewGO<DoubleAttack>(0);		//ダブルアタック。
	doublAttack->InitSkill("ダブルアタック", 1.0f, 50.0f, 0.85f, 1);
	typeList[0].push_back(doublAttack);

	//回復魔法。
	auto heal = NewGO<Heal>(0);		//ヒール。
	heal->InitSkill("ヒール", 0.7f, 30.0f, 1.0f, 100, en_elements_Empty, true);
	typeList[1].push_back(heal);
	auto hiheal = NewGO<Heal>(0);	//ハイヒール。
	hiheal->InitSkill("ハイヒール", 1.3f, 50.0f, 1.0f, 101, en_elements_Empty, true);
	typeList[1].push_back(hiheal);

	//バフ魔法
	auto sukuruto = NewGO<BuffSkill>(0);	//スクルト。
	sukuruto->InitSkill("スクルト", 2.0f, 50.0f, 1.0f, 200, en_elements_Empty, true);
	sukuruto->SetStatusBuff(en_buff_DEF);
	typeList[2].push_back(sukuruto);
	auto sukara = NewGO<BuffSkillWide>(0);
	sukara->InitSkill("スカラ", 1.5f, 60.0f, 1.0f, 201, en_elements_Empty, true);
	sukara->SetStatusBuff(en_buff_DEF);
	typeList[2].push_back(sukara);
	
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
	if(skillEffect == nullptr){
		//エフェクトの再生。
		skillEffect = NewGO<prefab::CEffect>(0);
		skillEffect->Play(effectPath);
		skillEffect->SetPosition(attack->GetPosition() + CVector3::AxisY()*20.0f);
		skillEffect->SetRotation(attack->GetRotation());
		skillEffect->SetScale(CVector3::One() * 20.0f);
	}
	else if (!skillEffect->IsPlay()) {
		//ダメージを与える。
		int damage = DamageCalcuration(attack, target);
		int res = target->Damage(damage);

		attack->SetActResult(m_skillNo, res);
		//クールタイムの設定。
		attack->SetCoolTime(coolTime);

		skillEffect = nullptr;

		return true;
	}

	return false;
}

//ダブルアタック。
bool DoubleAttack::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	if (skillEffect == nullptr) {
		//エフェクトの再生。
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
		int res = 0;
		//ダメージの計算。
		int damage = DamageCalcuration(attack, target);
		res += target->Damage(damage);
		//２回攻撃。
		damage = DamageCalcuration(attack, target);
		res += target->Damage(damage);
		
		attack->SetActResult(m_skillNo, res);

		//クールタイムの設定。
		attack->SetCoolTime(coolTime);

		skillEffect = nullptr;

		return true;
	}


	return false;
}


//ヒール。
bool Heal::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	if (skillEffect == nullptr) {
		//エフェクトの再生。
		skillEffect = NewGO<prefab::CEffect>(0);
		skillEffect->Play(L"Assets/effect/chant1.efk");
		skillEffect->SetPosition(attack->GetPosition() + CVector3::AxisY()*20.0f);
		skillEffect->SetScale(CVector3::One() * 50.0f);
	}
	else if (!skillEffect->IsPlay()) {
		//回復量の計算。
		int result = attack->GetStatus().MAT * skillPower;
		int res = target->Healing(result);
		attack->SetActResult(m_skillNo, res);
		//クールタイムの設定。
		attack->SetCoolTime(coolTime);

		skillEffect = nullptr;

		return true;
	}

	return false;
}

bool BuffSkill::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	if (skillEffect == nullptr) {
		//エフェクトの再生。
		skillEffect = NewGO<prefab::CEffect>(0);
		skillEffect->Play(L"Assets/effect/chant1.efk");
		skillEffect->SetPosition(attack->GetPosition() + CVector3::AxisY()*20.0f);
		skillEffect->SetScale(CVector3::One() * 50.0f);
	}
	else if (!skillEffect->IsPlay()) {
		//効果時間を計算。
		int result = attack->GetStatus().MAT * 5.0f;
		//バフをかける。
		int res = target->Monster_Buff(m_status, skillPower, result);
		attack->SetActResult(m_skillNo, res);
		//クールタイムの設定。
		attack->SetCoolTime(coolTime);

		skillEffect = nullptr;

		return true;
	}

	return false;
}

bool BuffSkillWide::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	if (skillEffect == nullptr) {
		//エフェクトの再生。
		skillEffect = NewGO<prefab::CEffect>(0);
		skillEffect->Play(L"Assets/effect/chant1.efk");
		skillEffect->SetPosition(attack->GetPosition() + CVector3::AxisY()*20.0f);
		skillEffect->SetScale(CVector3::One() * 50.0f);
	}
	else if (!skillEffect->IsPlay()) {
		//効果時間の計算。
		int result = attack->GetStatus().MAT * 5.0f;
		//チームメンバーを取得。
		auto list = target->GetTeamMenber();

		int res = 0;
		for (int i = 0; i < list.size(); i++) {
			//全体にバフをかける。
			res += list[i]->Monster_Buff(m_status, skillPower, result);
		}
		res /= list.size();		//上昇値の平均をとる。
		attack->SetActResult(m_skillNo, res);
		//クールタイムの設定。
		attack->SetCoolTime(coolTime);

		skillEffect = nullptr;

		return true;
	}

	return false;
}
