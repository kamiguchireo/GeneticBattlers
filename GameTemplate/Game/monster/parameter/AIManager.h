#pragma once
#include "AIBase.h"

struct ResultData {
	int damage = 0;
	int skillNo = 0;
	int target = 0;
};

struct SkillRate
{
	int skillNo = 0;
	float rate = 0.0f;
};

class AIManager : public AIBase
{
public:
	AIManager();
	~AIManager();
	/// <summary>
	/// �t�@�C���p�X����GA�����[�h����B
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X�B</param>
	bool Load(const char* filePath);
	/// <summary>
	/// �f�t�H���g�̃f�[�^�����[�h����Ƃ��Ɏg���B
	/// </summary>
	/// <param name="filePath">�f�t�H���g�̐��l�̓������t�@�C���p�X�B</param>
	void LoadDefault(const char* filePath);
	/// <summary>
	/// GA���L�^����B
	/// </summary>
	void Save();
	/// <summary>
	/// AI�̍X�V���s���B
	/// </summary>
	void AIUpdate();
	/// <summary>
	/// �V�����s����ǉ�
	/// </summary>
	void AddNewSkill();
	/// <summary>
	/// �s���𗐐��Ō��肷��B
	/// </summary>
	/// <param name="skill">���肵���X�L�����擾����B</param>
	/// <param name="target">���肵���^�[�Q�b�g���擾����B</param>
	void ActionDicide(int& skill, int& target);
	/// <summary>
	/// �s���̃��U���g��ςށB
	/// </summary>
	/// <param name="damage">�_���[�W�ʁB</param>
	/// <param name="skill">�g�p�X�L���B</param>
	/// <param name="target">�^�[�Q�b�g�B</param>
	void PushBackResult(int damage, int skill, int target)
	{
		ResultData res = { damage,skill,target };
		m_actResList.push_back(res);
	}
private:
	//�X�L�����Ƃ̎g�p�����v�Z����B
	void SkillRateCalc();

private:
	static const float SKILL_NEW_RATE;
	static const float FIRST_RATE;
	static const int MAX_TARGET_COUNT;

private:
	char m_AIPath[128];									//AI�f�[�^�̃t�@�C���p�X�B
	std::vector<ResultData> m_actResList;				//�s���̃��U���g�̉ϒ��z��B
	std::vector<SkillRate> m_skillRateList;				//�X�L�����Ƃ̎g�p���B
};

