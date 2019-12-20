#pragma once
#include "ShaderResourceView.h"
#include "graphics/Shader.h"
#include "SourceFile/graphic/Primitive.h"

namespace Engine {
	class Sprite
	{
	public:
		//�R���X�g���N�^
		Sprite();
		//�f�X�g���N�^
		~Sprite();

		/*
		������
		tex		.�e�N�X�`��
		*/
		void Init(ShaderResourceView&tex, float w, float h);
	
	private:
		Shader m_ps;			//�s�N�Z���V�F�[�_�[
		Shader m_vs;			//���_�V�F�[�_�[
		CVector2 m_size = CVector2::Zero();			//�T�C�Y
		Primitive m_primitive;			//�v���~�e�B�u
	};

}