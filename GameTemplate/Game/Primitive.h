#pragma once
#include "IndexBuffer.h"
#include "VertexBuffer.h"
namespace Engine {
	
	//プリミティブ
	class Primitive
	{
	public:
		//コンストラクタ
		Primitive();
		//デストラクタ
		~Primitive();

		void Release();

		bool Create(
			D3D_PRIMITIVE_TOPOLOGY topology,
			int numVertex,
			int vertexStride,
			void*pSrcVertexBuffer,
			int numIndex,
			IndexBuffer::EnIndexType indexType,
			void*pSrcIndexBuffer
		);

	private:
		IndexBuffer m_indexBuffer;		//インデックスバッファ
		VertexBuffer m_vertexBuffer;		//頂点バッファ
		D3D_PRIMITIVE_TOPOLOGY m_topology;		//トポロジー
	};


}