#pragma once
#include "Skill/SkillBase.h"

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
	/// スキルデータを取得する。
	/// </summary>
	/// <param name="table">スキルの属性
	/// <remarks>０通常行動</remarks>
	/// <remarks>１回復魔法</remarks>
	/// <remarks>２バフ魔法</remarks>
	/// </param>
	/// <param name="no">スキルナンバー</param>
	/// <returns>スキルのデータ</returns>
	SkillBase* GetSkillData(int table, int no)
	{
		return m_skillList[table][no];
	}

private:
	typedef std::vector<SkillBase*>SkillTable;
	std::vector<SkillTable>m_skillList;
};

//単体攻撃。
class Attack : public SkillBase
{
public:
	Attack() {}
	bool UseSkill(MonsterBase* attack,MonsterBase* target);
private:
	
};

//複数回攻撃。
class DoubleAttack : public SkillBase
{
public:
	DoubleAttack() {}
	bool UseSkill(MonsterBase* attack, MonsterBase* target);
};

//単体回復。
class Heal : public SkillBase
{
public:
	Heal(){}
	bool UseSkill(MonsterBase* attack, MonsterBase* target);
};