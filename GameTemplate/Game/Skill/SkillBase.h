#pragma once
#include "SourceFile/graphic/Effect/CEffect.h"

class MonsterBase;

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
	virtual bool UseSkill(MonsterBase* attack, MonsterBase* target) = 0;
	/*
	�X�L���̐ݒ������B
	char*		name	!<�X�L���̖��O�B
	float		power	!<�X�L���̈З́B
	float		time	!<�N�[���^�C���B
	float		acc		!<�X�L���̖������B
	int			no		!<�X�L���ԍ��B
	Elements	ele		!<�X�L���̑����B
	bool		isMagic	!<���@���ǂ����B
	*/
	void InitSkill(const char* name,
		float power,
		float time,
		float acc,
		int no,
		Elements ele = en_elements_Empty,
		bool isMagic = false);
	//�X�L���̖��O��ݒ�B
	void SetSkillName(const char* name)
	{
		sprintf_s(skillName, name);
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
	//
	void SetElements(Elements ele)
	{
		m_skillElements = ele;
	}
	//���@���ǂ�����ݒ肷��B
	void SetMagic(bool isMagic)
	{
		m_isMagic = isMagic;
	}
	//�Đ�����G�t�F�N�g�̃t�@�C���p�X��ݒ肷��B
	void SetEffect(const wchar_t* path)
	{
		swprintf(effectPath, path);
	}
	//�X�L���ԍ����擾����B
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
	/// �����������擾����B
	/// </summary>
	/// <param name="attack">�U�����̑����B</param>
	/// <param name="target">�Ώۑ��̑����B</param>
	/// <returns></returns>
	const float GetCompatibility(Elements attack, Elements target)
	{
		return m_elementsComp[attack][target];
	}
	//���������擾int�^����ver�B
	float GetCompatibility(int attack, int target);
	/// <summary>
	/// �_���[�W�v�Z�B
	/// </summary>
	/// <param name="attack">�U������L�����B</param>
	/// <param name="target">�^�[�Q�b�g�̃L�����B</param>
	/// <returns>�_���[�W�ʁB</returns>
	int DamageCalcuration(MonsterBase* attack, MonsterBase* target);

	static float eleResist;		//�����s���B
	static float eleCritical;		//�����L���B
	static float eleNormal;		//�������ʁB
protected:
	prefab::CEffect* skillEffect = nullptr;
	//wchar_t* effectPath = nullptr;
	wchar_t effectPath[128];	//�G�t�F�N�g�̃t�@�C���p�X�B
	char skillName[30];
	float skillPower = 1.0f;
	float coolTime = 0.0f;	//�N�[���^�C��
	float accuracy = 1.0f;	//������
	int m_skillNo = 0;
	Elements m_skillElements = en_elements_Empty;
	bool m_isMagic = false;

	//���������B[�U����][�Ώۑ�]
	const float m_elementsComp[en_elements_Num][en_elements_Num]=
	{
		{eleNormal	,	eleCritical	,	eleResist	,eleNormal},
		{eleResist	,	eleNormal	,	eleCritical	,eleNormal},
		{eleCritical,	eleResist	,	eleNormal	,eleNormal},
		{eleNormal	,	eleNormal	,	eleNormal	,eleNormal}
	};
};

