#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Fade.h"

Game::Game()
{	
	g_camera3D.SetPosition({ 0.0f, 100.0f, 500.0f });
	g_camera3D.SetTarget({ 0.0f, 0.0f, 0.0f });
	
	//アニメーションクリップの読み込み。
	m_animClip[0].Load(L"Assets/animData/idle.tka");
	m_animClip2[0].Load(L"Assets/animData/run.tka");
	m_animClip[0].SetLoopFlag(true);
	m_animClip2[0].SetLoopFlag(true);
}


Game::~Game()
{

}

bool Game::Start()
{
	bool result = m_skeleton.Load(L"Assets/modelData/unityChan.tks");
	if (result == false)
	{
		throw;
	}
	result = m_skeleton2.Load(L"Assets/modelData/unityChan.tks");
	if (result == false)
	{
		throw;
	}

	m_model.Init(L"Assets/modelData/unityChan.cmo",m_skeleton);
	CVector3 m_pos = { 0.0f,0.0f,0.0f };
	m_model.SetActiveDLFlag(0);
	m_model.SetActiveRLFlag(1);
	m_position = m_pos;
	m_rotation.SetRotationDeg(CVector3::AxisX(), -90.0f);


	m_skeleton.Update(m_model.GetWorldMatrix());
	m_bone = (m_skeleton2.GetChildBoneMat(L"Character1_Hips"));
	m_animation.Init(m_skeleton, m_animClip, 2);
	m_animation2.Init(m_skeleton2, m_animClip2, 2);
	m_animation.Play(0);
	m_animation2.Play(0);

	////モデル2
	//m_model2.Init(L"Assets/modelData/DesertDragon.cmo");
	//m_model2.UpdateWorldMatrix(m_pos2, CQuaternion::Identity(), CVector3::One());
	//CVector4 m_ligCol = { 1.0f,1.0f,1.0f,1.0f };
	//CQuaternion m_ligdir = { 0.707f,0.0f,1.0f,1.0f};
	//m_model2.SetLightColor(m_ligCol);
	//m_model2.SetLightDir(m_ligdir);
	//m_model2.SetActiveDLFlag(1);
	//m_model2.SetActiveRLFlag(1);

	//モデル3
	m_model3.Init(L"Assets/modelData/EngineGround.cmo");
	CVector3 m_pos3 = { 0.0f,0.0f,0.0f };
	CVector3 m_scale = { 5.0f,5.0f,5.0f };
	m_model3.UpdateWorldMatrix(m_pos3, CQuaternion::Identity(), m_scale);
	//CQuaternion m_ligdir3 = { 0.0f,-1.0f,0.0f,0.0f };
	//m_model3.SetLightDir(m_ligdir3);
	m_model3.SetActiveDLFlag(0);
	m_model3.SetShadowReciever(true);
	//m_position.y = 100.0f;

	return true;
}

void Game::Update()
{
	if (GetAsyncKeyState(VK_UP))
	{
		m_position.z-=5.0f;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		m_position.z+=5.0f;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_position.x-=5.0f;
	}	
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_position.x+=5.0f;
	}

	//fr->SetScale(f);
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
	//m_model2.UpdateWorldMatrix(m_pos2, CQuaternion::Identity(), CVector3::One()/3.0f);
	m_animation.Update(1.0f / 30.0f);
	m_animation2.Update(1.0f / 30.0f);
	for (int i = 0; i < m_bone.size(); i++)
	{
		m_skeleton.ChangeMatrix(m_bone[i]->GetNo(),m_bone[i]->GetLocalMatrix());
	}
	m_skeleton.Update(m_model.GetWorldMatrix());

	m_skeleton.SendBoneMatrixArrayToGPU();



	auto m_shadowMap = g_graphicsEngine->GetShadowMap();

	m_shadowMap->Update({ 0.0f, 1000.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f });
	m_shadowMap->RegistShadowCaster(&m_model);
	m_shadowMap->SendShadowRecieverParamToGpu();
	m_shadowMap->RenderToShadowMap();
}

void Game::Draw()
{
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
}