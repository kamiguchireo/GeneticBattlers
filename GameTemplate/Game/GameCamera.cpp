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
	m_firstPosition.Set(2000.0f,1500.0f,2000.0f);
	//カメラの初期設定。
	g_camera3D.SetNear(2.0f);
	g_camera3D.SetFar(10000.0f);
	g_camera3D.SetPosition(m_firstPosition);
	g_camera3D.SetTarget(CVector3::Zero());

	return true;
}

void GameCamera::Update()
{
}
