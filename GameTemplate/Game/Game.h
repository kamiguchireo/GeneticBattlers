#pragma once
#include "SpriteRender.h"
#include "SourceFile/graphic/Effect/CEffect.h"
#include "SourceFile/Sound/CSoundSource.h"

class Game:public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();

private:
	//prefab::SpriteRender*m_spriteRender;	//�X�v���C�g�����_�[
	prefab::CEffect* effect = NewGO<prefab::CEffect>(0);		//�G�t�F�N�g���쐬�B
	//prefab::CSoundSource ss;		//�T�E���h
	SkinModel m_model;		//���f��
	SkinModel m_model2;		//���f���Q



};

