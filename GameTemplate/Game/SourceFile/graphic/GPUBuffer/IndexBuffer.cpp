#include "stdafx.h"
#include "IndexBuffer.h"

namespace Engine {
	IndexBuffer::IndexBuffer()
	{
	}
	IndexBuffer::~IndexBuffer()
	{
		Release();
	}
	//開放処理
	void IndexBuffer::Release()
	{
		//インデックスバッファに何か入っていたら
		if (m_indexBuffer)
		{
			//開放処理
			m_indexBuffer->Release();
			m_indexBuffer = nullptr;
		}
		m_isCreated = false;
	}
	bool IndexBuffer::Create(int numIndex, EnIndexType indexType, const void*pSrcIndexBuffer)
	{
		//中身があるかもしれないから開放を行う
		Release();

		int stride = 0;
		if (indexType == enIndexType_16)
		{
			//16ビット
			stride = 2;
		}
		else
		{
			//32ビット
			stride = 4;
		}
		m_indexType = indexType;
		m_numIndex = numIndex;
		//バッファーリソースを作成するために使われる
		D3D11_BUFFER_DESC bd;
		//バッファーデスクのメモリを0にセットする
		ZeroMemory(&bd, sizeof(bd));
		//バッファーの読み込み書き込みの方法
		//D3D11_USAGE_DEFAULTが一般的
		bd.Usage = D3D11_USAGE_DEFAULT;
		//構造体のサイズ(バイト単位)
		bd.StructureByteStride = stride;
		//バッファーのサイズ(バイト単位)
		//構造体のサイズにインデックスの数を掛ける
		bd.ByteWidth = stride * numIndex;
		//バッファーをパイプラインにバインドする方法
		//バッファーをインデックスバッファーとして
		//入力アセンブラーステージにバインドする
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		//CPUアクセスのフラグ
		//CPUアクセスが必要でない場合は0
		bd.CPUAccessFlags = 0;
		//バッファーやテクスチャを作成するときに使われる
		D3D11_SUBRESOURCE_DATA InitData;
		//サブリソースデータのメモリを0にセットする
		ZeroMemory(&InitData, sizeof(InitData));
		//初期かデータへのポインタを代入する
		InitData.pSysMem = pSrcIndexBuffer;

		//HRESULT型は処理の失敗の原因まで特定してくれる便利な奴
		HRESULT hr = g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &m_indexBuffer);
		//失敗したとき
		if (FAILED(hr))
		{
			//falseを返す
			return false;
		}
		//インデックスバッファが作られたフラグを立てる
		m_isCreated = true;
		//trueを返す
		return true;
	}
}