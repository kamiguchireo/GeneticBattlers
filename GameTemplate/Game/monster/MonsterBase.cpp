#include "stdafx.h"
#include "MonsterBase.h"
#include "Skill/SkillList.h"


MonsterBase::MonsterBase()
{
}


MonsterBase::~MonsterBase()
{
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
	//描画処理。
	Draw();
	//アニメーションの更新処理。
	m_animation.Update(1.0f / 30.0f);
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

void MonsterBase::Draw()
{
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());

	auto shadowMap = g_graphicsEngine->GetShadowMap();
	//shadowMap->Update(CVector3::AxisY()*1000.0f, CVector3::Zero());
	//shadowMap->SendShadowRecieverParamToGpu();
	//shadowMap->RenderToShadowMap();
	shadowMap->RegistShadowCaster(
		&m_model
	);
	//描画処理。
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

//行動の評価。
bool MonsterBase::ACTScoring()
{
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

int MonsterBase::Monster_Buff(StatusBuff status, float pow, float time)
{
	if (IsDeath()) {
		//死亡時はバフをかけられない。
		return 0;
	}
	////エフェクトの再生。
	//auto ef = NewGO<prefab::CEffect>(0);
	//ef->Play(L"Assets/effect/buff.efk");
	//ef->SetPosition(m_position + CVector3::AxisY()*20.0f);
	//ef->SetScale(CVector3::One()*80.0f);

	return m_status.Monster_Buff(status,pow,time);
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

