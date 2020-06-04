#include "stdafx.h"
#include "ShadowMap.h"

namespace Engine {
	ShadowMap::ShadowMap()
	{

	}

	ShadowMap::~ShadowMap()
	{

	}


	CVector3 ShadowMap::CalcLightPosition(float lightHeight, CVector3 viewFrustomCenterPosition)
	{
		auto alpha = (lightHeight - viewFrustomCenterPosition.y) / lightDir.y;
		auto lightPos = viewFrustomCenterPosition + lightDir * alpha;
		return lightPos;
	}

	void ShadowMap::ShadowMapRTCreate()
	{

		for (int i = 0; i < CascadeShadow; i++)
		{
			//シャドウマップ生成用のレンダリングターゲットを作る
			//解像度は2048*2048
			//テクスチャのフォーマットはR成分のみの32ビットのFloat型
			m_shadowMapRT[i].Create
			(
				2048,
				2048,
				DXGI_FORMAT_R32_FLOAT
			);

		}

		//定数バッファを作成
		m_shadowCb.Create(&m_shadowCbEntity, sizeof(m_shadowCbEntity));

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
			//ほぼ真上or真下を向いている
			lightCameraUpAxis = CVector3::AxisX();
			lightCameraUpAxis.Cross(lightDir, CVector3::Right());
			//lightCameraUpAxis = CVector3::Right();
		}
		else
		{
			//真上を向いていない
			lightCameraUpAxis = CVector3::AxisY();
			lightCameraUpAxis.Cross(lightDir, CVector3::Up());
			//lightCameraUpAxis = CVector3::Up();
		}
		//ライトの右方向
		CVector3 lightViewRight;
		lightViewRight.Cross(lightCameraUpAxis, lightDir);
		//正規化
		lightViewRight.Normalize();
		
		CMatrix lightViewRot;
		//ライトビューの横を設定する
		lightViewRot.m[0][0] = lightViewRight.x;
		lightViewRot.m[0][1] = lightViewRight.y;
		lightViewRot.m[0][2] = lightViewRight.z;
		lightViewRot.m[0][3] = 0.0f;
		//ライトビューの上を設定する。
		lightViewRot.m[1][0] = lightCameraUpAxis.x;
		lightViewRot.m[1][1] = lightCameraUpAxis.y;
		lightViewRot.m[1][2] = lightCameraUpAxis.z;
		lightViewRot.m[1][3] = 0.0f;
		//ライトビューの前を設定する。
		lightViewRot.m[2][0] = lightDir.x;
		lightViewRot.m[2][1] = lightDir.y;
		lightViewRot.m[2][2] = lightDir.z;
		lightViewRot.m[2][3] = 0.0f;
		float shadowAreaTbl[] = {
			1000.0f,//m_lightHeight * 0.8f,
			2000.0f,//m_lightHeight * 1.6f,
			3000.0f//m_lightHeight * 3.6f
		};

		//ライトビューの高さを計算
		float lightHeight = g_camera3D.GetTarget().y + m_lightHeight;

		//近平面の距離
		float nearPlaneZ = 0.0f;
		//遠平面の距離
		float farPlaneZ;
		CVector3 cameraUp;
		cameraUp = g_camera3D.GetUp();
		//カスケードシャドウの枚数分回す
		for(int i = 0;i < CascadeShadow;i++)
		{
			farPlaneZ = nearPlaneZ + shadowAreaTbl[i];
			
			//ライトビュー行
			for (int i = 0; i < 3; i++)
			{
				m_lightViewMatrix[i] = CMatrix::Identity();
			}
			//画角の半分を取得
			float halfViewAngle = g_camera3D.GetViewAngle()*0.5f;
			//視推台の8頂点をライト空間に変換して、正射影の幅と高さを求める
			float w, h;
			float far_z = -1.0f;

			CVector3 v[8];
			{
				//画角から距離に対する高さの割合を計算
				float t = tan(halfViewAngle);

				CVector3 toUpperNear, toUpperFar;
				toUpperNear = cameraUp * t * nearPlaneZ;
				toUpperFar = cameraUp * t * farPlaneZ;
				t *= g_camera3D.GetAspect();

				//近平面の中央座標を計算
				auto nearPlaneCenterPos = g_camera3D.GetPosition() + g_camera3D.GetForward() * nearPlaneZ;
				//手前右上の座標
				v[0] = nearPlaneCenterPos + g_camera3D.GetRight() * t * nearPlaneZ + toUpperNear;
				//手前右下の座標
				v[1] = v[0] - toUpperNear * 2.0f;
				//手前左上の座標
				v[2] = nearPlaneCenterPos + g_camera3D.GetRight() * -t * nearPlaneZ + toUpperNear;
				//手前左下の座標
				v[3] = v[2] - toUpperNear * 2.0f;

				//遠平面の中央座標を計算
				auto farPlaneCenterPos = g_camera3D.GetPosition() + g_camera3D.GetForward() * farPlaneZ;
				//奥右上の座標
				v[4] = farPlaneCenterPos + g_camera3D.GetRight() * t * farPlaneZ + toUpperFar;
				//奥右下の座標
				v[5] = v[4] - toUpperFar * 2.0f;
				//奥左上の座標
				v[6] = farPlaneCenterPos + g_camera3D.GetRight() * -t * farPlaneZ + toUpperFar;
				//奥左下の座標
				v[7] = v[6] - toUpperFar * 2.0f;

				//ライト行列を作成
				auto viewFrustumCenterPosition = (nearPlaneCenterPos + farPlaneCenterPos) * 0.5f;
				auto lightPos = CalcLightPosition(lightHeight, viewFrustumCenterPosition);

				m_lightViewMatrix[i] = lightViewRot;

				m_lightViewMatrix[i].m[3][0] = lightPos.x;
				m_lightViewMatrix[i].m[3][1] = lightPos.y;
				m_lightViewMatrix[i].m[3][2] = lightPos.z;
				m_lightViewMatrix[i].m[3][3] = 1.0f;

				//ライトビュー完成
				m_lightViewMatrix[i].Inverse(m_lightViewMatrix[i]);

				//視推台を構成する8頂点を計算で来たので、ライト空間に座標変換して、AABBを求める
				CVector3 vMax = { -FLT_MAX,-FLT_MAX,-FLT_MAX };
				CVector3 vMin = { FLT_MAX, FLT_MAX, FLT_MAX };
				for (auto& vInLight : v)
				{
					//ベクトルと行列の乗算
					m_lightViewMatrix[i].Mul(vInLight);

					//最大値を設定
					vMax.Max(vInLight);
					//最小値を設定
					vMin.Min(vInLight);
				}
				w = vMax.x - vMin.x;
				h = vMax.y - vMin.y;
				far_z = vMax.z;
			}

			CMatrix proj = CMatrix::Identity();
			proj.MakeOrthoProjectionMatrix(
				w,
				h,
				far_z / 100.0f,
				far_z
			);
			CMatrix m_mat = CMatrix::Identity();

			m_mat.Mul(m_lightViewMatrix[i], proj);
			m_lightProMatrix[i] = m_mat;
			m_shadowCbEntity.mLVP[i] = m_mat;
			m_shadowCbEntity.shadowAreaDepthInViewSpace[i] = farPlaneZ;
			m_shadowCbEntity.shadowAreaDepthInViewSpaceNear[i] = nearPlaneZ;
			nearPlaneZ = farPlaneZ;
			
			////カメラの上方向が決まったので、ライトビュー行列を計算する
			//m_lightViewMatrix.MakeLookAt
			//(
			//	lightCameraPos,
			//	lightCameraTarget,
			//	lightCameraUpAxis
			//);

			////ライトプロジェクション行列を作成する
			////太陽光からの影を落としたいなら、平行投影行列を作成する
			//m_shadowCbEntity.mLVP[0].MakeOrthoProjectionMatrix
			//(
			//	3000,
			//	3000,
			//	0.1f,
			//	5000.0f
			//);
		}
	}

	void ShadowMap::RenderToShadowMap()
	{
		auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		
		for (int i = 0; i < CascadeShadow; i++)
		{
			ShadowTextureNum = i;
			//レンダリングターゲットを切り替える
			ID3D11RenderTargetView* rts[] =
			{
				m_shadowMapRT[i].GetRenderTargetView()
			};
			d3dDeviceContext->OMSetRenderTargets
			(
				1,
				rts,
				m_shadowMapRT[i].GetDepthStensilView()
			);
			//ビューポートを設定
			d3dDeviceContext->RSSetViewports
			(
				1,
				m_shadowMapRT[i].GetViewport()
			);

			//シャドウマップをクリア
			//一番奥のZは1.0なので、1.0で塗りつぶす
			float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
			m_shadowMapRT[i].ClearRenderTarget(clearColor);

			//シャドウキャスターをシャドウマップにレンダリング。
			for (auto& caster : m_shadowCasters) {
				caster->Draw(
					m_lightViewMatrix[i],
					m_lightProMatrix[i],
					enRenderMode_CreateShadowMap
				);

			}		

		}
		m_shadowCasters.clear();
	}

	void ShadowMap::SendShadowRecieverParamToGpu()
	{
		auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		//定数バッファの内容を更新
		d3dDeviceContext->UpdateSubresource(m_shadowCb.GetBody(), 0, NULL, &m_shadowCbEntity, 0, 0);
		d3dDeviceContext->PSSetConstantBuffers(2, 1, &m_shadowCb.GetBody());
		//テクスチャを送信
		for (int i = 0; i < CascadeShadow; i++)
		{
			m_shadow = GetSRV(i);
			d3dDeviceContext->PSSetShaderResources(2 + i, 1,&m_shadow);
		}
	}

}