#include "stdafx.h"
#include "IndexBuffer.h"

namespace Engine {
	IndexBuffer::IndexBuffer()
	{
	}
	IndexBuffer::~IndexBuffer()
	{
		Release();
	}
	//�J������
	void IndexBuffer::Release()
	{
		//�C���f�b�N�X�o�b�t�@�ɉ��������Ă�����
		if (m_indexBuffer)
		{
			//�J������
			m_indexBuffer->Release();
			m_indexBuffer = nullptr;
		}
		m_isCreated = false;
	}
	bool IndexBuffer::Create(int numIndex, EnIndexType indexType, const void*pSrcIndexBuffer)
	{
		//���g�����邩������Ȃ�����J�����s��
		Release();

		int stride = 0;
		if (indexType == enIndexType_16)
		{
			//16�r�b�g
			stride = 2;
		}
		else
		{
			//32�r�b�g
			stride = 4;
		}
		m_indexType = indexType;
		m_numIndex = numIndex;
		//�o�b�t�@�[���\�[�X���쐬���邽�߂Ɏg����
		D3D11_BUFFER_DESC bd;
		//�o�b�t�@�[�f�X�N�̃�������0�ɃZ�b�g����
		ZeroMemory(&bd, sizeof(bd));
		//�o�b�t�@�[�̓ǂݍ��ݏ������݂̕��@
		//D3D11_USAGE_DEFAULT����ʓI
		bd.Usage = D3D11_USAGE_DEFAULT;
		//�\���̂̃T�C�Y(�o�C�g�P��)
		bd.StructureByteStride = stride;
		//�o�b�t�@�[�̃T�C�Y(�o�C�g�P��)
		//�\���̂̃T�C�Y�ɃC���f�b�N�X�̐����|����
		bd.ByteWidth = stride * numIndex;
		//�o�b�t�@�[���p�C�v���C���Ƀo�C���h������@
		//�o�b�t�@�[���C���f�b�N�X�o�b�t�@�[�Ƃ���
		//���̓A�Z���u���[�X�e�[�W�Ƀo�C���h����
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		//CPU�A�N�Z�X�̃t���O
		//CPU�A�N�Z�X���K�v�łȂ��ꍇ��0
		bd.CPUAccessFlags = 0;
		//�o�b�t�@�[��e�N�X�`�����쐬����Ƃ��Ɏg����
		D3D11_SUBRESOURCE_DATA InitData;
		//�T�u���\�[�X�f�[�^�̃�������0�ɃZ�b�g����
		ZeroMemory(&InitData, sizeof(InitData));
		//�������f�[�^�ւ̃|�C���^��������
		InitData.pSysMem = pSrcIndexBuffer;

		//HRESULT�^�͏����̎��s�̌����܂œ��肵�Ă����֗��ȓz
		HRESULT hr = g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &m_indexBuffer);
		//���s�����Ƃ�
		if (FAILED(hr))
		{
			//false��Ԃ�
			return false;
		}
		//�C���f�b�N�X�o�b�t�@�����ꂽ�t���O�𗧂Ă�
		m_isCreated = true;
		//true��Ԃ�
		return true;
	}
}