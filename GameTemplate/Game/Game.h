#pragma once
class Fade;
class Player;

class Game:public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();

private:
	Fade* m_fade = nullptr;
	Player* m_player = nullptr;
};

