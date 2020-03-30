#include "stdafx.h"
#include "GaussianBlur.h"
#include "PostEffect.h"

GaussianBlur::GaussianBlur()
{

}

GaussianBlur::~GaussianBlur()
{

}

void GaussianBlur::Init(ID3D11ShaderResourceView*stcTextureSRV, float blurIntensity)
{
	//�\�[�X�e�N�X�`����SRV���R�s�[
	m_srcTextureSRV = stcTextureSRV;
	//UpdateWeight�֐��Ŏg�p����̂ŁA�u���[�̋����������o�ϐ��ɓ����
	m_blurIntensity = blurIntensity;

	//�\�[�X�e�N�X�`���̏����擾
	ID3D11Texture2D*tex;
	//SRV�Ɋ֘A�t������Ă���e�N�X�`�����擾����
	m_srcTextureSRV->GetResource((ID3D11Resource**)&tex);
	//�擾�����e�N�X�`������A�e�N�X�`�������擾����
	D3D11_TEXTURE2D_DESC texDesc;
	tex->GetDesc(&texDesc);
	//�e�N�X�`�������擾�ł����̂ŁA�e�N�X�`���̎Q�ƃJ�E���^������
	tex->Release();
	//�\�[�X�e�N�X�`���̕��ƍ������L�����Ă���
	m_srcTextureWidth = texDesc.Width;
	m_srcTextureHeight = texDesc.Height;
	//X�u���[�p�̃����_�����O�^�[�Q�b�g���쐬
	m_renderTarget[enRenderTarget_XBlur].Create
	(
		texDesc.Width / 2,		//���̉𑜓x�𔼕��ɂ���
		texDesc.Height,
		texDesc.Format
	);
	//Y�u���[�p�̃����_�����O�^�[�Q�b�g���쐬
	m_renderTarget[enRenderTarget_YBlur].Create
	(
		texDesc.Width / 2,		//���̉𑜓x�𔼕��ɂ���
		texDesc.Height / 2,		//�c�̉𑜓x�𔼕��ɂ���
		texDesc.Format
	);

	//�V�F�[�_�[�����[�h
	m_vsXBlur.Load("Assets/shader/GaussianBlur.fx", "VSXBlur", Shader::EnType::VS);
	m_vsYBlur.Load("Assets/shader/GaussianBlur.fx", "VSYBlur", Shader::EnType::VS);
	m_psBlur.Load("Assets/shader/GaussianBlur.fx", "PSBlur", Shader::EnType::PS);

	//VRAM��ɒ萔�o�b�t�@���쐬
	m_blurCbGpu.Create(nullptr, sizeof(SBlurParam));

	//�������ς݂̃t���O
	m_isInited = true;
}

void GaussianBlur::UpdateWeight()
{
	//�K�E�X�t�B���^�̏d�݂��X�V����
	float total = 0;
	for (int i = 0; i < NUM_WEIGHTS; i++)
	{
		//expf�֐��̓l�C�s�A��e�Ɉ����悷��
		m_blurParam.weights[i] = expf(-0.5f*(float)(i*i) / m_blurIntensity);
		total += 2.0f*m_blurParam.weights[i];
	}
	//�K�i���B�d�݂̃g�[�^����1.0�ɂȂ�悤�ɁA�S�̂̏d�݂ŏ��Z����
	for (int i = 0; i < NUM_WEIGHTS; i++)
	{
		m_blurParam.weights[i] /= total;
	}
}

void GaussianBlur::Execute(PostEffect&postEffect)
{
	if (m_isInited == false)
	{
		//�������ł��Ă��܂���
		throw;
	}
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//�K�E�V�A���t�B���^�[�̏d�݂��X�V����
	UpdateWeight();

	//�d�݂��X�V�����̂ŁAVRAM��̒萔�o�b�t�@���X�V����
	//���C���������̓��e��VRAM�ɃR�s�[
	auto d3d11CbGpu = m_blurCbGpu.GetD3D11Buffer();
	deviceContext->UpdateSubresource
	(
		d3d11CbGpu,
		0,
		nullptr,
		&m_blurParam,
		0,
		0
	);

	//���W�X�^b0��m_blurCbGpu�̃A�h���X��ݒ肷��
	deviceContext->PSSetConstantBuffers
	(
		0,
		1,
		&d3d11CbGpu
	);

	//X�u���[
	{
		//X�u���[�p�̃����_�����O�^�[�Q�b�g�ɕύX����
		g_graphicsEngine->ChangeRenderTarget
		(
			deviceContext,
			&m_renderTarget[enRenderTarget_XBlur],
			m_renderTarget[enRenderTarget_XBlur].GetViewport()
		);

		//�\�[�X�e�N�X�`���̃A�h���X��t0���W�X�^�ɐݒ肷��
		deviceContext->VSSetShaderResources
		(
			0,
			1,
			&m_srcTextureSRV
		);
		deviceContext->PSSetShaderResources
		(
			0,
			1,
			&m_srcTextureSRV
		);

		//�t���X�N���[���`����s���ău���[�����s
		postEffect.DrawFS
		(
			deviceContext,
			m_vsXBlur,
			m_psBlur
		);
	}

	//Y�u���[
	{
		//Y�u���[�p�̃����_�����O�^�[�Q�b�g�ɕύX����
		g_graphicsEngine->ChangeRenderTarget
		(
			deviceContext,
			&m_renderTarget[enRenderTarget_YBlur],
			m_renderTarget[enRenderTarget_YBlur].GetViewport()
		);

		//Y�u���[��������\�[�X�e�N�X�`���̃A�h���X��t0�ɐݒ肷��
		//Y�u���[��������̂�X�u���[���������e�N�X�`���ɂȂ�
		auto srcTextureSrv = m_renderTarget[enRenderTarget_XBlur].GetRenderTargetSRV();
		deviceContext->VSSetShaderResources
		(
			0,
			1,
			&srcTextureSrv
		);
		deviceContext->PSSetShaderResources
		(
			0,
			1,
			&srcTextureSrv
		);

		//�t���X�N���[���`����s���ău���[�����s
		postEffect.DrawFS
		(
			deviceContext,
			m_vsYBlur,
			m_psBlur
		);
	}
}