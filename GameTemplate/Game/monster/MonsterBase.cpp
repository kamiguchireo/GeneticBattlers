#include "stdafx.h"
#include "MonsterBase.h"
#include "Skill/SkillList.h"


MonsterBase::MonsterBase()
{
}


MonsterBase::~MonsterBase()
{
}

void MonsterBase::PreRender()
{
	auto shadowMap = g_graphicsEngine->GetShadowMap();
	shadowMap->RegistShadowCaster(
		&m_model
	);
}

void MonsterBase::Update()
{
	switch (m_status.GetState())
	{
	case en_state_Death:
		if (!m_status.IsDeath()) {
			m_status.SetDeath(true);
			m_animation.Play(en_anim_Death, 0.3f);
		}

		break;
	default:
		//�A�j���[�V��������Ă��Ȃ��Ȃ�B
		if (!m_animation.IsPlaying()) {
			m_status.SetDeath(false);
			m_animation.Play(en_anim_Idle, 0.3f);
		}

		break;
	}
	//�A�j���[�V�����̍X�V�����B
	m_animation.Update(g_gameTime.GetFrameDeltaTime() * 2.0f);
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void MonsterBase::Draw()
{

	//�`�揈���B
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void MonsterBase::SetStatus(int hp, int atk, int def, int mat, int mdf, int dex)
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


//�s���̕]���B
bool MonsterBase::ACTScoring()
{
	//�G��������]���s�v�B
	if (m_isEnemy)
	{
		m_status.ClearATB();
		m_UI->SetScaling(0.0f);
		DeleteGO("sLog");
		return true;
	}
	m_status.ClearATB();
	m_UI->SetScaling(0.0f);
	//�������傢���̕ӂ��؂藣���������Ȃ�
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
		DeleteGO("sLog");

		return true;
	}

	return false;
}

int MonsterBase::MonsterBuffAndDebuff(StatusBuff status, float pow, float time)
{
	if (IsDeath()) {
		//���S���̓o�t���������Ȃ��B
		return 0;
	}
	int res = 0;

	if (pow > 1.0f)
	{
		//�{����1�𒴂��Ă���Ȃ�o�t�B
		res = m_status.Monster_Buff(status, pow, time);
	}
	else
	{
		//�����Ă��Ȃ��Ȃ�f�o�t�B
		res = m_status.Monster_Debuff(status, pow, time);
	}

	return res;
}

void MonsterBase::SelectUseSkill(
	const std::vector<MonsterBase*>& e_team,
	const std::vector<MonsterBase*>& m_team, 
	int& skill, int& target)
{
	int skillNo = 0;	//�擾�����ԍ����L�^����B
	int targetNo = 0;	//�擾�����ԍ����L�^����B

	bool flag = false;
	//�^�[�Q�b�g����܂�܂ŉ񂷁B
	while (!flag) {
		//�s�����e�[�u�����猈��B
		m_GIData.ActionDicide(skillNo, targetNo);
		//�X�L���̑I���B
		int skillTable = (int)(skillNo / 100);

		switch (skillTable)
		{
			//�U���n�X�L����
		case 0:
			//�^�[�Q�b�g�����S���Ă��Ȃ���΁B
			if (!e_team[targetNo]->IsDeath()) {
				flag = true;
			}
			break;

			//�����Ɏg�p����X�L����
		case 1:
		case 2:
			//�^�[�Q�b�g�����S���Ă��Ȃ���΁B
			if (!m_team[targetNo]->IsDeath()) {
				flag = true;
			}
			break;

		default:
			break;
		}

	}

	//���肵�����̂��󂯓n���B
	skill = skillNo;
	target = targetNo;
}

void MonsterBase::Init(const char * filePath)
{
	//�t�@�C���p�X����ǂݍ��߂Ȃ�����΁B
	if (!m_GIData.Load(filePath)) {
		//�f�t�H���g�̃f�[�^�̃t�@�C����ǂݍ��ށB
		m_GIData.LoadDefault(GetDefaultDataPath());
	}
}

