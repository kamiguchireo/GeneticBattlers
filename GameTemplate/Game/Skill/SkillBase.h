#pragma once
#include "monster/MonsterBase.h"

class SkillLog;

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
	bool Start();
	/*
	スキルの設定をする。
	char*		name	!<スキルの名前。
	float		power	!<スキルの威力。
	float		time	!<クールタイム。
	float		acc		!<スキルの命中率。
	int			no		!<スキル番号。
	Elements	ele		!<スキルの属性。
	*/
	void InitSkill(const wchar_t* name,
		float power,
		float time,
		float acc,
		int no
	);
	//使用者のポインタをセット。
	void SetUser(MonsterBase* user)
	{
		m_user = user;
	}
	//ターゲットのポインタをセット。
	void SetTarget(MonsterBase* target)
	{
		m_target = target;
	}
	//再生するエフェクトのファイルパスを設定する。
	void SetEffect(const wchar_t* path)
	{
		swprintf(effectPath, path);
	}
	//スキルが全体効果か？
	void SetIsWide(bool isFlag = false)
	{
		m_isWide = isFlag;
	}
	//スキル番号を取得する。
	const int GetSkillNo()const
	{
		return m_skillNo;
	}
	//スキルの設定
	virtual void SkillSetting() = 0;

	/// <summary>
	/// ダメージ計算。
	/// </summary>
	/// <param name="attack">攻撃するキャラ。</param>
	/// <param name="target">ターゲットのキャラ。</param>
	/// <returns>ダメージ量。</returns>
	int DamageCalcuration();

	//魔法かどうか。
	virtual bool IsMagic() = 0;
	//攻撃スキルかどうか。
	virtual bool IsAttack() = 0;
protected:
	//スキルの名前を設定。
	void SetSkillName(const wchar_t* name)
	{
		swprintf_s(skillName, name);
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

	SkillLog* m_log = nullptr;
	MonsterBase* m_user = nullptr;
	MonsterBase* m_target = nullptr;
	prefab::CEffect* skillEffect = nullptr;	//行動のエフェクト。
	wchar_t effectPath[128];	//エフェクトのファイルパス。
	wchar_t skillName[30];
	float skillPower = 1.0f;
	float coolTime = 0.0f;	//クールタイム
	float accuracy = 1.0f;	//命中率
	int m_skillNo = 0;
	bool m_isWide = false;	//全体効果か？
};

