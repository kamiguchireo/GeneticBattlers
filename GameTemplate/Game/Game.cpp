#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Fade.h"

Game::Game()
{	

}


Game::~Game()
{
	if (m_player != nullptr)DeleteGO(m_player);
}

bool Game::Start()
{
	//m_fade = Fade::GetInstance();
	//m_fade->StartFadeIn();

	//スプライトの確認のためのポインタ
	prefab::SpriteRender*m_spriteRender;

	//スプライトを初期化
	m_spriteRender = NewGO<prefab::SpriteRender>(0,"sprite");
	m_spriteRender->Init(L"Assets/sprite/mikyan.dds", 400, 300);

	return true;
}

void Game::Update()
{
	if (g_pad[0].IsTrigger(enButtonA))
	{
		if (m_player == nullptr) m_player = NewGO<Player>(0, nullptr);
		//m_fade->StartFadeIn();
	}
	if (g_pad[0].IsTrigger(enButtonB))
	{
		if (m_player != nullptr)
		{
			DeleteGO(m_player);
			m_player = nullptr;
		}
		//m_fade->StartFadeOut();
	}
}