#pragma once
#include "SpriteRender.h"
#include "SourceFile/graphic/Effect/CEffect.h"
#include "SourceFile/Sound/CSoundSource.h"
#include "SourceFile/graphic/RenderTarget.h"
#include "SourceFile/graphic/font/FontRender.h"
#include "graphics/Skeleton.h"

class Game:public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void UpdateShadowMap();
	void Render();
	//void ForwordRender();
	//void PostRender();
	//�X�P���g���̏�����
	//void InitSkelton(const wchar_t* filePath);
private:
	//prefab::SpriteRender*m_spriteRender;	//�X�v���C�g�����_�[
	//prefab::CEffect* effect = NewGO<prefab::CEffect>(0);		//�G�t�F�N�g���쐬�B
	//prefab::CSoundSource ss;		//�T�E���h
	SkinModel m_model;		//���f��(���j�e�B�����)
	SkinModel m_model2;	//���f���Q(���j�e�B�����)
	SkinModel m_model3;		//���f���R(�n��)
	RenderTarget m_shadowMapRT;		//�V���h�E�}�b�v��`�悷�郌���_�����O�^�[�Q�b�g
	CVector3 m_ligPos = { 0.0f,300.0f,0.0f };
	CVector3 m_ligDir = { 1.0f,0.0f,0.0f };
	CVector3 m_position = CVector3::Zero();
	CVector3 m_pos2 = { 40.0f,0.0f,0.0f };

	//RenderTarget m_mainRenderTarget;		//���C�������_�����O�^�[�Q�b�g�B
	//D3D11_VIEWPORT m_frameBufferViewports;			//�t���[���o�b�t�@�̃r���[�|�[�g�B
	//Sprite m_copyMainRtToFrameBufferSprite;			//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g�B
	//CVector3 m_sposition = { 0.0,0.0,5.0 };			//���W�B
	CQuaternion m_rotation = CQuaternion::Identity();			//!<��]�B
	//CVector3 m_scale = CVector3::One();			//�g�嗦�B
	//CVector2 m_pivot = Sprite::DEFAULT_PIVOT;	//�s�{�b�g�B
	//prefab::FontRender* fr;
	Skeleton m_skeleton;		//�X�P���g���B
	Skeleton m_skeleton2;			//�u�����f�B���O�p�X�P���g��
	Animation m_animation;				//�A�j���[�V�����B
	Animation m_animation2;				//�A�j���[�V�����u�����f�B���O�p
	AnimationClip m_animClip[2];				//�A�j���[�V�����N���b�v�B
	std::vector<Bone*> m_bone;
};

