#pragma once
#include "Skill/SkillBase.h"
//#include "monster/MonsterBase.h"

class SkillDataLoad;

class SkillList
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
	/// <remarks>３デバフ魔法</remarks>
	/// </param>
	/// <param name="no">スキルナンバー</param>
	/// <returns>スキルのデータ</returns>
	SkillBase* NewSkillData(int table, int no);


	static SkillList* GetInstance()
	{
		return m_instance;
	}
private:
	SkillBase* NewSkillAttack(int no);
	SkillBase* NewSkillHeal(int no);
	SkillBase* NewSkillBuff(int no);
	SkillBase* NewSkillDebuff(int no);
	static SkillList* m_instance;
	SkillDataLoad* m_skillData = nullptr;
};