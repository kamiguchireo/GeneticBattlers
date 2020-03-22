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
	//��b�X�e�[�^�X��ݒ�B
	m_statusBase.HP = hp;
	//m_statusBase.MP = mp;
	m_statusBase.ATK = atk;
	m_statusBase.DEF = def;
	m_statusBase.MAT = mat;
	m_statusBase.MDF = mdf;
	m_statusBase.DEX = dex;
	//�X�e�[�^�X�ɑ���B
	m_status = m_statusBase;
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

bool MonsterBase::AddATB()
{
	//���S���͏����𒆒f����B
	if (m_stateAI == en_state_Death) return false;

	m_activeTime += (float)m_status.DEX / 144.0f;
	for (int i = 0; i < en_buff_num; i++) {
		if (buffTimeList[i] >= 0.0f) continue;

		buffTimeList[i] -= 1.0f / 144.0f;
		if (buffTimeList[i] < 0.0f) {
			ResetBuff(i);
		}
	}

	//�A�N�e�B�u�^�C���Q�[�W�B
	float res = m_activeTime / m_coolTime;
	res = min(1.0f, res);
	m_UI->SetScaling(res);

	if (m_activeTime > m_coolTime) {
		m_activeTime = 0.0f;
		return true;
	}
	return false;
}

//�s���̕]���B
bool MonsterBase::ACTScoring()
{
	if (g_pad[0].IsTrigger(enButtonRight)) {		
		m_scoringFlag = 0;
	}
	if (g_pad[0].IsTrigger(enButtonLeft)) {
		m_scoringFlag = 1;
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
		m_UI->ScoreReset();
		return true;
	}

	return false;
}

int MonsterBase::Healing(int healing)
{
	int res = healing;
	m_status.HP += healing;
	//�ő�HP�𒴂����B
	if (m_status.HP > m_statusBase.HP) {
		int diff = m_status.HP - m_statusBase.HP;
		res -= diff;		//�����������������B

		m_status.HP = min(m_status.HP, m_statusBase.HP);
	}

	//�G�t�F�N�g�̍Đ��B
	auto ef = NewGO<prefab::CEffect>(0);
	ef->Play(L"Assets/effect/heal.efk");
	ef->SetPosition(m_position + CVector3::AxisY()*20.0f);
	ef->SetScale(CVector3::One()*80.0f);

	return res;
}

void MonsterBase::Monster_Buff(StatusBuff status, float pow, float time)
{
	////�o�t�̌��ʂ������Ă���Ȃ璆�f�B
	//if (buffTimeList[status] >= 0.0f) {
	//	return;
	//}
	
	//�G�t�F�N�g�̍Đ��B
	auto ef = NewGO<prefab::CEffect>(0);
	ef->Play(L"Assets/effect/buff.efk");
	ef->SetPosition(m_position + CVector3::AxisY()*20.0f);
	ef->SetScale(CVector3::One()*80.0f);

	//�o�t��������B
	switch (status)
	{
	case en_buff_ATK:
		m_status.ATK = m_statusBase.ATK * pow;
		break;
	case en_buff_DEF:
		m_status.DEF = m_statusBase.DEF * pow;
		break;
	case en_buff_MAT:
		m_status.MAT = m_statusBase.MAT * pow;
		break;
	case en_buff_MDF:
		m_status.MDF = m_statusBase.MDF * pow;
		break;
	case en_buff_DEX:
		m_status.DEX = m_statusBase.DEX * pow;
		break;
	default:
		return;
	}
	buffTimeList[status] = time;
}

void MonsterBase::ResetBuff(int i)
{
	////���ʎ��Ԃ�����Ȃ璆�f�B
	//if (buffTimeList[i] > 0.0f) {
	//	return;
	//}
	//�X�e�[�^�X�����̃X�e�[�^�X�ɖ߂��B
	switch (i)
	{
	case en_buff_ATK:
		m_status.ATK = m_statusBase.ATK;
		break;
	case en_buff_DEF:
		m_status.DEF = m_statusBase.DEF;
		break;
	case en_buff_MAT:
		m_status.MAT = m_statusBase.MAT;
		break;
	case en_buff_MDF:
		m_status.MDF = m_statusBase.MDF;
		break;
	case en_buff_DEX:
		m_status.DEX = m_statusBase.DEX;
		break;
	default:
		return;
	}
	//
	buffTimeList[i] = 0.0f;
}

void MonsterBase::SelectUseSkill(const std::vector<MonsterBase*>& e_team, const std::vector<MonsterBase*>& m_team)
{
	if (m_useSkill != nullptr) return;

	SkillList* skillList = SkillList::GetInstance();

	//�c��HP�ɉ����čs�������߂�B
	switch (m_stateAI)
	{
	case en_state_Good:
		m_useSkill = skillList->GetSkillData(0, 0);
		m_target = e_team[rand() % e_team.size()];
		break;

	case en_state_Usually:
		m_useSkill = skillList->GetSkillData(0, 1);
		m_target = e_team[rand() % e_team.size()];
		break;

	case en_state_Bad:
		m_useSkill = skillList->GetSkillData(1, 0);
		m_target = this;
		break;

	case en_state_Death:
		break;
	}
}

void MonsterBase::StateUpdate()
{
	//����HP/�ő�HP�̊�������X�e�[�g��ω�������B
	float nowHP = (float)m_status.HP / (float)m_statusBase.HP;
	//�X�e�[�g�̕ύX�B
	if (2.0f / 3.0f < nowHP) {
		m_stateAI = en_state_Good;
	}
	else if (1.0f / 3.0f < nowHP
		&& 2.0f / 3.0f > nowHP) {
		m_stateAI = en_state_Usually;
	}
	else if (0 < m_status.HP
		&& 1.0f / 3.0f > nowHP) {
		m_stateAI = en_state_Bad;
	}
	else { 
		m_stateAI = en_state_Death; 
		m_activeTime = 0.0f;
	}
	//UI�ɔ��f�B
	float res = m_activeTime / m_coolTime;
	res = min(1.0f, res);
	m_UI->SetScaling(res);
	m_UI->SetHPScaling(nowHP);
}

bool MonsterBase::Action()
{
	bool flag = false;
	//�c��HP�ɉ����čs�������߂�B
	switch (m_stateAI)
	{
	case en_state_Good:
		flag = Action_good();
		break;
	
	case en_state_Usually:
		flag = Action_usually();
		break;
	
	case en_state_Bad:
		flag = Action_bad();
		break;
	
	case en_state_Death:
		return true;
		break;
	}
	return flag;
}
