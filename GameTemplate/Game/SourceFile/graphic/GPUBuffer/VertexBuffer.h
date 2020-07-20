#pragma once
#include "SourceFile/Noncopyable.h"

namespace Engine {
	//頂点バッファ
	class VertexBuffer:Engine::Noncopyable
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		//開放処理
		void Release();

		//頂点ストライドを取得
		int GetStride() const
		{
			return m_stride;
		}

		//ID3D11Buffer*を取得
		ID3D11Buffer*& GetBody()
		{
			return m_vertexBuffer;
		}
		/*
		頂点バッファの作成
		numVertex		頂点数
		stride		頂点ストライド
		pSrcVertexBuffer		ソース頂点バッファ
		
		ストライドに入れた数字分の間隔をあけて
		色が配置される??
		*/
		bool Create(int numVertex, int stride, const void*pSrcVertexBuffer);

	private:
		ID3D11Buffer* m_vertexBuffer = nullptr;		//頂点バッファ
		int m_stride = 0;		//頂点ストライド
	};

}