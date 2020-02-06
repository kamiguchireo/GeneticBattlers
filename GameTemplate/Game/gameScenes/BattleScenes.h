#pragma once
#include "Skill/SkillList.h"

class MonsterBase;
class MonsterTeam1;
//class SkillList;
class Fade;

class BattleScenes : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	BattleScenes();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~BattleScenes();

	bool Start();
	void Update();

	void InitMonster();
	void MonsterAction();

private:
	enum SceneState {
		enState_FadeIn,
		enState_Battle,
		enState_FadeOut
	};
	Fade* m_fade = nullptr;
	SceneState m_state = enState_FadeIn;
	void ActiveTimeUpdate();
	std::vector<MonsterBase*>m_monsterTeam1List;
	std::vector<MonsterBase*>m_monsterTeam2List;
	MonsterBase* m_monsterACT = nullptr;
	SkillList skillList;
};

