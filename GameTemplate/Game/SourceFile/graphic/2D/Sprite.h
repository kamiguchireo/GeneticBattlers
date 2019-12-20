#pragma once
#include "ShaderResourceView.h"
#include "graphics/Shader.h"
#include "SourceFile/graphic/Primitive.h"

namespace Engine {
	class Sprite
	{
	public:
		//コンストラクタ
		Sprite();
		//デストラクタ
		~Sprite();

		/*
		初期化
		tex		.テクスチャ
		*/
		void Init(ShaderResourceView&tex, float w, float h);
	
	private:
		Shader m_ps;			//ピクセルシェーダー
		Shader m_vs;			//頂点シェーダー
		CVector2 m_size = CVector2::Zero();			//サイズ
		Primitive m_primitive;			//プリミティブ
	};

}