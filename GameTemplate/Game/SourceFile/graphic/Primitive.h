#pragma once
#include "SourceFile/graphic/GPUBuffer/IndexBuffer.h"
#include "SourceFile/graphic/GPUBuffer/VertexBuffer.h"
#include "SourceFile/graphic/RenderContext.h"

namespace Engine {
	//�v���~�e�B�u
	class Primitive
	{
	public:
		//�R���X�g���N�^
		Primitive();
		//�f�X�g���N�^
		~Primitive();

		//�J������
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

		//�`��
		void Draw(RenderContext& rc);

		//�`��
		void Draw(RenderContext& rc, int numVertex);

	private:
		IndexBuffer m_indexBuffer;		//�C���f�b�N�X�o�b�t�@
		VertexBuffer m_vertexBuffer;		//���_�o�b�t�@
		D3D_PRIMITIVE_TOPOLOGY m_topology;		//�g�|���W�[
	};


}