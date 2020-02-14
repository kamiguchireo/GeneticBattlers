#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Fade.h"

Game::Game()
{	

}


Game::~Game()
{

}

bool Game::Start()
{
	//m_fade = Fade::GetInstance();
	//m_fade->StartFadeIn();

	//�X�v���C�g�̊m�F�̂��߂̃|�C���^
	prefab::SpriteRender*m_spriteRender;

	//�X�v���C�g��������
	m_spriteRender = NewGO<prefab::SpriteRender>(0, "sprite");
	m_spriteRender->Init(L"Assets/sprite/mikyan.dds", 400, 300);

	
	return true;
}

void Game::Update()
{
	if (g_pad[0].IsTrigger(enButtonA)
		&& m_player == nullptr)
	{
		m_player = NewGO<Player>(0);
		//m_fade->StartFadeIn
	}
	if (g_pad[0].IsTrigger(enButtonB)
		&& m_player != nullptr)
	{
		DeleteGO(m_player);
		m_player = nullptr;
		//m_fade->StartFadeOut();
	}
}