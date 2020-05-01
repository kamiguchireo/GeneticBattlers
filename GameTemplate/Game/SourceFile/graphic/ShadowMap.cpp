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
		for (int i = 0; i < CascadeShadow; i++)
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
	}

	void ShadowMap::Update(CVector3 lightCameraPos, CVector3 lightCameraTarget)
	{
		//カメラの位置を取得
		m_cameraPos = g_camera3D.GetPosition();
		//カメラの注視点を取得
		m_cameraTarget = g_camera3D.GetTarget();
		//カメラの画角を取得
		//ラジアンで返ってくる
		ViewAngle = g_camera3D.GetViewAngle();
		//カメラの視点と注視点の距離を計算
		CVector3 m_cameraLength = m_cameraPos - m_cameraTarget;
		m_cameraDist = m_cameraLength.Length();
		//m_cameraDistをCascadeShadowで割る
		m_cameraDist = m_cameraDist / CascadeShadow;

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

		//カスケードシャドウの枚数分回す
	//	for(int i = 0;i < CascadeShadow;i++)
	//	{
			//カメラの上方向が決まったので、ライトビュー行列を計算する
			m_lightViewMatrix[1].MakeLookAt
			(
				lightCameraPos,
				lightCameraTarget,
				lightCameraUpAxis
			);


			//ライトプロジェクション行列を作成する
			//太陽光からの影を落としたいなら、平行投影行列を作成する
			m_lightProMatrix[1].MakeOrthoProjectionMatrix
			(
				100,
				100,
				0.1f,
				5000.0f
			);
	//	}
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

			//for (int i = 0; i < CascadeShadow; i++)
			//{
				//シャドウキャスターをシャドウマップにレンダリング。
				for (auto& caster : m_shadowCasters) {
					caster->Draw(
						m_lightViewMatrix[1],
						m_lightProMatrix[1],
						enRenderMode_CreateShadowMap
					);
			//	}
			}
		m_shadowCasters.clear();
	}
}