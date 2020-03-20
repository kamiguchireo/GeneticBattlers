#pragma once
#include "SpriteRender.h"
#include "SourceFile/graphic/Effect/CEffect.h"
#include "SourceFile/Sound/CSoundSource.h"
#include "SourceFile/graphic/RenderTarget.h"

class Game:public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void UpdateShadowMap();
	void Render();

private:
	//prefab::SpriteRender*m_spriteRender;	//�X�v���C�g�����_�[
	prefab::CEffect* effect = NewGO<prefab::CEffect>(0);		//�G�t�F�N�g���쐬�B
	//prefab::CSoundSource ss;		//�T�E���h
	SkinModel m_model;		//���f��(���j�e�B�����)
	//SkinModel m_model2;	//���f���Q(���j�e�B�����)
	SkinModel m_model3;		//���f���R(�n��)
	RenderTarget m_shadowMapRT;		//�V���h�E�}�b�v��`�悷�郌���_�����O�^�[�Q�b�g
	CVector3 m_ligPos = { 0.0f,300.0f,0.0f };
	CVector3 m_ligDir = { 1.0f,0.0f,0.0f };
	CVector3 m_position = CVector3::Zero();
};

