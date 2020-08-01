#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Fade.h"

Game::Game()
{	
	////���C���ƂȂ郌���_�����O�^�[�Q�b�g���쐬����B
	//m_mainRenderTarget.Create(
	//	FRAME_BUFFER_W,
	//	FRAME_BUFFER_H,
	//	DXGI_FORMAT_R8G8B8A8_UNORM
	//);

	////���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G��
	////�t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g������������
	//m_copyMainRtToFrameBufferSprite.Init(
	//	m_mainRenderTarget.GetRenderTargetSRV(),
	//	FRAME_BUFFER_W,
	//	FRAME_BUFFER_H
	//);

	g_camera3D.SetPosition({ 0.0f, 100.0f, 500.0f });
	g_camera3D.SetTarget({ 0.0f, 0.0f, 0.0f });
	
	//�A�j���[�V�����N���b�v�̓ǂݍ��݁B
	m_animClip[0].Load(L"Assets/animData/idle.tka");
	m_animClip[1].Load(L"Assets/animData/run.tka");
	m_animClip[0].SetLoopFlag(true);
	m_animClip[1].SetLoopFlag(true);
}


Game::~Game()
{

}

bool Game::Start()
{

	//�X�v���C�g��������
	//m_spriteRender = NewGO<prefab::SpriteRender>(0,"sprite");
	//m_spriteRender->Init(L"Assets/sprite/Good.dds", 400, 300);

	//�G�t�F�N�g���Đ��B
	//effect->Play(L"Assets/effect/test.efk");
	//CVector3 emitPos = CVector3::Zero();
	//emitPos.y += 100.0f;
	//effect->SetPosition(emitPos);
	
	//�T�E���h���Đ�
	//ss.Init(L"Assets/sound/bgm_00.wav");
	//ss.Play(false);

	//���f��1
	//m_model.Init(L"Assets/modelData/DesertDragon.cmo");

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
	//m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
	//CQuaternion m_ligdir2 = { 1.0f,.0f,0.0f,0.0f };
	//m_model.SetLightDir(m_ligdir2);
	m_model.SetActiveDLFlag(0);
	m_model.SetActiveRLFlag(1);
	m_position = m_pos;
	m_rotation.SetRotationDeg(CVector3::AxisX(), -90.0f);


	m_skeleton.Update(m_model.GetWorldMatrix());
	m_bone = (m_skeleton.GetChildBoneMat(L"Character1_Hips"));
	m_animation.Init(m_skeleton, m_animClip, 2);
	m_animation.Play(1);

	////���f��2
	//m_model2.Init(L"Assets/modelData/DesertDragon.cmo");
	//m_model2.UpdateWorldMatrix(m_pos2, CQuaternion::Identity(), CVector3::One());
	//CVector4 m_ligCol = { 1.0f,1.0f,1.0f,1.0f };
	//CQuaternion m_ligdir = { 0.707f,0.0f,1.0f,1.0f};
	//m_model2.SetLightColor(m_ligCol);
	//m_model2.SetLightDir(m_ligdir);
	//m_model2.SetActiveDLFlag(1);
	//m_model2.SetActiveRLFlag(1);



	//���f��3
	m_model3.Init(L"Assets/modelData/EngineGround.cmo");
	CVector3 m_pos3 = { 0.0f,0.0f,0.0f };
	CVector3 m_scale = { 5.0f,5.0f,5.0f };
	m_model3.UpdateWorldMatrix(m_pos3, CQuaternion::Identity(), m_scale);
	//CQuaternion m_ligdir3 = { 0.0f,-1.0f,0.0f,0.0f };
	//m_model3.SetLightDir(m_ligdir3);
	m_model3.SetActiveDLFlag(0);
	m_model3.SetShadowReciever(true);
	//m_position.y = 100.0f;
	
	//fr = NewGO<prefab::FontRender>(0);
	//fr->SetText(L"aaaaaaaaaaaaaaaaaaaaaa");
	//fr->SetPosition({ 0.0f, 0.0f });
	//fr->SetPivot({0.5f, 0.5f });
	return true;
}

void Game::Update()
{
	static float f = 0.5f;
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

	
	m_skeleton.Update(m_model.GetWorldMatrix());
	m_animation.Update(1.0f / 30.0f);
	m_skeleton.SendBoneMatrixArrayToGPU();
	
	
	auto m_shadowMap = g_graphicsEngine->GetShadowMap();

	if (GetAsyncKeyState('A'))
	{
		f += 0.01f;
		m_position.y += 10.0f;
		m_model.SetLightColor(f);
		//m_shadowMap->SetMaxheight(500.0f);
		//m_shadowMap->SetRange({ 400.0f,5000.0f,2000.0f });
	}
	m_shadowMap->Update({ 0.0f, 1000.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f });
	m_shadowMap->RegistShadowCaster(&m_model);
	m_shadowMap->SendShadowRecieverParamToGpu();
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

	//���f��2�̒ʏ�̃h���[
	//m_model2.Draw
	//(
	//	g_camera3D.GetViewMatrix(),
	//	g_camera3D.GetProjectionMatrix()
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

//void Game::ForwordRender()
//{
//	//�����_�����O�^�[�Q�b�g�����C���ɕύX����B
//	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
//	g_graphicsEngine->ChangeRenderTarget(
//		d3dDeviceContext, 
//		&m_mainRenderTarget, 
//		&m_frameBufferViewports
//	);
//	//���C�������_�����O�^�[�Q�b�g���N���A����B
//	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//	m_mainRenderTarget.ClearRenderTarget(clearColor);
//}

//void Game::PostRender()
//{
//	//�����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂�
//	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
//	g_graphicsEngine->ChangeRenderTarget(
//		d3dDeviceContext,
//		oldRenderTargetView,
//		oldDepthStencilView,
//		&m_frameBufferViewports
//	);
//
//	//�X�v���C�g�ɂ��Ă������̂��h���[
//	m_copyMainRtToFrameBufferSprite.Update(m_sposition, m_rotation, m_scale, m_pivot);
//	m_copyMainRtToFrameBufferSprite.Draw
//	(
//		g_camera2D.GetViewMatrix(),
//		g_camera2D.GetProjectionMatrix()
//	);
//
//}
void Game::Render()
{
	////�`��J�n
	////�V���h�E�}�b�v�Ƀ����_�����O
	//auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	////���݂̃����_�����O�^�[�Q�b�g���o�b�N�A�b�v���Ă���
	//d3dDeviceContext->OMGetRenderTargets
	//(
	//	1,
	//	&oldRenderTargetView,
	//	&oldDepthStencilView
	//);
	////�r���[�|�[�g���o�b�N�A�b�v������Ă���
	//unsigned int numViewPort = 1;
	//D3D11_VIEWPORT oldViewPorts;
	//d3dDeviceContext->RSGetViewports(&numViewPort, &oldViewPorts);
	


	//�V���h�E�}�b�v�Ƀ����_�����O
	auto m_shadowMap = g_graphicsEngine->GetShadowMap();
	m_shadowMap->RenderToShadowMap();

	////�f�o�C�X�R���e�L�X�g�����Ƃɖ߂�
	//d3dDeviceContext->OMSetRenderTargets
	//(
	//	1,
	//	&oldRenderTargetView,
	//	oldDepthStencilView
	//);
	//d3dDeviceContext->RSSetViewports
	//(
	//	numViewPort,
	//	&oldViewPorts
	//);
	//
	////�����_�����O�^�[�Q�b�g�ƃf�v�X�X�e���V���̎Q�ƃJ�E���^������
	//oldRenderTargetView->Release();
	//oldDepthStencilView->Release();

	//m_shadowMap->SendShadowRecieverParamToGpu();
	//ForwordRender();


	//PostRender();
	
	//�ʏ탌���_�����O
	//���f���̃h���[
	m_model.Draw
	(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
		//g_graphicsEngine->GetShadowMap()->GetLigthProjMatrix(0),
		//g_graphicsEngine->GetShadowMap()->GetLightViewMatrix(0)
	);

	//���f��3�̃h���[
	m_model3.Draw
	(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
		//g_graphicsEngine->GetShadowMap()->GetLigthProjMatrix(0),
		//g_graphicsEngine->GetShadowMap()->GetLightViewMatrix(0)
	);
}