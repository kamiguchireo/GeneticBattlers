#pragma once
#include "Skill/SkillBase.h"
//前方宣言。
struct SkillData;
//enum Elements;
//class SkillBase;

const int ActionNum = 10;							//AIがとりうる行動の数。

/// <summary>
/// ステータスの構造体。
/// </summary>
/// <remarks>
/// 魔法攻撃力はINTだとint型と間違えそうだからMATとした。
/// </remarks>
struct Status {
	int HP		= 0,
		MP		= 0,
		ATK		= 0,
		DEF		= 0,
		MAT		= 0,
		MDF		= 0,
		DEX		= 0;
};

struct AIData {
	int skillNo = 0;
	float rate = 0.0f;
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
	void Init(const wchar_t* filePath);

	//座標を取得。
	const CVector3& GetPosition() const
	{
		return m_position;
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
	//描画処理。
	void Draw();
	//アクティブタイムを加算する。
	bool AddATB();
	/// <summary>
	/// ダメージを与える。
	/// </summary>
	/// <param name="damage">ダメージ量。</param>
	void Damage(int damage)
	{
		m_status.HP -= damage;
		m_status.HP = max(0, m_status.HP);
	}
	/// <summary>
	/// HPを回復させる。
	/// </summary>
	/// <param name="healing">回復量。</param>
	void Healing(int healing)
	{
		m_status.HP += healing;
		m_status.HP = min(m_status.HP, m_statusBase.HP);
	}
	/// <summary>
	/// MPを回復させる。
	/// </summary>
	/// <param name="healing">回復量。</param>
	void HealingMP(int healing)
	{
		m_status.MP += healing;
		m_status.MP = min(m_status.MP, m_statusBase.MP);
	}
	/// <summary>
	/// MPを使う。
	/// </summary>
	/// <param name="mp">消費MP量。</param>
	bool UseMP(int mp)
	{
		if (m_status.MP < mp) {
			return false;	//MPが足りないときの処理。
		}
		m_status.MP -= mp;
		return true;
	}
	/// <summary>
	/// スキルのターゲットを定める。
	/// </summary>
	/// <param name="list">ターゲットを選ぶためのリスト</param>
	void SelectUseSkill(const std::vector<MonsterBase*>& list);
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
	SkinModel m_model;									//モデルデータ。
	CVector3 m_position = CVector3::Zero();				//座標。
	CQuaternion m_rotation = CQuaternion::Identity();	//回転。
	Status m_statusBase;								//基礎ステータス。
	Status m_status;									//ステータス。
	AIData m_AI[3][ActionNum];							//AIデータ。
	bool m_isDeath = false;								//戦闘不能フラグ。
	int m_stateAI = en_state_Good;						//ステート。
	float m_activeTime = 0.0f;							//アクティブタイム。
	Elements m_elemnts = en_elements_Empty;				//属性。
	SkillBase* m_useSkill = nullptr;					//使用しているスキルのポインタ。
	MonsterBase* m_target = nullptr;					//スキルの対象。
};

