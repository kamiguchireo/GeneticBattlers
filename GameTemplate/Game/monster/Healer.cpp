#include "stdafx.h"
#include "Healer.h"
#include "Skill/SkillList.h"

Healer::Healer()
{
}

Healer::~Healer()
{
}

bool Healer::Start()
{
	m_model.Init(L"Assets/modelData/testModel.cmo");
	m_model.SetActiveDLFlag(0);
	m_model.SetActiveRLFlag(0);

	//アニメーションクリップの読み込み。
	m_animClip[en_anim_Idle].Load(L"Assets/animData/TestIdle.tka");
	m_animClip[en_anim_Idle].SetLoopFlag(true);
	m_animClip[en_anim_Attack].Load(L"Assets/animData/TestAttack.tka");
	m_animClip[en_anim_Attack].SetLoopFlag(false);
	m_animClip[en_anim_Magic].Load(L"Assets/animData/TestMagic.tka");
	m_animClip[en_anim_Magic].SetLoopFlag(false);
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

void Healer::Update()
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

bool Healer::BattleAction()
{
	MonsterBase* attack = this;

	bool flag = m_useSkill->UseSkill(attack, m_target);

	if (!m_useSkill->GetIsMagic()) {
		m_animation.Play(en_anim_Attack, 0.3f);
	}
	else if (m_useSkill->GetIsMagic()) {
		m_animation.Play(en_anim_Magic, 0.3f);
	}

	if (m_useSkill != nullptr && flag)
	{
		m_useSkill = nullptr;
		m_target = nullptr;
	}

	return flag;
}

void Healer::SelectUseSkill(const std::vector<MonsterBase*>& e_team, const std::vector<MonsterBase*>& m_team)
{
	SkillList* skillList = SkillList::GetInstance();	//スキルリストの取得。
	int res = rand() % 10;	//適当な乱数。
	const int size = 3;

	int HPsort[size] = { 0,1,2 };
	int maxHP = 0;
	int minHP = 100000;

	for (int i = 0; i < m_team.size(); i++)
	{
		if (m_team[i]->GetStatus().HP > maxHP) {
			maxHP = m_team[i]->GetStatus().HP;
			int hoge = HPsort[2];
			HPsort[2] = HPsort[i];
			HPsort[i] = hoge;
		}
		else if (m_team[i]->GetStatus().HP < minHP) {
			minHP = m_team[i]->GetStatus().HP;
			int hoge = HPsort[0];
			HPsort[0] = HPsort[i];
			HPsort[i] = hoge;
		}
	}

	//残りHPに応じて行動を決める。
	switch (m_stateAI)
	{
	case en_state_Good:
		if (res < 3) {
			m_useSkill = skillList->GetSkillData(1, 1);
		}
		else {
			m_useSkill = skillList->GetSkillData(1, 0);
		}
		m_target = m_team[HPsort[0]];
		break;

	case en_state_Usually:
		if (res < 5) {
			m_useSkill = skillList->GetSkillData(1, 1);
		}
		else {
			m_useSkill = skillList->GetSkillData(1, 0);
		}
		m_target = m_team[HPsort[0]];
		break;

	case en_state_Bad:
		m_useSkill = skillList->GetSkillData(1, 1);
		m_target = m_team[HPsort[0]];
		break;

	case en_state_Death:
		break;
	}
}
