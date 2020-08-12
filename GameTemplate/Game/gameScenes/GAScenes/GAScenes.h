#pragma once

class SkillCalculator;
class SkillDataLoad;
class MonsterData;

typedef std::vector<MonsterData> MonsterList;

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
	MonsterList m_members;
	MonsterList m_enemys;
};

