#include "stdafx.h"
#include "Sprite.h"

namespace Engine {
	namespace {
		struct SSinmpleVertex {
			CVector4 pos;
			CVector2 tex;
		};
	}
	//�N�_�̏�����
	const CVector2 Sprite::DEFAULT_PIVOT = { 0.5f,0.5f };
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
		m_ps.Load("Assets/shader/sprite.fx", "PSMain", Shader::EnType::PS);
		//���_�V�F�[�_�[
		m_vs.Load("Assets/shader/sprite.fx", "VSMain", Shader::EnType::VS);
		//�T�C�Y����
		m_size.x = w;
		m_size.y = h;
		//�T�C�Y�̔������v�Z
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

		//�v���~�e�B�u�̃N���G�C�g�֐�
		m_primitive.Create(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
			//���_��
			4,
			//���_�̃T�C�Y
			sizeof(SSinmpleVertex),
			//���_�o�b�t�@
			vertices,
			//�C���f�b�N�X�o�b�t�@�̐�
			4,
			//�C���f�b�N�X�̌^
			IndexBuffer::enIndexType_16,
			//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
			indices
		);
		//Init�֐��̒��g
		//�e�N�X�`���̃V�F�[�_�[���\�[�X�r���[
		m_textureSRV = &tex;
		m_cb.Create(nullptr, sizeof(SSpriteCB));
		//�������t���O��true�ɂ���
		m_isInited = true;
	}

	//�X�V����
	//trans		���s�ړ�
	//rot		��]
	//sale		�g��
	void Sprite::Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, const CVector2& pivot)
	{
		if (m_isInited = false)
		{
			//����������Ă��Ȃ��Ƃ�
			//�����Ԃ��Ȃ�
			return;
		}
		//����������Ă���Ƃ�
		//�s�{�b�g(�N�_)���l���ɓ��ꂽ���s�ړ��s����쐬
		//�s�{�b�g�͐^�񒆂�0.0,0.0�A���オ-1.0,-1.0�A
		//�E����1.0,1.0�ɂȂ�悤�ɂ���
		CVector2 localPivot = pivot;
		localPivot.x -= 0.5f;
		localPivot.y -= 0.5f;
		localPivot.x *= -2.0f;
		localPivot.y *= -2.0f;
		//�摜�̃n�[�t�T�C�Y�����߂�
		CVector2 halfSize = m_size;
		halfSize.x *= 0.5f;
		halfSize.y *= 0.5f;
		//���s�ړ��p�̋N�_�p�̍s����쐬
		CMatrix m_PivotTrans;
		m_PivotTrans.MakeTranslation
		(
			{
				//�n�[�t�T�C�Y�ɋN�_���|����
				//�܂肱���ł͋N�_�̈ʒu�����߂Ă���
				halfSize.x * localPivot.x , halfSize.y * localPivot.y , 0.0f
			}
		);
		//
		CMatrix m_Trans, m_Rot, m_Scale;
		//���s�ړ��p�̍s��
		m_Trans.MakeTranslation(trans);
		//��]�p�̍s��
		m_Rot.MakeRotationFromQuaternion(rot);
		//�g��p�̍s��
		m_Scale.MakeScaling(scale);
		//���[���h�s��ɏ�Z���Ă���
		//���Ԃ͌��X�̍s��*�g�嗦*��]��*���s�ړ�
		//���X�̍s��*�g�嗦
		m_world.Mul(m_PivotTrans, m_Scale);
		//���Ɋg�嗦���|����
		m_world.Mul(m_world,m_Rot);
		//���s�ړ��s����|����
		m_world.Mul(m_world, m_Trans);
	}
}