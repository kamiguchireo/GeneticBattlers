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
	void MonsterAction();

private:
	void ActiveTimeUpdate();
	std::vector<MonsterBase*>m_monsterTeam1List;
	std::vector<MonsterBase*>m_monsterTeam2List;
	MonsterBase* m_monsterACT = nullptr;
	Player*player;
};

