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
	m_UI->SetPosition({ -50.0f,-250.0f,0.0f });

	return true;
}

void Attacker::Update()
{
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

bool Attacker::BattleAction()
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

//void Attacker::SelectUseSkill(const std::vector<MonsterBase*>& e_team, const std::vector<MonsterBase*>& m_team)
//{
//	SkillList* skillList = SkillList::GetInstance();
//
//	auto ene_list = e_team;	//�\�[�g���邽�߂Ƀ��X�g���R�s�[�B
//	auto list = m_team;
//
//	//����HP�̒Ⴂ�����珇�ԂɃ\�[�g�B
//	for (int i = 0; i < list.size(); i++) {
//		for (int j = i; j < list.size(); j++) {
//			if (list[i]->GetStatus().HP > list[j]->GetStatus().HP) {
//				auto hoge = list[i];
//				list[i] = list[j];
//				list[j] = hoge;
//			}
//		}
//	}
//	for (int i = 0; i < ene_list.size(); i++) {
//		for (int j = i; j < ene_list.size(); j++) {
//			if (ene_list[i]->GetStatus().HP > ene_list[j]->GetStatus().HP) {
//				auto hoge = ene_list[i];
//				ene_list[i] = ene_list[j];
//				ene_list[j] = hoge;
//			}
//		}
//	}
//
//	//�^�[�Q�b�g����܂�܂ŉ񂷁B
//	while (m_target == nullptr) {
//		int res = rand() % 100;	//�K���ȗ����B
//		int sum = 0;
//
//		//�s���e�[�u�������Ƃɍs��������B
//		int AINum = sizeof(m_AI) / sizeof(*m_AI);
//		for (int i = 0; i < AINum; i++) {
//			sum += (int)(m_AI[i].rate * 100);
//			if (sum > res) {
//				int skillTable = (int)(m_AI[i].skillNo / 100);
//				int skillNo = m_AI[i].skillNo % 100;
//				int targetNo = m_AI[i].target;
//				m_useSkill = skillList->GetSkillData(skillTable, skillNo);
//
//				//�G�������̂ǂ���ɍU�����邩�B
//				if (!m_useSkill->GetIsAttack()) {
//					//�^�[�Q�b�g�����S���Ă��Ȃ���΁B
//					if (!list[targetNo]->IsDeath())m_target = list[targetNo];
//				}
//				else if (m_useSkill->GetIsAttack()) {
//					//�^�[�Q�b�g�����S���Ă��Ȃ���΁B
//					if (!list[targetNo]->IsDeath())m_target = ene_list[targetNo];
//				}
//
//				break;
//			}
//		}
//	}
//}

void Attacker::Init(const char* filePath)
{
	strcpy(m_AIPath, filePath);
	FILE* fp = fopen(filePath, "rb");
	if (fp == nullptr) {
		//�t�@�C�������݂��Ȃ��Ȃ�f�t�H���g�B
		m_AI[0] = { 0,0,0.25f };
		m_AI[1] = { 0,1,0.1f };
		m_AI[2] = { 0,2,0.15f };
		m_AI[3] = { 1,0,0.25f };
		m_AI[4] = { 1,1,0.1f };
		m_AI[5] = { 1,2,0.15f };

		return;
	}
	

	fread(m_AI, sizeof(m_AI), 1, fp);

	fclose(fp);
}

void Attacker::Save(const char * filePath)
{
	//�Ƃ肠�����ύX������B
	GIUpdate();

	FILE* fp = fopen(m_AIPath, "wb");

	if (fp == nullptr) {
		return;
	}

	fwrite(m_AI, sizeof(m_AI), 1, fp);

	fclose(fp);
}

