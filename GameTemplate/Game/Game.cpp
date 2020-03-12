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
	CVector3 m_pos = { 0.0f,0.0f,0.0f };
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
	CQuaternion m_ligdir2 = { 1.0f,.0f,0.0f,0.0f };
	//m_model.SetLightDir(m_ligdir2);
	m_model.SetActiveDLFlag(0);
	m_model.SetActiveRLFlag(0);

	////���f��2
	//m_model2.Init(L"Assets/modelData/unityChan.cmo");
	//CVector3 m_pos2 = { 40.0f,0.0f,0.0f };
	//m_model2.UpdateWorldMatrix(m_pos2, CQuaternion::Identity(), CVector3::One());
	//CVector4 m_ligCol = { 1.0f,1.0f,1.0f,1.0f };
	//CQuaternion m_ligdir = { 0.707f,0.0f,1.0f,1.0f};
	//m_model2.SetLightColor(m_ligCol);
	//m_model2.SetLightDir(m_ligdir);
	//m_model2.SetActiveDLFlag(1);
	
	//���f��3
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
	////���f���̃h���[
	//m_model.Draw
	//(
	//	g_camera3D.GetViewMatrix(),
	//	g_camera3D.GetProjectionMatrix(),
	//	0
	//);

	////���f��2�̃V���G�b�g�̃h���[
	//m_model2.Draw
	//(
	//	g_camera3D.GetViewMatrix(),
	//	g_camera3D.GetProjectionMatrix(),
	//	1
	//);

	////���f��2�̒ʏ�̃h���[
	//m_model2.Draw
	//(
	//	g_camera3D.GetViewMatrix(),
	//	g_camera3D.GetProjectionMatrix(),
	//	0
	//);

	////���f��3�̃h���[
	//m_model3.Draw
	//(
	//	g_camera3D.GetViewMatrix(),
	//	g_camera3D.GetProjectionMatrix(),
	//	0
	//);

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

void Game::UpdateShadowMap()
{

}

void Game::Render()
{
	//�`��J�n
	g_graphicsEngine->BegineRender();
	//�V���h�E�}�b�v�Ƀ����_�����O
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//���݂̃����_�����O�^�[�Q�b�g���o�b�N�A�b�v���Ă���
	ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;
	d3dDeviceContext->OMGetRenderTargets
	(
		1,
		&oldRenderTargetView,
		&oldDepthStencilView
	);
	//�r���[�|�[�g���o�b�N�A�b�v������Ă���
	unsigned int numViewPort = 1;
	D3D11_VIEWPORT oldViewPorts;
	d3dDeviceContext->RSGetViewports(&numViewPort, &oldViewPorts);
	//�V���h�E�}�b�v�Ƀ����_�����O
	auto m_shadowMap = g_graphicsEngine->GetShadowMap();
	m_shadowMap->RenderToShadowMap();

	//�f�o�C�X�R���e�L�X�g�����Ƃɖ߂�
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
	//�����_�����O�^�[�Q�b�g�ƃf�v�X�X�e���V���̎Q�ƃJ�E���^������
	oldRenderTargetView->Release();
	oldDepthStencilView->Release();

	//�ʏ탌���_�����O
	//���f���̃h���[
	m_model.Draw
	(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	//���f��3�̃h���[
	m_model3.Draw
	(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);

	//�`��I��
	g_graphicsEngine->EndRender();
}