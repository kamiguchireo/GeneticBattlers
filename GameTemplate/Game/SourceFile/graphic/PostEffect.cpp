#include "stdafx.h"
#include "PostEffect.h"

PostEffect::PostEffect()
{
	//フルスクリーン描画のための四角形プリミティブを初期化
	InitFSQuadPrimitive();
}

PostEffect::~PostEffect()
{

}

void PostEffect::Update()
{

}

void PostEffect::Draw()
{
	m_bloom.Draw(*this);
}

void PostEffect::InitFSQuadPrimitive()
{
	//頂点バッファを初期化
	SVertex vertex[4] = {
		//頂点１
		{
			//座標  position[4]
			-1.0f,-1.0f,0.0f,1.0f,
			//UV座標  uv[2]
			0.0f,1.0f
		},
		//頂点２
		{
			//座標  position[4]
			1.0f,-1.0f,0.0f,1.0f,
			//UV座標  uv[2]
			1.0f,1.0f
		},
		//頂点３
		{
			//座標　position[4]
			-1.0f,  1.0f, 0.0f, 1.0f,
			//UV座標 uv[2]
			0.0f, 0.0f
		},
		//頂点４
		{
			//座標　position[4]
			1.0f,  1.0f, 0.0f, 1.0f,
			//UV座標 uv[2]
			1.0f, 0.0f
		},

	};

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;		//バッファで想定されている読み書き込みの方法
	bd.ByteWidth = sizeof(vertex);		//バッファのサイス
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;		//これから作成するバッファの種類(頂点バッファ)
	
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	//初期化データへのポインタ
	InitData.pSysMem = vertex;

	//頂点バッファの作成
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &m_vertexBuffer);

}

void PostEffect::DrawFS(ID3D11DeviceContext*deviceContext, Shader&vsShader, Shader&psShader)
{
	//プリミティブのトポロジーとして、トライアングルストリップを設定
	deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	unsigned int vertexSize = sizeof(SVertex);
	unsigned int offset = 0;

	//輝度抽出用のシェーダーを設定する
	//頂点シェーダー
	deviceContext->VSSetShader
	(
		(ID3D11VertexShader*)vsShader.GetBody(), nullptr, 0
	);
	//ピクセルシェーダー
	deviceContext->PSSetShader
	(
		(ID3D11PixelShader*)psShader.GetBody(), nullptr, 0
	);

	deviceContext->IASetInputLayout(vsShader.GetInputLayout());
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &vertexSize, &offset);
	deviceContext->Draw(4, 0);
}