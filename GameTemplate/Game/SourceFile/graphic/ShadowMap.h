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
		ID3D11ShaderResourceView*GetSRV()
		{
			return m_shadowMapRT.GetSRV();
		}
		
		//シャドウキャスターを登録
		//RenderToShadowMapを呼び出したら登録したリストはクリアされるので
		//常に影を出したかったら毎フレーム呼んでください
		void RegistShadowCaster(SkinModel* shadowCaster)
		{
			m_shadowCasters.push_back(shadowCaster);
		}
	private:
		RenderTarget m_shadowMapRT;
		CVector3 m_lightCameraPos = CVector3::Zero();
		CVector3 m_lightCameraTarget = CVector3::Zero();
		CMatrix m_lightViewMatrix = CMatrix::Identity();
		CMatrix m_lightProMatrix = CMatrix::Identity();
		std::vector<SkinModel*> m_shadowCasters;	//シャドウキャスターの配列。
	};

}