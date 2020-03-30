#include "stdafx.h"
#include "Bloom.h"
#include "PostEffect.h"

Bloom::Bloom()
{
	//�����_�[�^�[�Q�b�g�̍쐬
	CreateRT();
	//�V�F�[�_�[�̐ݒ�
	InitShader();
	//�ŏI�����p�̃u�����h�X�e�[�g�̍쐬
	InitAlphaBlendState();
	//�T���v���[�X�e�[�g�̍쐬
	InitSamplerState();

	//�P�x�e�N�X�`�����ڂ������߂̃K�E�V�A���u���[������������
	ID3D11ShaderResourceView*srcBlurTexture = m_luminaceRT.GetRenderTargetSRV();
	for (int i = 0; i < NUM_DOWN_SAMPLE; i++)
	{
		m_gaussianBlur[i].Init(srcBlurTexture, 25.0f);
		//���̃K�E�X�u���[�Ŏg�p����\�[�X�e�N�X�`����ݒ肷��
		srcBlurTexture = m_gaussianBlur[i].GetResultTextureSRV();
	}
}

Bloom::~Bloom()
{
	if (m_disableBlendState != nullptr)
	{
		m_disableBlendState->Release();
		m_disableBlendState = nullptr;
	}
	if (m_finalBlendState != nullptr)
	{
		m_finalBlendState->Release();
		m_finalBlendState = nullptr;
	}
	if (m_samplerState != nullptr)
	{
		m_samplerState->Release();
		m_samplerState = nullptr;
	}
}

//�P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬����
void Bloom::CreateRT()
{
	//�t�H�[�}�b�g��16bit
	m_luminaceRT.Create
	(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);
}
void Bloom::InitAlphaBlendState()
{
	CD3D11_DEFAULT defaultSettings;
	//�f�t�H���g�ŃZ�b�e�B���O����
	CD3D11_BLEND_DESC blendDesc(defaultSettings);
	
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	//�u�����h�X�e�[�g���쐬����
	d3dDevice->CreateBlendState(&blendDesc, &m_disableBlendState);

	//�ŏI�����p�̃u�����h�X�e�[�g�̐ݒ�
	//�ŏI�����͉��Z����
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	//�ŏI�����p�̃u�����h�X�e�[�g���쐬
	d3dDevice->CreateBlendState(&blendDesc, &m_finalBlendState);
}

void Bloom::InitSamplerState()
{
	//�T���v���[�X�e�[�g�̐ݒ�
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	//�T���v���[�X�e�[�g�̍쐬
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
}

void Bloom::InitShader()
{
	m_vs.Load("Assets/shader/bloom.fx", "VSMain", Shader::EnType::VS);
	m_psLuminace.Load("Assets/shader/bloom.fx", "PSSamplingLuminace", Shader::EnType::PS);
	m_psFinal.Load("Assets/shader/bloom.fx", "PSFinal", Shader::EnType::PS);
}

void Bloom::Draw(PostEffect&postEffect)
{
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//�T���v���[�X�e�[�g��ݒ�
	deviceContext->PSSetSamplers(0, 1, &m_samplerState);

	//�܂��͋P�x�𒊏o����
	{
		//���u�����h�𖳌��ɂ���
		float blendFactor[] = { 0.0f,0.0f,0.0f,0.0f };
		deviceContext->OMSetBlendState
		(
			m_disableBlendState,
			blendFactor,
			0xffffffff
		);

		//�P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX����
		g_graphicsEngine->ChangeRenderTarget
		(
			deviceContext,
			&m_luminaceRT,
			m_luminaceRT.GetViewport()
		);

		//�����_�����O�^�[�Q�b�g�̃N���A
		float clearColor[] = { 0.0f,0.0f,0.0f,0.0f };
		m_luminaceRT.ClearRenderTarget(clearColor);

		//�V�[�����e�N�X�`���Ƃ���
		auto mainRTTexSRV = g_graphicsEngine->GetRT()->GetRenderTargetSRV();
		deviceContext->PSSetShaderResources
		(
			0,
			1,
			&mainRTTexSRV
		);

		//�t���X�N���[���`��
		postEffect.DrawFS
		(
			deviceContext,
			m_vs,
			m_psLuminace
		);
	}

	//�P�x�e�N�X�`�����K�E�V�A���u���[�łڂ���
	for (int i = 0; i < NUM_DOWN_SAMPLE; i++)
	{
		m_gaussianBlur[i].Execute(postEffect);
	}

	//�Ō�ɂڂ������G�����Z�����Ń��C�������_�����O�^�[�Q�b�g�ɍ�������
	{
		auto mainRT = g_graphicsEngine->GetRT();
		g_graphicsEngine->ChangeRenderTarget
		(
			deviceContext,
			mainRT,
			mainRT->GetViewport()
		);

		//�K�E�V�A���u���[���������e�N�X�`����t0�`t3���W�X�^�ɐݒ肷��
		for (int registerNo = 0; registerNo < NUM_DOWN_SAMPLE; registerNo++)
		{
			auto srv = m_gaussianBlur[registerNo].GetResultTextureSRV();
			deviceContext->PSSetShaderResources
			(
				registerNo,
				1,
				&srv
			);
		}

		//���Z�����p�̃u�����f�B���O�X�e�[�g��ݒ肷��
		float blendFactor[] = { 0.0f,0.0f,0.0f,0.0f };
		deviceContext->OMSetBlendState
		(
			m_finalBlendState,
			blendFactor,
			0xffffffff
		);

		//�t���X�N���[���`��
		postEffect.DrawFS
		(
			deviceContext,
			m_vs,
			m_psFinal
		);

		//�u�����f�B���O�X�e�[�g��߂�
		deviceContext->OMSetBlendState
		(
			m_disableBlendState,
			blendFactor,
			0xffffffff
		);
	}
}