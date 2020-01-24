#include "stdafx.h"
#include "system/system.h"
#include "level/Level.h"
#include "SourceFile/GameObject/GameObjectManager.h"
#include "Game.h"
#include "SpriteRender.h"
#include "ShaderResourceView.h"
#include "SourceFile/graphic/2D/Sprite.h"

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

	//ゲームクラスの生成。
	NewGO<Game>(0, nullptr);

	//スプライトの確認のためのポインタ
	prefab::SpriteRender*m_spriteRender;

	//スプライトを初期化
	m_spriteRender = NewGO<prefab::SpriteRender>(0,"sprite");
	m_spriteRender->Init(L"Assets/sprite/mikyan.dds", 400, 300);
	const float FRAME_BUFFER_W = 1280.0;				//フレームバッファの幅。
	const float FRAME_BUFFER_H = 720.0f;				//フレームバッファの高さ。

	//ShaderResourceView m_srv;
	//Sprite sprite;
	//m_srv.CreateFromDDSTextureFromFile(L"Assets/sprite/win.dds");
	//sprite.Init(m_srv.GetBody(), 500.0f, 500.0f);
	//sprite.Update({0.0,0.0,5.0}, CQuaternion::Identity(), CVector3::One());
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

		//描画終了。
		g_graphicsEngine->EndRender();
	}
}