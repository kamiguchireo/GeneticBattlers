#include "stdafx.h"
#include "system/system.h"
#include "level/Level.h"
#include "SourceFile/GameObject/GameObjectManager.h"
#include "Game.h"
#include "Fade.h"
#include "gameScenes/TitleScene.h"
#include "SourceFile/Sound/SoundEngine.h"
#include "SourceFile/Light/DirectionLight.h"
#include "SourceFile/graphic/PostEffect.h"
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

	D3D11_VIEWPORT m_frameBufferViewports;			//フレームバッファのビューポート。
	CVector3 m_sposition = { 0.0,0.0,5.0 };			//座標。
	CQuaternion m_rotation = CQuaternion::Identity();			//!<回転。
	CVector3 m_scale = CVector3::One();			//拡大率。
	CVector2 m_pivot = Sprite::DEFAULT_PIVOT;	//ピボット。
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。


	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);

	g_camera2D.SetPosition({ 0.0f, 0.0f, 0.0f });
	g_camera2D.SetTarget({ 0.0f, 0.0f, 10.0f });
	g_camera2D.SetFar(100.0f);

	//Gameの生成。
	//エンジンの実験してるので中身は触らないで
	NewGO<Game>(0, nullptr);

	//ここに必要なものはNewGOしていってください
	//NewGO<TitleScene>(0, nullptr);
	//NewGO<Fade>(1, "Fade");

	//エフェクサーマネージャーの初期化
	//コメントアウトしないで
	g_graphicsEngine->managerInit();

	//サウンド関係の初期化
	//コメントアウトしないで
	CSoundEngine se;
	se.Init();

	g_camera2D.Update2D();
	PostEffect m_postEffect;		//ポストエフェクト

	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//i++;
		networkLogic.run();

		//描画開始。
		g_graphicsEngine->BegineRender();

		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}

		//ポストエフェクトの更新
		m_postEffect.Update();

		//物理エンジンの更新。
		g_physics.Update();


		//フレームバッファののレンダリングターゲットをバックアップしておく。
		auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		d3dDeviceContext->OMGetRenderTargets(
			1,
			&m_frameBufferRenderTargetView,
			&m_frameBufferDepthStencilView
		);

		//ビューポートもバックアップを取っておく。
		unsigned int numViewport = 1;
		d3dDeviceContext->RSGetViewports(&numViewport, &m_frameBufferViewports);


		//ゲームオブジェクトマネージャーのStart関数
		GameObjectManager().Start();

		//レンダーターゲットの変更
		g_graphicsEngine->ChangeRenderTarget
		(
			d3dDeviceContext,
			g_graphicsEngine->GetRT()->GetRenderTargetView(),
			g_graphicsEngine->GetRT()->GetDepthStensilView(),
			&m_frameBufferViewports
		);

		//メインレンダリングターゲットをクリアする。
		float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		g_graphicsEngine->GetRT()->ClearRenderTarget(clearColor);

		//ゲームオブジェクトマネージャーのUpdate関数
		GameObjectManager().Update();

		//ポストエフェクトの描画
		m_postEffect.Draw();

		//レンダーターゲットをもとに戻す
		g_graphicsEngine->ChangeRenderTarget
		(
			d3dDeviceContext,
			m_frameBufferRenderTargetView,
			m_frameBufferDepthStencilView,
			&m_frameBufferViewports
		);

		//作成したスプライトを表示する
		g_graphicsEngine->GetSp()->Update(m_sposition, m_rotation, m_scale, m_pivot);
		g_graphicsEngine->GetSp()->Draw
		(
			g_camera2D.GetViewMatrix(),
			g_camera2D.GetProjectionMatrix()
		);

		//レンダーターゲットとデプスステンシルの解放
		m_frameBufferRenderTargetView->Release();
		m_frameBufferDepthStencilView->Release();

		
		//カメラの更新。
		g_camera3D.Update();


		//描画終了。
		g_graphicsEngine->EndRender();
	}

	networkLogic.disconnect();
}
