#pragma once
class Player;
class MonsterBase;
class MonsterTeam1;

class Game:public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void InitMonster();

private:
	std::vector<MonsterBase*>m_monsterTeam1List;
	std::vector<MonsterBase*>m_monsterTeam2List;
	Player*player;
};

