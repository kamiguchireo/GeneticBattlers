#pragma once
#include "EffekseerRuntime130/src/Effekseer/Effekseer.h"

namespace Engine {
	namespace prefab{
		class CEffect:public IGameObject
		{
		public:
			CEffect();
			~CEffect();

			//�������
			void Release();

			//�G�t�F�N�g���Đ�
			//filePath		�Đ�����G�t�F�N�g�̃t�@�C���p�X
			void Play(const wchar_t*filePath);

			//���W��ݒ�
			void SetPosition(const CVector3& pos)
			{
				m_position = pos;
			}

			//��]�̐ݒ�
			void SetRotation(const CQuaternion&rot)
			{
				m_rotation = rot;
			}

			//�g�嗦��ݒ�
			void SetSacle(const CVector3&scale)
			{
				m_scale = scale;
			}

			//�X�V
			//void Update();
		private:
			Effekseer::Effect*m_effect = nullptr;
			Effekseer::Handle m_handle = -1;
			CVector3 m_position = CVector3::Zero();		//���W
			CQuaternion m_rotation = CQuaternion::Identity();		//��]
			CVector3 m_scale = CVector3::One();		//�g��
		};
	}
}


