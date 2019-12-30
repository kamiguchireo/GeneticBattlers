#include "stdafx.h"
#include "ConstantBuffer.h"


namespace Engine {
	//�R���X�g���N�^
	ConstantBuffer::ConstantBuffer()
	{
	}
	//�f�X�g���N�^
	ConstantBuffer::~ConstantBuffer()
	{
	}
	
	//ConstantBuffer���쐬
	//pInitData		�����f�[�^
	//bufferSize		�o�b�t�@�T�C�Y
	bool ConstantBuffer::Create(const void*pInitData, int bufferSize)
	{
		//ConstantBuffer�p�̃o�b�t�@��`���쐬����B
		//�o�b�t�@���\�[�X���쐬���邽�߂Ɏg����
		D3D11_BUFFER_DESC bufferDesc;
		//bufferDesc�̃�������0��������
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));
		//�o�b�t�@�[�őz�肳��Ă���ǂݍ��݋y�я������݂̕��@
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		//�o�b�t�@�[�̃T�C�Y
		//16�{�ƃA���C�����g�ɐ؂�グ��
		bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;
		//�o�b�t�@�[���ǂ̂悤�Ƀp�C�v���C���Ƀo�C���h(�֘A�t����)
		//�������ʂ���
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		//CPU�A�N�Z�X�̃t���O
		//CPU�A�N�Z�X���K�v�łȂ��ꍇ��0�ɂȂ�
		bufferDesc.CPUAccessFlags = 0;
		//
		return CGPUBuffer::Create(pInitData, bufferDesc);
	}
}