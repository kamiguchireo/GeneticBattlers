#pragma once
#include "SpriteRender.h"
#include "graphics/Skeleton.h"

class Game:public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Draw();
private:
	SkinModel m_model;		//���f��(���j�e�B�����)
	//SkinModel m_model2;	//���f���Q(���j�e�B�����)
	SkinModel m_model3;		//���f���R(�n��)
	RenderTarget m_shadowMapRT;		//�V���h�E�}�b�v��`�悷�郌���_�����O�^�[�Q�b�g
	CVector3 m_ligPos = { 0.0f,300.0f,0.0f };
	CVector3 m_ligDir = { 1.0f,0.0f,0.0f };
	CVector3 m_position = CVector3::Zero();
	CVector3 m_pos2 = { 40.0f,0.0f,0.0f };

	CQuaternion m_rotation = CQuaternion::Identity();			//!<��]�B
	Skeleton m_skeleton;		//�X�P���g���B
	Skeleton m_skeleton2;			//�u�����f�B���O�p�X�P���g��
	Animation m_animation;				//�A�j���[�V�����B
	Animation m_animation2;				//�A�j���[�V�����u�����f�B���O�p
	AnimationClip m_animClip[1];				//�A�j���[�V�����N���b�v�B
	AnimationClip m_animClip2[1];
	std::vector<Bone*> m_bone;
};

