#pragma once
#include "Skill/SkillBase.h"
#include "monster/MonsterBase.h"


class SkillList : public IGameObject
{
public:
	SkillList();
	~SkillList();

	/// <summary>
	/// �X�L���f�[�^���擾����B
	/// </summary>
	/// <param name="table">�X�L���̑���
	/// <remarks>�O�ʏ�s��</remarks>
	/// <remarks>�P�񕜖��@</remarks>
	/// <remarks>�Q�o�t���@</remarks>
	/// </param>
	/// <param name="no">�X�L���i���o�[</param>
	/// <returns>�X�L���̃f�[�^</returns>
	SkillBase* GetSkillData(int table, int no);

	SkillBase* GetSkillAttack(int no);
	SkillBase* GetSkillHeal(int no);
	SkillBase* GetSkillBuff(int no);
	SkillBase* GetSkillMagic(int no);

	static SkillList* GetInstance()
	{
		return m_instance;
	}
private:
	static SkillList* m_instance;

	//typedef std::vector<SkillBase*>SkillTable;
	//std::vector<SkillTable>m_skillList;
};
////�P�̍U���B
//class Attack : public SkillBase
//{
//public:
//	Attack() {}
//	bool UseSkill(MonsterBase* attack,MonsterBase* target);
//private:
//	
//};
//
////������U���B
//class DoubleAttack : public SkillBase
//{
//public:
//	DoubleAttack() {}
//	bool UseSkill(MonsterBase* attack, MonsterBase* target);
//};
//
////�P�̉񕜁B
//class Heal : public SkillBase
//{
//public:
//	Heal(){}
//	bool UseSkill(MonsterBase* attack, MonsterBase* target);
//};
//
//class BuffSkill : public SkillBase
//{
//public:
//	BuffSkill() {}
//	bool UseSkill(MonsterBase* attack, MonsterBase* target);
//	void SetStatusBuff(StatusBuff status)
//	{
//		m_status = status;
//	}
//private:
//	StatusBuff m_status = en_buff_ATK;
//};
//
//class BuffSkillWide :public SkillBase
//{
//public:
//	BuffSkillWide() {}
//	bool UseSkill(MonsterBase* attack, MonsterBase* target);
//	void SetStatusBuff(StatusBuff status)
//	{
//		m_status = status;
//	}
//private:
//	StatusBuff m_status = en_buff_ATK;
//};