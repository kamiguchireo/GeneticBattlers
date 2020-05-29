/*!
 * @brief	モデルシェーダー。
 */


/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//アルベドテクスチャ。
Texture2D<float4> albedoTexture : register(t0);	
//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t1);
//シャドウテクスチャ
Texture2D<float4>g_shadowMap0:register(t2);
//シャドウテクスチャ
Texture2D<float4>g_shadowMap1:register(t3);
//シャドウテクスチャ
Texture2D<float4>g_shadowMap2:register(t4);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// 定数バッファ。
/////////////////////////////////////////////////////////////
/*!
 * @brief	頂点シェーダーとピクセルシェーダー用の定数バッファ。
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	float4x4 mLightView;		//ライトビュー行列
	float4x4 mLightProj;		//ライトプロジェクション行列
	int isShadowReciever;		//シャドウレシーバーフラグ
};

static const int NUM_DIRECTION_LIG = 4;
static const int NUM_SHADOW_MAP = 3;
cbuffer LightCb:register(b1)
{
	float3 dligDirection[NUM_DIRECTION_LIG];	//ライトの向き
	float4 dligColor[NUM_DIRECTION_LIG];	//ライトの色
	float3 eyePos;	//視点の座標
	float specPow;	//鏡面反射の絞り
	uint3 ActiveFlag;	//ライトの各アクティブフラグ
}

//シャドウマップ用の定数バッファ
cbuffer ShadowCb : register(b2) {
	float4x4 mLVP[NUM_SHADOW_MAP];		//ライトビュープロジェクション行列。
	float  shadowAreaDepthInViewSpace[NUM_SHADOW_MAP];	//カメラ空間での影を落とすエリアの深度テーブル。
};

/////////////////////////////////////////////////////////////
//各種構造体
/////////////////////////////////////////////////////////////
/*!
 * @brief	スキンなしモデルの頂点構造体。
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float3 Tangent  : TANGENT;				//接ベクトル。
    float2 TexCoord : TEXCOORD0;			//UV座標。
};
/*!
 * @brief	スキンありモデルの頂点構造体。
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float2 TexCoord	: TEXCOORD0;			//UV座標。
    float3 Tangent	: TANGENT;				//接ベクトル。
    uint4  Indices  : BLENDINDICES0;		//この頂点に関連付けされているボーン番号。x,y,z,wの要素に入っている。4ボーンスキニング。
    float4 Weights  : BLENDWEIGHT0;			//この頂点に関連付けされているボーンへのスキンウェイト。x,y,z,wの要素に入っている。4ボーンスキニング。
};

/*!
 * @brief	ピクセルシェーダーの入力。
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 worldPos:TEXCOORD1;
	float4 posInLVP:TEXCOORD2;		//ライトビュープロジェクション空間での座標
	float4 posInview:TEXCOORD3;
	float4 Pos:TEXCOORD4;
};

//シャドウマップ用のピクセルシェーダーへの入力構造体
struct PSInput_ShadowMap {
	float4 Position:SV_POSITION;		//座標
};

//使用するシャドウマップの番号を取得
int GetCascadeIndex(float zInView)
{
	for (int i = 0; i < NUM_SHADOW_MAP; i++) {
		if (zInView < shadowAreaDepthInViewSpace[i]) {
			return i;
		}
	}
	return 0;
}

float CalcShadowPercent(Texture2D<float4> tex, float2 uv, float depth)
{
	float shadow_val = tex.Sample(Sampler, uv).r;
	if (depth > shadow_val.r + 0.01f) {
		return 1.0f;
	}
	return 0.0f;
}

//シャドウを計算
float CalcShadow(float3 worldPos, float zInView)
{
	float shadow = 0.0f;
	//シャドウレシーバーのフラグが1
	if (isShadowReciever == 1)
	{
		//影を落とす。
		//使用するシャドウマップの番号を取得する。
		int cascadeIndex = GetCascadeIndex(zInView);

		float4 posInLVP = mul(mLVP[cascadeIndex], float4(worldPos, 1.0f));
		posInLVP.xyz /= posInLVP.w;

		//深度値を取得
		float depth = min(posInLVP.z, 1.0f);

		//uv座標に変換。
		float2 shadowMapUV = float2(0.5f, -0.5f) * posInLVP.xy + float2(0.5f, 0.5f);

		if (cascadeIndex == 0) {
			shadow = CalcShadowPercent(g_shadowMap0, shadowMapUV, depth);
		}
		else if (cascadeIndex == 1) {
			shadow = CalcShadowPercent(g_shadowMap1, shadowMapUV, depth);
		}
		else if (cascadeIndex == 2) {
			shadow = CalcShadowPercent(g_shadowMap2, shadowMapUV, depth);
		}

	}

	return shadow;
}

/*!
 *@brief	スキン行列を計算。
 */
float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
        w += In.Weights[i];
    }
    
    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
    return skinning;
}
/*!--------------------------------------------------------------------------------------
 * @brief	スキンなしモデル用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	//ローカル座標系からワールド座標系に変換する。
	float4 worldPos = mul(mWorld, In.Position);
	psInput.Pos = worldPos;
	//ワールド座標系からカメラ座標系に変換する。
	psInput.Position = mul(mView, worldPos);
	psInput.posInview = psInput.Position;
	//カメラ座標系からスクリーン座標系に変換する。
	psInput.Position = mul(mProj, psInput.Position);


	if (isShadowReciever == 1) {
		//続いて、ライトビュープロジェクション空間に変換。
		psInput.posInLVP = mul(mLightView, worldPos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}

	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));
	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	スキンありモデル用の頂点シェーダー。
 * 全ての頂点に対してこのシェーダーが呼ばれる。
 * Inは1つの頂点データ。VSInputNmTxWeightsを見てみよう。
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //最後のボーンを計算する。
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
	    pos = mul(skinning, In.Position);
	}
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );

	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
    return psInput;
}

//--------------------------------------------------------------------------------------
// ピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain(PSInput In) : SV_Target0
{
	float4 albedoColor = albedoTexture.Sample(Sampler,In.TexCoord);
	float3 ShadowColor = 0.0;
	//ディレクションライトの拡散反射光を計算する
	float3 lig = 0.0;
	if (ActiveFlag.x == 0)
	{
		for (int i = 0; i < NUM_DIRECTION_LIG; i++) {
			lig += max(0.0f, dot(In.Normal * -1.0f, dligDirection[i])) * dligColor[i];
		}
	}
		float3 DepthColor = 0.0;

		//最終的な色
		float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
		finalColor = albedoColor;

		//鏡面反射の計算
		if (ActiveFlag.y == 0)
		{
			for (int i = 0; i < NUM_DIRECTION_LIG; i++) {
				//ライトを当てる面から視点に伸びるベクトルtoEyeDirを求める。
				float3 toEyeDir = normalize(eyePos - In.worldPos);
				//求めたtoEyeDirの反射ベクトルを求める。
				float3 reflectEyeDir = -toEyeDir + 2 * dot(In.Normal, toEyeDir)* In.Normal;
				//求めた反射ベクトルとディレクションライトの方向との内積を取って、スペキュラの強さを計算する。
				float3 t = max(0.0f, dot(-dligDirection[i], reflectEyeDir));
				//pow関数を使って、スペキュラを絞る。絞りの強さは定数バッファで渡されている。
				float3 spec = pow(t, specPow) * dligColor[i].xyz;
				//⑤ スペキュラ反射が求まったら、ligに加算する。
				//鏡面反射を反射光に加算する。
				lig += spec;
				}
			}
		////シャドウレシーバーのフラグが1
		//if (isShadowReciever == 1)
		//{
		//	//LVP空間から見た時の最も手前の深度値をシャドウマップから取得する
		//	float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
		//	//シャドウマップのUV座標を0.0～1.0にする
		//	shadowMapUV *= float2(0.5f, -0.5f);
		//	shadowMapUV += 0.5f;
		//	//シャドウマップの範囲内かどうかを判定する。
		//	if (shadowMapUV.x > 0.0&&shadowMapUV.x < 1.0
		//		&&shadowMapUV.y > 0.0&&shadowMapUV.y < 1.0
		//		)
		//	{
		//		//LVP空間での深度値を計算
		//		float zInLVP = In.posInLVP.z / In.posInLVP.w;
		//		//シャドウマップに書き込まれている深度値を取得
		//		float zInShadowMap = g_shadowMap.Sample(Sampler, shadowMapUV);

		//		if (zInLVP > zInShadowMap + 0.01f)
		//		{
		//			//影が落ちているので、光を弱くする
		//			lig *= 0.5f;
		//		}


		//	}
		//}
		float f;
		f = CalcShadow(In.Pos, In.posInview.z);
		if (f == 1.0f)
		{
			lig *= 0.5f;
		}

		if (ActiveFlag.x == 0)
		{
			finalColor.xyz = albedoColor.xyz * lig;
		}

		return finalColor;
		//if (isShadowReciever == 1)
		//{
		//	albedoColor.xyz *= lig;
		//}
		//if (ActiveFlag.x == 0)
		//{
		//	return finalColor;
		//}
		//else
		//{
		//	return albedoColor;
		//}
}

//--------------------------------------------------------------------------------------
// シルエット描画用のピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain_Silhouette(PSInput In) : SV_Target0
{
	return float4(0.5f, 0.5f, 0.5f, 1.0f);
}

//シャドウマップ生成用の頂点シェーダー
PSInput_ShadowMap VSMain_ShadowMap(VSInputNmTxVcTangent In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}

//ピクセルシェーダーのエントリ関数
float4 PSMain_ShadowMap(PSInput_ShadowMap In): SV_Target0
{
	//射影空間でのZ値を返す
	return In.Position.z / In.Position.w;
}

