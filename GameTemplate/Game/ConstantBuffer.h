#pragma once
#include "CGPUBuffer.h"

namespace Engine {
	//�萔�o�b�t�@
	//CGPUBuffer���p��
	class ConstantBuffer:public CGPUBuffer
	{
	public:
		//�R���X�g���N�^
		ConstantBuffer();
		//�f�X�g���N�^
		~ConstantBuffer();
		//ConstantBuffer���쐬
		//pInitData		�����f�[�^
		//bufferSize		�o�b�t�@�T�C�Y
		bool Create(const void*pInitData, int bufferSize);
	};

}