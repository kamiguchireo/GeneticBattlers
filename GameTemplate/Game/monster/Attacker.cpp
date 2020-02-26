#include "stdafx.h"
#include "Attacker.h"
#include "Skill/SkillList.h"

Attacker::Attacker()
{
}

Attacker::~Attacker()
{
}

bool Attacker::Start()
{
	m_model.Init(L"Assets/modelData/testModel.cmo");
	
	//アニメーションクリップの読み込み。
	m_animClip[en_anim_Idle].Load(L"Assets/animData/TestIdle.tka");
	m_animClip[en_anim_Idle].SetLoopFlag(true);
	m_animClip[en_anim_Attack].Load(L"Assets/animData/TestAttack.tka");
	m_animClip[en_anim_Attack].SetLoopFlag(false);
	m_animClip[en_anim_Damage].Load(L"Assets/animData/TestDamage.tka");
	m_animClip[en_anim_Damage].SetLoopFlag(false);
	m_animClip[en_anim_Death].Load(L"Assets/animData/TestDeath.tka");
	m_animClip[en_anim_Death].SetLoopFlag(false);

	//アニメーションの設定。
	m_animation.Init(
		m_model,
		m_animClip,
		en_anim_num
	);

	return true;
}

void Attacker::Update()
{
	switch (m_stateAI)
	{
	case en_state_Death:
		if (!IsDeath) {
			IsDeath = true;
			m_animation.Play(en_anim_Death, 0.3f);
		}

		break;
	default:
		//アニメーションされていないなら。
		if (!m_animation.IsPlaying()) {
			m_animation.Play(en_anim_Idle, 0.3f);
		}

		break;
	}
	//描画処理。
	Draw();
	//アニメーションの更新処理。
	m_animation.Update(1.0f / 30.0f);
}

bool Attacker::BattleAction()
{
	MonsterBase* attack = this;

	bool flag = m_useSkill->UseSkill(attack, m_target);

	m_animation.Play(en_anim_Attack, 0.3f);

	if (m_useSkill != nullptr && flag)
	{
		m_useSkill = nullptr;
		m_target = nullptr;
	}

	return flag;
}

void Attacker::SelectUseSkill(const std::vector<MonsterBase*>& list)
{
	//if (m_useSkill != nullptr) return;

	SkillList* skillList = SkillList::GetInstance();

	//int listSize = list.size();
	int res = rand() % 10;	//適当な乱数。

	//残りHPに応じて行動を決める。
	switch (m_stateAI)
	{
	case en_state_Good:
		if (res < 3) {
			m_useSkill = skillList->GetSkillData(0, 1);
		}
		else {
			m_useSkill = skillList->GetSkillData(0, 0);
		}
		m_target = list[rand() % list.size()];
		break;

	case en_state_Usually:
		if (res < 5) {
			m_useSkill = skillList->GetSkillData(0, 1);
		}
		else {
			m_useSkill = skillList->GetSkillData(0, 0);
		}
		m_target = list[rand() % list.size()];
		break;

	case en_state_Bad:
		m_useSkill = skillList->GetSkillData(0, 1);
		m_target = list[rand() % list.size()];
		break;

	case en_state_Death:
		break;
	}
}
