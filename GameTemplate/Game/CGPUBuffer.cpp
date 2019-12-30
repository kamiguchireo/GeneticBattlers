#include "stdafx.h"
#include "CGPUBuffer.h"

namespace Engine {
	CGPUBuffer::CGPUBuffer()
	{
	}
	CGPUBuffer::~CGPUBuffer()
	{
		Release();
	}

	//�J������
	void CGPUBuffer::Release()
	{
		//GPUBuffer�ɉ��������Ă�����
		if (m_gpuBuffer != nullptr)
		{
			//ID3D11Buffer�̊J���������s��
			m_gpuBuffer->Release();
			//m_gpuBuffer���ʂ�Ղ����ɂ���
			m_gpuBuffer = nullptr;
		}
	}

	bool CGPUBuffer::Create(const void* pInitData, D3D11_BUFFER_DESC& bufferDesc)
	{
		//���g�����邩������Ȃ�����J���������s��
		Release();
		//���s�̌����܂ŏo���Ă����֗��Ȃ��
		HRESULT hr;
		if (pInitData)
		{
			//�o�b�t�@�[��2D��3D�̃e�N�X�`�����쐬����Ăяo����
			//�g�p�����
			D3D11_SUBRESOURCE_DATA InitData;
			//�������f�[�^�ւ̃|�C���^
			InitData.pSysMem = pInitData;
			//���s�̌��������
			hr = GraphicEngine.GetD3DDevice()->CreateBuffer(&bufferDesc, &InitData, &m_gpuBuffer);
		}
		else 
		{
			//���s�̌��������
			hr = GraphicEngine.GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_gpuBuffer);
		}
		//���s������
		if (FAILED(hr))
		{
			//false�����
			return false;
		}
		//����������true��Ԃ�
		return true;
	}
}