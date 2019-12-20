#pragma once
#include "ShaderResourceView.h"

namespace Engine {
	//テクスチャやストラクチャバッファなど、シェーダーで使用するリソースで使用するビュー
	class CStructuredBuffer
	{
	public:
		CStructuredBuffer();
		~CStructuredBuffer();
		
		//pInitData		初期データ
		//bufferDesc	バッファ定義
		bool Create(const void*pInitData, D3D11_BUFFER_DESC&bufferDesc);

		//ID3D11Buffer*を取得
		ID3D11Buffer*& GetBody()
		{
			return m_structuredBuffer;
		}
		//開放して欲しくばReleaseを呼ぶんだな
		void Release();

		//SRVを取得
		ShaderResourceView& GetSRV()
		{
			return m_srv;
		}
	private:
		ID3D11Buffer*m_structuredBuffer = nullptr;		//voidみたいな便利な奴
		ShaderResourceView m_srv;						//SRV
	};

}