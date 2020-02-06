#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo");
}

Player::~Player()
{
}

bool Player::Start()
{

	return true;
}
void Player::Update()
{	
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
	Draw();
	m_position.x += 1.0f;

}
	
void Player::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}