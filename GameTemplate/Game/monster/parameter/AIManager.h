#pragma once
#include "AIBase.h"

struct SkillData;

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
	/// AIデータのコピーを行う。
	/// </summary>
	/// <param name="copy">行動データ。</param>
	void SetAIData(const std::vector<AIData>& copy)
	{
		m_AI = copy;
	}
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
	/// 新しいスキルを決定する。
	/// </summary>
	/// <param name="data">データ情報。</param>
	/// <returns>決定したスキル番号。</returns>
	int DisideNewSkill(const SkillData& data);
	/// <summary>
	/// 確率の低いスキルを消す。
	/// </summary>
	void DeleteSkill();
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
	static const int NEW_SKILL_PLOB_WEIGHT[];
	static const int MAX_TARGET_COUNT;

private:
	char m_AIPath[128];									//AIデータのファイルパス。
	std::vector<ResultData> m_actResList;				//行動のリザルトの可変長配列。
	std::vector<SkillRate> m_skillRateList;				//スキルごとの使用率。
};

