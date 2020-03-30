#include "stdafx.h"
#include "PostEffect.h"

PostEffect::PostEffect()
{
	//�t���X�N���[���`��̂��߂̎l�p�`�v���~�e�B�u��������
	InitFSQuadPrimitive();
}

PostEffect::~PostEffect()
{

}

void PostEffect::Update()
{

}

void PostEffect::Draw()
{
	m_bloom.Draw(*this);
}

void PostEffect::InitFSQuadPrimitive()
{
	//���_�o�b�t�@��������
	SVertex vertex[4] = {
		//���_�P
		{
			//���W  position[4]
			-1.0f,-1.0f,0.0f,1.0f,
			//UV���W  uv[2]
			0.0f,1.0f
		},
		//���_�Q
		{
			//���W  position[4]
			1.0f,-1.0f,0.0f,1.0f,
			//UV���W  uv[2]
			1.0f,1.0f
		},
		//���_�R
		{
			//���W�@position[4]
			-1.0f,  1.0f, 0.0f, 1.0f,
			//UV���W uv[2]
			0.0f, 0.0f
		},
		//���_�S
		{
			//���W�@position[4]
			1.0f,  1.0f, 0.0f, 1.0f,
			//UV���W uv[2]
			1.0f, 0.0f
		},

	};

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;		//�o�b�t�@�őz�肳��Ă���ǂݏ������݂̕��@
	bd.ByteWidth = sizeof(vertex);		//�o�b�t�@�̃T�C�X
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;		//���ꂩ��쐬����o�b�t�@�̎��(���_�o�b�t�@)
	
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	//�������f�[�^�ւ̃|�C���^
	InitData.pSysMem = vertex;

	//���_�o�b�t�@�̍쐬
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &m_vertexBuffer);

}

void PostEffect::DrawFS(ID3D11DeviceContext*deviceContext, Shader&vsShader, Shader&psShader)
{
	//�v���~�e�B�u�̃g�|���W�[�Ƃ��āA�g���C�A���O���X�g���b�v��ݒ�
	deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	unsigned int vertexSize = sizeof(SVertex);
	unsigned int offset = 0;

	//�P�x���o�p�̃V�F�[�_�[��ݒ肷��
	//���_�V�F�[�_�[
	deviceContext->VSSetShader
	(
		(ID3D11VertexShader*)vsShader.GetBody(), nullptr, 0
	);
	//�s�N�Z���V�F�[�_�[
	deviceContext->PSSetShader
	(
		(ID3D11PixelShader*)psShader.GetBody(), nullptr, 0
	);

	deviceContext->IASetInputLayout(vsShader.GetInputLayout());
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &vertexSize, &offset);
	deviceContext->Draw(4, 0);
}