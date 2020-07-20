#pragma once
#include "SourceFile/Noncopyable.h"

namespace Engine {
	//�C���f�b�N�X�o�b�t�@
	class IndexBuffer:Engine::Noncopyable
	{
	public:

		//�C���f�b�N�X�̌^
		enum EnIndexType {
			enIndexType_16,		//16�r�b�g�C���f�b�N�X�B
			enIndexType_32,		//32�r�b�g�C���f�b�N�X
		};
		//�R���X�g���N�^
		IndexBuffer();
		//�f�X�g���N�^
		~IndexBuffer();
		
		/*�C���f�b�N�X�o�b�t�@���쐬
		numIndex		�C���f�b�N�X�̐�
		indexType		�C���f�b�N�X�̌^
		pSrcIndexBuffer		�\�[�X�C���f�b�N�X�o�b�t�@
		*/
		bool Create(int numIndex, EnIndexType indexType, const void*pSrcIndexBuffer);

		//�J��
		void Release();

		//�C���f�b�N�X�̌^���擾
		EnIndexType GetIndexType() const
		{
			return m_indexType;
		}
		//ID3D11Buffer���擾
		ID3D11Buffer*GetBody()const
		{
			return m_indexBuffer;
		}
		//�C���f�b�N�X�̐����擾
		unsigned int GetNumIndex()const
		{
			return m_numIndex;
		}
	private:
		bool m_isCreated = false;		//�C���f�b�N�X�o�b�t�@���쐬����Ă��邩�ǂ���
		ID3D11Buffer* m_indexBuffer = nullptr;		//�C���f�b�N�X�o�b�t�@
		EnIndexType m_indexType = enIndexType_16;		//�C���f�b�N�X�̌^
		unsigned int m_numIndex = 0;		//�C���f�b�N�X�̐�
	};

}