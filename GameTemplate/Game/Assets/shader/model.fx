/*!
 * @brief	���f���V�F�[�_�[�B
 */


/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//�A���x�h�e�N�X�`���B
Texture2D<float4> albedoTexture : register(t0);	
//�{�[���s��
StructuredBuffer<float4x4> boneMatrix : register(t1);
//�V���h�E�e�N�X�`��
Texture2D<float4>g_shadowMap0:register(t2);
//�V���h�E�e�N�X�`��
Texture2D<float4>g_shadowMap1:register(t3);
//�V���h�E�e�N�X�`��
Texture2D<float4>g_shadowMap2:register(t4);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// �萔�o�b�t�@�B
/////////////////////////////////////////////////////////////
/*!
 * @brief	���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�B
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	float4x4 mLightView;		//���C�g�r���[�s��
	float4x4 mLightProj;		//���C�g�v���W�F�N�V�����s��
	int isShadowReciever;		//�V���h�E���V�[�o�[�t���O
};

static const int NUM_DIRECTION_LIG = 4;
static const int NUM_SHADOW_MAP = 3;
cbuffer LightCb:register(b1)
{
	float3 dligDirection[NUM_DIRECTION_LIG];	//���C�g�̌���
	float4 dligColor[NUM_DIRECTION_LIG];	//���C�g�̐F
	float3 eyePos;	//���_�̍��W
	float specPow;	//���ʔ��˂̍i��
	uint3 ActiveFlag;	//���C�g�̊e�A�N�e�B�u�t���O
}

//�V���h�E�}�b�v�p�̒萔�o�b�t�@
cbuffer ShadowCb : register(b2) {
	float4x4 mLVP[NUM_SHADOW_MAP];		//���C�g�r���[�v���W�F�N�V�����s��B
	float  shadowAreaDepthInViewSpace[NUM_SHADOW_MAP];	//�J������Ԃł̉e�𗎂Ƃ��G���A�̐[�x�e�[�u���B
};

/////////////////////////////////////////////////////////////
//�e��\����
/////////////////////////////////////////////////////////////
/*!
 * @brief	�X�L���Ȃ����f���̒��_�\���́B
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float3 Tangent  : TANGENT;				//�ڃx�N�g���B
    float2 TexCoord : TEXCOORD0;			//UV���W�B
};
/*!
 * @brief	�X�L�����胂�f���̒��_�\���́B
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float2 TexCoord	: TEXCOORD0;			//UV���W�B
    float3 Tangent	: TANGENT;				//�ڃx�N�g���B
    uint4  Indices  : BLENDINDICES0;		//���̒��_�Ɋ֘A�t������Ă���{�[���ԍ��Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
    float4 Weights  : BLENDWEIGHT0;			//���̒��_�Ɋ֘A�t������Ă���{�[���ւ̃X�L���E�F�C�g�Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
};

/*!
 * @brief	�s�N�Z���V�F�[�_�[�̓��́B
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 worldPos:TEXCOORD1;
	float4 posInLVP:TEXCOORD2;		//���C�g�r���[�v���W�F�N�V������Ԃł̍��W
	float4 posInview:TEXCOORD3;
	float4 Pos:TEXCOORD4;
};

//�V���h�E�}�b�v�p�̃s�N�Z���V�F�[�_�[�ւ̓��͍\����
struct PSInput_ShadowMap {
	float4 Position:SV_POSITION;		//���W
};

//�g�p����V���h�E�}�b�v�̔ԍ����擾
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

//�V���h�E���v�Z
float CalcShadow(float3 worldPos, float zInView)
{
	float shadow = 0.0f;
	//�V���h�E���V�[�o�[�̃t���O��1
	if (isShadowReciever == 1)
	{
		//�e�𗎂Ƃ��B
		//�g�p����V���h�E�}�b�v�̔ԍ����擾����B
		int cascadeIndex = GetCascadeIndex(zInView);

		float4 posInLVP = mul(mLVP[cascadeIndex], float4(worldPos, 1.0f));
		posInLVP.xyz /= posInLVP.w;

		//�[�x�l���擾
		float depth = min(posInLVP.z, 1.0f);

		//uv���W�ɕϊ��B
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
 *@brief	�X�L���s����v�Z�B
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
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	//���[�J�����W�n���烏�[���h���W�n�ɕϊ�����B
	float4 worldPos = mul(mWorld, In.Position);
	psInput.Pos = worldPos;
	//���[���h���W�n����J�������W�n�ɕϊ�����B
	psInput.Position = mul(mView, worldPos);
	psInput.posInview = psInput.Position;
	//�J�������W�n����X�N���[�����W�n�ɕϊ�����B
	psInput.Position = mul(mProj, psInput.Position);


	if (isShadowReciever == 1) {
		//�����āA���C�g�r���[�v���W�F�N�V������Ԃɕϊ��B
		psInput.posInLVP = mul(mLightView, worldPos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}

	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));
	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	�X�L�����胂�f���p�̒��_�V�F�[�_�[�B
 * �S�Ă̒��_�ɑ΂��Ă��̃V�F�[�_�[���Ă΂��B
 * In��1�̒��_�f�[�^�BVSInputNmTxWeights�����Ă݂悤�B
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//��������X�L�j���O���s���Ă���ӏ��B
	//�X�L���s����v�Z�B
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
			//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
			//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //�Ō�̃{�[�����v�Z����B
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//���_���W�ɃX�L���s�����Z���āA���_�����[���h��Ԃɕϊ��B
		//mul�͏�Z���߁B
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
// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain(PSInput In) : SV_Target0
{
	float4 albedoColor = albedoTexture.Sample(Sampler,In.TexCoord);
	float3 ShadowColor = 0.0;
	//�f�B���N�V�������C�g�̊g�U���ˌ����v�Z����
	float3 lig = 0.0;
	if (ActiveFlag.x == 0)
	{
		for (int i = 0; i < NUM_DIRECTION_LIG; i++) {
			lig += max(0.0f, dot(In.Normal * -1.0f, dligDirection[i])) * dligColor[i];
		}
	}
		float3 DepthColor = 0.0;

		//�ŏI�I�ȐF
		float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
		finalColor = albedoColor;

		//���ʔ��˂̌v�Z
		if (ActiveFlag.y == 0)
		{
			for (int i = 0; i < NUM_DIRECTION_LIG; i++) {
				//���C�g�𓖂Ă�ʂ��王�_�ɐL�т�x�N�g��toEyeDir�����߂�B
				float3 toEyeDir = normalize(eyePos - In.worldPos);
				//���߂�toEyeDir�̔��˃x�N�g�������߂�B
				float3 reflectEyeDir = -toEyeDir + 2 * dot(In.Normal, toEyeDir)* In.Normal;
				//���߂����˃x�N�g���ƃf�B���N�V�������C�g�̕����Ƃ̓��ς�����āA�X�y�L�����̋������v�Z����B
				float3 t = max(0.0f, dot(-dligDirection[i], reflectEyeDir));
				//pow�֐����g���āA�X�y�L�������i��B�i��̋����͒萔�o�b�t�@�œn����Ă���B
				float3 spec = pow(t, specPow) * dligColor[i].xyz;
				//�D �X�y�L�������˂����܂�����Alig�ɉ��Z����B
				//���ʔ��˂𔽎ˌ��ɉ��Z����B
				lig += spec;
				}
			}
		////�V���h�E���V�[�o�[�̃t���O��1
		//if (isShadowReciever == 1)
		//{
		//	//LVP��Ԃ��猩�����̍ł���O�̐[�x�l���V���h�E�}�b�v����擾����
		//	float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
		//	//�V���h�E�}�b�v��UV���W��0.0�`1.0�ɂ���
		//	shadowMapUV *= float2(0.5f, -0.5f);
		//	shadowMapUV += 0.5f;
		//	//�V���h�E�}�b�v�͈͓̔����ǂ����𔻒肷��B
		//	if (shadowMapUV.x > 0.0&&shadowMapUV.x < 1.0
		//		&&shadowMapUV.y > 0.0&&shadowMapUV.y < 1.0
		//		)
		//	{
		//		//LVP��Ԃł̐[�x�l���v�Z
		//		float zInLVP = In.posInLVP.z / In.posInLVP.w;
		//		//�V���h�E�}�b�v�ɏ������܂�Ă���[�x�l���擾
		//		float zInShadowMap = g_shadowMap.Sample(Sampler, shadowMapUV);

		//		if (zInLVP > zInShadowMap + 0.01f)
		//		{
		//			//�e�������Ă���̂ŁA�����キ����
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
// �V���G�b�g�`��p�̃s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain_Silhouette(PSInput In) : SV_Target0
{
	return float4(0.5f, 0.5f, 0.5f, 1.0f);
}

//�V���h�E�}�b�v�����p�̒��_�V�F�[�_�[
PSInput_ShadowMap VSMain_ShadowMap(VSInputNmTxVcTangent In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}

//�s�N�Z���V�F�[�_�[�̃G���g���֐�
float4 PSMain_ShadowMap(PSInput_ShadowMap In): SV_Target0
{
	//�ˉe��Ԃł�Z�l��Ԃ�
	return In.Position.z / In.Position.w;
}

