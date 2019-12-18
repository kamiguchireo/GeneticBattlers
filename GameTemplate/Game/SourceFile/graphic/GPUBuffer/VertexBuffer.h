#pragma once

namespace Engine {
	//���_�o�b�t�@
	class VertexBuffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		//�J������
		void Release();

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