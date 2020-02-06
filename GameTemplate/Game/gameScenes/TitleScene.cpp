#include "stdafx.h"
#include "TitleScene.h"
#include "Fade.h"
#include "BattleScenes.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	if (!m_sprite)
	{
		DeleteGO(m_sprite);
	}
}

bool TitleScene::Start()
{
	m_sprite = NewGO<prefab::SpriteRender>(0);
	m_sprite->Init(L"Assets/sprite/PreTitle.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);

	m_fade = Fade::GetInstance();
	m_fade->StartFadeIn();
	return true;
}

void TitleScene::Update()
{
	switch (m_state)
	{
	case enState_inTitle:
		if (!m_fade->IsFade())
			m_state = enState_idle;		//�t�F�[�h�C�����I���΃X�e�[�g��؂�ւ���B
		break;
	case enState_idle:
		//A�{�^���ŃV�[���؂�ւ��B
		if (g_pad[0].IsTrigger(enButtonA))
		{
			m_fade->StartFadeOut();
			m_state = enState_inGame;	//A�{�^���������ꂽ��X�e�[�g��؂�ւ���B
		}
		break;
	case enState_inGame:
		if (!m_fade->IsFade())
		{
			NewGO<BattleScenes>(0);
			DeleteGO(this);
		}
	}
}
