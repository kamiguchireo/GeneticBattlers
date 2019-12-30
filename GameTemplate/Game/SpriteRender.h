#pragma once
#include "ShaderResourceView.h"
#include "SourceFile/graphic/2D/Sprite.h"

namespace Engine {
	namespace prefab {
		class SpriteRender
		{
		public:
			//�R���X�g���N�^
			SpriteRender() {}
			/*
			������
			texFilePath		�e�N�X�`���t�@�C���p�X
			w		��
			h		����
			isDraw3D		3D��Ԃŕ`�ʂ���
			*/
			void Init(const wchar_t*texFilePath, float w, float h, bool isDraw3D = false);

			//�A�b�v�f�[�g�֐�
			void Update();

		private:
			bool m_isDraw3D = false;		//3D��Ԃŕ`�悷��
			ShaderResourceView m_texture;		//�e�N�X�`��
			Sprite m_sprite;		//�X�v���C�g
			CVector3 m_position = CVector3::Zero();			//���W�B
			CQuaternion m_rotation = CQuaternion::Identity();			//!<��]�B
			CVector3 m_scale = CVector3::One();			//�g�嗦�B
			CVector2 m_pivot = Sprite::DEFAULT_PIVOT;	//�s�{�b�g�B
		};
	}
}