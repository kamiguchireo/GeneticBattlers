#include "stdafx.h"
#include "Sprite.h"

namespace Engine {
	namespace {
		struct SSinmpleVertex {
			CVector4 pos;
			CVector2 tex;
		};
	}
	Sprite::Sprite()
	{
	}
	Sprite::~Sprite()
	{
	}

	//����������
	void Sprite::Init(ShaderResourceView& tex, float w, float h)
	{
		//�V�F�[�_�[���[�h
		//�s�N�Z���V�F�[�_�[
		m_ps.Load("shader/sprite.fx", "PSMain", Shader::EnType::PS);
		m_vs.Load("shader/sprite.fx", "VSMain", Shader::EnType::VS);
		//�T�C�Y����
		m_size.x = w;
		m_size.y = h;
		float halfW = w * 0.5f;
		float halfH = h * 0.5f;
		//���_�o�b�t�@�̃\�[�X�f�[�^
		SSinmpleVertex vertices[] =
		{
			{
				CVector4(-halfW,-halfH,0.0f,1.0f),
				CVector2(0.0f,1.0f),
			},
			{
				CVector4(halfW,-halfH,0.0f,1.0f),
				CVector2(1.0f,1.0),
			},
		    {
				CVector4(-halfW,halfH,0.0f,1.0f),
				CVector2(1.0f,0.0f),
			},
			{
				CVector4(halfW,halfH,0.0f,1.0f),
				CVector2(1.0f,0.0f),
			},
		};
		short indices[] = { 0,1,2,3 };
	}
}