#include "stdafx.h"
#include "CEffect.h"

namespace Engine {
	namespace prefab {
		CEffect::CEffect()
		{
		}
		CEffect::~CEffect()
		{
			Release();
		}

		//�������
		void CEffect::Release()
		{
			if (m_handle != -1)
			{
				m_manager->StopEffect(m_handle);
				m_handle = -1;
			}
		}

		void CEffect::Play(const wchar_t* filePath)
		{
			int nameKey = Util::MakeHash(filePath);
			m_effect = GetResource(nameKey);
			if (m_effect == nullptr)
			{
				//���o�^
				m_effect = CreateEffekseerEffect(filePath);
				if (m_effect == nullptr)
				{
					//�G�t�F�N�g�̃��[�h�Ɏ��s�������I
					//��O�X���[���I������ˁI������
					throw;
				}
				RegistResource(nameKey,m_effect);
			}
			m_handle = m_manager->Play(m_effect, 0, 0, 0);
		}

		void CEffect::Update()
		{
			CMatrix m_Trans, m_Rot, m_Scale, m_Base = CMatrix::Identity();
			m_Trans.MakeTranslation(m_position);
			m_Rot.MakeRotationFromQuaternion(m_rotation);
			m_Scale.MakeScaling(m_scale);
			m_Base.Mul(m_Scale, m_Rot);
			m_Base.Mul(m_Base, m_Trans);
			m_manager->SetBaseMatrix(m_handle, m_Base);
			if (IsPlay() == false)
			{
				//�Đ�����������I���
				DeleteGO(this);
			}
		}
	}
}