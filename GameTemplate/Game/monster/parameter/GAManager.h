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

struct ResultData {
	int damage = 0;
	int skillNo = 0;
	int target = 0;
};

class GAManager
{
public:
	GAManager();
	~GAManager();
	/// <summary>
	/// ファイルパスからGAをロードする。
	/// </summary>
	/// <param name="filePath">ファイルパス。</param>
	bool Load(const char* filePath);
	/// <summary>
	/// デフォルトのデータをロードするときに使う。
	/// </summary>
	/// <param name="filePath">デフォルトの数値の入ったファイルパス。</param>
	void LoadDefault(const char* filePath);
	/// <summary>
	/// 通信で取得したデータを取り込む。
	/// </summary>
	/// <param name="copy">行動データ。</param>
	void Init(const std::vector<AIData>& copy)
	{
		m_AI = copy;
	}
	/// <summary>
	/// GAを記録する。
	/// </summary>
	void Save();
	/// <summary>
	/// GAの更新を行う。
	/// </summary>
	void AIUpdate();
	/// <summary>
	/// 新しい行動を追加
	/// </summary>
	void AddNewSkill();
	/// <summary>
	/// 行動を乱数で決定する。
	/// </summary>
	/// <param name="skill">決定したスキルを取得する。</param>
	/// <param name="target">決定したターゲットを取得する。</param>
	void ActionDicide(int& skill, int& target);
	/// <summary>
	/// 行動のリザルトを積む。
	/// </summary>
	/// <param name="damage">ダメージ量。</param>
	/// <param name="skill">使用スキル。</param>
	/// <param name="target">ターゲット。</param>
	void PushBackResult(int damage, int skill, int target)
	{
		ResultData res = { damage,skill,target };
		m_actResList.push_back(res);
	}
private:
	static const float SKILL_NEW_RATE;
	static const float FIRST_RATE;
	static const int MAX_TARGET_COUNT;

private:
	//	AIデータ。
	std::vector<AIData> m_AI;							//AIデータ。
	char m_AIPath[128];									//AIデータのファイルパス。
	std::vector<ResultData> m_actResList;				//行動のリザルトの可変長配列。
};

