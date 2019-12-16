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

	//�J������
	void ShaderResourceView::Release()
	{
		//���ɉ��������Ă���J������
		if (m_srv != nullptr)
		{
			m_srv->Release();
			m_srv = nullptr;
		}
		m_isValid = false;
	}
	bool ShaderResourceView::Create(CStructuredBuffer& structuredBuffer)
	{
		//�Ȃɂ������Ă���s���Ȃ�����J���������Ă�
		Release();
		ID3D11Buffer*pBuf = structuredBuffer.GetBody();
		//ID3D11Buffer�ɉ��������Ă�����
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

			//�����̎��s�̌����܂œ��肵�Ă����֗��ȓz
			HRESULT hr = GraphicsEngine().GetD3DDevice()->CreateShaderResourceView(pBuf, &desc, &m_srv);
			if (FAILED(hr))
			{
				return false;
			}
		}
		//�L���ɂȂ���
		m_isValid = true;
		return true;
	}
}