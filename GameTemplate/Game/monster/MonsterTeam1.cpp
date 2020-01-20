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
	m_animClip[en_anim_walk].Load(L"Assets/animData/walk.tka");
	m_animClip[en_anim_walk].SetLoopFlag(true);
	m_animClip[en_anim_run].Load(L"Assets/animData/run.tka");
	m_animClip[en_anim_run].SetLoopFlag(false);

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
	m_position.y = m_activeTime;
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	//�`�揈���B
	Draw();
	//�A�j���[�V�����̍X�V�����B
	m_animation.Update(1.0f / 30.0f);
}

bool MonsterTeam1::Action_good()
{
	m_animation.Play(en_anim_run, 0.3f);

	if (!m_animation.IsPlaying()) {
		m_status.DEX += rand() % 5 - 3;
		m_animation.Play(en_anim_walk, 0.3f);

		return true;
	}

	return false;
}

bool MonsterTeam1::Action_usually()
{
	return false;
}

bool MonsterTeam1::Action_bad()
{
	return false;
}
