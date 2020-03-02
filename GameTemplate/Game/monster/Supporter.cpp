#include "stdafx.h"
#include "Supporter.h"
#include "Skill/SkillList.h"

Supporter::Supporter()
{
}

Supporter::~Supporter()
{
	DeleteGO(m_UI);
}

bool Supporter::Start()
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

	//UIを作る。
	m_UI = NewGO<StatusUI>(0);
	m_UI->SetPosition({ -500.0f,-200.0f,0.0f });
	
	return true;
}

void Supporter::Update()
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

bool Supporter::BattleAction()
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

void Supporter::SelectUseSkill(const std::vector<MonsterBase*>& e_team, const std::vector<MonsterBase*>& m_team)
{
	SkillList* skillList = SkillList::GetInstance();

	int res = rand() % 10;	//適当な乱数。

	int tagNum = rand() % m_team.size();

	//残りHPに応じて行動を決める。
	switch (m_stateAI)
	{
	case en_state_Good:
		if (res < 3) {
			m_useSkill = skillList->GetSkillData(2, 1);
			m_target = this;
		}
		else {
			m_useSkill = skillList->GetSkillData(2, 0);
			m_target = m_team[tagNum];
		}
		break;

	case en_state_Usually:
		if (res < 5) {
			m_useSkill = skillList->GetSkillData(2, 1);
			m_target = this;
		}
		else {
			m_useSkill = skillList->GetSkillData(2, 0);
			m_target = m_team[tagNum];
		}
		break;

	case en_state_Bad:
		m_useSkill = skillList->GetSkillData(2, 1);
		m_target = this;
		break;

	case en_state_Death:
		break;
	}
}
