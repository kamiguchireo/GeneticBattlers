#pragma once
#include "Camera.h"
#include "SourceFile/graphic/RenderContext.h"
#include "SourceFile/graphic/2D/Sprite.h"
#include "EffekseerRendererDX11.h"
#include "Effekseer.h"
#include "SourceFile/graphic/ShadowMap.h"
//#include "SourceFile/graphic/RenderTarget.h"

enum EnRenderMode
{
	enRenderMode_CreateShadowMap,		//シャドウマップ生成
	enRenderMode_Normal,				//通常レンダリング
	enRenderMode_silhouette,			//シルエット生成用レンダリング
	enRenderMode_shadowReciever,		//シャドウレシーバーとして生成
};
/*!
 *@brief	グラフィックスエンジン。
 */
class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	初期化。
	 *@param[in]	hWnd		ウィンドウハンドル。
	 */
	void Init(HWND hWnd);
	/*!
	 *@brief	解放。
	 */
	void Release();
	/*!
	 *@brief	D3D11デバイスを取得。
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11デバイスコンテキストを取得。
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}
	Camera&GetMainCamera()
	{
		return m_mainCamera;		//カメラ
	}
	Camera&Get2DCamera()
	{
		return g_camera2D;
	}

	void Execute2DDraw()
	{
		m_sprite.Draw
		(
			g_camera2D.GetViewMatrix(),
			g_camera2D.GetProjectionMatrix()
		);
	}
	//レンダリングコンテキストのインスタンスを取得
	Engine::RenderContext& GetRenderContext()
	{
		return m_renderContext;
	}
	/*!
	 *@brief	描画開始。
	 */
	void BegineRender();
	/*!
	 *@brief	描画終了。
	 */
	void EndRender();


	ID3D11RasterizerState* GetRasterizerState()
	{
		return m_rasterizerState;
	}

	void managerInit();
	
	//Effekseerマネージャの取得。 
	Effekseer::Manager& GetEffekseerManager()
	{
		return *m_manager;
	}

	EffekseerRenderer::Renderer& GetEffekseerRender()
	{
		return *m_renderer;
	}
	Effekseer::Effect* GraphicsEngine::CreateEffekseerEffect(const wchar_t* filePath)
	{
		return Effekseer::Effect::Create(m_manager, (const EFK_CHAR*)filePath);
	}

	Engine::ShadowMap* GetShadowMap()
	{
		return &m_shadowmap;
	}
	ID3D11BlendState* GetBlendState()
	{
		return m_translucentBlendState;
	}

	void RtSpInit();
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, Engine::RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);

	Engine::RenderTarget*GetRT()
	{
		return &m_mainRenderTarget;
	}

	Engine::Sprite*GetSp()
	{
		return &m_copyMainRtToFrameBufferSprite;
	}
	void InitRender();
private:
	Camera m_mainCamera;		//カメラ
	//Camera m_2DCamera;
	Engine::Sprite m_sprite;
	Engine::RenderContext m_renderContext;		//レンダリングコンテキスト。
	//ID3D11DeviceContext* m_pImmediateContext = nullptr;		//D3D11即時デバイスコンテキスト
	ID3D11DeviceContext* m_pDeferredDeviceContext = nullptr;		//D3D11ディファードデバイスコンテキスト
	D3D_FEATURE_LEVEL		m_featureLevel;				//Direct3D デバイスのターゲットとなる機能セット。
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11デバイス。
	IDXGISwapChain*			m_pSwapChain = NULL;		//スワップチェイン。
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11デバイスコンテキスト。
	ID3D11RenderTargetView* m_backBuffer = NULL;		//バックバッファ。
	ID3D11RasterizerState*	m_rasterizerState = NULL;	//ラスタライザステート。
	ID3D11Texture2D*		m_depthStencil = NULL;		//デプスステンシル。
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//デプスステンシルビュー。
	D3D11_FEATURE_DATA_THREADING m_featureDataThreading;
	Effekseer::Manager* m_manager = nullptr;
	EffekseerRenderer::Renderer* m_renderer = nullptr;
	Engine::ShadowMap m_shadowmap;
	ID3D11BlendState*m_translucentBlendState = nullptr;
	Engine::RenderTarget m_mainRenderTarget;		//メインレンダリングターゲット。
	Engine:: Sprite m_copyMainRtToFrameBufferSprite;			//メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。
	D3D11_VIEWPORT m_frameBufferViewports;			//フレームバッファのビューポート。
	CVector3 m_sposition = { 0.0,0.0,5.0 };			//座標。
	CQuaternion m_rotation = CQuaternion::Identity();			//!<回転。
	CVector3 m_scale = CVector3::One();			//拡大率。
	CVector2 m_pivot = Engine:: Sprite::DEFAULT_PIVOT;	//ピボット。
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。

};

extern GraphicsEngine* g_graphicsEngine;			//グラフィックスエンジン