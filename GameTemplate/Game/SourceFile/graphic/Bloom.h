#pragma once
#include "SourceFile/graphic/RenderTarget.h"
#include "GaussianBlur.h"
#include "SourceFile/Noncopyable.h"

class PostEffect;

class Bloom :Engine::Noncopyable
{
public:
	Bloom();
	~Bloom();

	//�`��
	void Draw(PostEffect& postEffect);

private:
	static const int NUM_DOWN_SAMPLE = 4;		//�_�E���T���v�����O�̉񐔁B
	void CreateRT();		//�P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬����
	void InitAlphaBlendState();		//�u�����h�X�e�[�g�̃���ݒ肷��
	void InitSamplerState();		//�T���v���[�X�e�[�g�̏�����
	void InitShader();		//�V�F�[�_�[�̃Z�b�g
	Engine::RenderTarget m_luminaceRT;		//�P�x���o�p�̃����_�[�^�[�Q�b�g
	ID3D11BlendState* m_disableBlendState = nullptr;	//�A���t�@�u�����f�B���O�𖳌��ɂ���u�����f�B���O�X�e�[�g�B
	ID3D11BlendState* m_finalBlendState = nullptr;		//�ŏI�����p�̃u�����f�B���O�X�e�[�g�B
	ID3D11SamplerState* m_samplerState = nullptr;		//�T���v���X�e�[�g�B
	Shader m_vs;		//�������Ȃ����_�V�F�[�_�[
	Shader m_psLuminace;		//�P�x���o�p�̃s�N�Z���V�F�[�_�[
	Shader m_psFinal;		//�ŏI�����p�̃s�N�Z���V�F�[�_�[
	GaussianBlur m_gaussianBlur[NUM_DOWN_SAMPLE];	//�P�x���ڂ������߂̃K�E�V�A���u���[�B

};