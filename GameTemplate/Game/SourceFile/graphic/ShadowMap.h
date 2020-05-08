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
		ID3D11ShaderResourceView*GetSRV(int i)
		{
			return m_shadowMapRT[i].GetSRV();
		}
		
		//�V���h�E�L���X�^�[��o�^
		//RenderToShadowMap���Ăяo������o�^�������X�g�̓N���A�����̂�
		//��ɉe���o�����������疈�t���[���Ă�ł�������
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
		int CascadeShadow = 4;		//�V���h�E�}�b�v�̖���
		int ShadowTextureNum = 0;		//�V���h�E�}�b�v�Ɏg���e�N�X�`���̔ԍ�
		RenderTarget m_shadowMapRT[4];
		CVector3 m_lightCameraPos = CVector3::Zero();
		CVector3 m_lightCameraTarget = CVector3::Zero();
		CMatrix m_lightViewMatrix[4];
		CMatrix m_lightProMatrix[4];
		std::vector<SkinModel*> m_shadowCasters;	//�V���h�E�L���X�^�[�̔z��B
		float ViewAngle = 0.0f;		//�J�����̉�p
		CVector3 m_shadowMapPos = CVector3::Zero();		//�V���h�E�}�b�v�̃|�W�V����
		float m_cameraDist = 0.0f;		//�J�����̋���
		CVector3 m_cameraPos = CVector3::Zero();		//�J�����̈ʒu
		CVector3 m_cameraTarget = CVector3::Zero();		//�J�����̒����_
	};

}