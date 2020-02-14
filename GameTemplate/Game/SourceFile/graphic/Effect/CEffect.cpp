#include "stdafx.h"
#include "CEffect.h"

namespace Engine {
	namespace prefab {
		CEffect::CEffect()
		{
		}
		CEffect::~CEffect()
		{
			Release();
		}

		//�������
		void CEffect::Release()
		{
			if (m_handle != -1)
			{
				m_manager->StopEffect(m_handle);
				m_handle = -1;
			}
		}

		void CEffect::managerInit()
		{
			//�����_���[��������
			m_renderer = EffekseerRendererDX11::Renderer::Create(
				g_graphicsEngine->GetD3DDevice(),
				g_graphicsEngine->GetD3DDeviceContext(),
				2000);

			//�G�t�F�N�g�}�l�[�W���[��������
			m_manager = Effekseer::Manager::Create(10000);
			//�`��p�C���X�^���X����`��@�\��ݒ�
			m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
			m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
			m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
			m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
			m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());

			//�`��p�C���X�^���X����e�N�X�`���̓ǂݍ��݋@�\��ݒ�
			m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
			m_manager->SetModelLoader(m_renderer->CreateModelLoader());
		}
		void CEffect::Play(const wchar_t* filePath)
		{
			managerInit();
			int nameKey = Util::MakeHash(filePath);
			m_effect = GetResource(nameKey);
			if (m_effect == nullptr)
			{
				//���o�^
				m_effect = Effekseer::Effect::Create(m_manager, (const EFK_CHAR*)filePath);
				if (m_effect == nullptr)
				{
					//�G�t�F�N�g�̃��[�h�Ɏ��s�������I
					//��O�X���[���I������ˁI������
					throw;
				}
				RegistResource(nameKey,m_effect);
			}
			m_handle = m_manager->Play(m_effect, 0, 0, 0);
		}

		void CEffect::Update()
		{
			Effekseer::Matrix44 efCameraMat;
			g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
			Effekseer::Matrix44 efProjMat;
			g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
			//�J�����s��ƃv���W�F�N�V�����s���ݒ�B
			m_renderer->SetCameraMatrix(efCameraMat);
			m_renderer->SetProjectionMatrix(efProjMat);

			m_manager->Update();

			CMatrix m_Trans, m_Rot, m_Scale, m_Base = CMatrix::Identity();
			m_Trans.MakeTranslation(m_position);
			m_Rot.MakeRotationFromQuaternion(m_rotation);
			m_Scale.MakeScaling(m_scale);
			m_Base.Mul(m_Scale, m_Rot);
			m_Base.Mul(m_Base, m_Trans);
			m_manager->SetBaseMatrix(m_handle, m_Base);

			m_renderer->BeginRendering();
			m_manager->Draw();
			m_renderer->EndRendering();

			if (IsPlay() == false)
			{
				//�Đ�����������I���
				DeleteGO(this);
			}
		}
	}
}