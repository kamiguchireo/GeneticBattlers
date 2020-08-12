#pragma once

class StatusBase;
class SkillCalculator;
class AIManager;
class SkillDataLoad;

class GAScenes:public IGameObject
{
public:
	GAScenes();
	~GAScenes();
	bool Start()override;
	void Update()override;
private:
	prefab::SpriteRender* m_sprite = nullptr;
	prefab::FontRender* m_font = nullptr;
};

