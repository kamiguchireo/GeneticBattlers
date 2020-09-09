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
		//アニメーションされていないなら。
		if (!m_animation.IsPlaying()) {
			m_status.SetDeath(false);
			m_animation.Play(en_anim_Idle, 0.3f);
		}

		break;
	}
	//アニメーションの更新処理。
	m_animation.Update(g_gameTime.GetFrameDeltaTime() * 2.0f);
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void MonsterBase::Draw()
{
	//描画処理。
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
//	//設定。
//	m_status.SetStatus(hoge);
//}


//行動の評価。
bool MonsterBase::ACTScoring()
{
	m_status.ClearATB();
	m_UI->SetScaling(0.0f);
	//敵だったら評価不要。
	if (m_isEnemy)
	{
		//スキルログを消す。
		auto sLog = SkillLog::GetInstance();
		if (sLog == nullptr)
		{
			//消え去った。
			return true;
		}
		else
		{
			//ログをある程度出しておく。
			sLog->SetDelete(true);
			return false;
		}
	}
	//もうちょいこの辺も切り離したいかなぁ
	//評価の選択の処理。
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
	//評価の決定の処理。
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
		//スキルログを消す。
		auto sLog = SkillLog::GetInstance();
		DeleteGO(sLog);

		return true;
	}

	return false;
}

void MonsterBase::Damage(int damage)
{
	//死亡時はダメージ無し。
	if (m_status.IsDeath()) return;

	//ダメージがあるならアニメーション。
	if (damage > 0)
	{
		//アニメーション。
		m_animation.Play(en_anim_Damage, 0.3f);

		auto sound = NewGO<prefab::CSoundSource>(0);
		sound->Init(L"Assets/sound/battle/slap1.wav");
		sound->SetVolume(0.6f);
		sound->Play(false);
		sound->SetVolume(SOUND_VOL);
	}
	else
	{
		//ダメージがないなら。
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
		//死亡時はバフをかけられない。
		return 0;
	}
	int res = 0;

	if (pow > 1.0f)
	{
		//倍率が1を超えているならバフ。
		res = m_status.Monster_Buff(status, pow, time);
	}
	else
	{
		//超えていないならデバフ。
		res = m_status.Monster_Debuff(status, pow, time);
	}

	return res;
}

void MonsterBase::SelectUseSkill(
	const std::vector<MonsterBase*>& e_team,
	const std::vector<MonsterBase*>& m_team, 
	int& skill, int& target)
{
	int skillNo = 0;	//取得した番号を記録する。
	int targetNo = 0;	//取得した番号を記録する。

	bool flag = false;
	//行動をテーブルから決定。
	m_AIData.ActionDicide(skillNo, targetNo);
	//スキルの選択。
	int skillTable = (int)(skillNo / 100);

	switch (skillTable)
	{
		//攻撃系スキルか
	case 0:
	case 3:
		//ターゲットが死亡していなければ。
		if (!e_team[targetNo]->IsDeath()) {
			flag = true;
		}
		break;

		//味方に使用するスキルか
	case 1:
	case 2:
		//ターゲットが死亡していなければ。
		if (!m_team[targetNo]->IsDeath()) {
			flag = true;
		}
		break;

	default:
		break;
	}

	//ターゲットが定まるまで回す。
	while (!flag) {

		switch (skillTable)
		{
			//攻撃系スキルか
		case 0:
		case 3:
			targetNo = g_random.GetRandomInt() % static_cast<int>(e_team.size());
			//ターゲットが死亡していなければ。
			if (!e_team[targetNo]->IsDeath()) {
				flag = true;
			}
			break;

			//味方に使用するスキルか
		case 1:
		case 2:
			targetNo = g_random.GetRandomInt() % static_cast<int>(m_team.size());
			//ターゲットが死亡していなければ。
			if (!m_team[targetNo]->IsDeath()) {
				flag = true;
			}
			break;

		default:
			break;
		}

	}
	//行動記録。
	m_actRes.skillNo = skillNo;
	m_actRes.target = targetNo;
	//決定したものを受け渡す。
	skill = skillNo;
	target = targetNo;
}

void MonsterBase::Init(const char * filePath)
{
	//ファイルパスから読み込めないければ。
	if (!m_AIData.Load(filePath)) {
		//デフォルトのデータのファイルを読み込む。
		m_AIData.LoadDefault(GetDefaultDataPath());
	}
}

