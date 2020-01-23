#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "monster/MonsterBase.h"
#include "monster/MonsterTeam1.h"

Game::Game()
{	
	////�v���C���[
	//player = NewGO<Player>(0, "player");
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
	ActiveTimeUpdate();
	MonsterAction();
}

void Game::InitMonster()
{
	const int MonsterNum = 3;

	for (int i = 0; i < MonsterNum; i++) {
		CVector3 pos(-50.0f + 50.0f*i, 0.0f, 0.0f);
		Status hoge;
		hoge.MAXHP = rand() % 50 + 100;
		hoge.MAXMP = rand() % 50 + 100;
		hoge.ATK = rand() % 10 + 10;
		hoge.DEF = rand() % 10 + 10;
		hoge.MAT = rand() % 10 + 10;
		hoge.MDF = rand() % 10 + 10;
		hoge.DEX = rand() % 10 + 10;
		MonsterBase* monster = NewGO<MonsterTeam1>(0);
		monster->SetPosition(pos);
		monster->SetStatus(hoge);
		m_monsterTeam1List.push_back(monster);
	}
}

void Game::MonsterAction()
{
	//�N���s�����Ă��Ȃ��Ȃ璆�f�B
	if (m_monsterACT == nullptr)return;

	//�s�����I���܂ōs����������B
	bool is_playAction = m_monsterACT->Action();

	//�s�����I�������|�C���^��null������B
	if (is_playAction) {
		m_monsterACT = nullptr;

		//�c��HP�ɉ����ăX�e�[�g���X�V�B
		for (int i = 0; i < m_monsterTeam1List.size(); i++) {
			m_monsterTeam1List[i]->StateUpdate();
		}
	}
}

void Game::ActiveTimeUpdate()
{
	//�s�����Ȃ璆�f�B
	if (m_monsterACT != nullptr)return;

	//�S���̃^�C���Q�[�W�����Z���Ă����B
	for (int i = 0; i < m_monsterTeam1List.size(); i++)
	{
		bool is_action = m_monsterTeam1List[i]->AddATB();

		//�Q�[�W�����܂�؂�����|�C���^���擾����B�@
		if (is_action) {
			m_monsterACT = m_monsterTeam1List[i];
			m_monsterACT->SelectUseSkill(m_monsterTeam1List);
		}
	}
}
