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
	m_model.Init(L"Assets/modelData/DesertDragon2.cmo");
	m_model.SetActiveDLFlag(0);
	m_model.SetActiveRLFlag(1);
	m_model.SetLightColor(0.8f);
	
	//アニメーションクリップの読み込み。
	m_animClip[en_anim_Idle].Load(L"Assets/animData/Dragon/D_Idle.tka");
	m_animClip[en_anim_Idle].SetLoopFlag(true);
	m_animClip[en_anim_Attack].Load(L"Assets/animData/Dragon/D_Attack.tka");
	m_animClip[en_anim_Attack].SetLoopFlag(false);
	m_animClip[en_anim_Magic].Load(L"Assets/animData/Dragon/D_Fire.tka");
	m_animClip[en_anim_Magic].SetLoopFlag(false);
	m_animClip[en_anim_Damage].Load(L"Assets/animData/Dragon/D_Damage.tka");
	m_animClip[en_anim_Damage].SetLoopFlag(false);
	m_animClip[en_anim_Death].Load(L"Assets/animData/Dragon/D_Death.tka");
	m_animClip[en_anim_Death].SetLoopFlag(false);

	//アニメーションの設定。
	m_animation.Init(
		m_model,
		m_animClip,
		en_anim_num
	);
	
	//UIを作る。
	m_UI = NewGO<StatusUI>(0);
	m_UI->SetPosition(m_UIpos);
	if (m_isEnemy) m_UI->EnableEnemy();
	m_status.SetUI(m_UI);

	return true;
}


