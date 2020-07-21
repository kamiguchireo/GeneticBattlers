#pragma once
#include "SourceFile/Noncopyable.h"

namespace Engine {
	class ConstantBufferGPU:Engine::Noncopyable
	{
	public:
		ConstantBufferGPU();
		~ConstantBufferGPU();

		//VRAM��ɒ萔�o�b�t�@���쐬����
		//pInitData		�������f�[�^	nullptr���w�肵���ꍇ�́A���������̒萔�o�b�t�@���쐬����܂��B
		//bufferSize		�쐬����o�b�t�@�̃T�C�Y
		//���̊֐�����16�o�C�g�A���C�����g�ɐ؂�グ�����
		void Create(const void* pInitData,int bufferSize);

		//�萔�o�b�t�@���擾
		ID3D11Buffer* GetD3D11Buffer()const
		{
			return m_constantBuffer;
		}

	private:
		ID3D11Buffer* m_constantBuffer = nullptr;		//GPUBuffer��̒萔�o�b�t�@
	};
}
