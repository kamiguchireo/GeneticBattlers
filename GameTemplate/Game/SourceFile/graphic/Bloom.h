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

	//描画
	void Draw(PostEffect& postEffect);

private:
	static const int NUM_DOWN_SAMPLE = 4;		//ダウンサンプリングの回数。
	void CreateRT();		//輝度抽出用のレンダリングターゲットを作成する
	void InitAlphaBlendState();		//ブレンドステートのαを設定する
	void InitSamplerState();		//サンプラーステートの初期化
	void InitShader();		//シェーダーのセット
	Engine::RenderTarget m_luminaceRT;		//輝度抽出用のレンダーターゲット
	ID3D11BlendState* m_disableBlendState = nullptr;	//アルファブレンディングを無効にするブレンディングステート。
	ID3D11BlendState* m_finalBlendState = nullptr;		//最終合成用のブレンディングステート。
	ID3D11SamplerState* m_samplerState = nullptr;		//サンプラステート。
	Shader m_vs;		//何もしない頂点シェーダー
	Shader m_psLuminace;		//輝度抽出用のピクセルシェーダー
	Shader m_psFinal;		//最終合成用のピクセルシェーダー
	GaussianBlur m_gaussianBlur[NUM_DOWN_SAMPLE];	//輝度をぼかすためのガウシアンブラー。

};