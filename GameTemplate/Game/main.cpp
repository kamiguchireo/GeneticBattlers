#include "stdafx.h"
#include "system/system.h"
#include "level/Level.h"
#include "SourceFile/GameObject/GameObjectManager.h"
#include "Game.h"
#include "Fade.h"
#include "gameScenes/TitleScene.h"
#include "SourceFile/Sound/SoundEngine.h"
#include "SourceFile/Light/DirectionLight.h"

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	
	/*
	RenderTarget m_mainRenderTarget;		//���C�������_�����O�^�[�Q�b�g�B
	//���C���ƂȂ郌���_�����O�^�[�Q�b�g���쐬����B
	m_mainRenderTarget.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R8G8B8A8_UNORM
	);
	
	Sprite m_copyMainRtToFrameBufferSprite;			//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g�B
	//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G��
	//�t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g������������
	m_copyMainRtToFrameBufferSprite.Init(
		m_mainRenderTarget.GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);
	*/
	D3D11_VIEWPORT m_frameBufferViewports;			//�t���[���o�b�t�@�̃r���[�|�[�g�B
	CVector3 m_sposition = { 0.0,0.0,5.0 };			//���W�B
	CQuaternion m_rotation = CQuaternion::Identity();			//!<��]�B
	CVector3 m_scale = CVector3::One();			//�g�嗦�B
	CVector2 m_pivot = Sprite::DEFAULT_PIVOT;	//�s�{�b�g�B
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B
	

	//�J�������������B
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
	
	g_camera2D.SetPosition({ 0.0f, 0.0f, 0.0f });
	g_camera2D.SetTarget({ 0.0f, 0.0f, 10.0f });
	g_camera2D.SetFar(100.0f);
	
	//Game�̐����B
	//�G���W���̎������Ă�̂Œ��g�͐G��Ȃ���
	//NewGO<Game>(0, nullptr);

	//�����ɕK�v�Ȃ��̂�NewGO���Ă����Ă�������
	NewGO<TitleScene>(0, nullptr);
	NewGO<Fade>(1, "Fade");
	
	//�G�t�F�N�T�[�}�l�[�W���[�̏�����
	//�R�����g�A�E�g���Ȃ���
	g_graphicsEngine->managerInit();

	//�T�E���h�֌W�̏�����
	//�R�����g�A�E�g���Ȃ���
	CSoundEngine se;
	se.Init();

	g_camera2D.Update2D();
	
	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{

		//�`��J�n�B
		g_graphicsEngine->BegineRender();

		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}	

		//�����G���W���̍X�V�B
		g_physics.Update();

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
		

		//�Q�[���I�u�W�F�N�g�}�l�[�W���[��Start�֐�
		GameObjectManager().Start();

		
		{
			//�����_�����O�^�[�Q�b�g�����C���ɕύX����B
			{
				RenderTarget* RT;
				RT = g_graphicsEngine->GetRT();
				ID3D11RenderTargetView* rtTbl[] = {
					RT->GetRenderTargetView()
				};
				//�����_�����O�^�[�Q�b�g�̐؂�ւ��B
				d3dDeviceContext->OMSetRenderTargets(1, rtTbl, RT->GetDepthStensilView());
				if (&m_frameBufferViewports != nullptr) {
					//�r���[�|�[�g���w�肳��Ă�����A�r���[�|�[�g���ύX����B
					d3dDeviceContext->RSSetViewports(1, &m_frameBufferViewports);
				}
			}
			//���C�������_�����O�^�[�Q�b�g���N���A����B
			float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			g_graphicsEngine->GetRT()->ClearRenderTarget(clearColor);
		}
		

		//�Q�[���I�u�W�F�N�g�}�l�[�W���[��Update�֐�
		GameObjectManager().Update();

		
		//�����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂�
		{
			ID3D11RenderTargetView* rtTbl[] = {
			m_frameBufferRenderTargetView
			};
			//�����_�����O�^�[�Q�b�g�̐؂�ւ��B
			d3dDeviceContext->OMSetRenderTargets(1, rtTbl, m_frameBufferDepthStencilView);
			if (&m_frameBufferViewports != nullptr) {
				//�r���[�|�[�g���w�肳��Ă�����A�r���[�|�[�g���ύX����B
				d3dDeviceContext->RSSetViewports(1, &m_frameBufferViewports);
			}
		}
		/*
		//�X�v���C�g�ɂ��Ă������̂��h���[
		m_copyMainRtToFrameBufferSprite.Update(m_sposition, m_rotation, m_scale, m_pivot);
		m_copyMainRtToFrameBufferSprite.Draw
		(
			g_camera2D.GetViewMatrix(),
			g_camera2D.GetProjectionMatrix()
		);
		*/
		g_graphicsEngine->GetSp()->Update(m_sposition, m_rotation, m_scale, m_pivot);
		g_graphicsEngine->GetSp()->Draw
		(
			g_camera2D.GetViewMatrix(),
			g_camera2D.GetProjectionMatrix()
		);

		m_frameBufferRenderTargetView->Release();
		m_frameBufferDepthStencilView->Release();

		//�Q�[���I�u�W�F�N�g�}�l�[�W���[��Update�֐�
		GameObjectManager().SpStart();
		//�Q�[���I�u�W�F�N�g�}�l�[�W���[��Update�֐�
		GameObjectManager().SpRender();


		//�J�����̍X�V�B
		g_camera3D.Update();


		//�`��I���B
		g_graphicsEngine->EndRender();
	}
}
