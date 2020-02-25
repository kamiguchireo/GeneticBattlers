#include "stdafx.h"
#include "DirectionLight.h"

namespace Engine {
	namespace prefab {
		DirectionLight::DirectionLight()
		{

			InitConstantBuffer();
		}
		DirectionLight::~DirectionLight()
		{
			//ライト用の定数バッファの解放
			if (m_lightCb != nullptr)
			{
				m_lightCb->Release();
			}
		}

		//bool DirectionLight::Start()
		//{
		//	InitConstantBuffer();
		//	m_dirLight.direction = { 1.0f, 0.0f, 0.0f, 0.0f };
		//	m_dirLight.color = { 1.0f, 1.0f, 1.0f, 1.0f };
		//	return true;
		//}

		//void DirectionLight::Update()
		//{
		//	CQuaternion qRot;
		//	qRot.SetRotationDeg(CVector3::AxisY(), 2.0f);
		//	qRot.Multiply(m_dirLight.direction);
		//	Draw();
		//}

		void DirectionLight::Draw()
		{
			auto dc = g_graphicsEngine->GetD3DDeviceContext();
			//ライト用の定数バッファを更新
			dc->UpdateSubresource(m_lightCb, 0, nullptr, &m_dirLight, 0, 0);
			//定数バッファをシェーダースロットに設定
			dc->PSSetConstantBuffers(0, 1, &m_lightCb);
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