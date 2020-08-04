#include "stdafx.h"
#include "Engine.h"

namespace Engine {
	void EngineProcessing::Init()
	{
		se.Init();
		//�J�������������B
		g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
		g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
		g_camera3D.SetFar(10000.0f);
		g_camera3D.Update();

		g_camera2D.SetPosition({ 0.0f, 0.0f, 0.0f });
		g_camera2D.SetTarget({ 0.0f, 0.0f, 10.0f });
		g_camera2D.SetFar(100.0f);
		g_camera2D.Update2D();
		//�G�t�F�N�T�[�}�l�[�W���[�̏�����
		g_graphicsEngine->managerInit();

	}

	void EngineProcessing::Update()
	{
		//�|�X�g�G�t�F�N�g�̍X�V
		m_postEffect.Update();
		//EffectDraw();

	}

	//void EngineProcessing::EffectDraw()
	//{
	//	Effekseer::Matrix44 efCameraMat;
	//	g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
	//	Effekseer::Matrix44 efProjMat;
	//	g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
	//	//�J�����s��ƃv���W�F�N�V�����s���ݒ�B
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
		//�t���[���o�b�t�@�̂̃����_�����O�^�[�Q�b�g���o�b�N�A�b�v���Ă����B
		auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		d3dDeviceContext->OMGetRenderTargets(
			1,
			&m_frameBufferRenderTargetView,
			&m_frameBufferDepthStencilView
		);

		//�r���[�|�[�g���o�b�N�A�b�v������Ă����B
		unsigned int numViewport = 1;
		d3dDeviceContext->RSGetViewports(&numViewport, &m_frameBufferViewports);

		//�����_�[�^�[�Q�b�g�̕ύX
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
		//�����_�[�^�[�Q�b�g�����Ƃɖ߂�
		g_graphicsEngine->ChangeRenderTarget
		(
			d3dDeviceContext,
			m_frameBufferRenderTargetView,
			m_frameBufferDepthStencilView,
			&m_frameBufferViewports
		);
		//�����_�[�^�[�Q�b�g�ƃf�v�X�X�e���V���̉��
		m_frameBufferRenderTargetView->Release();
		m_frameBufferDepthStencilView->Release();

	}

	void EngineProcessing::MainSpriteDraw()
	{
		//�쐬�����X�v���C�g��\������
		g_graphicsEngine->GetSp()->Update(MSC.m_sposition, MSC.m_rotation, MSC.m_scale, MSC.m_pivot);
		g_graphicsEngine->GetSp()->Draw
		(
			g_camera2D.GetViewMatrix(),
			g_camera2D.GetProjectionMatrix()
		);
	}

	void EngineProcessing::ClearRT()
	{
		//���݂̃����_�����O�^�[�Q�b�g���N���A����B
		float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		g_graphicsEngine->GetRT()->ClearRenderTarget(clearColor);
	}

}