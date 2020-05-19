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

		//���C�g�̍��W���v�Z����B
		// �������ꂽ��������ʂ����C�g�̍��W���v�Z���܂��B
		// ���C�g�̍��W�̌v�Z�̓��C�g�̍����A���C�g�̕����A�����āA
		// ������̒��S���W(�ߕ��ʂ̒��S���W�Ɖ����ʂ̒��S���W�����񂾐����̒��_���W)
		// ����v�Z����܂��B
		// �@�@���m�����ɂ��Ă̈ꎟ�������������܂��B
		// ���C�g�̍��� = ������̒��S���W.y + ���C�g�̕���.y * ��
		// �� = ( ���C�g�̍��� - ������̒��S���W.y ) / ���C�g�̕���.y
		// �A�@�����g���āA���C�g�̍��W�����߂�B
		// ���C�g�̍��W = ������̒��S���W + ���C�g�̕��� * ��
		//lightHeight		���C�g�̍����B
		//viewFrustomCenterPosition		�������ꂽ������̒��S���W�B
		// �v�Z���ꂽ���C�g�̍��W
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
		int CascadeShadow = 3;		//�V���h�E�}�b�v�̖���
		int ShadowTextureNum = 0;		//�V���h�E�}�b�v�Ɏg���e�N�X�`���̔ԍ�
		RenderTarget m_shadowMapRT[3];
		CVector3 m_lightCameraPos = CVector3::Zero();
		CVector3 m_lightCameraTarget = CVector3::Zero();
		CMatrix m_lightViewMatrix;
		CMatrix m_lightProMatrix[3];
		std::vector<SkinModel*> m_shadowCasters;	//�V���h�E�L���X�^�[�̔z��B
		float m_lightHeight = 2000.0f;				//���C�g�̍����B
		CVector3 lightDir = CVector3::Down();		//���C�g�̌���

	};

}