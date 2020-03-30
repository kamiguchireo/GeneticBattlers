#include "stdafx.h"
#include "Bloom.h"
#include "PostEffect.h"

Bloom::Bloom()
{
	//レンダーターゲットの作成
	CreateRT();
	//シェーダーの設定
	InitShader();
	//最終合成用のブレンドステートの作成
	InitAlphaBlendState();
	//サンプラーステートの作成
	InitSamplerState();

	//輝度テクスチャをぼかすためのガウシアンブラーを初期化する
	ID3D11ShaderResourceView*srcBlurTexture = m_luminaceRT.GetRenderTargetSRV();
	for (int i = 0; i < NUM_DOWN_SAMPLE; i++)
	{
		m_gaussianBlur[i].Init(srcBlurTexture, 25.0f);
		//次のガウスブラーで使用するソーステクスチャを設定する
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

//輝度抽出用のレンダリングターゲットを作成する
void Bloom::CreateRT()
{
	//フォーマットは16bit
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
	//デフォルトでセッティングする
	CD3D11_BLEND_DESC blendDesc(defaultSettings);
	
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	//ブレンドステートを作成する
	d3dDevice->CreateBlendState(&blendDesc, &m_disableBlendState);

	//最終合成用のブレンドステートの設定
	//最終合成は加算合成
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	//最終合成用のブレンドステートを作成
	d3dDevice->CreateBlendState(&blendDesc, &m_finalBlendState);
}

void Bloom::InitSamplerState()
{
	//サンプラーステートの設定
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	//サンプラーステートの作成
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
	//サンプラーステートを設定
	deviceContext->PSSetSamplers(0, 1, &m_samplerState);

	//まずは輝度を抽出する
	{
		//αブレンドを無効にする
		float blendFactor[] = { 0.0f,0.0f,0.0f,0.0f };
		deviceContext->OMSetBlendState
		(
			m_disableBlendState,
			blendFactor,
			0xffffffff
		);

		//輝度抽出用のレンダリングターゲットに変更する
		g_graphicsEngine->ChangeRenderTarget
		(
			deviceContext,
			&m_luminaceRT,
			m_luminaceRT.GetViewport()
		);

		//レンダリングターゲットのクリア
		float clearColor[] = { 0.0f,0.0f,0.0f,0.0f };
		m_luminaceRT.ClearRenderTarget(clearColor);

		//シーンをテクスチャとする
		auto mainRTTexSRV = g_graphicsEngine->GetRT()->GetRenderTargetSRV();
		deviceContext->PSSetShaderResources
		(
			0,
			1,
			&mainRTTexSRV
		);

		//フルスクリーン描画
		postEffect.DrawFS
		(
			deviceContext,
			m_vs,
			m_psLuminace
		);
	}

	//輝度テクスチャをガウシアンブラーでぼかす
	for (int i = 0; i < NUM_DOWN_SAMPLE; i++)
	{
		m_gaussianBlur[i].Execute(postEffect);
	}

	//最後にぼかした絵を加算合成でメインレンダリングターゲットに合成する
	{
		auto mainRT = g_graphicsEngine->GetRT();
		g_graphicsEngine->ChangeRenderTarget
		(
			deviceContext,
			mainRT,
			mainRT->GetViewport()
		);

		//ガウシアンブラーをかけたテクスチャをt0～t3レジスタに設定する
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

		//加算合成用のブレンディングステートを設定する
		float blendFactor[] = { 0.0f,0.0f,0.0f,0.0f };
		deviceContext->OMSetBlendState
		(
			m_finalBlendState,
			blendFactor,
			0xffffffff
		);

		//フルスクリーン描画
		postEffect.DrawFS
		(
			deviceContext,
			m_vs,
			m_psFinal
		);

		//ブレンディングステートを戻す
		deviceContext->OMSetBlendState
		(
			m_disableBlendState,
			blendFactor,
			0xffffffff
		);
	}
}