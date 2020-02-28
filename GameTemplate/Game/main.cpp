#include "stdafx.h"
#include "system/system.h"
#include "level/Level.h"
#include "SourceFile/GameObject/GameObjectManager.h"
#include "Game.h"
#include "Fade.h"
#include "gameScenes/TitleScene.h"
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
	
	//Gameの生成。
	//エンジンの実験してるので中身は触らないで
	//NewGO<Game>(0, nullptr);

	//ここに必要なものはNewGOしていってください
	NewGO<TitleScene>(0, nullptr);
	NewGO<Fade>(1, "Fade");
	
	//エフェクサーマネージャーの初期化
	//コメントアウトしないで
	g_graphicsEngine->managerInit();

	//サウンド関係の初期化
	//コメントアウトしないで
	CSoundEngine se;
	se.Init();

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


		//描画終了。
		g_graphicsEngine->EndRender();
	}
}