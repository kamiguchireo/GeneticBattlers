#pragma once
#include "ShaderResourceView.h"
#include "SourceFile/graphic/2D/Sprite.h"

namespace Engine {
	namespace prefab {
		class SpriteRender:public IGameObject
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
			//�Z�b�g�֌W
			void SetPosition(CVector3 pos)
			{
				m_position = pos;
			}
			void SetRotation(CQuaternion rot)
			{
				m_rotation = rot;
			}
			void SetScale(CVector3 scale)
			{
				m_scale = scale;
			}
			void SetPivot(CVector2 pivot)
			{
				m_pivot = pivot;
			}
			void SetMulColor(const CVector3& mulColor)
			{
				m_sprite.SetMulColor(mulColor);
			}
			//�`��
			void PostRender(RenderContext&rc)override final;
		private:
			bool m_isDraw3D = false;		//3D��Ԃŕ`�悷��
			ShaderResourceView m_texture;		//�e�N�X�`��
			Sprite m_sprite;		//�X�v���C�g
			CVector3 m_position = { 0.0,0.0,5.0 };			//���W�B
			CQuaternion m_rotation = CQuaternion::Identity();			//!<��]�B
			CVector3 m_scale = CVector3::One();			//�g�嗦�B
			CVector2 m_pivot = Sprite::DEFAULT_PIVOT;	//�s�{�b�g�B
		};
	}
}