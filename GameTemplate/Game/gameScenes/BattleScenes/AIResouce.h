#pragma once
#include "monster/parameter/AIBase.h"

/// <summary>
/// �G��AI����ێ����Ă����B
/// </summary>

class AIResouce:public IGameObject
{
public:
	AIResouce();
	~AIResouce();

	static AIResouce* GetInstance()
	{
		return m_instance;
	}

	//�A�^�b�J�[�̏���ۑ��B
	void SetAttaker(const std::vector<AIData>& attacker)
	{
		m_attacker = attacker;
	}
	//�q�[���[�̏���ۑ��B
	void SetHealer(const std::vector<AIData>& healer)
	{
		m_healer = healer;
	}
	//�T�|�[�^�[�̏���ۑ��B
	void SetSupporter(const std::vector<AIData>& supporter)
	{
		m_supporter = supporter;
	}
	//�A�^�b�J�[�̏��擾�B
	std::vector<AIData>& GetAttacker()
	{
		return m_attacker;
	}
	//�q�[���[�̏��擾�B
	std::vector<AIData>& GetHealer()
	{
		return m_healer;
	}
	//�T�|�[�^�[�̏��擾�B
	std::vector<AIData>& GetSupporter()
	{
		return m_supporter;
	}

	//�f�[�^���N���A�B
	void ClearData();

private:
	static AIResouce* m_instance;			//�C���X�^���X�B

	std::vector<AIData> m_attacker;			//�A�^�b�J�[���
	std::vector<AIData> m_healer;			//�q�[���[���
	std::vector<AIData> m_supporter;		//�T�|�[�^�[���
};

