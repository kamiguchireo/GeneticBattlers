#pragma once
#include "Skill/SkillBase.h"
#include "parameter/StatusManager.h"
#include "parameter/StatusUI.h"

//const int AI_SIZE = 6;							//AIがとりうる行動の数。
//const int AI_SIZE = 6;							//AIがとりうる行動の数。

struct Status;

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

/************************/
/*		基底クラス		*/
/************************/
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
	StatusManager& GetStatusManager()
	{
		return m_status;
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
		m_status.SetStatus(status);
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

	void Draw();			//描画処理とかをまとめたもの。

	//クールタイムを設定する。
	void SetCoolTime(float time)
	{
		m_status.SetCoolTime(time);
	}
	//HPが0になっているかどうか。
	bool IsDeath() {
		return m_status.IsDeath();
	}

	//行動の評価を行う。
	virtual bool ACTScoring();

	//行動のリザルトの設定。
	//!<No			スキル番号。
	//!<damage		ダメージ値。
	void SetActResult(int No ,int damage) {
		m_actRes.skillNo = No;
		m_actRes.damage = damage;
	}

	/// <summary>
	/// ダメージを与える。
	/// </summary>
	/// <param name="damage">ダメージ量。</param>
	/// <returns>入ったダメージ量。</returns>
	int Damage(int damage)
	{
		if (m_status.IsDeath()) return 0;
		//アニメーション。
		m_animation.Play(en_anim_Damage, 0.3f);

		return m_status.Damage(damage);
	}

	/// <summary>
	/// HPを回復させる。
	/// </summary>
	/// <param name="healing">回復量。</param>
	/// <returns>回復できた量。</returns>
	int Healing(int healing) {
		return m_status.Healing(healing);
	};

	/// <summary>
	/// バフをかける。
	/// </summary>
	/// <param name="status">バフをかけるステータス。</param>
	/// <param name="pow">バフの威力。</param>
	/// <param name="time">バフの効果時間。</param>
	/// <returns>効果値。</returns>
	int Monster_Buff(StatusBuff status,float pow,float time);

	//バフをリセットする。
	void ResetBuff(int i) 
	{
		m_status.ResetBuff(i);
	};

	/// <summary>
	/// スキルのターゲットを定める。
	/// </summary>
	/// <param name="e_team">敵のチーム。</param>
	/// <param name="m_team">味方のチーム。</param>
	virtual void SelectUseSkill(const std::vector<MonsterBase*>& e_team, const std::vector<MonsterBase*>& m_team);

	//行動をさせる。
	virtual bool BattleAction() = 0;

	/// <summary>
	/// binファイルからデータを読み込む。
	/// </summary>
	/// <param name="filePath">ファイルパス。</param>
	virtual void Init(const char* filePath);
	/// <summary>
	/// binファイルにデータを書き込む。
	/// </summary>
	/// <param name="filePath">ファイルパス。</param>
	virtual void Save(const char* filePath);

protected:
	/// <summary>
	/// デフォルトの行動を作り出す。
	/// </summary>
	virtual void MakeData() {};
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

	StatusManager m_status;								//ステータス。

	//	AIデータ。
	std::vector<AIData> m_AI;							//AIデータ。
	char m_AIPath[64];									//AIデータのファイルパス。
	ACTResullt m_actRes;								//行動のリザルト。
	std::vector<ACTResullt> m_actResList;				//行動のリザルトの可変長配列。
	int m_scoringFlag = 0;								//評価のフラグ。

	//	ポインタとか。
	std::vector<MonsterBase*> m_teamMenber;				//自分のチーム。
	SkillBase* m_useSkill = nullptr;					//使用しているスキルのポインタ。
	MonsterBase* m_target = nullptr;					//スキルの対象。

	//UIを表示させる。
	StatusUI* m_UI;
};

