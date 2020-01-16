#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "monster/MonsterBase.h"
#include "monster/MonsterTeam1.h"

Game::Game()
{	//ÉvÉåÉCÉÑÅ[
	player = NewGO<Player>(0, "player");
}


Game::~Game()
{
	DeleteGO(player);
}

bool Game::Start()
{
	InitMonster();

	return true;
}

void Game::Update()
{
}

void Game::InitMonster()
{
	const int MonsterNum = 3;

	for (int i = 0; i < MonsterNum; i++) {
		CVector3 pos(-50.0f + 50.0f*i, 0.0f, 0.0f);
		MonsterBase* monster = NewGO<MonsterTeam1>(0);
		monster->SetPosition(pos);
		m_monsterTeam1List.push_back(monster);
	}
}
