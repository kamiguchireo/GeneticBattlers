#include "stdafx.h"
#include "system/system.h"
#include "level/Level.h"
#include "SourceFile/GameObject/GameObjectManager.h"
#include "Game.h"
#include "Fade.h"
#include "gameScenes/TitleScene.h"
#include "SpriteRender.h"
#include "ShaderResourceView.h"
#include "SourceFile/graphic/2D/Sprite.h"
#include "SourceFile/graphic/Effect/CEffect.h"
#include "SourceFile/Sound/CSoundSource.h"
#include "SourceFile/Sound/SoundEngine.h"
#include "SourceFile/Light/DirectionLight.h"

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
	
	g_camera2D.SetPosition({ 0.0f, 0.0f, 0.0f });
	g_camera2D.SetTarget({ 0.0f, 0.0f, 10.0f });
	g_camera2D.SetFar(100.0f);
	//CGameObjectManager gameObject;

	//エフェクサーマネージャーの初期化
	g_graphicsEngine->managerInit();
	
	//ゲームクラスの生成。
	//NewGO<Game>(0, nullptr);
	//NewGO<TitleScene>(0, nullptr);
	//NewGO<Fade>(1, "Fade");
	
	////スプライトの確認のためのポインタ
	//prefab::SpriteRender*m_spriteRender;

	////スプライトを初期化
	//m_spriteRender = NewGO<prefab::SpriteRender>(0,"sprite");
	//m_spriteRender->Init(L"Assets/sprite/mikyan.dds", 400, 300);
	//const float FRAME_BUFFER_W = 1280.0;				//フレームバッファの幅。
	//const float FRAME_BUFFER_H = 720.0f;				//フレームバッファの高さ。

	//ShaderResourceView m_srv;
	//Sprite sprite;
	//m_srv.CreateFromDDSTextureFromFile(L"Assets/sprite/win.dds");
	//sprite.Init(m_srv.GetBody(), 500.0f, 500.0f);
	//sprite.Update({0.0,0.0,5.0}, CQuaternion::Identity(), CVector3::One());

	////エフェクトを作成。
	//prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
	////エフェクトを再生。
	//effect->Play(L"Assets/effect/test.efk");
	//CVector3 emitPos = CVector3::Zero();
	//emitPos.y += 100.0f;
	//effect->SetPosition(emitPos);

	//CSoundEngine se;
	//se.Init();

	//prefab::CSoundSource ss;
	////ss = NewGO<prefab::CSoundSource>(0);
	//ss.Init(L"Assets/sound/bgm_00.wav");
	//ss.Play(false);

	SkinModel m_model;
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	CVector3 m_pos = { 100.0f,0.0f,0.0f };
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
	CQuaternion m_ligdir2 = { 0.707,0.0,1.0,1.0 };
	m_model.SetLightDir(m_ligdir2);
	//m_model.SetActiveDLFlag(1);

	SkinModel m_model2;
	m_model2.Init(L"Assets/modelData/unityChan.cmo");
	CVector3 m_pos2 = { -100.0f,0.0f,0.0f };
	m_model2.UpdateWorldMatrix(m_pos2, CQuaternion::Identity(), CVector3::One());
	CVector4 m_ligCol = { 1.0,1.0,1.0,1.0 };
	CQuaternion m_ligdir = { 0.707,0.0,1.0,1.0 };
	m_model2.SetLightColor(m_ligCol);
	m_model2.SetLightDir(m_ligdir);

	//prefab::DirectionLight* DL;
	//DL = NewGO<prefab::DirectionLight>(0);

	g_camera2D.Update2D();
	
	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		
		//描画開始。
		g_graphicsEngine->BegineRender();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//物理エンジンの更新。
		g_physics.Update();

		GameObjectManager().Start();
		GameObjectManager().Update();
		//カメラの更新。
		g_camera3D.Update();
		//sprite.Update({ 0.0,0.0,5.0 }, CQuaternion::Identity(), CVector3::One());
		//sprite.Draw
		//(
		//	g_camera2D.GetViewMatrix(),
		//	g_camera2D.GetProjectionMatrix()
		//);
		//g_graphicsEngine->Execute2DDraw();

		//if(GetAsyncKeyState(VK_UP))
		//{

		//	//エフェクトを作成。
		//	prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
		//	//エフェクトを再生。
		//	effect->Play(L"Assets/effect/test.efk");
		//	CVector3 emitPos = CVector3::Zero();
		//	emitPos.y += 100.0f;
		//	effect->SetPosition(emitPos);
		//	effect->SetScale({ 10.0f,10.0f,10.0f });
		//}

		//モデルのドロー
		m_model.Draw
		(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);

		m_model2.Draw
		(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
		//描画終了。
		g_graphicsEngine->EndRender();
	}
}