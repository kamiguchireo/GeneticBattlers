#include "stdafx.h"
#include "DirectionLight.h"

namespace Engine {
	namespace prefab {
		DirectionLight::DirectionLight()
		{

		}
		DirectionLight::~DirectionLight()
		{

		}

		//定数バッファの初期化
		void DirectionLight::InitConstantBuffer()
		{
			//bufferDescをゼロにセット
			ZeroMemory(&bufferDesc, sizeof(bufferDesc));
			bufferDesc.Usage = D3D11_USAGE_DEFAULT;
			//バッファのサイズ
			bufferDesc.ByteWidth = sizeof(SDirectionLight);
			//定数バッファ
			bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			//CPUは使わない
			bufferDesc.CPUAccessFlags = 0;
			//ディレクションライトの定数バッファを作成
			g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightCb);
		}
	}
}