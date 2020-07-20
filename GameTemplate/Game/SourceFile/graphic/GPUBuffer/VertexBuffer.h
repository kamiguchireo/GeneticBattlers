#pragma once
#include "SourceFile/Noncopyable.h"

namespace Engine {
	//���_�o�b�t�@
	class VertexBuffer:Engine::Noncopyable
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		//�J������
		void Release();

		//���_�X�g���C�h���擾
		int GetStride() const
		{
			return m_stride;
		}

		//ID3D11Buffer*���擾
		ID3D11Buffer*& GetBody()
		{
			return m_vertexBuffer;
		}
		/*
		���_�o�b�t�@�̍쐬
		numVertex		���_��
		stride		���_�X�g���C�h
		pSrcVertexBuffer		�\�[�X���_�o�b�t�@
		
		�X�g���C�h�ɓ��ꂽ�������̊Ԋu��������
		�F���z�u�����??
		*/
		bool Create(int numVertex, int stride, const void*pSrcVertexBuffer);

	private:
		ID3D11Buffer* m_vertexBuffer = nullptr;		//���_�o�b�t�@
		int m_stride = 0;		//���_�X�g���C�h
	};

}