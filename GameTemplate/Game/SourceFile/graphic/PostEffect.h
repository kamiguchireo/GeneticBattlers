#pragma once
#include "SourceFile/graphic/Bloom.h"

class PostEffect
{
public:
	PostEffect();
	~PostEffect();

	//�X�V
	void Update();
	//�`��
	void Draw();
	//�t���X�N���[���`��
	void DrawFS(ID3D11DeviceContext*deviceContext, Shader&vsShader, Shader&psShader);

private:
	struct SVertex {
		float position[4];		//���_���W
		float uv[2];		//UV���W�B���ꂪ�e�N�X�`�����W
	};

	//�t���X�N���[���`��p�̎l�p�`�v���~�e�B�u�̏�����
	void InitFSQuadPrimitive();

	Bloom m_bloom;		//�u���[��
	/*
	//�t���X�N���[���`��p�̃����o�ϐ�
	*/
	ID3D11Buffer* m_vertexBuffer = nullptr;		//���_�o�b�t�@
	ID3D11InputLayout* m_inputLayout = nullptr;		//���̓��C�A�E�g
};

