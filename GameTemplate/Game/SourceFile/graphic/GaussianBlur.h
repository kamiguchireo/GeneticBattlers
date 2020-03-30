#pragma once
#include "RenderTarget.h"
#include "SourceFile/graphic/GPUBuffer/ConstantBufferGPU.h"

class PostEffect;
class GaussianBlur
{
public:
	GaussianBlur();
	~GaussianBlur();

	//srcTextureSRV		ブラーをかけるテクスチャのSRV
	//blurIntensity		ブラーの強さ。値が大きいほど強くブラーがかかる
	void Init(ID3D11ShaderResourceView*stcTextureSRV, float blurIntensity);

	//ブラーの実行
	//postEffect		ポストエフェクトのインスタンス		全画面描画の機能を使うだけ
	//Init関数を呼び出した後で実行してください
	void Execute(PostEffect&postEffect);

	//ブラーをかけた結果のテクスチャSRVを取得
	ID3D11ShaderResourceView*GetResultTextureSRV()
	{
		return m_renderTarget[enRenderTarget_YBlur].GetRenderTargetSRV();
	}
private:	
	//ブラーの重みの更新
	void UpdateWeight();

	static const int NUM_WEIGHTS = 8;	//カウスフィルタの重みの数。
	//ブラー用のパラメータバッファ
	//これを変更したら、GaussianBlur.fxのCBBlurの中身も変更する
	struct SBlurParam {
		float weights[NUM_WEIGHTS];
	};

	//レンダリングターゲット
	enum EnRenderTarget{
		enRenderTarget_XBlur,		//Xブラーの書き込み先となるレンダリングターゲット
		enRenderTarget_YBlur,		//Yブラーの書き込み先となるレンダリングターゲット
		enRenderTarget_Num,		//レンダリングターゲットの枚数
	};
	ID3D11ShaderResourceView* m_srcTextureSRV = nullptr;	//ソーステクスチャのSRV
	float m_blurIntensity = 25.0f;		//ブラーの強さ。ブラーのウェイトの計算で使用されます。
	unsigned int m_srcTextureWidth = 0;			//ソーステクスチャの幅。
	unsigned int m_srcTextureHeight = 0;		//ソーステクスチャの高さ。
	Engine::RenderTarget m_renderTarget[enRenderTarget_Num];		//レンダリングターゲット。
	Shader m_vsXBlur;						//Xブラー用の頂点シェーダー。
	Shader m_vsYBlur;						//Yブラー用の頂点シェーダー。
	Shader m_psBlur;						//ブラー用のピクセルシェーダー。
	ConstantBufferGPU m_blurCbGpu;				//ブラー用の定数バッファ(GPU側)
	bool m_isInited = false;		//初期化済みフラグ。
	SBlurParam m_blurParam;						//ブラー用のパラメータ。

};

