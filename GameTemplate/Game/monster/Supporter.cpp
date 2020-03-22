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

	//�A�j���[�V�����N���b�v�̓ǂݍ��݁B
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

	//�A�j���[�V�����̐ݒ�B
	m_animation.Init(
		m_model,
		m_animClip,
		en_anim_num
	);

	//UI�����B
	m_UI = NewGO<StatusUI>(0);
	m_UI->SetPosition({ -450.0f,-250.0f,0.0f });
	
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
		//�A�j���[�V��������Ă��Ȃ��Ȃ�B
		if (!m_animation.IsPlaying()) {
			m_animation.Play(en_anim_Idle, 0.3f);
		}

		break;
	}
	//�`�揈���B
	Draw();
	//�A�j���[�V�����̍X�V�����B
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


	auto list = m_team;	//�\�[�g���邽�߂Ƀ��X�g���R�s�[�B

	for (int i = 0; i < list.size(); i++) {
		for (int j = i; j < list.size(); j++) {
			if (list[i]->GetStatus().HP > list[j]->GetStatus().HP) {
				auto hoge = list[i];
				list[i] = list[j];
				list[j] = hoge;
			}
		}
	}

	int res = rand() % 100;	//�K���ȗ����B
	int sum = 0;
	
	for (int i = 0; i < 3; i++) {
		sum += (int)(m_AI[i].rate * 100);
		if (sum > res) {
			int skillTable = (int)(m_AI[i].skillNo / 100);
			int skillNo = m_AI[i].skillNo % 100;
			int targetNo = m_AI[i].target;
			m_useSkill = skillList->GetSkillData(skillTable, skillNo);
			m_target = list[targetNo];
			break;
		}
	}

	//int res = rand() % 10;	//�K���ȗ����B
	//int tagNum = rand() % m_team.size();

	////�c��HP�ɉ����čs�������߂�B
	//switch (m_stateAI)
	//{
	//case en_state_Good:
	//	if (res < 3) {
	//		m_useSkill = skillList->GetSkillData(2, 1);
	//		m_target = this;
	//	}
	//	else {
	//		m_useSkill = skillList->GetSkillData(2, 0);
	//		m_target = m_team[tagNum];
	//	}
	//	break;

	//case en_state_Usually:
	//	if (res < 5) {
	//		m_useSkill = skillList->GetSkillData(2, 1);
	//		m_target = this;
	//	}
	//	else {
	//		m_useSkill = skillList->GetSkillData(2, 0);
	//		m_target = m_team[tagNum];
	//	}
	//	break;

	//case en_state_Bad:
	//	m_useSkill = skillList->GetSkillData(2, 1);
	//	m_target = this;
	//	break;

	//case en_state_Death:
	//	break;
	//}
}

void Supporter::Init(const wchar_t * filePath)
{
	m_AI[0] = { 201,0,0.5f };
	m_AI[1] = { 200,1,0.2f };
	m_AI[2] = { 200,0,0.3f };
}
