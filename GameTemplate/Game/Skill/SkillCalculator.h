#pragma once

struct Status;

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

private:
	//�֐��B
	int AttackCalculation(CStatusBase* user, CStatusBase* target, int SkillNo);		//�U���X�L���B
	int HealCalculation(CStatusBase* user, CStatusBase* target, int SkillNo);		//�񕜃X�L���B
	int BuffCalculation(CStatusBase* user, CStatusBase* target, int SkillNo);		//�o�t�X�L���B
	int DebuffCalculation(CStatusBase* user, CStatusBase* target, int SkillNo);		//�f�o�t�X�L���B

	SkillDataLoad* m_skillData = nullptr;	//�X�L���������̃N���X
	const float BUFF_TIME = 100.0f;		//�X�e�[�^�X�ω��̊�{���ʎ��ԁB
};

