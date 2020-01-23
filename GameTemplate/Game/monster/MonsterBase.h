#pragma once
#include "Skill/SkillBase.h"
//前方宣言。
struct SkillData;
//enum Elements;
//class SkillBase;

/// <summary>
/// ステータスの構造体。
/// </summary>
/// <remarks>
/// 魔法攻撃力はINTだとint型と間違えそうだからMATとした。
/// </remarks>
struct Status {
	int MAXHP	= 0,
		HP		= 0,
		MAXMP	= 0,
		MP		= 0,
		ATK		= 0,
		DEF		= 0,
		MAT		= 0,
		MDF		= 0,
		DEX		= 0;
		//baseATK,
		//baseDEF,
		//baseMAT,
		//baseMDF,
		//baseDEX;
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
	MonsterBase();
	~MonsterBase();
	
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
		m_status = status;
		m_status.HP = m_status.MAXHP;
		m_status.MP = m_status.MAXMP;
	}
	//座標の設定。
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//描画処理。
	void Draw();
	//
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
		m_status.HP = min(0, m_status.MAXHP);
	}
	/// <summary>
	/// MPを使う。
	/// </summary>
	/// <param name="mp">消費MP量。</param>
	void UseMP(int mp)
	{
		m_status.MP -= mp;
	}
	/// <summary>
	/// スキルを使用する。
	/// </summary>
	/// <param name="skill">スキルデータへのポインタ。</param>
	/// <param name="target">ターゲット。</param>
	void UseSkill(SkillData* skill,MonsterBase& target);

	//void SelectUseSkill(MonsterBase* list);
	void SelectUseSkill(const std::vector<MonsterBase*>& list);
	//ステートの更新処理。
	void StateUpdate();
	/// <summary>
	/// ステートに応じて行動を決める。
	/// </summary>
	bool Action();

	virtual bool Action_good() { return false; }
	virtual bool Action_usually() { return false; }
	virtual bool Action_bad() { return false; }
	

protected:
	SkinModel m_model;									//モデルデータ。
	CVector3 m_position = CVector3::Zero();				//座標。
	CQuaternion m_rotation = CQuaternion::Identity();	//回転。
	Status m_status;									//ステータス。
	bool m_isDeath = false;								//戦闘不能フラグ。
	int m_stateAI = en_state_Good;						//ステート。
	float m_activeTime = 0.0f;							//アクティブタイム。
	Elements m_elemnts = en_elements_Empty;				//属性。
	SkillBase* m_useSkill = nullptr;					//使用しているスキルのポインタ。
	MonsterBase* m_target = nullptr;					//スキルの対象。
};

