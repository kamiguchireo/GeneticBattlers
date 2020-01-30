#pragma once
class TitleScene : public IGameObject
{
public:
	TitleScene();
	~TitleScene();

	bool Start();
	void Update();

private:
	prefab::SpriteRender* m_sprite = nullptr;
	CVector4 m_color = CVector4::White();
	bool isFlag = false;

};

