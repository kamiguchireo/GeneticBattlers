#pragma once
#include "Skill/SkillBase.h"

struct SkillData;
class MonsterBase;


class SkillList : public IGameObject
{
public:
	SkillList();
	~SkillList();

	static SkillList* m_instance;
	static SkillList* GetInstance()
	{
		return m_instance;
	}
	/// <summary>
	/// �X�L���f�[�^���擾����B
	/// </summary>
	/// <param name="table">�X�L���̑���
	/// <remarks>�O�ʏ�s��</remarks>
	/// <remarks>�P�����@</remarks>
	/// <remarks>�Q�����@</remarks>
	/// <remarks>�R�ؖ��@</remarks>
	/// <remarks>�S�񕜁A�o�t���@</remarks>
	/// </param>
	/// <param name="no">�X�L���i���o�[</param>
	/// <returns>�X�L���̃f�[�^</returns>
	SkillBase* GetSkillData(int table, int no)
	{
		return m_skillList[table][no];
	}

private:
	typedef std::vector<SkillBase*>SkillTable;
	//SkillTable m_skillList[5];
	std::vector<SkillTable>m_skillList;
};

class Attack : public SkillBase
{
public:
	Attack() {
		sprintf_s(skillName, "�ʏ�U��");
		skillPower = 1.0f;
		useMP = 0;
		m_skillNo = 0;
		m_skillElements = en_elements_Empty;
		isMagic = false;
	}
	bool UseSkill(MonsterBase* attack,MonsterBase* target);
private:
	
};

class Rest : public SkillBase
{
public:
	Rest()
	{
		sprintf_s(skillName, "�x�e");
		skillPower = 0.5f;
		useMP = 0;
		m_skillNo = 1;
		m_skillElements = en_elements_Empty;
		isMagic = false;
	}
	bool UseSkill(MonsterBase* attack, MonsterBase* target);
};

class Fire : public SkillBase
{
public:
	Fire()
	{
		sprintf_s(skillName, "�t�@�C�A");
		skillPower = 1.0f;
		useMP = 10;
		m_skillNo = 100;
		m_skillElements = en_elements_Fire;
		isMagic = true;
	}
	bool UseSkill(MonsterBase* attack, MonsterBase* target);
};

class Heal : public SkillBase
{
public:
	Heal()
	{
		sprintf(skillName, "�q�[��");
		skillPower = 1.0f;
		useMP = 10;
		m_skillNo = 400;
		m_skillElements = en_elements_Empty;
		isMagic = true;
	}
	bool UseSkill(MonsterBase* attack, MonsterBase* target);
};