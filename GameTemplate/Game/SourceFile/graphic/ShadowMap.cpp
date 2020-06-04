#include "stdafx.h"
#include "ShadowMap.h"

namespace Engine {
	ShadowMap::ShadowMap()
	{

	}

	ShadowMap::~ShadowMap()
	{

	}


	CVector3 ShadowMap::CalcLightPosition(float lightHeight, CVector3 viewFrustomCenterPosition)
	{
		auto alpha = (lightHeight - viewFrustomCenterPosition.y) / lightDir.y;
		auto lightPos = viewFrustomCenterPosition + lightDir * alpha;
		return lightPos;
	}

	void ShadowMap::ShadowMapRTCreate()
	{

		for (int i = 0; i < CascadeShadow; i++)
		{
			//�V���h�E�}�b�v�����p�̃����_�����O�^�[�Q�b�g�����
			//�𑜓x��2048*2048
			//�e�N�X�`���̃t�H�[�}�b�g��R�����݂̂�32�r�b�g��Float�^
			m_shadowMapRT[i].Create
			(
				2048,
				2048,
				DXGI_FORMAT_R32_FLOAT
			);

		}

		//�萔�o�b�t�@���쐬
		m_shadowCb.Create(&m_shadowCbEntity, sizeof(m_shadowCbEntity));

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
			//�قڐ^��or�^���������Ă���
			lightCameraUpAxis = CVector3::AxisX();
			lightCameraUpAxis.Cross(lightDir, CVector3::Right());
			//lightCameraUpAxis = CVector3::Right();
		}
		else
		{
			//�^��������Ă��Ȃ�
			lightCameraUpAxis = CVector3::AxisY();
			lightCameraUpAxis.Cross(lightDir, CVector3::Up());
			//lightCameraUpAxis = CVector3::Up();
		}
		//���C�g�̉E����
		CVector3 lightViewRight;
		lightViewRight.Cross(lightCameraUpAxis, lightDir);
		//���K��
		lightViewRight.Normalize();
		
		CMatrix lightViewRot;
		//���C�g�r���[�̉���ݒ肷��
		lightViewRot.m[0][0] = lightViewRight.x;
		lightViewRot.m[0][1] = lightViewRight.y;
		lightViewRot.m[0][2] = lightViewRight.z;
		lightViewRot.m[0][3] = 0.0f;
		//���C�g�r���[�̏��ݒ肷��B
		lightViewRot.m[1][0] = lightCameraUpAxis.x;
		lightViewRot.m[1][1] = lightCameraUpAxis.y;
		lightViewRot.m[1][2] = lightCameraUpAxis.z;
		lightViewRot.m[1][3] = 0.0f;
		//���C�g�r���[�̑O��ݒ肷��B
		lightViewRot.m[2][0] = lightDir.x;
		lightViewRot.m[2][1] = lightDir.y;
		lightViewRot.m[2][2] = lightDir.z;
		lightViewRot.m[2][3] = 0.0f;
		float shadowAreaTbl[] = {
			1000.0f,//m_lightHeight * 0.8f,
			2000.0f,//m_lightHeight * 1.6f,
			3000.0f//m_lightHeight * 3.6f
		};

		//���C�g�r���[�̍������v�Z
		float lightHeight = g_camera3D.GetTarget().y + m_lightHeight;

		//�ߕ��ʂ̋���
		float nearPlaneZ = 0.0f;
		//�����ʂ̋���
		float farPlaneZ;
		CVector3 cameraUp;
		cameraUp = g_camera3D.GetUp();
		//�J�X�P�[�h�V���h�E�̖�������
		for(int i = 0;i < CascadeShadow;i++)
		{
			farPlaneZ = nearPlaneZ + shadowAreaTbl[i];
			
			//���C�g�r���[�s
			for (int i = 0; i < 3; i++)
			{
				m_lightViewMatrix[i] = CMatrix::Identity();
			}
			//��p�̔������擾
			float halfViewAngle = g_camera3D.GetViewAngle()*0.5f;
			//�������8���_�����C�g��Ԃɕϊ����āA���ˉe�̕��ƍ��������߂�
			float w, h;
			float far_z = -1.0f;

			CVector3 v[8];
			{
				//��p���狗���ɑ΂��鍂���̊������v�Z
				float t = tan(halfViewAngle);

				CVector3 toUpperNear, toUpperFar;
				toUpperNear = cameraUp * t * nearPlaneZ;
				toUpperFar = cameraUp * t * farPlaneZ;
				t *= g_camera3D.GetAspect();

				//�ߕ��ʂ̒������W���v�Z
				auto nearPlaneCenterPos = g_camera3D.GetPosition() + g_camera3D.GetForward() * nearPlaneZ;
				//��O�E��̍��W
				v[0] = nearPlaneCenterPos + g_camera3D.GetRight() * t * nearPlaneZ + toUpperNear;
				//��O�E���̍��W
				v[1] = v[0] - toUpperNear * 2.0f;
				//��O����̍��W
				v[2] = nearPlaneCenterPos + g_camera3D.GetRight() * -t * nearPlaneZ + toUpperNear;
				//��O�����̍��W
				v[3] = v[2] - toUpperNear * 2.0f;

				//�����ʂ̒������W���v�Z
				auto farPlaneCenterPos = g_camera3D.GetPosition() + g_camera3D.GetForward() * farPlaneZ;
				//���E��̍��W
				v[4] = farPlaneCenterPos + g_camera3D.GetRight() * t * farPlaneZ + toUpperFar;
				//���E���̍��W
				v[5] = v[4] - toUpperFar * 2.0f;
				//������̍��W
				v[6] = farPlaneCenterPos + g_camera3D.GetRight() * -t * farPlaneZ + toUpperFar;
				//�������̍��W
				v[7] = v[6] - toUpperFar * 2.0f;

				//���C�g�s����쐬
				auto viewFrustumCenterPosition = (nearPlaneCenterPos + farPlaneCenterPos) * 0.5f;
				auto lightPos = CalcLightPosition(lightHeight, viewFrustumCenterPosition);

				m_lightViewMatrix[i] = lightViewRot;

				m_lightViewMatrix[i].m[3][0] = lightPos.x;
				m_lightViewMatrix[i].m[3][1] = lightPos.y;
				m_lightViewMatrix[i].m[3][2] = lightPos.z;
				m_lightViewMatrix[i].m[3][3] = 1.0f;

				//���C�g�r���[����
				m_lightViewMatrix[i].Inverse(m_lightViewMatrix[i]);

				//��������\������8���_���v�Z�ŗ����̂ŁA���C�g��Ԃɍ��W�ϊ����āAAABB�����߂�
				CVector3 vMax = { -FLT_MAX,-FLT_MAX,-FLT_MAX };
				CVector3 vMin = { FLT_MAX, FLT_MAX, FLT_MAX };
				for (auto& vInLight : v)
				{
					//�x�N�g���ƍs��̏�Z
					m_lightViewMatrix[i].Mul(vInLight);

					//�ő�l��ݒ�
					vMax.Max(vInLight);
					//�ŏ��l��ݒ�
					vMin.Min(vInLight);
				}
				w = vMax.x - vMin.x;
				h = vMax.y - vMin.y;
				far_z = vMax.z;
			}

			CMatrix proj = CMatrix::Identity();
			proj.MakeOrthoProjectionMatrix(
				w,
				h,
				far_z / 100.0f,
				far_z
			);
			CMatrix m_mat = CMatrix::Identity();

			m_mat.Mul(m_lightViewMatrix[i], proj);
			m_lightProMatrix[i] = m_mat;
			m_shadowCbEntity.mLVP[i] = m_mat;
			m_shadowCbEntity.shadowAreaDepthInViewSpace[i] = farPlaneZ;
			m_shadowCbEntity.shadowAreaDepthInViewSpaceNear[i] = nearPlaneZ;
			nearPlaneZ = farPlaneZ;
			
			////�J�����̏���������܂����̂ŁA���C�g�r���[�s����v�Z����
			//m_lightViewMatrix.MakeLookAt
			//(
			//	lightCameraPos,
			//	lightCameraTarget,
			//	lightCameraUpAxis
			//);

			////���C�g�v���W�F�N�V�����s����쐬����
			////���z������̉e�𗎂Ƃ������Ȃ�A���s���e�s����쐬����
			//m_shadowCbEntity.mLVP[0].MakeOrthoProjectionMatrix
			//(
			//	3000,
			//	3000,
			//	0.1f,
			//	5000.0f
			//);
		}
	}

	void ShadowMap::RenderToShadowMap()
	{
		auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		
		for (int i = 0; i < CascadeShadow; i++)
		{
			ShadowTextureNum = i;
			//�����_�����O�^�[�Q�b�g��؂�ւ���
			ID3D11RenderTargetView* rts[] =
			{
				m_shadowMapRT[i].GetRenderTargetView()
			};
			d3dDeviceContext->OMSetRenderTargets
			(
				1,
				rts,
				m_shadowMapRT[i].GetDepthStensilView()
			);
			//�r���[�|�[�g��ݒ�
			d3dDeviceContext->RSSetViewports
			(
				1,
				m_shadowMapRT[i].GetViewport()
			);

			//�V���h�E�}�b�v���N���A
			//��ԉ���Z��1.0�Ȃ̂ŁA1.0�œh��Ԃ�
			float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
			m_shadowMapRT[i].ClearRenderTarget(clearColor);

			//�V���h�E�L���X�^�[���V���h�E�}�b�v�Ƀ����_�����O�B
			for (auto& caster : m_shadowCasters) {
				caster->Draw(
					m_lightViewMatrix[i],
					m_lightProMatrix[i],
					enRenderMode_CreateShadowMap
				);

			}		

		}
		m_shadowCasters.clear();
	}

	void ShadowMap::SendShadowRecieverParamToGpu()
	{
		auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		//�萔�o�b�t�@�̓��e���X�V
		d3dDeviceContext->UpdateSubresource(m_shadowCb.GetBody(), 0, NULL, &m_shadowCbEntity, 0, 0);
		d3dDeviceContext->PSSetConstantBuffers(2, 1, &m_shadowCb.GetBody());
		//�e�N�X�`���𑗐M
		for (int i = 0; i < CascadeShadow; i++)
		{
			m_shadow = GetSRV(i);
			d3dDeviceContext->PSSetShaderResources(2 + i, 1,&m_shadow);
		}
	}

}