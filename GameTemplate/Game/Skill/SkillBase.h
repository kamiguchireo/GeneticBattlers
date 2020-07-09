#pragma once
#include "monster/MonsterBase.h"

class SkillLog;

enum Elements {
	en_elements_Fire,		//!<�������B
	en_elements_Reef,		//!<�������B
	en_elements_Water,		//!<�������B
	en_elements_Empty,		//!<�������B
	en_elements_Num
};

class SkillBase : public IGameObject
{
public:
	SkillBase();
	~SkillBase();
	bool Start();
	/*
	�X�L���̐ݒ������B
	char*		name	!<�X�L���̖��O�B
	float		power	!<�X�L���̈З́B
	float		time	!<�N�[���^�C���B
	float		acc		!<�X�L���̖������B
	int			no		!<�X�L���ԍ��B
	Elements	ele		!<�X�L���̑����B
	*/
	void InitSkill(const wchar_t* name,
		float power,
		float time,
		float acc,
		int no
	);
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
	void SetEffect(const wchar_t* path)
	{
		swprintf(effectPath, path);
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
	//�X�L���̐ݒ�
	virtual void SkillSetting() = 0;

	/// <summary>
	/// �_���[�W�v�Z�B
	/// </summary>
	/// <param name="attack">�U������L�����B</param>
	/// <param name="target">�^�[�Q�b�g�̃L�����B</param>
	/// <returns>�_���[�W�ʁB</returns>
	int DamageCalcuration();

	//���@���ǂ����B
	virtual bool IsMagic() = 0;
	//�U���X�L�����ǂ����B
	virtual bool IsAttack() = 0;
protected:
	//�X�L���̖��O��ݒ�B
	void SetSkillName(const wchar_t* name)
	{
		swprintf_s(skillName, name);
	}
	//�X�L���̈З�(�{��)��ݒ�
	void SetSkillPower(float power)
	{
		skillPower = power;
	}
	//�N�[���^�C����ݒ肷��B
	void SetCoolTime(float time)
	{
		coolTime = time;
	}
	//��������ݒ肷��B
	void SetAccuracy(float acc)
	{
		accuracy = acc;
	}
	//�X�L���ԍ���ݒ肷��B
	void SetSkillNo(int no)
	{
		m_skillNo = no;
	}

	SkillLog* m_log = nullptr;
	MonsterBase* m_user = nullptr;
	MonsterBase* m_target = nullptr;
	prefab::CEffect* skillEffect = nullptr;	//�s���̃G�t�F�N�g�B
	wchar_t effectPath[128];	//�G�t�F�N�g�̃t�@�C���p�X�B
	wchar_t skillName[30];
	float skillPower = 1.0f;
	float coolTime = 0.0f;	//�N�[���^�C��
	float accuracy = 1.0f;	//������
	int m_skillNo = 0;
	bool m_isWide = false;	//�S�̌��ʂ��H
};

