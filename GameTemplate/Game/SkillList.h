#pragma once

/// <summary>
/// �X�L���f�[�^�̍\���́B
/// ���O�B
/// �X�L���̈З́B
/// ����MP�ʁB
/// </summary>
struct SkillData {
	char skillName[30];
	int skillPower = 1;
	int useMP = 0;
};

class SkillList
{
public:
	SkillList();
	~SkillList();
private:
	std::vector<SkillData>m_skillList;
};

