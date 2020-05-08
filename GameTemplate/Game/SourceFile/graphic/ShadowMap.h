#pragma once
#include "SourceFile/graphic/RenderTarget.h"

class SkinModel;
namespace Engine {
	class ShadowMap
	{
	public:
		ShadowMap();
		~ShadowMap();

		void ShadowMapRTCreate();

		//lightCameraPos		ライトの位置
		//lightCameraTarget		ライトのターゲット
		void Update(CVector3 lightCameraPos, CVector3 lightCameraTarget);
		
		void RenderToShadowMap();
		ID3D11ShaderResourceView*GetSRV(int i)
		{
			return m_shadowMapRT[i].GetSRV();
		}
		
		//シャドウキャスターを登録
		//RenderToShadowMapを呼び出したら登録したリストはクリアされるので
		//常に影を出したかったら毎フレーム呼んでください
		void RegistShadowCaster(SkinModel* shadowCaster)
		{
			m_shadowCasters.push_back(shadowCaster);
		}

		CMatrix GetLightViewMatrix(int i)
		{
			return m_lightViewMatrix[i];
		}
		CMatrix GetLigthProjMatrix(int i)
		{
			return m_lightProMatrix[i];
		}

		int GetShadowTextureNum()
		{
			return ShadowTextureNum;
		}
	private:
		int CascadeShadow = 4;		//シャドウマップの枚数
		int ShadowTextureNum = 0;		//シャドウマップに使うテクスチャの番号
		RenderTarget m_shadowMapRT[4];
		CVector3 m_lightCameraPos = CVector3::Zero();
		CVector3 m_lightCameraTarget = CVector3::Zero();
		CMatrix m_lightViewMatrix[4];
		CMatrix m_lightProMatrix[4];
		std::vector<SkinModel*> m_shadowCasters;	//シャドウキャスターの配列。
		float ViewAngle = 0.0f;		//カメラの画角
		CVector3 m_shadowMapPos = CVector3::Zero();		//シャドウマップのポジション
		float m_cameraDist = 0.0f;		//カメラの距離
		CVector3 m_cameraPos = CVector3::Zero();		//カメラの位置
		CVector3 m_cameraTarget = CVector3::Zero();		//カメラの注視点
	};

}