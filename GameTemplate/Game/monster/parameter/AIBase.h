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

	//�g�p���̐��l���m���ɂ���B
	void RateCalc();

protected:
	//	AI�f�[�^�B
	std::vector<AIData> m_AI;							//AI�f�[�^�B
};

