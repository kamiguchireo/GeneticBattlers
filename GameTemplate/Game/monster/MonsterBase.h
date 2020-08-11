#pragma once
//#include "Skill/SkillBase.h"
#include "parameter/StatusManager.h"
#include "parameter/StatusUI.h"
#include "parameter/GAManager.h"

struct Status;

//行動のリザルト。
//!<damage		ダメージ値。
//!<skillNo		スキル番号。
//!<target		ターゲット値。
//!<score		評価。
struct ACTResullt {
	int damage = 0;
	int skillNo = 0;
	int target = 0;
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
	virtual ~MonsterBase();

	void PreRender()override;
	void Update()override;
	void Draw()override;

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
	const StatusManager& GetStatusManager() const
	{
		return m_status;
	}
	//チームメンバーリストを取得。
	const std::vector<MonsterBase*>& GetTeamMenber()const
	{
		return m_teamMenber;
	}
	GAManager& GetGAManager()
	{
		return m_GAData;
	}
	//ステータスの設定。
	//正直ファイルからロードしたい。
	void SetStatus(int hp, int atk, int def, int mat, int mdf, int dex);
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
	//拡大率の設定。
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
	//敵か味方かの設定。デフォルトfalse(味方),true(敵)
	void SetIsEnemy(bool flag = false)
	{
		m_isEnemy = flag;
	}
	//UIの位置を設定する。
	void SetUIPos(const CVector3& pos)
	{
		m_UIpos = pos;
	}
	//味方チームのリストを設定。
	void SetTeamMenber(const std::vector<MonsterBase*>& list)
	{
		m_teamMenber = list;
	}

	/// <summary>
	/// モデル関係の処理もクラス分けしたほうがいいんかなぁ？
	/// </summary>

	//魔法のアニメーションを再生。
	void AnimationMagic()
	{
		m_animation.Play(en_anim_Magic, 0.3f);
	}
	//攻撃のアニメーション
	void AnimationAttack()
	{
		m_animation.Play(en_anim_Attack, 0.3f);
	}
	//待機状態のアニメーション。
	void AnimationIdle()
	{
		m_animation.Play(en_anim_Idle, 0.3f);
	}

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
	//ダメージのリザルトを取得。
	void SetDamageResult(int res)
	{
		m_actRes.damage = res;
	}

	//アクティブタイム加算。
	bool AddATB()
	{
		return m_status.AddATB();
	}
	//ステートのアップデート。
	void StateUpdate()
	{
		m_status.StateUpdate();
	}

	/// <summary>
	/// この辺の処理ステータスのほうでまとめたほうがいいのでは？
	/// </summary>

	/// <summary>
	/// ダメージを与える。
	/// </summary>
	/// <param name="damage">ダメージ量。</param>
	/// <returns>入ったダメージ量。</returns>
	int Damage(int damage);

	/// <summary>
	/// HPを回復させる。
	/// </summary>
	/// <param name="healing">回復量。</param>
	/// <returns>回復できた量。</returns>
	int Healing(int healing) {
		if (IsDeath()) return 0;		//死亡時は回復しない。
		return m_status.Healing(healing);
	};

	/// <summary>
	/// バフをかける。
	/// </summary>
	/// <param name="status">バフをかけるステータス。</param>
	/// <param name="pow">バフの威力。</param>
	/// <param name="time">バフの効果時間。</param>
	/// <returns>効果値。</returns>
	int MonsterBuffAndDebuff(StatusBuff status,float pow,float time);

	/// <summary>
	/// スキルのターゲットを定める。
	/// </summary>
	/// <param name="e_team">敵のチーム。</param>
	/// <param name="m_team">味方のチーム。</param>
	/// <param name="skill">スキル番号のバッファ。</param>
	/// <param name="target">ターゲット番号のバッファ。</param>
	virtual void SelectUseSkill(
		const std::vector<MonsterBase*>& e_team, 
		const std::vector<MonsterBase*>& m_team,
		int& skill, int& target);

	/// <summary>
	/// binファイルからデータを読み込む。
	/// </summary>
	/// <param name="filePath">ファイルパス。</param>
	void Init(const char* filePath);
private:
	static const float SOUND_VOL;

protected:
	/// <summary>
	/// デフォルトの行動のデータを読み込むためのファイルパス。
	/// </summary>
	virtual const char* GetDefaultDataPath() = 0;

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
	CVector3 m_scale = CVector3::One();					//拡大率。

	StatusManager m_status;								//ステータス。

	//	AIデータ。
	GAManager m_GAData;									//行動テーブルのデータ。
	ACTResullt m_actRes = { 0,0,0 };					//行動のリザルト。
	int m_scoringFlag = 0;								//評価のフラグ。

	//	ポインタとか。
	std::vector<MonsterBase*> m_teamMenber;				//自分のチーム。
	MonsterBase* m_target = nullptr;					//スキルの対象。

	//UIを表示させる。
	StatusUI* m_UI;
	CVector3 m_UIpos = CVector3::Zero();
	bool m_isEnemy = false;
};

