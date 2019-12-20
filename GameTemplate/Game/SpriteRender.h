#pragma once
#include "ShaderResourceView.h"

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

		private:
			bool m_isDraw3D = false;		//3D��Ԃŕ`�悷��
			ShaderResourceView m_texture;		//�e�N�X�`��
		};
	}
}