#include "stdafx.h"
#include "DirectionLight.h"

namespace Engine {
	namespace prefab {
		DirectionLight::DirectionLight()
		{
			//�A�N�e�B�u�t���O�̏�����
			for (int i = 0; i < 3; i++)
			{
				m_dirLight.ActiveFlag[i] = 0;
			}
			//���ʔ��˂̍i��̏�����
			m_dirLight.specPow = 10.0;
			InitConstantBuffer();
		}
		DirectionLight::~DirectionLight()
		{
			//���C�g�p�̒萔�o�b�t�@�̉��
			if (m_lightCb != nullptr)
			{
				m_lightCb->Release();
			}
		}

		//bool DirectionLight::Start()
		//{
		//	InitConstantBuffer();
		//	m_dirLight.direction = { 1.0f, 0.0f, 0.0f, 0.0f };
		//	m_dirLight.color = { 1.0f, 1.0f, 1.0f, 1.0f };
		//	return true;
		//}

		//void DirectionLight::Update()
		//{
		//	CQuaternion qRot;
		//	qRot.SetRotationDeg(CVector3::AxisY(), 2.0f);
		//	qRot.Multiply(m_dirLight.direction);
		//	Draw();
		//}

		void DirectionLight::Draw()
		{
			//���ʔ��˗p�̃J�����̎��_���擾����
			m_dirLight.eyePos = g_camera3D.GetPosition();
			auto dc = g_graphicsEngine->GetD3DDeviceContext();
			//���C�g�p�̒萔�o�b�t�@���X�V
			dc->UpdateSubresource(m_lightCb, 0, nullptr, &m_dirLight, 0, 0);
			//�萔�o�b�t�@���V�F�[�_�[�X���b�g�ɐݒ�
			dc->PSSetConstantBuffers(0, 1, &m_lightCb);
		}

		//�萔�o�b�t�@�̏�����
		void DirectionLight::InitConstantBuffer()
		{
			int bufferSize = sizeof(SDirectionLight);
			//bufferDesc���[���ɃZ�b�g
			ZeroMemory(&bufferDesc, sizeof(bufferDesc));
			bufferDesc.Usage = D3D11_USAGE_DEFAULT;
			//�o�b�t�@�̃T�C�Y
			//�o�b�t�@��16�o�C�g�A���C�����g�ɂȂ��Ă���K�v������
			bufferDesc.ByteWidth = Raundup16(bufferSize);	
			//�萔�o�b�t�@
			bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			//CPU�͎g��Ȃ�
			bufferDesc.CPUAccessFlags = 0;
			//�f�B���N�V�������C�g�̒萔�o�b�t�@���쐬
			g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightCb);
		}
	}
}