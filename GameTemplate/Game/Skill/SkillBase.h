#pragma once
#include "SourceFile/graphic/Effect/CEffect.h"

class MonsterBase;

enum Elements {
	en_elements_Fire,		//!<炎属性。
	en_elements_Reef,		//!<草属性。
	en_elements_Water,		//!<水属性。
	en_elements_Empty,		//!<無属性。
	en_elements_Num
};

class SkillBase : public IGameObject
{
public:
	SkillBase();
	~SkillBase();
	virtual bool UseSkill(MonsterBase* attack, MonsterBase* target) = 0;
	/*
	スキルの設定をする。
	char*		name	!<スキルの名前。
	float		power	!<スキルの威力。
	float		time	!<クールタイム。
	float		acc		!<スキルの命中率。
	int			no		!<スキル番号。
	Elements	ele		!<スキルの属性。
	bool		isMagic	!<魔法かどうか。
	*/
	void InitSkill(const char* name,
		float power,
		float time,
		float acc,
		int no,
		Elements ele = en_elements_Empty,
		bool isMagic = false);
	//スキルの名前を設定。
	void SetSkillName(const char* name)
	{
		sprintf_s(skillName, name);
	}
	//スキルの威力(倍率)を設定
	void SetSkillPower(float power)
	{
		skillPower = power;
	}
	//クールタイムを設定する。
	void SetCoolTime(float time)
	{
		coolTime = time;
	}
	//命中率を設定する。
	void SetAccuracy(float acc)
	{
		accuracy = acc;
	}
	//スキル番号を設定する。
	void SetSkillNo(int no)
	{
		m_skillNo = no;
	}
	//
	void SetElements(Elements ele)
	{
		m_skillElements = ele;
	}
	//魔法かどうかを設定する。
	void SetMagic(bool isMagic)
	{
		m_isMagic = isMagic;
	}
	//再生するエフェクトのファイルパスを設定する。
	void SetEffect(const wchar_t* path)
	{
		swprintf(effectPath, path);
	}
	//スキル番号を取得する。
	const int GetSkillNo()const
	{
		return m_skillNo;
	}
	//
	const bool GetIsMagic()const
	{
		return m_isMagic;
	}

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
	//属性相性取得int型引数ver。
	float GetCompatibility(int attack, int target);
	/// <summary>
	/// ダメージ計算。
	/// </summary>
	/// <param name="attack">攻撃するキャラ。</param>
	/// <param name="target">ターゲットのキャラ。</param>
	/// <returns>ダメージ量。</returns>
	int DamageCalcuration(MonsterBase* attack, MonsterBase* target);

	static float eleResist;		//相性不利。
	static float eleCritical;		//相性有利。
	static float eleNormal;		//相性普通。
protected:
	prefab::CEffect* skillEffect = nullptr;
	//wchar_t* effectPath = nullptr;
	wchar_t effectPath[128];	//エフェクトのファイルパス。
	char skillName[30];
	float skillPower = 1.0f;
	float coolTime = 0.0f;	//クールタイム
	float accuracy = 1.0f;	//命中率
	int m_skillNo = 0;
	Elements m_skillElements = en_elements_Empty;
	bool m_isMagic = false;

	//属性相性。[攻撃側][対象側]
	const float m_elementsComp[en_elements_Num][en_elements_Num]=
	{
		{eleNormal	,	eleCritical	,	eleResist	,eleNormal},
		{eleResist	,	eleNormal	,	eleCritical	,eleNormal},
		{eleCritical,	eleResist	,	eleNormal	,eleNormal},
		{eleNormal	,	eleNormal	,	eleNormal	,eleNormal}
	};
};

