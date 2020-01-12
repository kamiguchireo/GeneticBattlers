#pragma once
//前方宣言。
struct Skill;

/// <summary>
/// ステータスの構造体。
/// </summary>
/// <remarks>
/// 魔法攻撃力はINTだとint型と間違えそうだからMATとした。
/// </remarks>
struct Status {
	int HP,
		MP,
		ATK,
		DEF,
		MAT,
		MDF,
		DEX;
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
	/// <summary>
	/// ダメージを与える。
	/// </summary>
	/// <param name="damage">ダメージ量。</param>
	void Damage(int damage)
	{
		m_status.HP -= damage;
	}
	/// <summary>
	/// HPを回復させる。
	/// </summary>
	/// <param name="healing">回復量。</param>
	void Healing(int healing)
	{
		m_status.HP += healing;
	}
	/// <summary>
	/// MPを使う。
	/// </summary>
	/// <param name="mp">消費MP量。</param>
	void UseMP(int mp)
	{
		m_status.MP -= mp;
	}
	

protected:
	/// <summary>
	/// ステートに応じて行動を決める。
	/// </summary>
	void Action();

	SkinModel* m_model = nullptr;
	CVector3 m_position = CVector3::Zero();				//座標。
	CQuaternion m_rotation = CQuaternion::Identity();	//回転。
	Status m_status;									//ステータス。
	bool m_isDeath = false;								//戦闘不能フラグ。
	int m_stateAI = en_state_Good;						//ステート。
};

