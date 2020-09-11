/*!
 * @brief	�X�v���C�g�p�̃V�F�[�_�[�B
 */

cbuffer cb : register(b0){
	float4x4 mvp;		//���[���h�r���[�v���W�F�N�V�����s��B
	float3 mulColor;	//��Z�J���[�B
	float alpha;		//���l
	int isAlpha;		//�摜���̂̃����g�����ǂ���
};
struct VSInput{
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0);	//�J���[�e�N�X�`���B
sampler Sampler : register(s0);

PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = mul( mvp, In.pos );
	psIn.uv = In.uv;
	return psIn;
}
float4 PSMain( PSInput In ) : SV_Target0
{
	float4 FinalColor = colorTexture.Sample(Sampler, In.uv);
	FinalColor.xyz = FinalColor.xyz * mulColor;
	if (isAlpha != 0)
	{
		FinalColor.a = alpha;
	}
	return FinalColor;
}