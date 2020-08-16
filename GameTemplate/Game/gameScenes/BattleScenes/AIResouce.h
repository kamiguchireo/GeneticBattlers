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

	void ClearData();

private:
	static AIResouce* m_instance;

	std::vector<AIData> m_attacker;
	std::vector<AIData> m_healer;
	std::vector<AIData> m_supporter;
};

