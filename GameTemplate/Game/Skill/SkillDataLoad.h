#pragma once

typedef std::vector<int> NextSkills;
struct SkillData
{
	std::wstring Name;
	float Power = 0.0f;
	float CoolTime = 0.0f;
	float HitRate = 0.0f;
	int SkillNo = 0;
	NextSkills NextSkillNo;
};

typedef std::vector<SkillData> SkillDataList;

class SkillDataLoad : public IGameObject
{
public:
	SkillDataLoad();
	~SkillDataLoad();
	bool Start();
	//�C���X�^���X�̎擾�B
	static SkillDataLoad* GetInstance()
	{
		return m_instance;
	}
	//�X�L�����̎擾�B
	SkillData GetSkillData(int No);

private:
	enum EnSkillType
	{
		en_Attack,
		en_Heal,
		en_Buff,
		en_SkillTypeNum
	};
	/// <summary>
	/// �t�@�C������f�[�^��ǂݍ��ށB
	/// </summary>
	/// <param name="FilePath">�t�@�C���p�X</param>
	/// <param name="skillType">�X�L���^�C�v�̎w��</param>
	void LoadData(const char* FilePath, EnSkillType skillType);


	static SkillDataLoad* m_instance;

	SkillDataList m_attackSkillList;
	SkillDataList m_healSkillList;
	SkillDataList m_buffSkillList;
};

