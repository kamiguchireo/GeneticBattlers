#pragma once
#include "Skill/SkillBase.h"
#include "monster/MonsterBase.h"


class SkillList : public IGameObject
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
	/// </param>
	/// <param name="no">�X�L���i���o�[</param>
	/// <returns>�X�L���̃f�[�^</returns>
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