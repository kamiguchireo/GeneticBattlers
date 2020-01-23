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
		//���_�o�b�t�@�ւ̃|�C���^
		void* pSrcVertexBuffer,
		//�C���f�b�N�X�̐�
		int numIndex,
		//�C���f�b�N�X�̌^
		IndexBuffer::EnIndexType indexType,
		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
		void* pSrcIndexBuffer)
	{
		//���g�����邩������Ȃ�����J���������s��
		Release();
		m_topology = topology;
		//���_�o�b�t�@��Create
		bool result = m_vertexBuffer.Create(numVertex, vertexStride, pSrcVertexBuffer);
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

	////�`��
	//void Primitive::Draw(RenderContext& rc)
	//{
	//	//���_�o�b�t�@��ݒ�B
	//	rc.IASetVertexBuffer(m_vertexBuffer);
	//	//�C���f�b�N�X�o�b�t�@��ݒ�
	//	rc.IASetIndexBuffer(m_indexBuffer);
	//	//�v���~�e�B�u�̃g�|���W�[��ݒ�B
	//	rc.IASetPrimitiveTopology(m_topology);
	//	//�`��B
	//	rc.DrawIndexed(m_indexBuffer.GetNumIndex(), 0, 0);
	//}



	////�`��
	//void Primitive::Draw(RenderContext& rc, int numVertex)
	//{
	//	rc.IASetVertexBuffer(m_vertexBuffer);
	//	//�v���~�e�B�u�̃g�|���W�[��ݒ�B
	//	rc.IASetPrimitiveTopology(m_topology);
	//	//�`��B
	//	rc.Draw(numVertex, 0);
	//}

	void Primitive::Draw(ID3D11DeviceContext&rc)
	{
		//���_�o�b�t�@��ݒ�
		UINT ofset = 0;
		UINT stride = m_vertexBuffer.GetStride();
		rc.IASetVertexBuffers(0, 1, &(m_vertexBuffer.GetBody()), &stride, &ofset);
		auto type = m_indexBuffer.GetIndexType();
		rc.IASetIndexBuffer(
			m_indexBuffer.GetBody(),
			type == IndexBuffer::enIndexType_16 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT,
			0
		);
		//�v���~�e�B�u�̃g�|���W�[��ݒ�
		rc.IASetPrimitiveTopology(m_topology);
		//�`��
		rc.DrawIndexed(m_indexBuffer.GetNumIndex(), 0, 0);
	}

	void Primitive::Draw(ID3D11DeviceContext& rc, int numVertex)
	{
		//���_�o�b�t�@�̐ݒ�
		UINT ofset = 0;
		UINT stride = m_vertexBuffer.GetStride();
		rc.IASetVertexBuffers(0, 1, &(m_vertexBuffer.GetBody()), &stride, &ofset);
		//�v���~�e�B�u�̃g�|���W�[��ݒ�
		rc.IASetPrimitiveTopology(m_topology);
		//�`��
		rc.Draw(numVertex, 0);
	}
}