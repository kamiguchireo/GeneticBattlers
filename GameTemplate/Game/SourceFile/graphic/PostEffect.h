#pragma once
#include "SourceFile/graphic/Bloom.h"

class PostEffect
{
public:
	PostEffect();
	~PostEffect();

	//更新
	void Update();
	//描画
	void Draw();
	//フルスクリーン描画
	void DrawFS(ID3D11DeviceContext*deviceContext, Shader&vsShader, Shader&psShader);

private:
	struct SVertex {
		float position[4];		//頂点座標
		float uv[2];		//UV座標。これがテクスチャ座標
	};

	//フルスクリーン描画用の四角形プリミティブの初期化
	void InitFSQuadPrimitive();

	Bloom m_bloom;		//ブルーム
	/*
	//フルスクリーン描画用のメンバ変数
	*/
	ID3D11Buffer* m_vertexBuffer = nullptr;		//頂点バッファ
	ID3D11InputLayout* m_inputLayout = nullptr;		//入力レイアウト
};

