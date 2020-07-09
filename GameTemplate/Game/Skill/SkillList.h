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

};