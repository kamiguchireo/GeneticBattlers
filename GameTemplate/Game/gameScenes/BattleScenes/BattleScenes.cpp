#include "stdafx.h"
#include "BattleScenes.h"
#include "BattleManager.h"
#include "monster/MonsterBase.h"
//#include "monster/MonsterTeam1.h"
#include "monster/Attacker.h"
#include "monster/Healer.h"
#include "monster/Supporter.h"
#include "AIResouce.h"
#include "../TitleScene.h"
#include "../NetScenes/NetScenes.h"
#include "Fade.h"
#include "GameCamera.h"
#include "Skill/SkillLog.h"

const CVector3 BattleScenes::ATTAKER = { -50.0f,-250.0f,0.0f };
const CVector3 BattleScenes::HEALER = { 350.0f,-250.0f,0.0f };
const CVector3 BattleScenes::SUPPORTER = { -450.0f,-250.0f,0.0f };
const CVector3 BattleScenes::ENEMY_ATTACKER = { -50.0f,300.0f,0.0f };
const CVector3 BattleScenes::ENEMY_HEALER = { -450.0f,300.0f,0.0f };
const CVector3 BattleScenes::ENEMY_SUPPORTER = { 350.0f,300.0f,0.0f };

BattleScenes::BattleScenes()
{

}

BattleScenes::~BattleScenes()
{
	DeleteGO(m_battleManager);
	DeleteGO(m_camera);
	DeleteGO(m_resultSprite);
	auto sLog = SkillLog::GetInstance();
	DeleteGO(sLog);
}

bool BattleScenes::Start()
{
	//ネットシーンのポインタ取得。
	m_netScenes = NetScenes::GetInstance();
	//戦闘管理用クラス作成。
	m_battleManager = NewGO<BattleManager>(1);

	//敵の情報を記録するクラス。
	AIResouce* aiResouse = AIResouce::GetInstance();
	if (aiResouse == nullptr)
	{
		aiResouse = NewGO<AIResouce>(0);
	}	
	aiResouse->ClearData();

	//カスケードシャドウの範囲指定。
	g_graphicsEngine->GetShadowMap()->SetRange({ 1000.0f,2000.0f,3000.0f });

	//レベル。
	m_level.Init(L"Assets/level/BattleStage.tkl",[&](LevelObjectData& objData) {
		if (wcscmp(objData.name, L"testGround") == 0)
		{
			//背景モデル。
			m_model.Init(L"Assets/modelData/testGround.cmo");
			m_model.SetActiveDLFlag(0);
			m_model.SetActiveRLFlag(0);
			m_model.SetShadowReciever(true);
			m_model.UpdateWorldMatrix(
				objData.position,
				objData.rotation,
				objData.scale
			);
			return true;
		}
		if (wcscmp(objData.name, L"EAttacker") == 0)
		{
			MonsterBase* monster = NewGO<Attacker>(0);
			Status hoge;
			hoge.HP = 130;
			hoge.ATK = 30;
			hoge.DEF = 10;
			hoge.MAT = 5;
			hoge.MDF = 10;
			hoge.DEX = 10;
			monster->SetStatus(hoge);
			monster->SetPosition(objData.position);
			monster->SetRotation(objData.rotation);
			monster->SetScale(objData.scale);
			if (m_netScenes == nullptr){		//ネット通信でなければ。
				monster->Init("Assets/AIData/DefaultData/AttackerDefault.bin");
			}
			else {		//通信しているなら。
				auto& ga = monster->GetAIManager();
				ga.SetAIData(m_netScenes->GetAttakerData());
			}
			//情報記録。
			aiResouse->SetAttaker(monster->GetAIManager().GetAIData());
			monster->SetUIPos(ENEMY_ATTACKER);
			monster->SetIsEnemy(true);

			m_battleManager->PushBackEnemys(monster,job::enjob_Attacker);

			return true;
		}
		if (wcscmp(objData.name, L"EBuff") == 0)
		{
			MonsterBase* monster = NewGO<Supporter>(0);
			Status hoge;
			hoge.HP = 130;
			//hoge.HP = 1;
			hoge.ATK = 5;
			hoge.DEF = 15;
			hoge.MAT = 20;
			hoge.MDF = 15;
			hoge.DEX = 15;
			monster->SetStatus(hoge);
			monster->SetPosition(objData.position);
			monster->SetRotation(objData.rotation);
			monster->SetScale(objData.scale);
			if (m_netScenes == nullptr){		//ネット通信でなければ。
				monster->Init("Assets/AIData/DefaultData/SupporterDefault.bin");
			}
			else {		//通信しているなら。
				auto& ga = monster->GetAIManager();
				ga.SetAIData(m_netScenes->GetSupporterData());
			}
			//情報記録。
			aiResouse->SetSupporter(monster->GetAIManager().GetAIData());
			monster->SetUIPos(ENEMY_SUPPORTER);
			monster->SetIsEnemy(true);

			m_battleManager->PushBackEnemys(monster,job::enjob_Supotter);


			return true;
		}
		if (wcscmp(objData.name, L"EHealer") == 0)
		{
			MonsterBase* monster = NewGO<Healer>(0);
			Status hoge;
			hoge.HP = 90;
			//hoge.HP = 1;
			hoge.ATK = 5;
			hoge.DEF = 10;
			hoge.MAT = 30;
			hoge.MDF = 20;
			hoge.DEX = 10;
			//hoge.HP = rand() % 50 + 100;
			//hoge.ATK = rand() % 10 + 10;
			//hoge.DEF = rand() % 10 + 10;
			//hoge.MAT = rand() % 10 + 10;
			//hoge.MDF = rand() % 10 + 10;
			//hoge.DEX = rand() % 10 + 10;
			monster->SetStatus(hoge);
			monster->SetPosition(objData.position);
			monster->SetRotation(objData.rotation);
			monster->SetScale(objData.scale);
			if (m_netScenes == nullptr){		//ネット通信でなければ。
				monster->Init("Assets/AIData/DefaultData/HealerDefault.bin");
			}
			else {		//通信しているなら。
				auto& ga = monster->GetAIManager();
				ga.SetAIData(m_netScenes->GetHealerData());
			}
			//情報記録。
			aiResouse->SetHealer(monster->GetAIManager().GetAIData());
			monster->SetUIPos(ENEMY_HEALER);
			monster->SetIsEnemy(true);

			m_battleManager->PushBackEnemys(monster,job::enjob_Healer);


			return true;
		}
		if (wcscmp(objData.name, L"Attacker") == 0)
		{
			MonsterBase* attacker = NewGO<Attacker>(0);
			Status hoge;
			hoge.HP = 130;
			//hoge.HP = 1;
			hoge.ATK = 30;
			hoge.DEF = 10;
			hoge.MAT = 5;
			hoge.MDF = 10;
			hoge.DEX = 10;
			attacker->SetStatus(hoge);
			attacker->SetPosition(objData.position);
			attacker->SetRotation(objData.rotation);
			attacker->SetScale(objData.scale);
			attacker->Init("Assets/AIData/Attacker.bin");
			attacker->SetUIPos(ATTAKER);
			m_battleManager->PushBackTeams(attacker,job::enjob_Attacker);

			return true;
		}	
		if (wcscmp(objData.name, L"Healer") == 0)
		{
			MonsterBase* healer = NewGO<Healer>(0);
			Status hoge;
			hoge.HP = 90;
			//hoge.HP = 1;
			hoge.ATK = 5;
			hoge.DEF = 10;
			hoge.MAT = 30;
			hoge.MDF = 20;
			hoge.DEX = 10;
			healer->SetStatus(hoge);
			healer->SetPosition(objData.position);
			healer->SetRotation(objData.rotation);
			healer->SetScale(objData.scale);
			healer->Init("Assets/AIData/Healer.bin");
			healer->SetUIPos(HEALER);
			m_battleManager->PushBackTeams(healer,job::enjob_Healer);
		
			return true;
		}
		if (wcscmp(objData.name, L"Buff") == 0)
		{
			MonsterBase* support = NewGO<Supporter>(0);
			Status hoge;
			hoge.HP = 130;
			//hoge.HP = 1;
			hoge.ATK = 5;
			hoge.DEF = 15;
			hoge.MAT = 20;
			hoge.MDF = 15;
			hoge.DEX = 15;
			support->SetStatus(hoge);
			support->SetPosition(objData.position);
			support->SetRotation(objData.rotation);
			support->SetScale(objData.scale);
			support->Init("Assets/AIData/Supporter.bin");
			support->SetUIPos(SUPPORTER);
			m_battleManager->PushBackTeams(support,job::enjob_Supotter);
		
			return true;
		}


		return false;
		});
	m_battleManager->SetScenePointa(this);
	m_battleManager->SetIsBattle(false);
	//カメラ。
	m_camera = NewGO<GameCamera>(0);
	//bgm
	m_bgm = NewGO<prefab::CSoundSource>(0);
	m_bgm->Init(L"Assets/sound/bgm/bgm_battle.wav");
	m_bgm->Play(true);
	m_bgm->SetVolume(m_bgmVol);

	//フェード。
	m_fade = Fade::GetInstance();
	m_fade->StartFadeIn();

	DeleteGO(m_netScenes);

	return true;
}

void BattleScenes::Update()
{
	//rand();
	switch (m_state)
	{
	case enState_FadeIn:
		if (m_bgmVol < 1.0f) {
			m_bgmVol += g_gameTime.GetFrameDeltaTime();
			m_bgmVol = min(1.0f, m_bgmVol);
		}
		if (!m_fade->IsFade()) {
			m_state = enState_Battle;
			//戦闘開始。
			m_battleManager->SetIsBattle(true);
		}
		break;
	case enState_Battle:
		if (g_pad[0].IsTrigger(enButtonStart)) 
		{
			//戦闘中断。
			m_battleManager->SetIsBattle(false);
			//フェードさせる。
			m_state = enState_FadeOut; 
			m_fade->StartFadeOut();
		}
		break;

	case enState_Result:
		battleCoolTime -= g_gameTime.GetFrameDeltaTime();
		if (battleCoolTime > 0.0f) {
			break;
		}
		if (m_isWin && !m_isSprite) {
			//勝利！
			m_resultSprite = NewGO<prefab::SpriteRender>(0);
			m_resultSprite->Init(L"Assets/sprite/win.dds",600.0f,400.0f);
			m_isSprite = true;
		}
		else if (!m_isWin && !m_isSprite) {
			//敗北。
			m_resultSprite = NewGO<prefab::SpriteRender>(0);
			m_resultSprite->Init(L"Assets/sprite/lose.dds",600.0f,400.0f);
			m_isSprite = true;
		}

		
		if (g_pad[0].IsTrigger(enButtonA))
		{
			//戦闘後処理。
			m_battleManager->SaveData();		//行動データの更新と保存。

			////戦闘シーンの削除。
			//DeleteGO(m_battleManager);
			//m_battleManager = nullptr;

			//フェードさせる。
			m_state = enState_FadeOut;
			m_fade->StartFadeOut();
		}

		break;

	case enState_FadeOut:
		//bgmのフェードアウト。
		if (m_bgmVol > 0.0f) {
			m_bgmVol -= g_gameTime.GetFrameDeltaTime();
			m_bgmVol = max(0.0f, m_bgmVol);
		}
		if (!m_fade->IsFade())
		{
			//フェードが終わるとタイトルに戻る。
			NewGO<TitleScene>(0, nullptr);
			DeleteGO(this);
		}
		break;
	}

	m_bgm->SetVolume(m_bgmVol*SOUND_VOL);
	////レベルの描画。
	//m_level.Draw();
}

void BattleScenes::Draw()
{
	//ここで呼んでるとゲームループできないんだが。
	auto shadowMap = g_graphicsEngine->GetShadowMap();
	shadowMap->Update(CVector3::AxisY()*1000.0f + CVector3::AxisX()*200.0f, CVector3::Zero());
	shadowMap->SendShadowRecieverParamToGpu();
	shadowMap->RenderToShadowMap();
	//ステージを表示させる。
	m_model.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
}

