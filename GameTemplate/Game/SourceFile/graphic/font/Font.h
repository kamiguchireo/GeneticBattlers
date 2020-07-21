#pragma once
#include "SourceFile/Noncopyable.h"

namespace Engine
{
	class Font:Engine::Noncopyable
	{
	public:
		Font();
		~Font();

		//�t�H���g��ݒ�
		//�f�t�H���g�̃t�H���g����ύX�������ꍇ��
		//DirectX::SpriteFont���g�p���āA�t�H���g�����[�h���č����ւ��ĉ�����
		void SetFont(DirectX::SpriteFont* font)
		{
			m_spriteFont = font;
		}

		//�`��J�n
		void Begin();
		//�`��I��
		void End();

		//�`��
		//text		�\���������e�L�X�g
		//trans		���s�ړ�
		//color		�J���[
		//rot		��]
		//sacle		�g��
		//pivot		�N�_
		//		0.5,0.5�ŉ摜�̒��S���N�_
		//		0.0,0.0�ŉ摜�̍���
		//		1.0,1.0�ŉ摜�̉E��
		void Draw
			(
			wchar_t const* text,
			const CVector2& position,
			const CVector4& color = CVector4::White(),
			float rotation = 0.0f,
			float scale = 1.0f,
			CVector2 pivot = { 0.5f, 0.5f }
		);

	private:
		DirectX::SpriteBatch* m_spriteBatch = nullptr;		//�X�v���C�g�o�b�`
		DirectX::SpriteFont* m_spriteFont = nullptr;		//�X�v���C�g�t�H���g
		CMatrix m_scaleMat = CMatrix::Identity();
		float kaizoudo[2] = { 1280.0f,720.0f };
	};
}