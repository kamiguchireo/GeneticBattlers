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
			m_actRes.score = true;
			break;
		case 1:
			m_actRes.score = false;
			break;
		default:
			break;
		}
		m_actResList.push_back(m_actRes);	//���X�g�ɐςݏグ��B
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

	//�I�΂��s���̐��B
	int AINum = m_AI.size();

	//�ˑR�ψٓI��
	int pMutation = rand() % 100;
	//100���̂P�̊m���B
	if (pMutation == 0) {
		while (m_target == nullptr)
		{
			//�����_���ɐ���������B
			int actNum = rand() % AINum;
			int skillTable = (int)(m_AI[actNum].skillNo / 100);
			int skillNo = m_AI[actNum].skillNo % 100;
			int targetNo = m_AI[actNum].target;
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
		}
		//�֐��𔲂���B
		return;
	}

	//�^�[�Q�b�g����܂�܂ŉ񂷁B
	while (m_target == nullptr) {
		int res = rand() % 100;	//�K���ȗ����B
		int sum = 0;

		//�s���e�[�u�������Ƃɍs��������B
		for (int i = 0; i < AINum; i++) {
			sum += (int)(m_AI[i].rate * 100);
			if (sum > res) {
				int skillTable = (int)(m_AI[i].skillNo / 100);
				int skillNo = m_AI[i].skillNo % 100;
				int targetNo = m_AI[i].target;
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
	}
}

void MonsterBase::Init(const char * filePath)
{
	strcpy(m_AIPath, filePath);
	FILE* fp = fopen(filePath, "rb");
	if (fp == nullptr) {
		//�t�@�C�������݂��Ȃ��Ȃ�f�t�H���g�B
		MakeData();

		return;
	}

	//�ǂݍ���ł����B
	AIData hoge;
	while (fread(&hoge, sizeof(AIData), 1, fp) == 1) {
		m_AI.push_back(hoge);
	}

	fclose(fp);
}

void MonsterBase::Save(const char * filePath)
{
	GIUpdate();

	FILE* fp = fopen(m_AIPath, "wb");

	if (fp == nullptr) {
		return;
	}

	//�f�[�^����������ł����B
	while (m_AI.size() != 0) {
		AIData hoge = m_AI.front();
		m_AI.erase(m_AI.begin());
		fwrite(&hoge, sizeof(AIData), 1, fp);
	}

	fclose(fp);
}

void MonsterBase::GIUpdate()
{
	//GI��p���čs��AI�̊m���̍X�V�B?
	const int listSize = m_actResList.size();
	int AISize = m_AI.size();
	std::vector<float> AIscoreList(AISize, 0.0f);		//�s�����Ƃ̃X�R�A�B
	float sum = 0.0f;
	//�X�R�A�����v����B
	for (auto res : m_actResList) {
		//�]������Ă��Ȃ��B
		if (!res.score)	continue;
		//�X�R�A�����v����B
		int i = 0;
		for (i = 0; i < AISize; i++) {
			//�����̍s���e�[�u���ɑ��݂���B
			if (res.skillNo == m_AI[i].skillNo
				&&res.target == m_AI[i].target) {
				AIscoreList[i] += res.damage;
				sum += res.damage;
				break;
			}
		}
		//���݂��Ȃ��B
		if (i == AISize) {
			//�s���ɒǉ��B
			AIData hoge;
			hoge.skillNo = res.skillNo;
			hoge.target = res.target;
			hoge.rate = 3.0f;		//�ŏ����炠����x�̊m�����������Ă����B
			//�z��ɐςށB
			m_AI.push_back(hoge);
			AIscoreList.push_back(res.damage);
			AISize++;		//�T�C�Y���������B
		}
	}
	//0�������B
	sum = max(sum, 1.0f);
	//�䗦�v�Z�B
	for (int i = 0; i < AISize; i++) {
		AIscoreList[i] /= sum;
	}

	sum = 0.0f;
	for (int i = 0; i < AISize; i++) {
		m_AI[i].rate = m_AI[i].rate * 10.0f + AIscoreList[i];
		sum += m_AI[i].rate;
	}

	for (int i = 0; i < AISize; i++) {
		m_AI[i].rate /= sum;
	}
}
