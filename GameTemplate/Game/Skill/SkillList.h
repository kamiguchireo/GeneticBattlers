#pragma once
#include "Skill/SkillBase.h"
#include "monster/MonsterBase.h"


class SkillList : public IGameObject
{
public:
	SkillList();
	~SkillList();

	/// <summary>
	/// スキルデータを取得する。
	/// </summary>
	/// <param name="table">スキルの属性
	/// <remarks>０通常行動</remarks>
	/// <remarks>１回復魔法</remarks>
	/// <remarks>２バフ魔法</remarks>
	/// </param>
	/// <param name="no">スキルナンバー</param>
	/// <returns>スキルのデータ</returns>
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
////単体攻撃。
//class Attack : public SkillBase
//{
//public:
//	Attack() {}
//	bool UseSkill(MonsterBase* attack,MonsterBase* target);
//private:
//	
//};
//
////複数回攻撃。
//class DoubleAttack : public SkillBase
//{
//public:
//	DoubleAttack() {}
//	bool UseSkill(MonsterBase* attack, MonsterBase* target);
//};
//
////単体回復。
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