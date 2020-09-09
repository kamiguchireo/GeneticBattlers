#include "stdafx.h"
#include "MonsterBase.h"
#include "Skill/SkillList.h"
#include "Skill/SkillLog.h"

const float MonsterBase::SOUND_VOL = 0.6f;

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

//void MonsterBase::SetStatus(int hp, int atk, int def, int mat, int mdf, int dex)
//{
//	Status hoge;
//	hoge.HP = hp;
//	//hoge.MP = mp;
//	hoge.ATK = atk;
//	hoge.DEF = def;
//	hoge.HEAL = mat;
//	hoge.BUF = mdf;
//	hoge.DEX = dex;
//	//�ݒ�B
//	m_status.SetStatus(hoge);
//}


//�s���̕]���B
bool MonsterBase::ACTScoring()
{
	m_status.ClearATB();
	m_UI->SetScaling(0.0f);
	//�G��������]���s�v�B
	if (m_isEnemy)
	{
		//�X�L�����O�������B
		auto sLog = SkillLog::GetInstance();
		if (sLog == nullptr)
		{
			//�����������B
			return true;
		}
		else
		{
			//���O��������x�o���Ă����B
			sLog->SetDelete(true);
			return false;
		}
	}
	//�������傢���̕ӂ��؂藣���������Ȃ�
	//�]���̑I���̏����B
	if (g_pad[0].IsTrigger(enButtonRight)) {
		auto cursor = NewGO<prefab::CSoundSource>(0);
		cursor->Init(L"Assets/sound/cursor/cursor2.wav");
		cursor->Play(false);
		cursor->SetVolume(SOUND_VOL);

		m_scoringFlag = 1;
	}
	if (g_pad[0].IsTrigger(enButtonLeft)) {
		auto cursor = NewGO<prefab::CSoundSource>(0);
		cursor->Init(L"Assets/sound/cursor/cursor2.wav");
		cursor->Play(false);
		cursor->SetVolume(SOUND_VOL);

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
			m_AIData.PushBackResult(m_actRes.damage,m_actRes.skillNo,m_actRes.target);
			break;
		case 1:
			break;
		default:
			break;
		}

		auto decision = NewGO<prefab::CSoundSource>(0);
		decision->Init(L"Assets/sound/cursor/decision17.wav");
		decision->Play(false);
		decision->SetVolume(SOUND_VOL);

		m_UI->ScoreReset();
		m_scoringFlag = 0;
		//�X�L�����O�������B
		auto sLog = SkillLog::GetInstance();
		DeleteGO(sLog);

		return true;
	}

	return false;
}

void MonsterBase::Damage(int damage)
{
	//���S���̓_���[�W�����B
	if (m_status.IsDeath()) return;

	//�_���[�W������Ȃ�A�j���[�V�����B
	if (damage > 0)
	{
		//�A�j���[�V�����B
		m_animation.Play(en_anim_Damage, 0.3f);

		auto sound = NewGO<prefab::CSoundSource>(0);
		sound->Init(L"Assets/sound/battle/slap1.wav");
		sound->SetVolume(0.6f);
		sound->Play(false);
		sound->SetVolume(SOUND_VOL);
	}
	else
	{
		//�_���[�W���Ȃ��Ȃ�B
		auto sound = NewGO<prefab::CSoundSource>(0);
		sound->Init(L"Assets/sound/battle/punch-swing1.wav");
		sound->SetVolume(1.0f);
		sound->Play(false);
		sound->SetVolume(SOUND_VOL);
	}

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
	//�s�����e�[�u�����猈��B
	m_AIData.ActionDicide(skillNo, targetNo);
	//�X�L���̑I���B
	int skillTable = (int)(skillNo / 100);

	switch (skillTable)
	{
		//�U���n�X�L����
	case 0:
	case 3:
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

	//�^�[�Q�b�g����܂�܂ŉ񂷁B
	while (!flag) {

		switch (skillTable)
		{
			//�U���n�X�L����
		case 0:
		case 3:
			targetNo = g_random.GetRandomInt() % static_cast<int>(e_team.size());
			//�^�[�Q�b�g�����S���Ă��Ȃ���΁B
			if (!e_team[targetNo]->IsDeath()) {
				flag = true;
			}
			break;

			//�����Ɏg�p����X�L����
		case 1:
		case 2:
			targetNo = g_random.GetRandomInt() % static_cast<int>(m_team.size());
			//�^�[�Q�b�g�����S���Ă��Ȃ���΁B
			if (!m_team[targetNo]->IsDeath()) {
				flag = true;
			}
			break;

		default:
			break;
		}

	}
	//�s���L�^�B
	m_actRes.skillNo = skillNo;
	m_actRes.target = targetNo;
	//���肵�����̂��󂯓n���B
	skill = skillNo;
	target = targetNo;
}

void MonsterBase::Init(const char * filePath)
{
	//�t�@�C���p�X����ǂݍ��߂Ȃ�����΁B
	if (!m_AIData.Load(filePath)) {
		//�f�t�H���g�̃f�[�^�̃t�@�C����ǂݍ��ށB
		m_AIData.LoadDefault(GetDefaultDataPath());
	}
}

