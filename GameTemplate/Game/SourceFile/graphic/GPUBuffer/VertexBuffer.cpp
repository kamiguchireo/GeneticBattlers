#include "stdafx.h"
#include "VertexBuffer.h"

namespace Engine {
	VertexBuffer::VertexBuffer()
	{
	}
	VertexBuffer::~VertexBuffer()
	{
		Release();
	}

	//�J������
	void VertexBuffer::Release()
	{
		if (m_vertexBuffer != nullptr)
		{
			m_vertexBuffer->Release();
			m_vertexBuffer = nullptr;
		}
	}
	bool VertexBuffer::Create(int numVertex, int stride, const void* pSrcVertexBuffer)
	{
		//���g�����邩������Ȃ��̂ŊJ���������s��
		Release();
		//�o�b�t�@���\�[�X���쐬���邽�߂Ɏg�p����
		D3D11_BUFFER_DESC bd;
		//bd�̃T�C�Y����������0���Z�b�g����
		ZeroMemory(&bd, sizeof(bd));
		//�o�b�t�@�[�őz�肳��Ă���
		//�ǂݍ��݋y�я������݂̕��@
		bd.Usage = D3D11_USAGE_DEFAULT;
		//�o�b�t�@�[�̃T�C�Y(�o�C�g�P��)
		bd.ByteWidth = stride * numVertex;
		//�o�b�t�@�[���ǂ̂悤�Ƀp�C�v���C����
		//�֘A�t���邩�����ʂ���
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		//CPU�A�N�Z�X�̃t���O
		//CPU�A�N�Z�X���K�v�łȂ��ꍇ��0
		bd.CPUAccessFlags = 0;
		//�o�b�t�@�[��2D��3D�̃e�N�X�`�����쐬����
		//�Ăяo���Ŏg�p�����
		D3D11_SUBRESOURCE_DATA InitData;
		//InitData�̃T�C�Y����������0�ɃZ�b�g����
		ZeroMemory(&InitData, sizeof(InitData));
		//�������f�[�^�ւ̃|�C���^
		InitData.pSysMem = pSrcVertexBuffer;
		//���s�̌����܂ŏo���Ă����֗��ȓz
		HRESULT hr = g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &m_vertexBuffer);
		//���s�����ꍇ
		if (FAILED(hr))
		{
			//false��Ԃ�
			return false;
		}
		m_stride = stride;
		//���������ꍇtrue��Ԃ�
		return true;
	}
}