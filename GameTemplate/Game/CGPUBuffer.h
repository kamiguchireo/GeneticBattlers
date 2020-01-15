#pragma once

namespace Engine {
	//GPU�o�b�t�@�[
	class CGPUBuffer
	{
	public:
		CGPUBuffer();
		virtual ~CGPUBuffer();

		//GPUBuffer���쐬
		//pInitData		�����f�[�^
		//bufferDesc		�o�b�t�@��`
		bool Create(const void*pInitData, D3D11_BUFFER_DESC& bufferDesc);

		//ID3D11Buffer�̃|�C���^���擾
		ID3D11Buffer*& GetBody()
		{
			return m_gpuBuffer;
		}

		//�J������
		//�f�X�g���N�^������R�[������Ă���
		//�����I�ȃ^�C�~���O�ŊJ���������ꍇ�ɌĂяo���āI
		void Release();

	private:
		//GPUBuffer
		ID3D11Buffer* m_gpuBuffer = nullptr;	
	};

}