#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Fade.h"

Game::Game()
{	
	g_camera3D.SetPosition({ 0.0f, 500.0f, 1100.0f });
	g_camera3D.SetTarget({ 0.0f, 200.0f, 0.0f });

}


Game::~Game()
{

}

bool Game::Start()
{
	//スプライトを初期化
	//m_spriteRender = NewGO<prefab::SpriteRender>(0,"sprite");
	//m_spriteRender->Init(L"Assets/sprite/mikyan.dds", 400, 300);
	
	//エフェクトを再生。
	//effect->Play(L"Assets/effect/test.efk");
	//CVector3 emitPos = CVector3::Zero();
	//emitPos.y += 100.0f;
	//effect->SetPosition(emitPos);
	
	//サウンドを再生
	//ss.Init(L"Assets/sound/bgm_00.wav");
	//ss.Play(false);

	//モデル1
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	CVector3 m_pos = { 0.0f,0.0f,0.0f };
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
	CQuaternion m_ligdir2 = { 1.0f,.0f,0.0f,0.0f };
	//m_model.SetLightDir(m_ligdir2);
	m_model.SetActiveDLFlag(0);
	m_model.SetActiveRLFlag(0);

	////モデル2
	//m_model2.Init(L"Assets/modelData/unityChan.cmo");
	//CVector3 m_pos2 = { 40.0f,0.0f,0.0f };
	//m_model2.UpdateWorldMatrix(m_pos2, CQuaternion::Identity(), CVector3::One());
	//CVector4 m_ligCol = { 1.0f,1.0f,1.0f,1.0f };
	//CQuaternion m_ligdir = { 0.707f,0.0f,1.0f,1.0f};
	//m_model2.SetLightColor(m_ligCol);
	//m_model2.SetLightDir(m_ligdir);
	//m_model2.SetActiveDLFlag(1);
	
	//モデル3
	m_model3.Init(L"Assets/modelData/EngineGround.cmo");
	CVector3 m_pos3 = { 0.0f,0.0f,0.0f };
	m_model3.UpdateWorldMatrix(m_pos3, CQuaternion::Identity(), CVector3::One());
	CQuaternion m_ligdir3 = { 0.0f,-1.0f,0.0f,0.0f };
	//m_model3.SetLightDir(m_ligdir3);
	m_model3.SetActiveDLFlag(1);
	m_model3.SetShadowReciever(true);

	return true;
}

void Game::Update()
{	
	auto m_shadowMap = g_graphicsEngine->GetShadowMap();
	m_shadowMap->Update({ 1000.0f, 1000.0f, 1000.0f },
		{ 0.0f, 0.0f, 0.0f });
	m_shadowMap->RegistShadowCaster(&m_model);
	Render();
	////モデルのドロー
	//m_model.Draw
	//(
	//	g_camera3D.GetViewMatrix(),
	//	g_camera3D.GetProjectionMatrix(),
	//	0
	//);

	////モデル2のシルエットのドロー
	//m_model2.Draw
	//(
	//	g_camera3D.GetViewMatrix(),
	//	g_camera3D.GetProjectionMatrix(),
	//	1
	//);

	////モデル2の通常のドロー
	//m_model2.Draw
	//(
	//	g_camera3D.GetViewMatrix(),
	//	g_camera3D.GetProjectionMatrix(),
	//	0
	//);

	////モデル3のドロー
	//m_model3.Draw
	//(
	//	g_camera3D.GetViewMatrix(),
	//	g_camera3D.GetProjectionMatrix(),
	//	0
	//);

	//if(GetAsyncKeyState(VK_UP))
	//{
		//エフェクトをNewGO
		//effect = NewGO<prefab::CEffect>(0);
		////エフェクトを再生。
		//effect->Play(L"Assets/effect/test.efk");
		//CVector3 emitPos = CVector3::Zero();
		//emitPos.y += 100.0f;
		//effect->SetPosition(emitPos);
		//effect->SetScale({ 10.0f,10.0f,10.0f });
	//}
}

void Game::UpdateShadowMap()
{

}

void Game::Render()
{
	//描画開始
	g_graphicsEngine->BegineRender();
	//シャドウマップにレンダリング
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//現在のレンダリングターゲットをバックアップしておく
	ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;
	d3dDeviceContext->OMGetRenderTargets
	(
		1,
		&oldRenderTargetView,
		&oldDepthStencilView
	);
	//ビューポートもバックアップを取っておく
	unsigned int numViewPort = 1;
	D3D11_VIEWPORT oldViewPorts;
	d3dDeviceContext->RSGetViewports(&numViewPort, &oldViewPorts);
	//シャドウマップにレンダリング
	auto m_shadowMap = g_graphicsEngine->GetShadowMap();
	m_shadowMap->RenderToShadowMap();

	//デバイスコンテキストをもとに戻す
	d3dDeviceContext->OMSetRenderTargets
	(
		1,
		&oldRenderTargetView,
		oldDepthStencilView
	);
	d3dDeviceContext->RSSetViewports
	(
		numViewPort,
		&oldViewPorts
	);
	//レンダリングターゲットとデプスステンシルの参照カウンタを下す
	oldRenderTargetView->Release();
	oldDepthStencilView->Release();

	//通常レンダリング
	//モデルのドロー
	m_model.Draw
	(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	//モデル3のドロー
	m_model3.Draw
	(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);

	//描画終了
	g_graphicsEngine->EndRender();
}