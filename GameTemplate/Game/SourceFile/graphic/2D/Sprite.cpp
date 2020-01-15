#include "stdafx.h"
#include "Sprite.h"

namespace Engine {
	namespace {
		struct SSinmpleVertex {
			CVector4 pos;
			CVector2 tex;
		};
	}
	//起点の初期化
	const CVector2 Sprite::DEFAULT_PIVOT = { 0.5f,0.5f };
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
		m_ps.Load("Assets/shader/sprite.fx", "PSMain", Shader::EnType::PS);
		//頂点シェーダー
		m_vs.Load("Assets/shader/sprite.fx", "VSMain", Shader::EnType::VS);
		//サイズを代入
		m_size.x = w;
		m_size.y = h;
		//サイズの半分を計算
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

		//プリミティブのクリエイト関数
		m_primitive.Create(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
			//頂点数
			4,
			//頂点のサイズ
			sizeof(SSinmpleVertex),
			//頂点バッファ
			vertices,
			//インデックスバッファの数
			4,
			//インデックスの型
			IndexBuffer::enIndexType_16,
			//インデックスバッファへのポインタ
			indices
		);
		//Init関数の中身
		//テクスチャのシェーダーリソースビュー
		m_textureSRV = &tex;
		m_cb.Create(nullptr, sizeof(SSpriteCB));
		//初期化フラグをtrueにする
		m_isInited = true;
	}

	//更新処理
	//trans		平行移動
	//rot		回転
	//sale		拡大
	void Sprite::Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, const CVector2& pivot)
	{
		if (m_isInited = false)
		{
			//初期化されていないとき
			//何も返さない
			return;
		}
		//初期化されているとき
		//ピボット(起点)を考慮に入れた平行移動行列を作成
		//ピボットは真ん中が0.0,0.0、左上が-1.0,-1.0、
		//右下が1.0,1.0になるようにする
		CVector2 localPivot = pivot;
		localPivot.x -= 0.5f;
		localPivot.y -= 0.5f;
		localPivot.x *= -2.0f;
		localPivot.y *= -2.0f;
		//画像のハーフサイズを求める
		CVector2 halfSize = m_size;
		halfSize.x *= 0.5f;
		halfSize.y *= 0.5f;
		//平行移動用の起点用の行列を作成
		CMatrix m_PivotTrans;
		m_PivotTrans.MakeTranslation
		(
			{
				//ハーフサイズに起点を掛ける
				//つまりここでは起点の位置を求めている
				halfSize.x * localPivot.x , halfSize.y * localPivot.y , 0.0f
			}
		);
		//
		CMatrix m_Trans, m_Rot, m_Scale;
		//平行移動用の行列
		m_Trans.MakeTranslation(trans);
		//回転用の行列
		m_Rot.MakeRotationFromQuaternion(rot);
		//拡大用の行列
		m_Scale.MakeScaling(scale);
		//ワールド行列に乗算していく
		//順番は元々の行列*拡大率*回転率*平行移動
		//元々の行列*拡大率
		m_world.Mul(m_PivotTrans, m_Scale);
		//次に拡大率を掛ける
		m_world.Mul(m_world,m_Rot);
		//平行移動行列を掛ける
		m_world.Mul(m_world, m_Trans);
	}
}