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
	m_fade = Fade::GetInstance();
	m_fade->StartFadeIn();

	return true;
}

void Game::Update()
{
	if (g_pad[0].IsTrigger(enButtonA))
	{
		m_fade->StartFadeIn();
	}
	if (g_pad[0].IsTrigger(enButtonB))
	{
		m_fade->StartFadeOut();
	}
}