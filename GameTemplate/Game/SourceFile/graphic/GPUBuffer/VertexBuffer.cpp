#include "stdafx.h"
#include "VertexBuffer.h"

namespace Engine {
	VertexBuffer::VertexBuffer()
	{
	}
	VertexBuffer::~VertexBuffer()
	{
		Release();
	}

	//開放処理
	void VertexBuffer::Release()
	{
		if (m_vertexBuffer != nullptr)
		{
			m_vertexBuffer->Release();
			m_vertexBuffer = nullptr;
		}
	}
	bool VertexBuffer::Create(int numVertex, int stride, const void* pSrcVertexBuffer)
	{
		//中身があるかもしれないので開放処理を行う
		Release();
		//バッファリソースを作成するために使用する
		D3D11_BUFFER_DESC bd;
		//bdのサイズ分メモリに0をセットする
		ZeroMemory(&bd, sizeof(bd));
		//バッファーで想定されている
		//読み込み及び書き込みの方法
		bd.Usage = D3D11_USAGE_DEFAULT;
		//バッファーのサイズ(バイト単位)
		bd.ByteWidth = stride * numVertex;
		//バッファーをどのようにパイプラインに
		//関連付けるかを識別する
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		//CPUアクセスのフラグ
		//CPUアクセスが必要でない場合は0
		bd.CPUAccessFlags = 0;
		//バッファーや2Dと3Dのテクスチャを作成する
		//呼び出しで使用される
		D3D11_SUBRESOURCE_DATA InitData;
		//InitDataのサイズ分メモリを0にセットする
		ZeroMemory(&InitData, sizeof(InitData));
		//初期化データへのポインタ
		InitData.pSysMem = pSrcVertexBuffer;
		//失敗の原因まで出してくれる便利な奴
		HRESULT hr = g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &m_vertexBuffer);
		//失敗した場合
		if (FAILED(hr))
		{
			//falseを返す
			return false;
		}
		m_stride = stride;
		//成功した場合trueを返す
		return true;
	}
}