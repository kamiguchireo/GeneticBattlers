#include "stdafx.h"
#include "BattleScenes.h"
#include "monster/MonsterBase.h"
#include "monster/MonsterTeam1.h"
#include "monster/Attacker.h"
#include "monster/Healer.h"
#include "monster/Supporter.h"
#include "../TitleScene.h"
#include "../NetScenes/NetScenes.h"
#include "Fade.h"
#include "GameCamera.h"

BattleScenes::BattleScenes()
{

}

BattleScenes::~BattleScenes()
{
	DeleteGO(m_camera);
	DeleteGO(m_resultSprite);
}

bool BattleScenes::Start()
{
	//ネットシーンのポインタ取得。
	m_netScenes = NetScenes::GetInstance();

	//レベル。
	m_level.Init(L"Assets/level/testStage.tkl",[&](LevelObjectData& objData) {
		if (wcscmp(objData.name, L"testGround") == 0)
		{
			m_model.Init(L"Assets/modelData/testGround.cmo");
			m_model.SetActiveDLFlag(1);
			m_model.SetActiveRLFlag(0);
			m_model.UpdateWorldMatrix(
				objData.position,
				objData.rotation,
				CVector3::One()
			);
			return true;
		}
		if (wcscmp(objData.name, L"testModel") == 0)
		{
			MonsterTeam1* monster = NewGO<MonsterTeam1>(0);
			Status hoge;
			hoge.HP = rand() % 50 + 100;
			hoge.ATK = rand() % 10 + 10;
			hoge.DEF = rand() % 10 + 10;
			hoge.MAT = rand() % 10 + 10;
			hoge.MDF = rand() % 10 + 10;
			hoge.DEX = rand() % 10 + 10;
			monster->SetStatus(hoge);
			monster->SetPosition(objData.position);
			monster->SetRotation(objData.rotation);
			if (m_netScenes == nullptr){		//ネット通信でなければ。
				monster->Init("aaa");
			}
			else {		//通信しているなら。
				auto gi = monster->GetGIManager();
				gi.Init(m_netScenes->GetHealerData());
			}
			m_battleManager.PushBackEnemys(monster);

			CVector3 uipos = { objData.position.x / -2.5f - 50.0f,300.0f,0.0f };
			monster->SetUIPos(uipos);

			return true;
		}
		if (wcscmp(objData.name, L"Attacker") == 0)
		{
			MonsterBase* attacker = NewGO<Attacker>(0);
			Status hoge;
			hoge.HP = 130;
			//hoge.HP = 1;
			hoge.ATK = 300;
			hoge.DEF = 10;
			hoge.MAT = 5;
			hoge.MDF = 10;
			hoge.DEX = 10;
			attacker->SetStatus(hoge);
			attacker->SetPosition(objData.position);
			attacker->SetRotation(objData.rotation);
			attacker->Init("Assets/AIData/Attacker.bin");
			m_battleManager.PushBackTeams(attacker);

			return true;
		}	
		if (wcscmp(objData.name, L"Healer") == 0)
		{
			MonsterBase* healer = NewGO<Healer>(0);
			Status hoge;
			hoge.HP = 130;
			//hoge.HP = 1;
			hoge.ATK = 5;
			hoge.DEF = 10;
			hoge.MAT = 30;
			hoge.MDF = 20;
			hoge.DEX = 10;
			healer->SetStatus(hoge);
			healer->SetPosition(objData.position);
			healer->SetRotation(objData.rotation);
			healer->Init("Assets/AIData/Healer.bin");
			m_battleManager.PushBackTeams(healer);
		
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
			support->Init("Assets/AIData/Supporter.bin");
			m_battleManager.PushBackTeams(support);
		
			return true;
		}


		return false;
		});
	
	m_battleManager.SetTeams();
	m_battleManager.SetScenePointa(this);
	//カメラ。
	m_camera = NewGO<GameCamera>(0);
	//フェード。
	m_fade = Fade::GetInstance();
	m_fade->StartFadeIn();

	return true;
}

void BattleScenes::Update()
{
	rand();
	switch (m_state)
	{
	case enState_FadeIn:
		if (!m_fade->IsFade())	m_state = enState_Battle;
		break;
	case enState_Battle:
		//戦闘の更新処理をさせる。
		m_battleManager.BattleUpdate();

		if (g_pad[0].IsTrigger(enButtonStart)) 
		{
			//フェードさせる。
			m_state = enState_FadeOut; 
			m_fade->StartFadeOut();
		}
		break;

	case enState_Result:
		battleCoolTime -= 1.0f / 72.0f;
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
			m_battleManager.SaveData();		//行動データの更新と保存。

			//フェードさせる。
			m_state = enState_FadeOut;
			m_fade->StartFadeOut();
		}

		break;

	case enState_FadeOut:
		if (!m_fade->IsFade())
		{
			//フェードが終わるとタイトルに戻る。
			NewGO<TitleScene>(0, nullptr);
			DeleteGO(this);
		}
		break;
	}

	//ステージを表示させる。
	m_model.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
	//レベルの描画。
	m_level.Draw();
}

void BattleScenes::InitMonster()
{
	const int MonsterNum = 3;

	for (int i = 0; i < MonsterNum; i++) {
		MonsterBase* monster = NewGO<MonsterTeam1>(0);
		CVector3 pos(-50.0f + 50.0f*i, 0.0f, 0.0f);
		Status hoge;
		hoge.HP = rand() % 50 + 100;
		//hoge.MP = rand() % 50 + 100;
		hoge.ATK = rand() % 10 + 10;
		hoge.DEF = rand() % 10 + 10;
		hoge.MAT = rand() % 10 + 10;
		hoge.MDF = rand() % 10 + 10;
		hoge.DEX = rand() % 10 + 10;
		monster->SetPosition(pos);
		monster->SetStatus(hoge);
	}
}

