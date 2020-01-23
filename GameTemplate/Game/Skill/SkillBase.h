#pragma once

class MonsterBase;

enum Elements {
	en_elements_Fire,
	en_elements_Reef,
	en_elements_Water,
	en_elements_Empty,
	en_elements_Num
};

/// <summary>
/// スキルデータの構造体。
/// 名前。
/// スキルの威力。
/// 消費MP量。
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
	/// 属性相性を取得する。
	/// </summary>
	/// <param name="attack">攻撃側の属性。</param>
	/// <param name="target">対象側の属性。</param>
	/// <returns></returns>
	const float GetCompatibility(Elements attack, Elements target)
	{
		return m_elementsComp[attack][target];
	}
	//int型引数ver。
	float GetCompatibility(int attack, int target);

	int DamageCalcuration(MonsterBase* attack, MonsterBase* target);

	static float eleResist;		//相性不利。
	static float eleCritical;		//相性有利。
	static float eleNormal;		//相性普通。
protected:
	//SkillData m_data;			
	char skillName[30];
	float skillPower = 1.0f;
	int useMP = 0;
	Elements m_skillElements = en_elements_Empty;

	//属性相性。[攻撃側][対象側]
	const float m_elementsComp[en_elements_Num][en_elements_Num]=
	{
		{eleNormal	,	eleCritical	,	eleResist	,eleNormal},
		{eleResist	,	eleNormal	,	eleCritical	,eleNormal},
		{eleCritical,	eleResist	,	eleNormal	,eleNormal},
		{eleNormal	,	eleNormal	,	eleNormal	,eleNormal}
	};
};

