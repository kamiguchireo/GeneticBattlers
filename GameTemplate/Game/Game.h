#pragma once
class Player;

class Game:public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();

private:
	Player*player;
};

