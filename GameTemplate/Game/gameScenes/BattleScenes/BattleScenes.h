#pragma once
#include "Skill/SkillList.h"
#include "level/Level.h"
#include "BattleManager.h"

class MonsterBase;
class MonsterTeam1;
class Fade;
class GameCamera;
class NetScenes;

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
	void Draw();
	//モンスターの初期化。
	void InitMonster();

	/// <summary>
	/// 勝利したかどうか。
	/// ついでにステートの切り替え。
	/// </summary>
	/// <param name="res">true 勝利 : false 敗北</param>
	void SetBattleResult(bool res)
	{
		m_isWin = res;
		battleCoolTime = 2.0f;
		m_state = enState_Result;
	}

private:
	//フェード切り替え
	enum SceneState {
		enState_FadeIn,
		enState_Battle,
		enState_Result,
		enState_FadeOut
	};
	Fade* m_fade = nullptr;
	NetScenes* m_netScenes = nullptr;
	SceneState m_state = enState_FadeIn;
	Level m_level;
	BattleManager m_battleManager;

	SkinModel m_model;						//!<ステージのモデル。
	GameCamera* m_camera = nullptr;			//!<ゲームカメラ。
	prefab::SpriteRender* m_resultSprite = nullptr;	//!<リザルト用のスプライトレンダー。
	float battleCoolTime = 0.0f;			//!<クールタイム。
	bool m_isWin = false;					//!<勝利フラグ。
	bool m_isSprite = false;				//!<スプライトが表示されたか。
};

