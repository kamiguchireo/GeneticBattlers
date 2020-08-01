#include "stdafx.h"
#include "SpriteRender.h"

namespace Engine {
	namespace prefab {
		//����������
		void SpriteRender::Init(const wchar_t*texFilePath, float w, float h, bool isDraw3D)
		{
			m_isDraw3D = isDraw3D;
			m_texture.CreateFromDDSTextureFromFile(texFilePath);
			m_sprite.Init(m_texture.GetBody(), w, h);
		}

		//�X�V����
		void SpriteRender::Update()
		{
			//�X�v���C�g�Ƀe�N�X�`����ݒ肷��
			//m_sprite.SetTexture(m_texture);
			//�X�v���C�g�̍X�V�������Ăяo��
			m_sprite.Update(m_position, m_rotation, m_scale, m_pivot);
			m_sprite.Draw
			(
				g_camera2D.GetViewMatrix(),
				g_camera2D.GetProjectionMatrix()
			);
		}

		void SpriteRender::PostRender()
		{
			//if (m_isDraw3D == false)
			//{
			//	m_sprite.Draw(g_graphicsEngine->Get2DCamera().GetViewMatrix(), g_graphicsEngine->Get2DCamera().GetProjectionMatrix());
			//}
		}
	}
}