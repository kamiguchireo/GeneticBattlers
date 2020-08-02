#include "stdafx.h"
#include "system/system.h"
#include "SourceFile/GameObject/GameObjectManager.h"
#include "Game.h"
#include "Fade.h"
#include "gameScenes/TitleScene.h"
#include "SourceFile/Engine.h"
//photon
#include "Photon/Common-cpp/inc/JString.h"
#include "Network/SampleNetwork.h"

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//photon
	//ここに作ったapp idをセットする
	static const ExitGames::Common::JString appID = L"ec02c427-5314-40b3-9328-d9d590465f14";
	static const ExitGames::Common::JString appVersion = L"1.0";
	//ネットワークに接続
	SampleNetwork networkLogic(appID, appVersion);
	networkLogic.connect();
	
	EngineProcessing EP;		//エンジンの処理関係をまとめたクラス
	EP.Init();

	//Gameの生成。
	//エンジンの実験してるので中身は触らないで
	//NewGO<Game>(0, nullptr);

	//ここに必要なものはNewGOしていってください	
	NewGO<TitleScene>(0, nullptr);
	NewGO<Fade>(3, "Fade");

	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{	
		//ネットワークの更新
		networkLogic.run();
		
		//カメラの更新。
		g_camera3D.Update();

		//描画開始。
		g_graphicsEngine->BegineRender();

		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}

		//物理エンジンの更新。
		g_physics.Update();

		//エンジン内部処理の更新処理
		EP.Update();

		////////////////////////////////////////////
		/////ここからオフスクリーンレンダリング/////
		////////////////////////////////////////////

		EP.ChangeRT();		//レンダリングターゲットを戻す

		//ゲームオブジェクトマネージャー全体の更新関数
		GameObjectManager().Thread();

		EP.PostEffectDraw();		//ポストエフェクトのDraw

		EP.ReturnRT();		//レンダリングターゲットを戻す

		////////////////////////////////////////////
		///////オフスクリーンレンダリング終了///////
		////////////////////////////////////////////

		EP.MainSpriteDraw();		//最終的に画面全体をスプライト化したものを描画
		
		//描画終了。
		g_graphicsEngine->EndRender();
	}

	//ゲームループ終了時にネットワークから切断する
	networkLogic.disconnect();
}