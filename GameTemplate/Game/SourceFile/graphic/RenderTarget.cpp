#include "stdafx.h"
#include "RenderTarget.h"

namespace Engine {
	RenderTarget::RenderTarget()
	{

	}

	RenderTarget::~RenderTarget()
	{

	}

	//解放処理
	void RenderTarget::Release()
	{
		if (m_renderTargetTex != nullptr)
		{
			m_renderTargetTex->Release();
		}
		if (m_renderTargetSRV != nullptr)
		{
			m_renderTargetSRV->Release();
		}
		if (m_renderTargetView != nullptr)
		{
			m_renderTargetView->Release();
		}
		if (m_depthStencilView != nullptr)
		{
			m_depthStencilView->Release();
		}
		if (m_depthStencilTex != nullptr)
		{
			m_depthStencilTex->Release();
		}
	}

	//レンダリングターゲットの作成
	void RenderTarget::Create(unsigned int w, unsigned int h, DXGI_FORMAT texFormat)
	{
		//D3Dデバイスを取得
		auto d3dDevice = g_graphicsEngine->GetD3DDevice();
		//幅の解像度を設定
		texDesc.Width = w;
		//高さの解像度を設定
		texDesc.Height = h;
		//ミップマップレベル。1でいい。
		texDesc.MipLevels = 1;
		//テクスチャ配列のサイズ。1でいい。
		texDesc.ArraySize = 1;
		//テクスチャのRGBAのフォーマット。
		texDesc.Format = texFormat;
		//テクスチャの使用用途を決める。
		//レンダリングターゲットのテクスチャは、
		//レンダリングターゲット、ShaderResourceView、UnorderedAccessViewとしてバインドする。
		texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
		//マルチサンプリングの数。1でいい。
		texDesc.SampleDesc.Count = 1;
		//マルチサンプリングの品質。0でいい。
		texDesc.SampleDesc.Quality = 0;
		//テクスチャの読み書きのされ方。D3D11_USAGE_DEFAULTでいい。
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		//CPUからのアクセスの仕方。アクセスしないので0でよい。
		texDesc.CPUAccessFlags = 0;
		//0でよい。
		texDesc.MiscFlags = 0;
		//テクスチャを作成。
		d3dDevice->CreateTexture2D(&texDesc, nullptr, &m_renderTargetTex);

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		//フォーマットはテクスチャと同じでよい。
		srvDesc.Format = texDesc.Format;
		//2次元テクスチャとして扱う。
		srvDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
		//ミップマップレベルもテクスチャと同じでよい。
		srvDesc.Texture2D.MipLevels = texDesc.MipLevels;
		//0でいい。
		srvDesc.Texture2D.MostDetailedMip = 0;
		//SRVを作成する。
		d3dDevice->CreateShaderResourceView(m_renderTargetTex, &srvDesc, &m_renderTargetSRV);

		//レンダリングターゲットビューを作成するためのデータを設定する。。
		D3D11_RENDER_TARGET_VIEW_DESC viewDesc;
		//フォーマットはテクスチャと同じにする。
		viewDesc.Format = texDesc.Format;
		//2Dテクスチャを扱うことを指定する。
		viewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		//0でいい。
		viewDesc.Texture2D.MipSlice = 0;
		//レンダリングターゲットビューの作成。
		d3dDevice->CreateRenderTargetView(m_renderTargetTex, &viewDesc, &m_renderTargetView);
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		//フォーマットは深度ステンシルと同じにする。
		depthStencilViewDesc.Format = depthTexDesc.Format;
		//2Dテクスチャを扱うことを指定する。
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		//0でいい。
		depthStencilViewDesc.Texture2D.MipSlice = 0;
		//0でいい。
		depthStencilViewDesc.Flags = 0;
		//デプスステンシルビューを作成。
		d3dDevice->CreateDepthStencilView(m_depthStencilTex, &depthStencilViewDesc, &m_depthStencilView);

		//デプスステンシルビューにバインドする。
		depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		//32bit浮動小数点のデプスステンシルバッファを作成する。
		depthTexDesc.Format = DXGI_FORMAT_D32_FLOAT;
		//デプスステンシルテクスチャを作成する。
		d3dDevice->CreateTexture2D(&depthTexDesc, nullptr, &m_depthStencilTex);
	}

	void RenderTarget::ClearRenderTarget(float*clearColor)
	{
		auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		d3dDeviceContext->ClearRenderTargetView(m_renderTargetView, clearColor);
		d3dDeviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}
}