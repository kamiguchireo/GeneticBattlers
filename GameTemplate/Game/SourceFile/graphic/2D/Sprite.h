#pragma once
#include "ShaderResourceView.h"
#include "graphics/Shader.h"
#include "SourceFile/graphic/Primitive.h"
#include "ConstantBuffer.h"
#include "SourceFile/graphic/RenderContext.h"

namespace Engine {
	class Sprite
	{
	public:
		//�N�_
		static const CVector2 DEFAULT_PIVOT;
		//�R���X�g���N�^
		Sprite();
		//�f�X�g���N�^
		~Sprite();

		/*
		������
		tex		.�e�N�X�`��
		*/
		void Init(ID3D11ShaderResourceView* tex, float w, float h);

		/*
		��Z�J���[��ݒ�
		mulColor	��Z�J���[
		*/
		void SetMulColor(const CVector3& mulColor)
		{
			m_mulColor = mulColor;
		}

		//�e�N�X�`����ݒ�
		//tex		�e�N�X�`��
		//void SetTexture(ShaderResourceView& tex)
		//{
		//	m_textureSRV = &tex;
		//}

		//�A�b�v�f�[�g�֐�
		//trans		���s�ړ�
		//rot		��]
		//scale		�g��
		//pivot		�N�_
		//0.5, 0.5�ŉ摜�̒��S���N�_�B
		//0.0, 0.0�ŉ摜�̍����B
		//1.0, 1.0�ŉ摜�̉E��B
		void Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, const CVector2& pivot = DEFAULT_PIVOT);
	
		/*
		�`��
		viewMatrix		�r���[�s��
		projMatrix		�v���W�F�N�V�����s��
		*/
		void Draw(const CMatrix&viewMatrix, const CMatrix& projMatrix);
		//���̒l�̕ύX
		void SetAlpha(float a)
		{
			cb.alpha = a;
		}
		//�����œn���ꂽ�����l��16�̔{���ɐ؂�グ
		int Raundup16(int n)
		{
			return (((n - 1) / 16) + 1) * 16;
		}

		void SetIsAlpha(int a)
		{
			cb.isAlpha = a;
		}
	private:
		//�萔�o�b�t�@(ConstantBuffer)��Create�֐��̈����Ɏg�p����
		struct SSpriteCB
		{
			CMatrix WVP;		//���[���h�r���[�v���W�F�N�V�����s��
			CVector3 mulColor;		//��Z�J���[
			float alpha = 1.0f;		//���l
			int isAlpha = 0;	//�摜���̂̃����g�����ǂ���1�̎��ɉ摜�̃����g��Ȃ�
		};
		SSpriteCB cb;
		Shader m_ps;			//�s�N�Z���V�F�[�_�[
		Shader m_vs;			//���_�V�F�[�_�[
		CVector3 m_mulColor = CVector3::Zero();		//��Z�J���[
		CVector2 m_size = CVector2::Zero();			//�T�C�Y
		Primitive m_primitive;			//�v���~�e�B�u
		//ShaderResourceView* m_textureSRV = nullptr;		//�e�N�X�`��
		ID3D11ShaderResourceView*m_textureSRV = nullptr;
		ConstantBuffer m_cb;
		CMatrix m_world = CMatrix::Identity();		//���[���h�s��
		bool m_isInited = false;		//�������t���O
	};

}