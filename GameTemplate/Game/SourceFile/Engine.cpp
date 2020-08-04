#include "stdafx.h"
#include "Engine.h"

namespace Engine {
	void EngineProcessing::Init()
	{
		se.Init();
		//カメラを初期化。
		g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
		g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
		g_camera3D.SetFar(10000.0f);
		g_camera3D.Update();

		g_camera2D.SetPosition({ 0.0f, 0.0f, 0.0f });
		g_camera2D.SetTarget({ 0.0f, 0.0f, 10.0f });
		g_camera2D.SetFar(100.0f);
		g_camera2D.Update2D();
		//エフェクサーマネージャーの初期化
		g_graphicsEngine->managerInit();

	}

	void EngineProcessing::Update()
	{
		//ポストエフェクトの更新
		m_postEffect.Update();
		//EffectDraw();

	}

	//void EngineProcessing::EffectDraw()
	//{
	//	Effekseer::Matrix44 efCameraMat;
	//	g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
	//	Effekseer::Matrix44 efProjMat;
	//	g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
	//	//カメラ行列とプロジェクション行列を設定。
	//	g_graphicsEngine->GetEffekseerRender().SetCameraMatrix(efCameraMat);
	//	g_graphicsEngine->GetEffekseerRender().SetProjectionMatrix(efProjMat);

	//	g_graphicsEngine->GetEffekseerManager().Update(g_gameTime.GetFrameDeltaTime() * 60.0f);

	//	g_graphicsEngine->GetEffekseerRender().BeginRendering();
	//	g_graphicsEngine->GetEffekseerManager().Draw();
	//	g_graphicsEngine->GetEffekseerRender().EndRendering();
	//}

	void EngineProcessing::PostEffectDraw()
	{
		m_postEffect.Draw();
	}

	void EngineProcessing::ChangeRT()
	{
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

		//レンダーターゲットの変更
		g_graphicsEngine->ChangeRenderTarget
		(
			d3dDeviceContext,
			g_graphicsEngine->GetRT()->GetRenderTargetView(),
			g_graphicsEngine->GetRT()->GetDepthStensilView(),
			&m_frameBufferViewports
		);

		ClearRT();
	}

	void EngineProcessing::ReturnRT()
	{
		auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		//レンダーターゲットをもとに戻す
		g_graphicsEngine->ChangeRenderTarget
		(
			d3dDeviceContext,
			m_frameBufferRenderTargetView,
			m_frameBufferDepthStencilView,
			&m_frameBufferViewports
		);
		//レンダーターゲットとデプスステンシルの解放
		m_frameBufferRenderTargetView->Release();
		m_frameBufferDepthStencilView->Release();

	}

	void EngineProcessing::MainSpriteDraw()
	{
		//作成したスプライトを表示する
		g_graphicsEngine->GetSp()->Update(MSC.m_sposition, MSC.m_rotation, MSC.m_scale, MSC.m_pivot);
		g_graphicsEngine->GetSp()->Draw
		(
			g_camera2D.GetViewMatrix(),
			g_camera2D.GetProjectionMatrix()
		);
	}

	void EngineProcessing::ClearRT()
	{
		//現在のレンダリングターゲットをクリアする。
		float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		g_graphicsEngine->GetRT()->ClearRenderTarget(clearColor);
	}

}