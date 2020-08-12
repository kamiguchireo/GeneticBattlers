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

	//使用率の数値を確率にする。
	void RateCalc();

protected:
	//	AIデータ。
	std::vector<AIData> m_AI;							//AIデータ。
};

