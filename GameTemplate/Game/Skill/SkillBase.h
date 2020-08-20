#pragma once
#include "monster/MonsterBase.h"
#include "SkillCalculator.h"

class SkillLog;
struct SkillData;
//class SkillCalculator;

//enum Elements {
//	en_elements_Fire,		//!<�������B
//	en_elements_Reef,		//!<�������B
//	en_elements_Water,		//!<�������B
//	en_elements_Empty,		//!<�������B
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
	�X�L���̐ݒ������B
	wchar_t*		name	!<�X�L���̖��O�B
	float		power	!<�X�L���̈З́B
	float		time	!<�N�[���^�C���B
	float		hitRate	!<�X�L���̖������B
	int			no		!<�X�L���ԍ��B
	*/
	void InitSkill(const wchar_t* name,
		float power,
		float time, 
		float hitRate,
		int no
	);
	void InitSkill(SkillData data);
	//�g�p�҂̃|�C���^���Z�b�g�B
	void SetUser(MonsterBase* user)
	{
		m_user = user;
	}
	//�^�[�Q�b�g�̃|�C���^���Z�b�g�B
	void SetTarget(MonsterBase* target)
	{
		m_target = target;
	}
	//�Đ�����G�t�F�N�g�̃t�@�C���p�X��ݒ肷��B
	void SetEffect(const wchar_t* path,int enPos, const wchar_t* sound = nullptr)
	{
		m_playSkillPaths.m_effectPaths.push_back(path);
		m_playSkillPaths.m_effectPosFlag.push_back(enPos);
		SetSound(sound);
	}
	//�Đ�����T�E���h�̃t�@�C���p�X��ݒ肷��B
	void SetSound(const wchar_t* path)
	{
		m_playSkillPaths.m_soundPaths.push_back(path);
	}
	//�X�L�����S�̌��ʂ��H
	void SetIsWide(bool isFlag = false)
	{
		m_isWide = isFlag;
	}
	//�X�L���ԍ����擾����B
	const int GetSkillNo()const
	{
		return m_skillNo;
	}
	bool GetIsPlay()
	{
		return m_isPlay;
	}
	//�X�L���̐ݒ�
	virtual void SkillSetting() = 0;

	//���@���ǂ����B
	virtual bool IsMagic() = 0;
	//�U���X�L�����ǂ����B
	virtual bool IsAttack() = 0;
private:
	static const float SKILL_SOUND_VOL;
protected:
	//�X�L���̖��O��ݒ�B
	void SetSkillName(const wchar_t* name)
	{
		swprintf_s(skillName, name);
	}

	//�X�e�[�^�X�ω���ݒ肷��B
	virtual void SetStatusChange(int status) {};
	//�X�L���ԍ���ݒ肷��B
	void SetSkillNo(int no)
	{
		m_skillNo = no;
	}
	//�G�t�F�N�g���Đ�����ꏊ�����߂�B
	//���[�J���ϐ���Ԃ��Ă��邽�ߎQ�Ɠn���ł͂���
	const CVector3 CreateEffectPosition(int enPos) const;
	const CQuaternion CreateEffectRotation(int enRot)const;

	//�G�t�F�N�g�A�T�E���h�̍Đ��B
	void PlaySkill();

	SkillLog* m_log = nullptr;
	MonsterBase* m_user = nullptr;
	MonsterBase* m_target = nullptr;
	prefab::CEffect* m_skillEffect = nullptr;	//�s���̃G�t�F�N�g�B
	prefab::CSoundSource* m_sound = nullptr;//�X�L���̃T�E���h�B
	Skill::PlaySkillPaths m_playSkillPaths;
	int m_playEffectNum = 0;

	SkillCalculator m_calculator;
	wchar_t skillName[30];
	int m_skillNo = 0;
	bool m_isWide = false;	//�S�̌��ʂ��H
	bool m_isPlay = true;	//�Đ������H
};

