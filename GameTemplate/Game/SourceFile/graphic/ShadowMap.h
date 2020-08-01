#pragma once
#include "SourceFile/graphic/RenderTarget.h"
#include "SourceFile/Noncopyable.h"

class SkinModel;
namespace Engine {
	class ShadowMap:Engine::Noncopyable
	{
	public:
		ShadowMap();
		~ShadowMap();

		void ShadowMapRTCreate();

		//lightCameraPos		ライトの位置
		//lightCameraTarget		ライトのターゲット
		void Update(CVector3 lightCameraPos, CVector3 lightCameraTarget);
		
		//シャドウマップに影を書き込むタイミングで呼んでください
		void RenderToShadowMap();

		ID3D11ShaderResourceView*GetSRV(int i)const
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
	
		CMatrix GetLightViewMatrix(int i)const
		{
			return m_lightViewMatrix[i];
		}
		CMatrix GetLigthProjMatrix(int i)const
		{
			return m_lightProMatrix[i];
		}

		//エンジン内部で使用しています。
		//使用しないでください
		int GetShadowTextureNum()
		{
			ShadowTextureNum++;
			if (ShadowTextureNum > CascadeShadow - 1)
			{
				ShadowTextureNum = 0;
			}
			return ShadowTextureNum;
		}
		
		//エンジン内部で使用しています。
		//使用しないでください
		int GetCascadeShadow()const
		{
			return CascadeShadow;
		}

		//シャドウマップの情報をシェーダーに送ります
		//シャドウマップの書き込みが終わった後に読んでください
		void SendShadowRecieverParamToGpu();

		//シャドウマップの高さの最大値を決めてください
		//初期値では500.0fが入っています
		//ビルなど高い建物の影を出したい場合はこの値を大きくしてください
		void SetMaxheight(float f)
		{
			maxheight = f;
		}

		//範囲を決めてください
		//初期値では{ 1000.0f,2000.0f,3000.0f }が入っています
		//この場合カメラビューでのz値が1000.0f,3000.0f,6000.0fがシャドウマップの境界となります
		void SetRange(CVector3 range)
		{
			m_range = range;
		}

		//キャスターが残ることによる次フレームのポインタ参照で例外スローされる場合は任意のタイミングで呼んでください
		void CasterClear()
		{
			m_shadowCasters.clear();
		}
	private:
		struct SShadowCb {
			CMatrix mLVP[3];
			float shadowAreaDepthInViewSpace[3];	//カメラ空間での影を落とすエリアの深度テーブル。
		};
		int CascadeShadow = 3;		//シャドウマップの枚数
		int ShadowTextureNum = 0;		//シャドウマップに使うテクスチャの番号
		RenderTarget m_shadowMapRT[3];
		CVector3 m_lightCameraPos = CVector3::Zero();
		CVector3 m_lightCameraTarget = CVector3::Zero();
		CMatrix m_lightViewMatrix[3];
		CMatrix m_lightProMatrix[3];
		std::vector<SkinModel*> m_shadowCasters;	//シャドウキャスターの配列。
		float m_lightHeight = 1000.0f;				//ライトの高さ。
		CVector3 lightDir = CVector3::Down();		//ライトの向き
		SShadowCb m_shadowCbEntity;
		ConstantBuffer m_shadowCb;		//影を落とす時に使用する定数バッファ。
		ID3D11ShaderResourceView* m_shadow = nullptr;
		float maxheight = 500.0f;
		CVector3 m_range = { 500.0f,1000.0f,2000.0f };
		ID3D11RenderTargetView* oldRenderTargetView = nullptr;
		ID3D11DepthStencilView* oldDepthStencilView = nullptr;
		const int TexResolution = 2048;		//シャドウマップテクスチャの解像度
		const float UpBoundary = 0.99998f;		//真上かどうかの境界
		const float DistBoundary = 0.0001f;		//距離限界の境界
		const float InitNearPlane = 0.0f;		//NearPlaneの初期値
		const int NumLightViewMat = 3;		//ライトビュー行列の数
	};

}