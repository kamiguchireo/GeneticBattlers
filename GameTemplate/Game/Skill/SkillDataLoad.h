#pragma once

//static const int NOSKILL = -1;			//���̃X�L���ԍ��Ȃ��B
//static const int MAX_NEXT_SIZE = 3;		//���̃X�L���̃T�C�Y�B

enum StatusBuff;

typedef std::vector<int> NextSkills;
struct SkillData
{
	std::wstring Name;			//!<�X�L�����B
	float Power = 0.0f;			//!<�З́B
	float CoolTime = 0.0f;		//!<�N�[���^�C���B
	float HitRate = 0.0f;		//!<������
	int targetNum = 0;			//!<�U���Ώې��B
	StatusBuff StatusChange;	//!<�X�e�[�^�X�ω��B
	int SkillNo = 0;			//!<�X�L���ԍ�
	NextSkills NextSkillNo;		//!<���̃X�L���ԍ�
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
	//�C���X�^���X�̎擾�B
	static SkillDataLoad* GetInstance()
	{
		return m_instance;
	}
	//�X�L�����̎擾�B
	SkillData GetSkillAttack(int No);
	SkillData GetSkillHeal(int No);
	SkillData GetSkillBuff(int No);
	SkillData GetSkillDebuff(int No);
	//�ԍ�����X�L�������擾�B
	SkillData GetSkillData(int No);

	static const int MAX_TARGETS_MEMBER = 3;
private:
	const int NOSKILL = -1;			//���̃X�L���ԍ��Ȃ��B
	//const int MAX_NEXT_SIZE = 3;	//���̃X�L���̃T�C�Y�B
private:
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
	SkillDataList m_debuffSkillList;
};

