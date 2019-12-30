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

	//開放処理
	void CGPUBuffer::Release()
	{
		//GPUBufferに何か入っていたら
		if (m_gpuBuffer != nullptr)
		{
			//ID3D11Bufferの開放処理を行う
			m_gpuBuffer->Release();
			//m_gpuBufferをぬるぷたぁにする
			m_gpuBuffer = nullptr;
		}
	}

	bool CGPUBuffer::Create(const void* pInitData, D3D11_BUFFER_DESC& bufferDesc)
	{
		//中身があるかもしれないから開放処理を行う
		Release();
		//失敗の原因まで出してくれる便利なやつ
		HRESULT hr;
		if (pInitData)
		{
			//バッファーや2Dと3Dのテクスチャを作成する呼び出しで
			//使用される
			D3D11_SUBRESOURCE_DATA InitData;
			//初期化データへのポインタ
			InitData.pSysMem = pInitData;
			//失敗の原因を特定
			hr = GraphicEngine.GetD3DDevice()->CreateBuffer(&bufferDesc, &InitData, &m_gpuBuffer);
		}
		else 
		{
			//失敗の原因を特定
			hr = GraphicEngine.GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_gpuBuffer);
		}
		//失敗したら
		if (FAILED(hr))
		{
			//falseを特定
			return false;
		}
		//成功したらtrueを返す
		return true;
	}
}