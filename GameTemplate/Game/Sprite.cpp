#include "stdafx.h"
#include "Sprite.h"

namespace Engine {
	namespace {
		struct SSinmpleVertex {
			CVector4 pos;
			CVector2 tex;
		};
	}
	Sprite::Sprite()
	{
	}
	Sprite::~Sprite()
	{
	}

	//初期化処理
	void Sprite::Init(ShaderResourceView& tex, float w, float h)
	{
		//シェーダーロード
		//ピクセルシェーダー
		m_ps.Load("shader/sprite.fx", "PSMain", Shader::EnType::PS);
		m_vs.Load("shader/sprite.fx", "VSMain", Shader::EnType::VS);
		//サイズを代入
		m_size.x = w;
		m_size.y = h;
		float halfW = w * 0.5f;
		float halfH = h * 0.5f;
		//頂点バッファのソースデータ
		SSinmpleVertex vertices[] =
		{
			{
				CVector4(-halfW,-halfH,0.0f,1.0f),
				CVector2(0.0f,1.0f),
			},
			{
				CVector4(halfW,-halfH,0.0f,1.0f),
				CVector2(1.0f,1.0),
			},
		    {
				CVector4(-halfW,halfH,0.0f,1.0f),
				CVector2(1.0f,0.0f),
			},
			{
				CVector4(halfW,halfH,0.0f,1.0f),
				CVector2(1.0f,0.0f),
			},
		};
		short indices[] = { 0,1,2,3 };
	}
}