#include "stdafx.h"
#include "Primitive.h"

namespace Engine {
	Primitive::Primitive()
	{
	}
	Primitive::~Primitive()
	{
	}

	void Primitive::Release()
	{
		//���_�o�b�t�@�̊J������
		m_vertexBuffer.Release();
		//�C���f�b�N�X�o�b�t�@�̊J������
		m_indexBuffer.Release();
	}
	bool Primitive::Create(
		D3D_PRIMITIVE_TOPOLOGY  topology,
		int numVertex,
		int vertexStride,
		void* pSrcVertexBuffer,
		int numIndex,
		IndexBuffer::EnIndexType indexType,
		void* pSrcIndexBuffer)
	{
		//���g�����邩������Ȃ�����J���������s��
		Release();
		m_topology = topology;
		//���_�o�b�t�@��Create
		bool result = m_vertexBuffer.Create(numVertex, vertexStride, pSrcIndexBuffer);
		if (!result)
		{
			//���s������false��Ԃ�
			return false;
		}
		if (pSrcIndexBuffer)
		{
			//�C���f�b�N�X�o�b�t�@��Create
			result = m_indexBuffer.Create(numIndex, indexType, pSrcIndexBuffer);
			if (!result)
			{
				//���s������false��Ԃ�
				return false;
			}
		}
		//����������true��Ԃ�
		return true;
	}

}