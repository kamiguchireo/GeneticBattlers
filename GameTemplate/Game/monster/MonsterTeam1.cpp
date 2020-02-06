#include "stdafx.h"
#include "MonsterTeam1.h"


MonsterTeam1::MonsterTeam1()
{
}


MonsterTeam1::~MonsterTeam1()
{
}

bool MonsterTeam1::Start()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo", enFbxUpAxisY);

	//アニメーションクリップの読み込み。
	m_animClip[en_anim_walk].Load(L"Assets/animData/walk.tka");
	m_animClip[en_anim_walk].SetLoopFlag(true);
	m_animClip[en_anim_run].Load(L"Assets/animData/run.tka");
	m_animClip[en_anim_run].SetLoopFlag(false);

	//アニメーションの設定。
	m_animation.Init(
		m_model,
		m_animClip,
		en_anim_num
	);

	return true;
}

void MonsterTeam1::Update()
{
	if (m_stateAI == en_state_Death) return;	//死亡時は更新しない。

	m_position.y = m_activeTime;
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	//描画処理。
	Draw();
	//アニメーションの更新処理。
	m_animation.Update(1.0f / 30.0f);
}

bool MonsterTeam1::Action_good()
{
	m_animation.Play(en_anim_run, 0.3f);

	if (!m_animation.IsPlaying()) {
		m_status.DEX += rand() % 5 - 3;
		m_animation.Play(en_anim_walk, 0.3f);

		MonsterBase* attack = this;

		m_useSkill->UseSkill(attack, m_target);

		if (m_useSkill != nullptr)
		{
			//DeleteGO(m_useSkill);
			m_useSkill = nullptr;
		}
		m_target = nullptr;

		return true;
	}

	return false;
}

bool MonsterTeam1::Action_usually()
{
	m_animation.Play(en_anim_run, 0.3f);

	if (!m_animation.IsPlaying()) {
		m_status.DEX += rand() % 5 - 2;
		m_animation.Play(en_anim_walk, 0.3f);

		MonsterBase* attack = this;

		m_useSkill->UseSkill(attack, m_target);

		if (m_useSkill != nullptr)
		{
			//DeleteGO(m_useSkill);
			m_useSkill = nullptr;
		}
		m_target = nullptr;

		return true;
	}

	return false;
}

bool MonsterTeam1::Action_bad()
{
	m_animation.Play(en_anim_run, 0.3f);

	if (!m_animation.IsPlaying()) {
		m_status.DEX += rand() % 5 - 1;
		m_animation.Play(en_anim_walk, 0.3f);

		MonsterBase* attack = this;

		m_useSkill->UseSkill(attack, m_target);

		if (m_useSkill != nullptr)
		{
			//DeleteGO(m_useSkill);
			m_useSkill = nullptr;
		}
		m_target = nullptr;

		return true;
	}

	return false;
}
