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

		//ライトの座標を計算する。
		// 分割された視推台を写すライトの座標を計算します。
		// ライトの座標の計算はライトの高さ、ライトの方向、そして、
		// 視推台の中心座標(近平面の中心座標と遠平面の中心座標を結んだ線分の中点座標)
		// から計算されます。
		// ①　未知数αについての一次方程式を解きます。
		// ライトの高さ = 視推台の中心座標.y + ライトの方向.y * α
		// α = ( ライトの高さ - 視推台の中心座標.y ) / ライトの方向.y
		// ②　αを使って、ライトの座標を求める。
		// ライトの座標 = 視推台の中心座標 + ライトの方向 * α
		//lightHeight		ライトの高さ。
		//viewFrustomCenterPosition		分割された視推台の中心座標。
		// 計算されたライトの座標
		CVector3 CalcLightPosition(float lightHeight, CVector3 viewFrustomCenterPosition);
	
		CMatrix GetLightViewMatrix()
		{
			return m_lightViewMatrix;
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
		int CascadeShadow = 3;		//シャドウマップの枚数
		int ShadowTextureNum = 0;		//シャドウマップに使うテクスチャの番号
		RenderTarget m_shadowMapRT[3];
		CVector3 m_lightCameraPos = CVector3::Zero();
		CVector3 m_lightCameraTarget = CVector3::Zero();
		CMatrix m_lightViewMatrix;
		CMatrix m_lightProMatrix[3];
		std::vector<SkinModel*> m_shadowCasters;	//シャドウキャスターの配列。
		float m_lightHeight = 2000.0f;				//ライトの高さ。
		CVector3 lightDir = CVector3::Down();		//ライトの向き

	};

}