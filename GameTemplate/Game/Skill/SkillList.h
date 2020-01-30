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
	/// スキルデータを取得する。
	/// </summary>
	/// <param name="table">スキルの属性
	/// <remarks>０通常行動</remarks>
	/// <remarks>１炎魔法</remarks>
	/// <remarks>２水魔法</remarks>
	/// <remarks>３木魔法</remarks>
	/// <remarks>４回復、バフ魔法</remarks>
	/// </param>
	/// <param name="no">スキルナンバー</param>
	/// <returns>スキルのデータ</returns>
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
		sprintf_s(skillName, "通常攻撃");
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
		sprintf_s(skillName, "休憩");
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
		sprintf_s(skillName, "ファイア");
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
		sprintf(skillName, "ヒール");
		skillPower = 1.0f;
		useMP = 10;
		m_skillNo = 400;
		m_skillElements = en_elements_Empty;
		isMagic = true;
	}
	bool UseSkill(MonsterBase* attack, MonsterBase* target);
};