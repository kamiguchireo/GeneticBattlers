#pragma once
#include "Font.h"

namespace Engine
{
	namespace prefab {
		//�t�H���g�����_�[
		class FontRender:public IGameObject
		{
		public:
			FontRender(){}
			~FontRender(){}

			//�t�H���g��ݒ�
			//�f�t�H���g�t�H���g����ύX�������ꍇ��
			//DirectX::SpriteFont���g�p���āA�t�H���g�����[�h���č����ւ��Ă�������
			//font		�t�H���g
			void SetFont(DirectX::SpriteFont*font)
			{
				m_font.SetFont(font);
			}

			//�e�L�X�g��ݒ�
			//text		�e�L�X�g
			void SetText(const wchar_t*text)
			{
				//wcscmp��2�̕�������r����
				if (wcscmp(m_text.c_str(), text) != 0)
				{
					//�����񂪕ς����
					m_text = text;
				}
			}

			//�t�H���g��\��������W��ݒ�
			//�t�H���g�̍��W��
			//(0.0f,0.0f)�ŉ�ʂ̒����ł�
			//�E������X+
			//�������Y+�̍��W�n�ł�
			void SetPosition(const CVector2&pos)
			{
				m_position = pos;
			}

			//�t�H���g�̃J���[��ݒ�
			//������xyz��rgb�̒l���w��
			//��j�^���Ԃɂ�����������xyz��(1.0f,0.0f,0.0f)�Ǝw�肵�Ă�������
			//color		�F
			void SetColor(const CVector3&color)
			{
				m_color = color;
			}		
			void SetColor(const CVector4& color)
			{
				m_color = color;
			}

			//��]��ݒ�
			//rotation		��]�p�x�B�P�ʂ̓��W�A��
			void SetRotation(float rotation)
			{
				m_rotation = rotation;
			}

			//�g�嗦��ݒ�
			//scale		�g�嗦
			void SetScale(float scale)
			{
				m_scale = scale;
			}

			//�s�{�b�g��ݒ�
			//�t�H���g�̊�_��ݒ肵�܂�
			//(0.5f,0.5f)�ŉ摜�̒��S����_
			//(0.0f,0.0f)�ŉ摜�̍���
			//(1.0f,1.0f)�ŉ摜�̉E��
			//pivot		��_
			void SetPivot(const CVector2&pivot)
			{
				m_pivot = pivot;
			}

			bool Start();
			void Update();
		private:
			Font m_font;		//�t�H���g
			std::wstring m_text;		//�e�L�X�g�B
			CVector2 m_position = CVector2::Zero();		//���W
			CVector4 m_color = CVector4::White();		//�J���[
			float m_rotation = 0.0f;		//��]
			float m_scale = 1.0f;		//�g�嗦
			CVector2 m_pivot  = CVector2::Zero();		//�s�{�b�g
		};
	}
}