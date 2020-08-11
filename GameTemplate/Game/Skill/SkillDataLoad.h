#pragma once

//static const int NOSKILL = -1;			//次のスキル番号なし。
//static const int MAX_NEXT_SIZE = 3;		//次のスキルのサイズ。

enum StatusBuff;

typedef std::vector<int> NextSkills;
struct SkillData
{
	std::wstring Name;			//!<スキル名。
	float Power = 0.0f;			//!<威力。
	float CoolTime = 0.0f;		//!<クールタイム。
	float HitRate = 0.0f;		//!<命中率
	int targetNum = 0;			//!<攻撃対象数。
	StatusBuff StatusChange;	//!<ステータス変化。
	int SkillNo = 0;			//!<スキル番号
	NextSkills NextSkillNo;		//!<次のスキル番号
};

enum EnSkillType
{
	en_Attack,
	en_Heal,
	en_Buff,
	en_Debuff,
	en_SkillTypeNum
};

typedef std::vector<SkillData> SkillDataList;

class SkillDataLoad : public IGameObject
{
public:
	SkillDataLoad();
	~SkillDataLoad();
	bool Start();
	//インスタンスの取得。
	static SkillDataLoad* GetInstance()
	{
		return m_instance;
	}
	//スキル情報の取得。
	SkillData GetSkillAttack(int No);
	SkillData GetSkillHeal(int No);
	SkillData GetSkillBuff(int No);
	SkillData GetSkillDebuff(int No);
	//番号からスキル情報を取得。
	SkillData GetSkillData(int No);

	static const int MAX_TARGETS_MEMBER = 3;
private:
	const int NOSKILL = -1;			//次のスキル番号なし。
	//const int MAX_NEXT_SIZE = 3;	//次のスキルのサイズ。
private:
	/// <summary>
	/// ファイルからデータを読み込む。
	/// </summary>
	/// <param name="FilePath">ファイルパス</param>
	/// <param name="skillType">スキルタイプの指定</param>
	void LoadData(const char* FilePath, EnSkillType skillType);


	static SkillDataLoad* m_instance;

	SkillDataList m_attackSkillList;
	SkillDataList m_healSkillList;
	SkillDataList m_buffSkillList;
	SkillDataList m_debuffSkillList;
};

