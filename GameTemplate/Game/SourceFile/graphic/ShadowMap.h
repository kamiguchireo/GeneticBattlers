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

		//lightCameraPos		���C�g�̈ʒu
		//lightCameraTarget		���C�g�̃^�[�Q�b�g
		void Update(CVector3 lightCameraPos, CVector3 lightCameraTarget);
		
		void RenderToShadowMap();
		ID3D11ShaderResourceView*GetSRV()
		{
			return m_shadowMapRT.GetSRV();
		}
		
		//�V���h�E�L���X�^�[��o�^
		//RenderToShadowMap���Ăяo������o�^�������X�g�̓N���A�����̂�
		//��ɉe���o�����������疈�t���[���Ă�ł�������
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
		std::vector<SkinModel*> m_shadowCasters;	//�V���h�E�L���X�^�[�̔z��B
	};

}