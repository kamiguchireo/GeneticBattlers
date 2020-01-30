#pragma once

class MonsterBase;

enum Elements {
	en_elements_Fire,		//!<�������B
	en_elements_Reef,		//!<�������B
	en_elements_Water,		//!<�������B
	en_elements_Empty,		//!<�������B
	en_elements_Num
};

/// <summary>
/// �X�L���f�[�^�̍\���́B
/// ���O�B
/// �X�L���̈З́B
/// ����MP�ʁB
/// </summary>
struct SkillData {
	char skillName[30];
	float skillPower = 1.0f;
	int useMP = 0;
};

class SkillBase : public IGameObject
{
public:
	SkillBase();
	~SkillBase();
	virtual bool UseSkill(MonsterBase* attack, MonsterBase* target) = 0;
	/// <summary>
	/// �����������擾����B
	/// </summary>
	/// <param name="attack">�U�����̑����B</param>
	/// <param name="target">�Ώۑ��̑����B</param>
	/// <returns></returns>
	const float GetCompatibility(Elements attack, Elements target)
	{
		return m_elementsComp[attack][target];
	}
	//int�^����ver�B
	float GetCompatibility(int attack, int target);
	/// <summary>
	/// �_���[�W�v�Z�B
	/// </summary>
	/// <param name="attack">�U������L�����B</param>
	/// <param name="target">�^�[�Q�b�g�̃L�����B</param>
	/// <returns>�_���[�W�ʁB</returns>
	int DamageCalcuration(MonsterBase* attack, MonsterBase* target);

	static float eleResist;		//�����s���B
	static float eleCritical;		//�����L���B
	static float eleNormal;		//�������ʁB
protected:
	//SkillData m_data;			
	char skillName[30];
	float skillPower = 1.0f;
	int useMP = 0;
	int m_skillNo = 0;
	Elements m_skillElements = en_elements_Empty;
	bool isMagic = false;

	//���������B[�U����][�Ώۑ�]
	const float m_elementsComp[en_elements_Num][en_elements_Num]=
	{
		{eleNormal	,	eleCritical	,	eleResist	,eleNormal},
		{eleResist	,	eleNormal	,	eleCritical	,eleNormal},
		{eleCritical,	eleResist	,	eleNormal	,eleNormal},
		{eleNormal	,	eleNormal	,	eleNormal	,eleNormal}
	};
};

