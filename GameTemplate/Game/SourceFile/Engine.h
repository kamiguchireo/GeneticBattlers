#pragma once
#include "SourceFile/Sound/SoundEngine.h"
#include "SourceFile/graphic/PostEffect.h"
//photon
#include "Photon/Common-cpp/inc/JString.h"
#include "Network/SampleNetwork.h"

namespace Engine {
	class EngineProcessing :public Noncopyable
	{
	public:
		EngineProcessing()
		{

		}

		~EngineProcessing()
		{

		}

		//エンジン関係の初期化
		void Init();
		//エンジン関係のアップデート
		void Update();

		void EffectDraw();
		//ポストエフェクトの描画
		void PostEffectDraw();

		//レンダリングターゲットを変更する
		void ChangeRT();
		//レンダリングターゲットを戻す
		void ReturnRT();
		//現在のレンダリングターゲットをクリアする
		void ClearRT();

		//最終的に画面に出すスプライトの描画
		void MainSpriteDraw();

	private:
		CSoundEngine se;		//サウンドエンジン
		PostEffect m_postEffect;		//ポストエフェクト
		ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
		ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。
		D3D11_VIEWPORT m_frameBufferViewports;			//フレームバッファのビューポート。
		struct MainSpriteConfig
		{
			CVector3 m_sposition = { 0.0,0.0,5.0 };			//座標。
			CQuaternion m_rotation = CQuaternion::Identity();			//!<回転。
			CVector3 m_scale = CVector3::One();			//拡大率。
			CVector2 m_pivot = Sprite::DEFAULT_PIVOT;	//ピボット。
		};
		MainSpriteConfig MSC;
	};
}