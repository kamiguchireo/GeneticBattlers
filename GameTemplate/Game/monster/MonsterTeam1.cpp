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
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo", enFbxUpAxisY);

	//�A�j���[�V�����N���b�v�̓ǂݍ��݁B
	m_animClip[en_anim_Idle].Load(L"Assets/animData/idle.tka");
	m_animClip[en_anim_Idle].SetLoopFlag(true);
	m_animClip[en_anim_Attack].Load(L"Assets/animData/run.tka");
	m_animClip[en_anim_Attack].SetLoopFlag(true);
	m_animClip[en_anim_Damage].Load(L"Assets/animData/damage.tka");
	m_animClip[en_anim_Damage].SetLoopFlag(false);

	//�A�j���[�V�����̐ݒ�B
	m_animation.Init(
		m_model,
		m_animClip,
		en_anim_num
	);

	return true;
}

void MonsterTeam1::Update()
{
	if (m_stateAI == en_state_Death) return;	//���S���͍X�V���Ȃ��B

	m_position.y = m_activeTime;

	if (!m_animation.IsPlaying()) {
		m_animation.Play(en_anim_Idle, 0.3f);
	}

	//�`�揈���B
	Draw();
	//�A�j���[�V�����̍X�V�����B
	m_animation.Update(1.0f / 30.0f);
}

bool MonsterTeam1::Action_good()
{
	if (m_useSkill == nullptr) return true;

	m_animation.Play(en_anim_Attack, 0.3f);

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

	m_animation.Play(en_anim_Attack, 0.3f);

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

	m_animation.Play(en_anim_Attack, 0.3f);

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
