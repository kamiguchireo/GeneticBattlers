#pragma once
#include "Skill/SkillBase.h"
#include "../StatusUI.h"

//const int AI_SIZE = 6;							//AIがとりうる行動の数。

/// <summary>
/// ステータスの構造体。
/// </summary>
/// <remarks>
/// 魔法攻撃力はINTだとint型と間違えそうだからMATとした。
/// </remarks>
struct Status {
	int HP		= 0,
		//MP		= 0,
		ATK		= 0,
		DEF		= 0,
		MAT		= 0,
		MDF		= 0,
		DEX		= 0;
};

//バフの列挙。
enum StatusBuff {
	en_buff_ATK,
	en_buff_DEF,
	en_buff_MAT,
	en_buff_MDF,
	en_buff_DEX,
	en_buff_num
};

//行動テーブルのデータ。
//!<skillNo		スキル番号。
//!<target		ターゲット番号。
//!<rate		使用頻度。
struct AIData {
	int skillNo = 0;
	int target = 0;
	float rate = 0.0f;
};

//行動のリザルト。
//!<damage		ダメージ値。
//!<skillNo		スキル番号。
//!<target		ターゲット値。
//!<score		評価。
struct ACTResullt {
	int damage = 0;
	int skillNo = 0;
	int target = 0;
	bool score = false;
};

/// <summary>
/// モンスターステート。
/// </summary>
/// <remarks>
/// 最大HPの3分の1刻みでステートは変わる予定。
/// </remarks>
enum MonsterState {
	en_state_Good,		//残りHPが高い。
	en_state_Usually,	//残りHPが半分前後。
	en_state_Bad,		//残りHPが低い。
	en_state_Death,		//残りHPが0。
	en_state_Num		//ステートの数。
};

class MonsterBase:public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	MonsterBase();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~MonsterBase();

	/// <summary>
	/// binファイルからデータを読み込む。
	/// </summary>
	/// <param name="filePath">ファイルパス。</param>
	virtual void Init(const char* filePath) {};
	/// <summary>
	/// binファイルにデータを書き込む。
	/// </summary>
	/// <param name="filePath">ファイルパス。</param>
	virtual void Save(const char* filePath) {};

	//座標を取得。
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	const CQuaternion& GetRotation() const
	{
		return m_rotation;
	}
	//ステータスを取得。
	const Status& GetStatus() const
	{
		return m_status;
	}
	//基礎ステータスを取得。
	const Status& GetStatusBase() const
	{
		return m_statusBase;
	}
	//モンスターの属性を取得。
	const Elements& GetElements() const
	{
		return m_elemnts;
	}
	//チームメンバーリストを取得。
	const std::vector<MonsterBase*> GetTeamMenber()const
	{
		return m_teamMenber;
	}
	//ステータスの設定。
	//正直ファイルからロードしたい。
	void SetStatus(int hp, int mp, int atk, int def, int mat, int mdf, int dex);
	//ステータスの設定。(ステータス構造体ver)。
	void SetStatus(const Status& status)
	{
		m_statusBase = status;
		m_status = m_statusBase;
	}
	//座標の設定。
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//回転の設定。
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	//UIの位置を設定する。
	virtual void SetUIPos(const CVector3& pos){}
	//味方チームのリストを設定。
	void SetTeamMenber(const std::vector<MonsterBase*>& list)
	{
		m_teamMenber = list;
	}
	//描画処理とかをまとめたもの。
	void Draw();
	//アクティブタイムを加算する。
	bool AddATB();
	//行動の評価を行う。
	virtual bool ACTScoring();
	//行動のリザルトの設定。
	//!<No			スキル番号。
	//!<damage		ダメージ値。
	void SetActResult(int No ,int damage) {
		m_actRes.skillNo = No;
		m_actRes.damage = damage;
	}
	//クールタイムを設定する。
	void SetCoolTime(float time)
	{
		m_coolTime = time;
	}
	//
	bool IsDeath() {
		return m_stateAI == en_state_Death;
	}
	/// <summary>
	/// ダメージを与える。
	/// </summary>
	/// <param name="damage">ダメージ量。</param>
	/// <returns>入ったダメージ量。</returns>
	int Damage(int damage)
	{
		//現在HPとダメージ量の比較。
		int res = min(m_status.HP,damage);
		m_status.HP -= res;
		//アニメーション。
		m_animation.Play(en_anim_Damage, 0.3f);

		return res;
	}
	/// <summary>
	/// HPを回復させる。
	/// </summary>
	/// <param name="healing">回復量。</param>
	/// <returns>回復できた量。</returns>
	int Healing(int healing);

	/// <summary>
	/// バフをかける。
	/// </summary>
	/// <param name="status">バフをかけるステータス。</param>
	/// <param name="pow">バフの威力。</param>
	/// <param name="time">バフの効果時間。</param>
	/// <returns>効果値。</returns>
	int Monster_Buff(StatusBuff status,float pow,float time);
	//バフをリセットする。
	void ResetBuff(int i);

	/// <summary>
	/// スキルのターゲットを定める。
	/// </summary>
	/// <param name="e_team">敵のチーム。</param>
	/// <param name="m_team">味方のチーム。</param>
	virtual void SelectUseSkill(const std::vector<MonsterBase*>& e_team, const std::vector<MonsterBase*>& m_team);
	/// <summary>
	///ステートの更新処理。 
	/// </summary>
	void StateUpdate();
	/// <summary>
	/// ステートに応じて行動を決める。
	/// </summary>
	bool Action();

	virtual bool Action_good() { return false; }
	virtual bool Action_usually() { return false; }
	virtual bool Action_bad() { return false; }
	virtual bool BattleAction() = 0;
	

protected:
	//遺伝的アルゴリズムを用いて行動テーブルを更新。
	void GIUpdate();
	//	モデル関係
	SkinModel m_model;									//モデルデータ。
	//アニメーションの列挙。
	enum enAnimation {
		en_anim_Idle,
		en_anim_Attack,
		en_anim_Magic,
		en_anim_Damage,
		en_anim_Death,
		en_anim_num
	};
	Animation m_animation;								//アニメーション。
	AnimationClip m_animClip[en_anim_num];				//アニメーションクリップ。
	CVector3 m_position = CVector3::Zero();				//座標。
	CQuaternion m_rotation = CQuaternion::Identity();	//回転。

	//	ステータス
	Status m_statusBase;								//基礎ステータス。
	Status m_status;									//ステータス。
	AIData m_AI[6];										//AIデータ。
	char m_AIPath[64];									//AIデータのファイルパス。
	ACTResullt m_actRes;								//行動のリザルト。
	std::vector<ACTResullt> m_actResList;				//行動のリザルトの可変長配列。
	int m_scoringFlag = 0;								//評価のフラグ。
	int m_stateAI = en_state_Good;						//ステート。
	bool m_IsDeath = false;								//死亡フラグ。
	const float addTime = 1.0f / 144.0f * 4.0f;			//加算タイム。
	float m_activeTime = 0.0f;							//アクティブタイム。
	float m_coolTime = 30.0f;							//クールタイム。
	float buffTimeList[en_buff_num] = { 0.0f };			//バフタイム。
	Elements m_elemnts = en_elements_Empty;				//属性。

	//	ポインタとか。
	std::vector<MonsterBase*> m_teamMenber;				//自分のチーム。
	SkillBase* m_useSkill = nullptr;					//使用しているスキルのポインタ。
	MonsterBase* m_target = nullptr;					//スキルの対象。

	//UIを表示させる。
	StatusUI* m_UI;
};

