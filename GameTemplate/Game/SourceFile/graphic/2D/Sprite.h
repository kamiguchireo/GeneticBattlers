#pragma once
#include "ShaderResourceView.h"
#include "graphics/Shader.h"
#include "SourceFile/graphic/Primitive.h"
#include "ConstantBuffer.h"
#include "SourceFile/graphic/RenderContext.h"

namespace Engine {
	class Sprite
	{
	public:
		//起点
		static const CVector2 DEFAULT_PIVOT;
		//コンストラクタ
		Sprite();
		//デストラクタ
		~Sprite();

		/*
		初期化
		tex		.テクスチャ
		*/
		void Init(ID3D11ShaderResourceView* tex, float w, float h);

		/*
		乗算カラーを設定
		mulColor	乗算カラー
		*/
		void SetMulColor(const CVector3& mulColor)
		{
			m_mulColor = mulColor;
		}

		//テクスチャを設定
		//tex		テクスチャ
		//void SetTexture(ShaderResourceView& tex)
		//{
		//	m_textureSRV = &tex;
		//}

		//アップデート関数
		//trans		平行移動
		//rot		回転
		//scale		拡大
		//pivot		起点
		//0.5, 0.5で画像の中心が起点。
		//0.0, 0.0で画像の左下。
		//1.0, 1.0で画像の右上。
		void Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, const CVector2& pivot = DEFAULT_PIVOT);
	
		/*
		描画
		viewMatrix		ビュー行列
		projMatrix		プロジェクション行列
		*/
		void Draw(const CMatrix&viewMatrix, const CMatrix& projMatrix);
		//αの値の変更
		void SetAlpha(float a)
		{
			cb.alpha = a;
		}
		//引数で渡された整数値を16の倍数に切り上げ
		int Raundup16(int n)
		{
			return (((n - 1) / 16) + 1) * 16;
		}

		void SetIsAlpha(int a)
		{
			cb.isAlpha = a;
		}
	private:
		//定数バッファ(ConstantBuffer)のCreate関数の引数に使用する
		struct SSpriteCB
		{
			CMatrix WVP;		//ワールドビュープロジェクション行列
			CVector3 mulColor;		//乗算カラー
			float alpha = 1.0f;		//α値
			int isAlpha = 0;	//画像自体のαを使うかどうか1の時に画像のαを使わない
		};
		SSpriteCB cb;
		Shader m_ps;			//ピクセルシェーダー
		Shader m_vs;			//頂点シェーダー
		CVector3 m_mulColor = CVector3::Zero();		//乗算カラー
		CVector2 m_size = CVector2::Zero();			//サイズ
		Primitive m_primitive;			//プリミティブ
		//ShaderResourceView* m_textureSRV = nullptr;		//テクスチャ
		ID3D11ShaderResourceView*m_textureSRV = nullptr;
		ConstantBuffer m_cb;
		CMatrix m_world = CMatrix::Identity();		//ワールド行列
		bool m_isInited = false;		//初期化フラグ
	};

}