#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Fade.h"

Game::Game()
{	

}


Game::~Game()
{

}

bool Game::Start()
{
	//�X�v���C�g��������
	//m_spriteRender = NewGO<prefab::SpriteRender>(0,"sprite");
	//m_spriteRender->Init(L"Assets/sprite/mikyan.dds", 400, 300);
	
	//�G�t�F�N�g���Đ��B
	//effect->Play(L"Assets/effect/test.efk");
	//CVector3 emitPos = CVector3::Zero();
	//emitPos.y += 100.0f;
	//effect->SetPosition(emitPos);
	
	//�T�E���h���Đ�
	//ss.Init(L"Assets/sound/bgm_00.wav");
	//ss.Play(false);

	//���f��1
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	CVector3 m_pos = { 0.0f,0.0f,100.0f };
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
	CQuaternion m_ligdir2 = { 1.0f,0.0f,0.0f,0.0f };
	m_model.SetLightDir(m_ligdir2);
	m_model.SetActiveDLFlag(1);
	m_model.SetActiveRLFlag(0);

	//���f��2
	m_model2.Init(L"Assets/modelData/unityChan.cmo");
	CVector3 m_pos2 = { 40.0f,0.0f,0.0f };
	m_model2.UpdateWorldMatrix(m_pos2, CQuaternion::Identity(), CVector3::One());
	CVector4 m_ligCol = { 1.0f,1.0f,1.0f,1.0f };
	CQuaternion m_ligdir = { 0.707f,0.0f,1.0f,1.0f};
	m_model2.SetLightColor(m_ligCol);
	m_model2.SetLightDir(m_ligdir);
	m_model2.SetActiveDLFlag(1);

	return true;
}

void Game::Update()
{	
	//���f���̃h���[
	m_model.Draw
	(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		0
	);

	//���f��2�̃V���G�b�g�̃h���[
	m_model2.Draw
	(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		1
	);

	//���f��2�̒ʏ�̃h���[
	m_model2.Draw
	(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		0
	);
	//if(GetAsyncKeyState(VK_UP))
	//{
		//�G�t�F�N�g��NewGO
		//effect = NewGO<prefab::CEffect>(0);
		////�G�t�F�N�g���Đ��B
		//effect->Play(L"Assets/effect/test.efk");
		//CVector3 emitPos = CVector3::Zero();
		//emitPos.y += 100.0f;
		//effect->SetPosition(emitPos);
		//effect->SetScale({ 10.0f,10.0f,10.0f });
	//}
}