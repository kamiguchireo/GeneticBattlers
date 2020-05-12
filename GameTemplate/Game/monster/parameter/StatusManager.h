#pragma once

class StatusUI;

/// <summary>
/// ステータスの構造体。
/// </summary>
/// <remarks>
/// 魔法攻撃力はINTだとint型と間違えそうだからMATとした。
/// </remarks>
struct Status {
	int HP = 0,
		//MP		= 0,
		ATK = 0,
		DEF = 0,
		MAT = 0,
		MDF = 0,
		DEX = 0;
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

//ステータスを管理するクラス。
class StatusManager
{
public:
	StatusManager() {};
	~StatusManager() {};

	//ステータスの設定。
	//正直ファイルからロードしたい。
	void SetStatus(const Status& status)
	{
		m_statusBase = status;
		m_status = m_statusBase;
	}
	void SetUI(StatusUI* UI)
	{
		m_UI = UI;
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
	const MonsterState& GetState()const
	{
		return m_stateAI;
	}
	////モンスターの属性を取得。
	//const Elements& GetElements() const
	//{
	//	return m_elemnts;
	//}
	//クールタイムを設定する。
	void SetCoolTime(float time)
	{
		m_coolTime = time;
	}
	//HPが0になっているかどうか。
	bool IsDeath() {
		return m_stateAI == en_state_Death;
	}
	//死亡フラグを設定する。
	void SetDeath(bool flag) {
		m_IsDeath = flag;
	}
	/// <summary>
	/// ダメージを与える。
	/// </summary>
	/// <param name="damage">ダメージ量。</param>
	/// <returns>入ったダメージ量。</returns>
	int Damage(int damage)
	{
		//現在HPとダメージ量の比較。
		int res = min(m_status.HP, damage);
		m_status.HP -= res;
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
	int Monster_Buff(StatusBuff status, float pow, float time);

	//バフをリセットする。
	void ResetBuff(int i);

	bool AddATB();			//アクティブタイムを加算する。

	/// <summary>
	///ステートの更新処理。 
	/// </summary>
	void StateUpdate();

private:
	//	ステータス
	Status m_statusBase;								//基礎ステータス。
	Status m_status;									//ステータス。
	MonsterState m_stateAI = en_state_Good;						//ステート。
	bool m_IsDeath = false;								//キャラクター死亡フラグ。
	const float addTime = 1.0f / 144.0f * 4.0f;			//加算タイム。
	float m_activeTime = 0.0f;							//アクティブタイム。
	float m_coolTime = 30.0f;							//クールタイム。
	float buffTimeList[en_buff_num] = { 0.0f };			//バフタイム。

	StatusUI* m_UI = nullptr;
};

