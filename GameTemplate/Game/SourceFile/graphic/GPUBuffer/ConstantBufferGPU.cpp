#include "stdafx.h"
#include "ConstantBufferGPU.h"

namespace Engine {
	ConstantBufferGPU::ConstantBufferGPU()
	{

	}

	ConstantBufferGPU::~ConstantBufferGPU()
	{
		if (m_constantBuffer != nullptr) {
			m_constantBuffer->Release();
		}
	}

	void ConstantBufferGPU::Create(const void* pInitData, int bufferSize)
	{
		//�쐬����萔�o�b�t�@�̏���ݒ肷��
		D3D11_BUFFER_DESC bufferDesc;
		//�[���������[�ŏ���������
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;		//�o�b�t�@�[�őz�肳��Ă���ǂݍ��݋y�я������݂̕��@
		bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;		//�o�b�t�@�̃T�C�Y��16�o�C�g�A���C�����g�Ő؂�グ
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		//�o�b�t�@�̎g����
		bufferDesc.CPUAccessFlags = 0;		//CPU���g�����ǂ���		0����CPU���g�p���Ȃ�

		auto d3dDevice = g_graphicsEngine->GetD3DDevice();
		if (pInitData != nullptr)
		{
			//�������f�[�^���w�肳��Ă���
			D3D11_SUBRESOURCE_DATA InitData;
			InitData.pSysMem = pInitData;
			d3dDevice->CreateBuffer(&bufferDesc, &InitData, &m_constantBuffer);
		}
		else
		{
			d3dDevice->CreateBuffer(&bufferDesc, nullptr, &m_constantBuffer);
		}
	}
}