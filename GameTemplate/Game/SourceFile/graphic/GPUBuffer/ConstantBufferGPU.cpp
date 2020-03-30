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
		//作成する定数バッファの情報を設定する
		D3D11_BUFFER_DESC bufferDesc;
		//ゼロメモリーで初期化する
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;		//バッファーで想定されている読み込み及び書き込みの方法
		bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;		//バッファのサイズを16バイトアライメントで切り上げ
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		//バッファの使い方
		bufferDesc.CPUAccessFlags = 0;		//CPUを使うかどうか		0だとCPUを使用しない

		auto d3dDevice = g_graphicsEngine->GetD3DDevice();
		if (pInitData != nullptr)
		{
			//初期化データが指定されている
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