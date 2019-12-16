#include "stdafx.h"
#include "StructuredBuffer.h"

namespace Engine {
	CStructuredBuffer::CStructuredBuffer()
	{
	}
	CStructuredBuffer::~CStructuredBuffer()
	{
		Release();
	}

	//�J���̏���
	void CStructuredBuffer::Release()
	{
		if (m_structuredBuffer != nullptr)
		{
			m_structuredBuffer->Release();
			m_structuredBuffer = nullptr;
		}
	}

	bool CStructuredBuffer::Create(const void*pInitData, D3D11_BUFFER_DESC&bufferDesc)
	{
		Release();
		HRESULT hr;		//���������s�����Ƃ��Ɍ����܂ŏo���Ă����֗��ȓz
		if (pInitData)
		{
			D3D11_SUBRESOURCE_DATA InitData;
			//�f�[�^��ϊ����Ă���
			//m_structureData��InitData��������bufferDesc��ϊ�����
			InitData.pSysMem = pInitData;
			hr = GraphicsEngine().GetD3DDevice()->CreateBuffer(&bufferDesc, &InitData, &m_structuredBuffer);
		}
		else {
			hr = GraphicsEngine().GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_structuredBuffer);
		}
		if (FAILED(hr))
		{
			return false;
		}
		if (bufferDesc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
		{
			m_srv.Create(*this);
		}
		return true;
	}
}