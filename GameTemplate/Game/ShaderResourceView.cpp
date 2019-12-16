#include "stdafx.h"
#include "ShaderResourceView.h"
#include "StructuredBuffer.h"

namespace Engine {
	ShaderResourceView::ShaderResourceView()
	{
	}


	ShaderResourceView::~ShaderResourceView()
	{
		Release();
	}

	//開放処理
	void ShaderResourceView::Release()
	{
		//中に何か入ってたら開放する
		if (m_srv != nullptr)
		{
			m_srv->Release();
			m_srv = nullptr;
		}
		m_isValid = false;
	}
	bool ShaderResourceView::Create(CStructuredBuffer& structuredBuffer)
	{
		//なにか入ってたら行けないから開放処理を呼ぶ
		Release();
		ID3D11Buffer*pBuf = structuredBuffer.GetBody();
		//ID3D11Bufferに何か入っていたら
		if (pBuf != nullptr)
		{
			D3D11_BUFFER_DESC descBuf;
			ZeroMemory(&descBuf, sizeof(descBuf));
			pBuf->GetDesc(&descBuf);

			D3D11_SHADER_RESOURCE_VIEW_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
			desc.BufferEx.FirstElement = 0;

			desc.Format = DXGI_FORMAT_UNKNOWN;
			desc.BufferEx.NumElements = descBuf.ByteWidth / descBuf.StructureByteStride;

			//処理の失敗の原因まで特定してくれる便利な奴
			HRESULT hr = GraphicsEngine().GetD3DDevice()->CreateShaderResourceView(pBuf, &desc, &m_srv);
			if (FAILED(hr))
			{
				return false;
			}
		}
		//有効になった
		m_isValid = true;
		return true;
	}
}