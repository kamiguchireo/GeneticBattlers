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

		//lightCameraPos		���C�g�̈ʒu
		//lightCameraTarget		���C�g�̃^�[�Q�b�g
		void Update(CVector3 lightCameraPos, CVector3 lightCameraTarget);
		
		//�V���h�E�}�b�v�ɉe���������ރ^�C�~���O�ŌĂ�ł�������
		void RenderToShadowMap();

		ID3D11ShaderResourceView*GetSRV(int i)const
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
	
		CMatrix GetLightViewMatrix(int i)const
		{
			return m_lightViewMatrix[i];
		}
		CMatrix GetLigthProjMatrix(int i)const
		{
			return m_lightProMatrix[i];
		}

		//�G���W�������Ŏg�p���Ă��܂��B
		//�g�p���Ȃ��ł�������
		int GetShadowTextureNum()
		{
			ShadowTextureNum++;
			if (ShadowTextureNum > CascadeShadow - 1)
			{
				ShadowTextureNum = 0;
			}
			return ShadowTextureNum;
		}
		
		//�G���W�������Ŏg�p���Ă��܂��B
		//�g�p���Ȃ��ł�������
		int GetCascadeShadow()const
		{
			return CascadeShadow;
		}

		//�V���h�E�}�b�v�̏����V�F�[�_�[�ɑ���܂�
		//�V���h�E�}�b�v�̏������݂��I�������ɓǂ�ł�������
		void SendShadowRecieverParamToGpu();

		//�V���h�E�}�b�v�̍����̍ő�l�����߂Ă�������
		//�����l�ł�500.0f�������Ă��܂�
		//�r���ȂǍ��������̉e���o�������ꍇ�͂��̒l��傫�����Ă�������
		void SetMaxheight(float f)
		{
			maxheight = f;
		}

		//�͈͂����߂Ă�������
		//�����l�ł�{ 1000.0f,2000.0f,3000.0f }�������Ă��܂�
		//���̏ꍇ�J�����r���[�ł�z�l��1000.0f,3000.0f,6000.0f���V���h�E�}�b�v�̋��E�ƂȂ�܂�
		void SetRange(CVector3 range)
		{
			m_range = range;
		}

		//�L���X�^�[���c�邱�Ƃɂ�鎟�t���[���̃|�C���^�Q�Ƃŗ�O�X���[�����ꍇ�͔C�ӂ̃^�C�~���O�ŌĂ�ł�������
		void CasterClear()
		{
			m_shadowCasters.clear();
		}
	private:
		struct SShadowCb {
			CMatrix mLVP[3];
			float shadowAreaDepthInViewSpace[3];	//�J������Ԃł̉e�𗎂Ƃ��G���A�̐[�x�e�[�u���B
		};
		int CascadeShadow = 3;		//�V���h�E�}�b�v�̖���
		int ShadowTextureNum = 0;		//�V���h�E�}�b�v�Ɏg���e�N�X�`���̔ԍ�
		RenderTarget m_shadowMapRT[3];
		CVector3 m_lightCameraPos = CVector3::Zero();
		CVector3 m_lightCameraTarget = CVector3::Zero();
		CMatrix m_lightViewMatrix[3];
		CMatrix m_lightProMatrix[3];
		std::vector<SkinModel*> m_shadowCasters;	//�V���h�E�L���X�^�[�̔z��B
		float m_lightHeight = 1000.0f;				//���C�g�̍����B
		CVector3 lightDir = CVector3::Down();		//���C�g�̌���
		SShadowCb m_shadowCbEntity;
		ConstantBuffer m_shadowCb;		//�e�𗎂Ƃ����Ɏg�p����萔�o�b�t�@�B
		ID3D11ShaderResourceView* m_shadow = nullptr;
		float maxheight = 500.0f;
		CVector3 m_range = { 500.0f,1000.0f,2000.0f };
		ID3D11RenderTargetView* oldRenderTargetView = nullptr;
		ID3D11DepthStencilView* oldDepthStencilView = nullptr;
		const int TexResolution = 2048;		//�V���h�E�}�b�v�e�N�X�`���̉𑜓x
		const float UpBoundary = 0.99998f;		//�^�ォ�ǂ����̋��E
		const float DistBoundary = 0.0001f;		//�������E�̋��E
		const float InitNearPlane = 0.0f;		//NearPlane�̏����l
		const int NumLightViewMat = 3;		//���C�g�r���[�s��̐�
	};

}