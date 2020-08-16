#pragma once


//行動テーブルのデータ。
//!<skillNo		スキル番号。
//!<target		ターゲット番号。
//!<rate		使用頻度。
struct AIData {
	int skillNo = 0;		//ここは固定値
	int target = 0;			//ここも固定値
	float rate = 0.0f;		//ここが遺伝子として変化する
};

class AIBase
{
public:
	AIBase();
	virtual ~AIBase();

	/// <summary>
	/// AIデータのコピーを行う。
	/// </summary>
	/// <param name="copy">行動データ。</param>
	void Init(const std::vector<AIData>& copy)
	{
		m_AI = copy;
	}
	//AI情報を取得。
	const std::vector<AIData>& GetAIData()
	{
		return m_AI;
	}
	/// <summary>
	/// 行動を乱数で決定する。
	/// </summary>
	/// <param name="skill">決定したスキルを取得する。</param>
	/// <param name="target">決定したターゲットを取得する。</param>
	void ActionDicide(int& skill, int& target);

protected:
	//使用率の数値を確率にする。
	void RateCalc();

protected:
	//	AIデータ。
	std::vector<AIData> m_AI;							//AIデータ。
};

