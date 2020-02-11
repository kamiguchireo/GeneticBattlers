#pragma once
#include "Skill/SkillList.h"
#include "level/Level.h"

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
	//モンスターの初期化。
	void InitMonster();
	//モンスターに行動させる。
	void MonsterAction();

private:
	//アクティブタイムバーの更新。
	void ActiveTimeUpdate();
	//フェード切り替え
	enum SceneState {
		enState_FadeIn,
		enState_Battle,
		enState_FadeOut
	};
	Fade* m_fade = nullptr;
	SceneState m_state = enState_FadeIn;

	Level m_level;
	//モンスターのポインタ。
	std::vector<MonsterBase*>m_monsterTeam1List;
	std::vector<MonsterBase*>m_monsterTeam2List;

	SkinModel m_model;						//!<ステージのモデル。
	MonsterBase* m_monsterACT = nullptr;	//!<現在行動中のモンスター。
	SkillList skillList;					//!<スキルリスト。
};

