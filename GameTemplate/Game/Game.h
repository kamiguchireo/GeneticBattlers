#pragma once
#include "SpriteRender.h"
#include "SourceFile/graphic/Effect/CEffect.h"
#include "SourceFile/Sound/CSoundSource.h"
#include "SourceFile/graphic/RenderTarget.h"

class Game:public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void UpdateShadowMap();
	void Render();
	void ForwordRender();
	void PostRender();
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);
private:
	//prefab::SpriteRender*m_spriteRender;	//スプライトレンダー
	prefab::CEffect* effect = NewGO<prefab::CEffect>(0);		//エフェクトを作成。
	//prefab::CSoundSource ss;		//サウンド
	SkinModel m_model;		//モデル(ユニティちゃん)
	//SkinModel m_model2;	//モデル２(ユニティちゃん)
	SkinModel m_model3;		//モデル３(地面)
	RenderTarget m_shadowMapRT;		//シャドウマップを描画するレンダリングターゲット
	CVector3 m_ligPos = { 0.0f,300.0f,0.0f };
	CVector3 m_ligDir = { 1.0f,0.0f,0.0f };
	CVector3 m_position = CVector3::Zero();
	RenderTarget m_mainRenderTarget;		//メインレンダリングターゲット。
	ID3D11RenderTargetView* oldRenderTargetView = nullptr;
	ID3D11DepthStencilView* oldDepthStencilView = nullptr;
	D3D11_VIEWPORT m_frameBufferViewports;			//フレームバッファのビューポート。
	Sprite m_copyMainRtToFrameBufferSprite;			//メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。

};

