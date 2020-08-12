#pragma once
#include "AIBase.h"

struct ResultData {
	int damage = 0;
	int skillNo = 0;
	int target = 0;
};

struct SkillRate
{
	int skillNo = 0;
	float rate = 0.0f;
};

class AIManager : public AIBase
{
public:
	AIManager();
	~AIManager();
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
	/// GAを記録する。
	/// </summary>
	void Save();
	/// <summary>
	/// AIの更新を行う。
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
	//スキルごとの使用率を計算する。
	void SkillRateCalc();

private:
	static const float SKILL_NEW_RATE;
	static const float FIRST_RATE;
	static const int MAX_TARGET_COUNT;

private:
	char m_AIPath[128];									//AIデータのファイルパス。
	std::vector<ResultData> m_actResList;				//行動のリザルトの可変長配列。
	std::vector<SkillRate> m_skillRateList;				//スキルごとの使用率。
};

