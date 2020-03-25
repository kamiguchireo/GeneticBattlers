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
	
	/*
	RenderTarget m_mainRenderTarget;		//メインレンダリングターゲット。
	//メインとなるレンダリングターゲットを作成する。
	m_mainRenderTarget.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R8G8B8A8_UNORM
	);
	
	Sprite m_copyMainRtToFrameBufferSprite;			//メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。
	//メインレンダリングターゲットに描かれた絵を
	//フレームバッファにコピーするためのスプライトを初期化する
	m_copyMainRtToFrameBufferSprite.Init(
		m_mainRenderTarget.GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);
	*/
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

		
		{
			//レンダリングターゲットをメインに変更する。
			{
				RenderTarget* RT;
				RT = g_graphicsEngine->GetRT();
				ID3D11RenderTargetView* rtTbl[] = {
					RT->GetRenderTargetView()
				};
				//レンダリングターゲットの切り替え。
				d3dDeviceContext->OMSetRenderTargets(1, rtTbl, RT->GetDepthStensilView());
				if (&m_frameBufferViewports != nullptr) {
					//ビューポートが指定されていたら、ビューポートも変更する。
					d3dDeviceContext->RSSetViewports(1, &m_frameBufferViewports);
				}
			}
			//メインレンダリングターゲットをクリアする。
			float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			g_graphicsEngine->GetRT()->ClearRenderTarget(clearColor);
		}
		

		//ゲームオブジェクトマネージャーのUpdate関数
		GameObjectManager().Update();

		
		//レンダリングターゲットをフレームバッファに戻す
		{
			ID3D11RenderTargetView* rtTbl[] = {
			m_frameBufferRenderTargetView
			};
			//レンダリングターゲットの切り替え。
			d3dDeviceContext->OMSetRenderTargets(1, rtTbl, m_frameBufferDepthStencilView);
			if (&m_frameBufferViewports != nullptr) {
				//ビューポートが指定されていたら、ビューポートも変更する。
				d3dDeviceContext->RSSetViewports(1, &m_frameBufferViewports);
			}
		}
		/*
		//スプライトにしていたものをドロー
		m_copyMainRtToFrameBufferSprite.Update(m_sposition, m_rotation, m_scale, m_pivot);
		m_copyMainRtToFrameBufferSprite.Draw
		(
			g_camera2D.GetViewMatrix(),
			g_camera2D.GetProjectionMatrix()
		);
		*/
		g_graphicsEngine->GetSp()->Update(m_sposition, m_rotation, m_scale, m_pivot);
		g_graphicsEngine->GetSp()->Draw
		(
			g_camera2D.GetViewMatrix(),
			g_camera2D.GetProjectionMatrix()
		);

		m_frameBufferRenderTargetView->Release();
		m_frameBufferDepthStencilView->Release();

		//ゲームオブジェクトマネージャーのUpdate関数
		GameObjectManager().SpStart();
		//ゲームオブジェクトマネージャーのUpdate関数
		GameObjectManager().SpRender();


		//カメラの更新。
		g_camera3D.Update();


		//描画終了。
		g_graphicsEngine->EndRender();
	}
}
