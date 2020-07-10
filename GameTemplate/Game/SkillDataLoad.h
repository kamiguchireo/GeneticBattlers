#pragma once

struct SkillData
{
	wchar_t Name[64];
	float Power = 0.0f;
	float CoolTime = 0.0f;
	float HitRate = 0.0f;
	int SkillNo = 0;
};

typedef std::list<SkillData> SkillDataList;

class SkillDataLoad:public IGameObject
{
public:
	SkillDataLoad();
	~SkillDataLoad();
	SkillDataLoad* GetInstance()
	{
		return m_instance;
	}

private:
	enum EnSkillType
	{
		en_Attack,
		en_Heal,
		en_Buff,
		en_SkillTypeNum
	};

	void LoadData(const char* filePath, EnSkillType type);

	static SkillDataLoad* m_instance;

	SkillDataList m_attackSkillList;
	SkillDataList m_healSkillList;
	SkillDataList m_buffSkillList;
};

