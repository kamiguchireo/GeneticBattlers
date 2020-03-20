#pragma once

namespace Engine {
	class RenderTarget
	{
	public:
		RenderTarget();
		~RenderTarget();

		//解放処理
		void Release();

		//レンダリングターゲットの作成
		//w テクスチャの幅
		//h テクスチャの高さ
		void Create(unsigned int w, unsigned int h, DXGI_FORMAT texFormat);

		//レンダーターゲットとデプスステンシルのクリア
		//clearColor	クリアカラー
		void ClearRenderTarget(float*clearColor);

		//レンダリングターゲットビューを取得
		ID3D11RenderTargetView*GetRenderTargetView()
		{
			return m_renderTargetView;
		}

		//デプスステンシルビューを取得
		ID3D11DepthStencilView*GetDepthStensilView()
		{
			return m_depthStencilView;
		}

		//レンダリングターゲットのSRVを取得
		ID3D11ShaderResourceView*GetRenderTargetSRV()
		{
			return m_renderTargetSRV;
		}

		//ビューポートの取得
		D3D11_VIEWPORT*GetViewport()
		{
			return &m_viewport;
		}

		//SRVの取得
		ID3D11ShaderResourceView* GetSRV()
		{
			return m_renderTargetSRV;
		}
	private:
		ID3D11Texture2D* m_renderTargetTex = nullptr;		//レンダリングターゲットとなるテクスチャ。
		//レンダリングターゲットとなるテクスチャの作成
		D3D11_TEXTURE2D_DESC texDesc = { 0 };
		ID3D11RenderTargetView*	m_renderTargetView = nullptr;		//レンダーターゲットビュー。
		//デプスステンシルテクスチャの作成
		D3D11_TEXTURE2D_DESC depthTexDesc;
		ID3D11Texture2D* m_depthStencilTex = nullptr;		//デプスステンシルとなるテクスチャ。
		ID3D11DepthStencilView*	m_depthStencilView = nullptr;		//デプスステンシルビュー。
		ID3D11ShaderResourceView*	m_renderTargetSRV = nullptr;		//レンダリングターゲットのSRV
		D3D11_VIEWPORT m_viewport;
	};

}