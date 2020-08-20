#pragma once

struct Status;
struct SkillData;

class CStatusBase;
class SkillDataLoad;

/// <summary>
/// �X�L�����ʌv�Z�N���X�B
/// </summary>

class SkillCalculator
{
public:
	SkillCalculator();
	~SkillCalculator();

	//�X�L���̏������v�Z����B
	int SkillCalculation(CStatusBase* user, CStatusBase* target,int SkillNo);
	int SkillCalculation(CStatusBase* user, std::vector<CStatusBase*> targets, int SkillNo);
	/// <summary>
	/// MP������Ă��邩�ǂ����B
	/// </summary>
	/// <param name="user">�g�p�҂̃X�e�[�^�X�B</param>
	/// <param name="SkillNo">�g�p����X�L���ԍ��B</param>
	/// <returns>�g�p�\���ǂ����Btrue�Ŏg�p�\,false��MP������Ă��Ȃ��B</returns>
	bool IsAvailableSkill(CStatusBase* user, const int SkillNo);

private:
	//�֐��B
	int AttackCalculation(CStatusBase* user, CStatusBase* target, SkillData& skill);		//�U���X�L���B
	int HealCalculation(CStatusBase* user, CStatusBase* target, SkillData& skill);		//�񕜃X�L���B
	int BuffCalculation(CStatusBase* user, CStatusBase* target, SkillData& skill);		//�o�t�X�L���B
	int DebuffCalculation(CStatusBase* user, CStatusBase* target, SkillData& skill);		//�f�o�t�X�L���B

	SkillDataLoad* m_skillData = nullptr;	//�X�L���������̃N���X
	const float BUFF_TIME = 100.0f;		//�X�e�[�^�X�ω��̊�{���ʎ��ԁB
};

