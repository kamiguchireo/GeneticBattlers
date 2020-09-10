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
	//スキル情報を読み込む。
	m_skillData = SkillDataLoad::GetInstance();
	if (m_skillData == nullptr)
	{
		m_skillData = NewGO<SkillDataLoad>(0);
	}
}

SkillList::~SkillList()
{
	m_instance = nullptr;

	//DeleteGO(m_skillData);
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
		attackSkill->InitSkill(L"通常攻撃", 1.0f, 30.0f, 0.95f, 0);
		attackSkill->SetEffect(
			L"Assets/effect/attack.efk",
			en_PosTarget,
			L"Assets/sound/battle/feed1.wav");
		break;
	case 1:
		attackSkill->InitSkill(L"強攻撃", 1.8f, 50.0f, 0.85f, 1);
		attackSkill->SetEffect(
			L"Assets/effect/attack2.efk",
			en_PosTarget,
			L"Assets/sound/battle/kick-high1.wav");
		break;
	case 3:
		attackSkill->SetEffect(
			L"Assets/effect/wideAttack.efk",
			en_PosTarget,
			L"Assets/sound/battle/kick-high1.wav");

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
		healSkill->SetEffect(L"Assets/effect/chant1.efk", en_PosUser, L"Assets/sound/battle/magic-cure1.wav");
		healSkill->SetEffect(L"Assets/effect/heal.efk",en_PosTarget,L"Assets/sound/battle/magic-status-cure1.wav");
		break;

	case 1:
		healSkill->SetEffect(L"Assets/effect/chant1.efk", en_PosUser, L"Assets/sound/battle/magic-cure1.wav");
		healSkill->SetEffect(L"Assets/effect/healS.efk",en_PosTarget, L"Assets/sound/battle/magic-status-cure1.wav");
		break;

	case 2:
		healSkill->SetEffect(L"Assets/effect/chant1.efk", en_PosUser, L"Assets/sound/battle/magic-cure1.wav");
		healSkill->SetEffect(L"Assets/effect/heal.efk", en_PosTarget, L"Assets/sound/battle/magic-status-cure1.wav");
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
		buffSkill->SetEffect(L"Assets/effect/chant1.efk", en_PosUser, L"Assets/sound/battle/magic-cure1.wav");
		buffSkill->SetEffect(L"Assets/effect/BuffDef.efk", en_PosTarget,L"Assets/sound/battle/aura1.wav");
		break;

	case 1:
		buffSkill->SetEffect(L"Assets/effect/chant1.efk", en_PosUser, L"Assets/sound/battle/magic-cure1.wav");
		buffSkill->SetEffect(L"Assets/effect/BuffDef.efk", en_PosTarget, L"Assets/sound/battle/aura1.wav");
		break;
	case 2:
		buffSkill->SetEffect(L"Assets/effect/chant1.efk", en_PosUser, L"Assets/sound/battle/magic-cure1.wav");
		buffSkill->SetEffect(L"Assets/effect/BuffAtk.efk", en_PosTarget, L"Assets/sound/battle/aura1.wav");
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
	//デバフスキルの生成。
	auto* debuffSkill = NewGO<SkillDebuff>(0);
	//データ取得。
	debuffSkill->InitSkill(m_skillData->GetSkillDebuff(no));
	switch (no)
	{
	case 0:
		debuffSkill->SetEffect(L"Assets/effect/chant1.efk", en_PosUser, L"Assets/sound/battle/magic-cure1.wav");
		debuffSkill->SetEffect(L"Assets/effect/DebuffDef.efk", en_PosTarget, L"Assets/sound/battle/magic-gravity1.wav");
		break;

	case 1:
		debuffSkill->SetEffect(L"Assets/effect/chant1.efk", en_PosUser, L"Assets/sound/battle/magic-cure1.wav");
		debuffSkill->SetEffect(L"Assets/effect/DebuffDex.efk", en_PosTarget, L"Assets/sound/battle/magic-gravity1.wav");
		break;
	default:
		DeleteGO(debuffSkill);
		return nullptr;
		break;
	}
	return debuffSkill;
}

