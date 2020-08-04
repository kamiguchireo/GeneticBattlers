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
	//設定。
	m_status.SetStatus(hoge);
}


//行動の評価。
bool MonsterBase::ACTScoring()
{
	//敵だったら評価不要。
	if (m_isEnemy)
	{
		m_status.ClearATB();
		m_UI->SetScaling(0.0f);
		DeleteGO("sLog");
		return true;
	}
	m_status.ClearATB();
	m_UI->SetScaling(0.0f);
	//もうちょいこの辺も切り離したいかなぁ
	//評価の選択の処理。
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
	//評価の決定の処理。
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
	//ターゲットが定まるまで回す。
	while (!flag) {
		//行動をテーブルから決定。
		m_GIData.ActionDicide(skillNo, targetNo);
		//スキルの選択。
		int skillTable = (int)(skillNo / 100);

		switch (skillTable)
		{
			//攻撃系スキルか
		case 0:
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

	}

	//決定したものを受け渡す。
	skill = skillNo;
	target = targetNo;
}

void MonsterBase::Init(const char * filePath)
{
	//ファイルパスから読み込めないければ。
	if (!m_GIData.Load(filePath)) {
		//デフォルトのデータのファイルを読み込む。
		m_GIData.LoadDefault(GetDefaultDataPath());
	}
}

