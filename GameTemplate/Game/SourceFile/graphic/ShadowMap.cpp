#include "stdafx.h"
#include "ShadowMap.h"

namespace Engine {
	ShadowMap::ShadowMap()
	{

	}

	ShadowMap::~ShadowMap()
	{

	}

	void ShadowMap::ShadowMapRTCreate()
	{
		//�V���h�E�}�b�v�����p�̃����_�����O�^�[�Q�b�g�����
		//�𑜓x��2048*2048
		//�e�N�X�`���̃t�H�[�}�b�g��R�����݂̂�32�r�b�g��Float�^
		m_shadowMapRT.Create
		(
			2048,
			2048,
			DXGI_FORMAT_R32_FLOAT
		);
	}
	void ShadowMap::Update(CVector3 lightCameraPos, CVector3 lightCameraTarget)
	{
		//���C�g�̕������v�Z����
		auto lightDir = lightCameraTarget - lightCameraPos;
		if (lightDir.Length() < 0.0001f)
		{
			//���C�g�J�����̒����_�Ǝ��_���߂�����
			//�����Ƌ����𗣂��Ă�������
			throw;
		}
		
		//���K�����ĕ����x�N�g���ɕϊ�����
		lightDir.Normalize();
		
		//���C�g�̕����ɂ���āA���C�g�J�����̏���������߂�
		CVector3 lightCameraUpAxis;
		if (fabsf(lightDir.y) > 0.99998f)
		{
			//�قڐ^��or�^���������Ă���̂ŁA1,0,0��������Ƃ���
			lightCameraUpAxis = CVector3::AxisX();
		}
		else
		{
			//�^��������Ă��Ȃ��Ƃ��́A0,1,0��������Ƃ���
			lightCameraUpAxis = CVector3::AxisY();
		}
		
		//�J�����̏���������܂����̂ŁA���C�g�r���[�s����v�Z����
		m_lightViewMatrix.MakeLookAt
		(
			lightCameraPos,
			lightCameraTarget,
			lightCameraUpAxis
		);

		//���C�g�v���W�F�N�V�����s����쐬����
		//���z������̉e�𗎂Ƃ������Ȃ�A���s���e�s����쐬����
		m_lightProMatrix.MakeOrthoProjectionMatrix
		(
			3000,
			3000,
			0.1f,
			5000.0f
		);
	}

	void ShadowMap::RenderToShadowMap()
	{
		auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		//�����_�����O�^�[�Q�b�g��؂�ւ���
		ID3D11RenderTargetView* rts[] = 
		{
			m_shadowMapRT.GetRenderTargetView()
		};
		d3dDeviceContext->OMSetRenderTargets
		(
			1,
			rts,
			m_shadowMapRT.GetDepthStensilView()
		);
		//�r���[�|�[�g��ݒ�
		d3dDeviceContext->RSSetViewports
		(
			1,
			m_shadowMapRT.GetViewport()
		);

		//�V���h�E�}�b�v���N���A
		//��ԉ���Z��1.0�Ȃ̂ŁA1.0�œh��Ԃ�
		float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
		m_shadowMapRT.ClearRenderTarget(clearColor);

		//�V���h�E�L���X�^�[���V���h�E�}�b�v�Ƀ����_�����O�B
		for (auto& caster : m_shadowCasters) {
			caster->Draw(
				m_lightViewMatrix,
				m_lightProMatrix,
				enRenderMode_CreateShadowMap
			);
		}
		m_shadowCasters.clear();
	}
}