#include "stdafx.h"
#include "Game.h"
#include "Player.h"

Game::Game()
{	//�v���C���[
	player = NewGO<Player>(0, "player");
}


Game::~Game()
{
	DeleteGO(player);
}

bool Game::Start()
{
	return true;
}

void Game::Update()
{
}
