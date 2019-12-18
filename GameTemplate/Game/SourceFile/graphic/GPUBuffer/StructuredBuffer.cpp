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

	//開放の処理
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
		HRESULT hr;		//処理が失敗したときに原因まで出してくれる便利な奴
		if (pInitData)
		{
			D3D11_SUBRESOURCE_DATA InitData;
			//データを変換している
			//m_structureDataにInitDataを条件にbufferDescを変換する
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