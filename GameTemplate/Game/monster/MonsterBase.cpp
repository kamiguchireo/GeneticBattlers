#include "stdafx.h"
#include "MonsterBase.h"
#include "Skill/SkillList.h"


MonsterBase::MonsterBase()
{
}


MonsterBase::~MonsterBase()
{
}

void MonsterBase::SetStatus(int hp, int mp, int atk, int def, int mat, int mdf, int dex)
{
	Status hoge;
	hoge.HP = hp;
	//hoge.MP = mp;
	hoge.ATK = atk;
	hoge.DEF = def;
	hoge.MAT = mat;
	hoge.MDF = mdf;
	hoge.DEX = dex;
	//�ݒ�B
	m_status.SetStatus(hoge);
}

void MonsterBase::Draw()
{
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	//�`�揈���B
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

//�s���̕]���B
bool MonsterBase::ACTScoring()
{
	//�]���̑I���̏����B
	if (g_pad[0].IsTrigger(enButtonRight)) {		
		m_scoringFlag = 1;
	}
	if (g_pad[0].IsTrigger(enButtonLeft)) {
		m_scoringFlag = 0;
	}
	switch (m_scoringFlag)
	{
	case 0:
		m_UI->SetGood();
		break;
	case 1:
		m_UI->SetBad();
		break;
	default:
		break;
	}
	//�]���̌���̏����B
	if (g_pad[0].IsTrigger(enButtonA)) {
		switch (m_scoringFlag)
		{
		case 0:
			m_GIData.PushBackResult(m_actRes.damage,m_actRes.skillNo,m_actRes.target);
			break;
		case 1:
			break;
		default:
			break;
		}
		m_UI->ScoreReset();
		m_scoringFlag = 0;
		return true;
	}

	return false;
}

int MonsterBase::Monster_Buff(StatusBuff status, float pow, float time)
{
	//�G�t�F�N�g�̍Đ��B
	auto ef = NewGO<prefab::CEffect>(0);
	ef->Play(L"Assets/effect/buff.efk");
	ef->SetPosition(m_position + CVector3::AxisY()*20.0f);
	ef->SetScale(CVector3::One()*80.0f);

	return m_status.Monster_Buff(status,pow,time);
}

void MonsterBase::SelectUseSkill(const std::vector<MonsterBase*>& e_team, const std::vector<MonsterBase*>& m_team)
{
	SkillList* skillList = SkillList::GetInstance();

	auto ene_list = e_team;	//�\�[�g���邽�߂Ƀ��X�g���R�s�[�B
	auto list = m_team;

	//����HP�̒Ⴂ�����珇�ԂɃ\�[�g�B
	for (int i = 0; i < list.size(); i++) {
		for (int j = i; j < list.size(); j++) {
			if (list[i]->GetStatusManager().GetStatus().HP > list[j]->GetStatusManager().GetStatus().HP) {
				auto hoge = list[i];
				list[i] = list[j];
				list[j] = hoge;
			}
		}
	}
	for (int i = 0; i < ene_list.size(); i++) {
		for (int j = i; j < ene_list.size(); j++) {
			if (ene_list[i]->GetStatusManager().GetStatus().HP > ene_list[j]->GetStatusManager().GetStatus().HP) {
				auto hoge = ene_list[i];
				ene_list[i] = ene_list[j];
				ene_list[j] = hoge;
			}
		}
	}
	//HP��0�̂�͌��ɉ񂷁B
	for (int i = list.size() - 1; i >= 0; i--) {
		for (int j = i; j < list.size(); j++) {
			if (list[i]->GetStatusManager().GetStatus().HP <= 0) {
				auto hoge = list[i];
				list[i] = list[j];
				list[j] = hoge;
			}
		}
	}
	for (int i = ene_list.size() - 1; i >= 0; i--) {
		for (int j = i; j < ene_list.size(); j++) {
			if (ene_list[i]->GetStatusManager().GetStatus().HP <= 0) {
				auto hoge = ene_list[i];
				ene_list[i] = ene_list[j];
				ene_list[j] = hoge;
			}
		}
	}

	//�^�[�Q�b�g����܂�܂ŉ񂷁B
	while (m_target == nullptr) {
		//�s�����e�[�u�����猈��B
		int skill, targetNo;
		m_GIData.ActionDicide(&skill, &targetNo);
		//�X�L���̑I���B
		int skillTable = (int)(skill / 100);
		int skillNo = skill % 100;
		m_useSkill = skillList->GetSkillData(skillTable, skillNo);

		//�G�������̂ǂ���ɍU�����邩�B
		if (!m_useSkill->GetIsAttack()) {
			//�^�[�Q�b�g�����S���Ă��Ȃ���΁B
			if (!list[targetNo]->IsDeath()) {
				m_target = list[targetNo];
			}
		}
		else if (m_useSkill->GetIsAttack()) {
			//�^�[�Q�b�g�����S���Ă��Ȃ���΁B
			if (!ene_list[targetNo]->IsDeath()) {
				m_target = ene_list[targetNo];
			}
		}

		break;
	}
}

void MonsterBase::Init(const char * filePath)
{
	if (m_GIData.Load(filePath)) {
		m_GIData.LoadDefault(GetDefaultDataPath());
	}
}

