#pragma once
#include "IndexBuffer.h"

namespace Engine {
	
	//プリミティブ
	class Primitive
	{
	public:
		//コンストラクタ
		Primitive();
		//デストラクタ
		~Primitive();

		bool Create(
			D3D_PRIMITIVE_TOPOLOGY topology,
			int numVertex,
			int vertexStride,
			void*pSrcVertexBuffer,
			int numIndex,
			IndexBuffer::EnIndexType indexType,
			void*pSrcIndexBuffer
		);
	};

}