#pragma once


//�s���e�[�u���̃f�[�^�B
//!<skillNo		�X�L���ԍ��B
//!<target		�^�[�Q�b�g�ԍ��B
//!<rate		�g�p�p�x�B
struct AIData {
	int skillNo = 0;		//�����͌Œ�l
	int target = 0;			//�������Œ�l
	float rate = 0.0f;		//��������`�q�Ƃ��ĕω�����
};

class AIBase
{
public:
	AIBase();
	virtual ~AIBase();

	/// <summary>
	/// AI�f�[�^�̃R�s�[���s���B
	/// </summary>
	/// <param name="copy">�s���f�[�^�B</param>
	void Init(const std::vector<AIData>& copy)
	{
		m_AI = copy;
	}
	//AI�����擾�B
	const std::vector<AIData>& GetAIData()
	{
		return m_AI;
	}
	/// <summary>
	/// �s���𗐐��Ō��肷��B
	/// </summary>
	/// <param name="skill">���肵���X�L�����擾����B</param>
	/// <param name="target">���肵���^�[�Q�b�g���擾����B</param>
	void ActionDicide(int& skill, int& target);

protected:
	//�g�p���̐��l���m���ɂ���B
	void RateCalc();

protected:
	//	AI�f�[�^�B
	std::vector<AIData> m_AI;							//AI�f�[�^�B
};

