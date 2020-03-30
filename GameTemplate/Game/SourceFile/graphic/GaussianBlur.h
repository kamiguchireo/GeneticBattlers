#pragma once
#include "RenderTarget.h"
#include "SourceFile/graphic/GPUBuffer/ConstantBufferGPU.h"

class PostEffect;
class GaussianBlur
{
public:
	GaussianBlur();
	~GaussianBlur();

	//srcTextureSRV		�u���[��������e�N�X�`����SRV
	//blurIntensity		�u���[�̋����B�l���傫���قǋ����u���[��������
	void Init(ID3D11ShaderResourceView*stcTextureSRV, float blurIntensity);

	//�u���[�̎��s
	//postEffect		�|�X�g�G�t�F�N�g�̃C���X�^���X		�S��ʕ`��̋@�\���g������
	//Init�֐����Ăяo������Ŏ��s���Ă�������
	void Execute(PostEffect&postEffect);

	//�u���[�����������ʂ̃e�N�X�`��SRV���擾
	ID3D11ShaderResourceView*GetResultTextureSRV()
	{
		return m_renderTarget[enRenderTarget_YBlur].GetRenderTargetSRV();
	}
private:	
	//�u���[�̏d�݂̍X�V
	void UpdateWeight();

	static const int NUM_WEIGHTS = 8;	//�J�E�X�t�B���^�̏d�݂̐��B
	//�u���[�p�̃p�����[�^�o�b�t�@
	//�����ύX������AGaussianBlur.fx��CBBlur�̒��g���ύX����
	struct SBlurParam {
		float weights[NUM_WEIGHTS];
	};

	//�����_�����O�^�[�Q�b�g
	enum EnRenderTarget{
		enRenderTarget_XBlur,		//X�u���[�̏������ݐ�ƂȂ郌���_�����O�^�[�Q�b�g
		enRenderTarget_YBlur,		//Y�u���[�̏������ݐ�ƂȂ郌���_�����O�^�[�Q�b�g
		enRenderTarget_Num,		//�����_�����O�^�[�Q�b�g�̖���
	};
	ID3D11ShaderResourceView* m_srcTextureSRV = nullptr;	//�\�[�X�e�N�X�`����SRV
	float m_blurIntensity = 25.0f;		//�u���[�̋����B�u���[�̃E�F�C�g�̌v�Z�Ŏg�p����܂��B
	unsigned int m_srcTextureWidth = 0;			//�\�[�X�e�N�X�`���̕��B
	unsigned int m_srcTextureHeight = 0;		//�\�[�X�e�N�X�`���̍����B
	Engine::RenderTarget m_renderTarget[enRenderTarget_Num];		//�����_�����O�^�[�Q�b�g�B
	Shader m_vsXBlur;						//X�u���[�p�̒��_�V�F�[�_�[�B
	Shader m_vsYBlur;						//Y�u���[�p�̒��_�V�F�[�_�[�B
	Shader m_psBlur;						//�u���[�p�̃s�N�Z���V�F�[�_�[�B
	ConstantBufferGPU m_blurCbGpu;				//�u���[�p�̒萔�o�b�t�@(GPU��)
	bool m_isInited = false;		//�������ς݃t���O�B
	SBlurParam m_blurParam;						//�u���[�p�̃p�����[�^�B

};

