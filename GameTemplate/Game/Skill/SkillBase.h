#pragma once
#include "monster/MonsterBase.h"
#include "SkillCalculator.h"

class SkillLog;
struct SkillData;
//class SkillCalculator;

//enum Elements {
//	en_elements_Fire,		//!<炎属性。
//	en_elements_Reef,		//!<草属性。
//	en_elements_Water,		//!<水属性。
//	en_elements_Empty,		//!<無属性。
//	en_elements_Num
//};

enum EffectPos
{
	en_PosUser,
	en_PosTarget
};

typedef const wchar_t* SkillPath;
namespace Skill 
{
	struct PlaySkillPaths
	{
		std::vector<SkillPath> m_effectPaths;
		std::vector<SkillPath> m_soundPaths;
		std::vector<int> m_effectPosFlag;
	};
}

class SkillBase : public IGameObject
{
public:
	SkillBase();
	virtual ~SkillBase();
	bool Start();
	/*
	スキルの設定をする。
	wchar_t*		name	!<スキルの名前。
	float		power	!<スキルの威力。
	float		time	!<クールタイム。
	float		hitRate	!<スキルの命中率。
	int			no		!<スキル番号。
	*/
	void InitSkill(const wchar_t* name,
		float power,
		float time, 
		float hitRate,
		int no
	);
	void InitSkill(SkillData data);
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
	void SetEffect(const wchar_t* path,int enPos, const wchar_t* sound = nullptr)
	{
		m_playSkillPaths.m_effectPaths.push_back(path);
		m_playSkillPaths.m_effectPosFlag.push_back(enPos);
		SetSound(sound);
	}
	//再生するサウンドのファイルパスを設定する。
	void SetSound(const wchar_t* path)
	{
		m_playSkillPaths.m_soundPaths.push_back(path);
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
	bool GetIsPlay()
	{
		return m_isPlay;
	}
	//スキルの設定
	virtual void SkillSetting() = 0;

	//魔法かどうか。
	virtual bool IsMagic() = 0;
	//攻撃スキルかどうか。
	virtual bool IsAttack() = 0;
private:
	static const float SKILL_SOUND_VOL;
protected:
	//スキルの名前を設定。
	void SetSkillName(const wchar_t* name)
	{
		swprintf_s(skillName, name);
	}

	//ステータス変化を設定する。
	virtual void SetStatusChange(int status) {};
	//スキル番号を設定する。
	void SetSkillNo(int no)
	{
		m_skillNo = no;
	}
	//エフェクトを再生する場所を決める。
	//ローカル変数を返しているため参照渡しではだめ
	const CVector3 CreateEffectPosition(int enPos) const;
	const CQuaternion CreateEffectRotation(int enRot)const;

	//エフェクト、サウンドの再生。
	void PlaySkill();

	SkillLog* m_log = nullptr;
	MonsterBase* m_user = nullptr;
	MonsterBase* m_target = nullptr;
	prefab::CEffect* m_skillEffect = nullptr;	//行動のエフェクト。
	prefab::CSoundSource* m_sound = nullptr;//スキルのサウンド。
	Skill::PlaySkillPaths m_playSkillPaths;
	int m_playEffectNum = 0;

	SkillCalculator m_calculator;
	wchar_t skillName[30];
	int m_skillNo = 0;
	bool m_isWide = false;	//全体効果か？
	bool m_isPlay = true;	//再生中か？
};

