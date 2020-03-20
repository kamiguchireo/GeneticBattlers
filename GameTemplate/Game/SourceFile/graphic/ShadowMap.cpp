#include "stdafx.h"
#include "ShadowMap.h"

namespace Engine {
	ShadowMap::ShadowMap()
	{

	}

	ShadowMap::~ShadowMap()
	{

	}

	void ShadowMap::ShadowMapRTCreate()
	{
		//シャドウマップ生成用のレンダリングターゲットを作る
		//解像度は2048*2048
		//テクスチャのフォーマットはR成分のみの32ビットのFloat型
		m_shadowMapRT.Create
		(
			2048,
			2048,
			DXGI_FORMAT_R32_FLOAT
		);
	}
	void ShadowMap::Update(CVector3 lightCameraPos, CVector3 lightCameraTarget)
	{
		//ライトの方向を計算する
		auto lightDir = lightCameraTarget - lightCameraPos;
		if (lightDir.Length() < 0.0001f)
		{
			//ライトカメラの注視点と視点が近すぎる
			//もっと距離を離してください
			throw;
		}
		
		//正規化して方向ベクトルに変換する
		lightDir.Normalize();
		
		//ライトの方向によって、ライトカメラの上方向を決める
		CVector3 lightCameraUpAxis;
		if (fabsf(lightDir.y) > 0.99998f)
		{
			//ほぼ真上or真下を向いているので、1,0,0を上方向とする
			lightCameraUpAxis = CVector3::AxisX();
		}
		else
		{
			//真上を向いていないときは、0,1,0を上方向とする
			lightCameraUpAxis = CVector3::AxisY();
		}
		
		//カメラの上方向が決まったので、ライトビュー行列を計算する
		m_lightViewMatrix.MakeLookAt
		(
			lightCameraPos,
			lightCameraTarget,
			lightCameraUpAxis
		);

		//ライトプロジェクション行列を作成する
		//太陽光からの影を落としたいなら、平行投影行列を作成する
		m_lightProMatrix.MakeOrthoProjectionMatrix
		(
			3000,
			3000,
			0.1f,
			5000.0f
		);
	}

	void ShadowMap::RenderToShadowMap()
	{
		auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		//レンダリングターゲットを切り替える
		ID3D11RenderTargetView* rts[] = 
		{
			m_shadowMapRT.GetRenderTargetView()
		};
		d3dDeviceContext->OMSetRenderTargets
		(
			1,
			rts,
			m_shadowMapRT.GetDepthStensilView()
		);
		//ビューポートを設定
		d3dDeviceContext->RSSetViewports
		(
			1,
			m_shadowMapRT.GetViewport()
		);

		//シャドウマップをクリア
		//一番奥のZは1.0なので、1.0で塗りつぶす
		float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
		m_shadowMapRT.ClearRenderTarget(clearColor);

		//シャドウキャスターをシャドウマップにレンダリング。
		for (auto& caster : m_shadowCasters) {
			caster->Draw(
				m_lightViewMatrix,
				m_lightProMatrix,
				enRenderMode_CreateShadowMap
			);
		}
		m_shadowCasters.clear();
	}
}