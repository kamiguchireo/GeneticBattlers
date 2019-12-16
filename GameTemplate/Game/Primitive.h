#pragma once
#include "IndexBuffer.h"

namespace Engine {
	
	//�v���~�e�B�u
	class Primitive
	{
	public:
		//�R���X�g���N�^
		Primitive();
		//�f�X�g���N�^
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