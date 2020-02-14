#include "stdafx.h"
#include "GameCamera.h"

GameCamera* GameCamera::m_instance = nullptr;

GameCamera::GameCamera()
{
	if (m_instance != nullptr)
	{
		std::abort();
		throw;
	}

	m_instance = this;
}

GameCamera::~GameCamera()
{
	m_instance = nullptr;
}

bool GameCamera::Start()
{
	//カメラの初期位置。
	m_firstPosition.Set(2500.0f,1500.0f,2500.0f);
	//m_firstPosition.Set(0.0f,1500.0f,2500.0f);
	m_firstTarget.Set(500.0f, 0.0f, 500.0f);
	//m_firstTarget.Set(0.0f, 0.0f, 500.0f);
	//カメラの初期設定。
	g_camera3D.SetNear(2.0f);
	g_camera3D.SetFar(10000.0f);
	g_camera3D.SetPosition(m_firstPosition);
	g_camera3D.SetTarget(m_firstTarget);
	g_camera3D.SetViewAngle(CMath::DegToRad(45.0f));

	return true;
}

void GameCamera::Update()
{
}
