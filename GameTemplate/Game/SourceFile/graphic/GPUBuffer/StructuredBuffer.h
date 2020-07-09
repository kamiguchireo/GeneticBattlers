#pragma once
#include "ShaderResourceView.h"

namespace Engine {
	//�e�N�X�`����X�g���N�`���o�b�t�@�ȂǁA�V�F�[�_�[�Ŏg�p���郊�\�[�X�Ŏg�p����r���[
	class CStructuredBuffer
	{
	public:
		CStructuredBuffer();
		~CStructuredBuffer();
		
		//pInitData		�����f�[�^
		//bufferDesc	�o�b�t�@��`
		bool Create(const void*pInitData, D3D11_BUFFER_DESC&bufferDesc);

		//ID3D11Buffer*���擾
		ID3D11Buffer*& GetBody()
		{
			return m_structuredBuffer;
		}

		//�������
		void Release();

	private:
		ID3D11Buffer*m_structuredBuffer = nullptr;		//void�݂����ȕ֗��ȓz
		ShaderResourceView m_srv;						//SRV
	};

}