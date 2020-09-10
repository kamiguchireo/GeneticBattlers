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
	/// �X�L���f�[�^���擾����B
	/// </summary>
	/// <param name="table">�X�L���̑���
	/// <remarks>�O�ʏ�s��</remarks>
	/// <remarks>�P�񕜖��@</remarks>
	/// <remarks>�Q�o�t���@</remarks>
	/// <remarks>�R�f�o�t���@</remarks>
	/// </param>
	/// <param name="no">�X�L���i���o�[</param>
	/// <returns>�X�L���̃f�[�^</returns>
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