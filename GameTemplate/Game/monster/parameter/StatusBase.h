#pragma once

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
	en_buff_NONE,
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

class CStatusBase
{
public:
	CStatusBase() {};
	virtual ~CStatusBase() {};

	//ステータスの設定。
	//正直ファイルからロードしたい。
	void SetStatus(const Status& status)
	{
		m_statusBase = status;
		m_status = m_statusBase;
	}
	//ステータス(アタッカー用)
	void StatusAttaker();
	//ステータス(ヒーラー用)
	void StatusHealer();
	//ステータス(ヒーラー用)
	void StatusSupporter();

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
	//現在のステートの取得。
	const MonsterState& GetState()const
	{
		return m_stateAI;
	}
	//クールタイムを設定する。
	void SetCoolTime(float time)
	{
		m_coolTime = time;
	}
	//HPが0になっているかどうか。
	bool IsDeath() {
		//return m_stateAI == en_state_Death;
		return m_IsDeath;
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
	/// <summary>
	/// デバフを掛ける。
	/// </summary>
	/// <param name="status">デバフをかけるステータス</param>
	/// <param name="pow"></param>
	/// <param name="time"></param>
	/// <returns></returns>
	int Monster_Debuff(StatusBuff status, float pow, float time);
	//バフとデバフの値をステータスに合計する。
	void SumBufAndDebuff(int status);
	//バフをリセットする。
	void ResetBuff(int i);
	//デバフをリセットする。
	void ResetDebuff(int i);

	/// <summary>
	/// アクティブタイムの加算。
	/// </summary>
	/// <returns>溜まり切ったかの判定。</returns>
	virtual bool AddATB() = 0;

	void ClearATB()
	{
		m_activeTime = 0.0f;
	}
	/// <summary>
	/// ステートの更新処理。
	/// </summary>
	/// <param name="ui"></param>
	virtual void StateUpdate() = 0;

protected:
	//	ステータス
	Status m_statusBase;								//基礎ステータス。
	Status m_status;									//ステータス。
	MonsterState m_stateAI = en_state_Good;				//ステート。
	bool m_IsDeath = false;								//キャラクター死亡フラグ。
	float m_activeTime = 0.0f;							//アクティブタイム。
	float m_coolTime = 30.0f;							//クールタイム。
	float m_buffTimeList[en_buff_num] = { 0.0f };			//バフタイム。
	int m_buffValues[en_buff_num] = { 0 };					//バフによる上昇値
	float m_debuffTimeList[en_buff_num] = { 0.0f };			//デバフタイム。作るかなぁ？
	int m_debuffValues[en_buff_num] = { 0 };				//デバフによる低下値
};

