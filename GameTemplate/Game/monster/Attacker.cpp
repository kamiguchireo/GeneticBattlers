#include "stdafx.h"
#include "Attacker.h"
#include "Skill/SkillList.h"

Attacker::Attacker()
{
}

Attacker::~Attacker()
{
	DeleteGO(m_UI);
}

bool Attacker::Start()
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
	m_UI->SetPosition({ -50.0f,-250.0f,0.0f });
	m_status.SetUI(m_UI);

	return true;
}

void Attacker::Update()
{
	switch (m_status.GetState())
	{
	case en_state_Death:
		if (!m_status.IsDeath()) {
			m_status.SetDeath(true);
			m_animation.Play(en_anim_Death, 0.3f);
		}

		break;
	default:
		//アニメーションされていないなら。
		if (!m_animation.IsPlaying()) {
			m_status.SetDeath(false);
			m_animation.Play(en_anim_Idle, 0.3f);
		}

		break;
	}
	//描画処理。
	Draw();
	//アニメーションの更新処理。
	m_animation.Update(1.0f / 30.0f);
}

//bool Attacker::BattleAction()
//{
//	MonsterBase* attack = this;
//
//	bool flag = m_useSkill->UseSkill(attack, m_target);
//
//	if (!m_useSkill->IsMagic()) {
//		m_animation.Play(en_anim_Attack, 0.3f);
//	}
//	else if (m_useSkill->IsMagic()) {
//		m_animation.Play(en_anim_Magic, 0.3f);
//	}
//
//	if (m_useSkill != nullptr && flag)
//	{
//		m_useSkill = nullptr;
//		m_target = nullptr;
//	}
//
//	return flag;
//}



