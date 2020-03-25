#include "stdafx.h"
#include "MonsterTeam1.h"


MonsterTeam1::MonsterTeam1()
{
}


MonsterTeam1::~MonsterTeam1()
{
	DeleteGO(m_UI);
}

bool MonsterTeam1::Start()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo", enFbxUpAxisY);
	m_model.SetActiveDLFlag(0);
	m_model.SetActiveRLFlag(0);

	//�A�j���[�V�����N���b�v�̓ǂݍ��݁B
	m_animClip[en_anim_Idle].Load(L"Assets/animData/idle.tka");
	m_animClip[en_anim_Idle].SetLoopFlag(true);
	m_animClip[en_anim_Attack].Load(L"Assets/animData/run.tka");
	m_animClip[en_anim_Attack].SetLoopFlag(true);
	m_animClip[en_anim_Magic].Load(L"Assets/animData/walk.tka");
	m_animClip[en_anim_Magic].SetLoopFlag(true);
	m_animClip[en_anim_Damage].Load(L"Assets/animData/damage.tka");
	m_animClip[en_anim_Damage].SetLoopFlag(false);
	m_animClip[en_anim_Death].Load(L"Assets/animData/KneelDown.tka");
	m_animClip[en_anim_Death].SetLoopFlag(false);	


	//�A�j���[�V�����̐ݒ�B
	m_animation.Init(
		m_model,
		m_animClip,
		en_anim_num
	);

	m_animation.Play(en_anim_Idle, 0.3f);

	//UI�����B
	m_UI = NewGO<StatusUI>(0);
	m_UI->SetPosition(m_UIpos);
	m_UI->EnableEnemy();

	return true;
}

void MonsterTeam1::Update()
{
	//if (m_stateAI == en_state_Death) return;	//���S���͍X�V���Ȃ��B

	//m_position.y = m_activeTime;
	switch (m_stateAI)
	{
	case en_state_Death:
		if (!m_IsDeath) {
			m_IsDeath = true;
			m_animation.Play(en_anim_Death, 0.3f);
		}

		break;
	default:
		//�A�j���[�V��������Ă��Ȃ��Ȃ�B
		if (!m_animation.IsPlaying()) {
			m_IsDeath = false;
			m_animation.Play(en_anim_Idle, 0.3f);
		}

		break;
	}
	//�`�揈���B
	Draw();
	//�A�j���[�V�����̍X�V�����B
	m_animation.Update(1.0f / 30.0f);
}

bool MonsterTeam1::Action_good()
{
	if (m_useSkill == nullptr) return true;

	if (!m_useSkill->GetIsMagic()){
		m_animation.Play(en_anim_Attack, 0.3f);
	}
	else if (m_useSkill->GetIsMagic()) {
		m_animation.Play(en_anim_Magic, 0.3f);
	}

	MonsterBase* attack = this;

	if (m_useSkill->UseSkill(attack, m_target))
	{
		m_useSkill = nullptr;
		m_target = nullptr;

		m_animation.Play(en_anim_Idle, 0.3f);

		return true;
	}

	return false;
}

bool MonsterTeam1::Action_usually()
{
	if (m_useSkill == nullptr) return true;

	if (!m_useSkill->GetIsMagic()) {
		m_animation.Play(en_anim_Attack, 0.3f);
	}
	else if (m_useSkill->GetIsMagic()) {
		m_animation.Play(en_anim_Magic, 0.3f);
	}

	MonsterBase* attack = this;

	if (m_useSkill->UseSkill(attack, m_target))
	{
		m_useSkill = nullptr;
		m_target = nullptr;

		m_animation.Play(en_anim_Idle, 0.3f);

		return true;
	}

	return false;
}

bool MonsterTeam1::Action_bad()
{
	if (m_useSkill == nullptr) return true;

	if (!m_useSkill->GetIsMagic()) {
		m_animation.Play(en_anim_Attack, 0.3f);
	}
	else if (m_useSkill->GetIsMagic()) {
		m_animation.Play(en_anim_Magic, 0.3f);
	}

	MonsterBase* attack = this;

	if (m_useSkill->UseSkill(attack, m_target))
	{
		m_useSkill = nullptr;
		m_target = nullptr;

		m_animation.Play(en_anim_Idle, 0.3f);

		return true;
	}

	return false;
}

bool MonsterTeam1::BattleAction()
{
	bool flag = Action();

	return flag;
}
