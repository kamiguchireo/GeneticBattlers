#include "stdafx.h"
#include "DirectionLight.h"

namespace Engine {
	namespace prefab {
		DirectionLight::DirectionLight()
		{

		}
		DirectionLight::~DirectionLight()
		{

		}

		//�萔�o�b�t�@�̏�����
		void DirectionLight::InitConstantBuffer()
		{
			//bufferDesc���[���ɃZ�b�g
			ZeroMemory(&bufferDesc, sizeof(bufferDesc));
			bufferDesc.Usage = D3D11_USAGE_DEFAULT;
			//�o�b�t�@�̃T�C�Y
			bufferDesc.ByteWidth = sizeof(SDirectionLight);
			//�萔�o�b�t�@
			bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			//CPU�͎g��Ȃ�
			bufferDesc.CPUAccessFlags = 0;
			//�f�B���N�V�������C�g�̒萔�o�b�t�@���쐬
			g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightCb);
		}
	}
}