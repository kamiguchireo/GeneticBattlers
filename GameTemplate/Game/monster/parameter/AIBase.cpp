#include "stdafx.h"
#include "AIBase.h"

namespace
{
	const int RANDOM_RATE = 10000;		//0.01%���Ƃɔ���B
}

AIBase::AIBase()
{
}

AIBase::~AIBase()
{
}

void AIBase::ActionDicide(int & skill, int & target)
{
	int res = g_random.GetRandomInt() % RANDOM_RATE;	//�K���ȗ����B
	float sum = 0;

	//�s���e�[�u�������Ƃɍs��������B
	for (int i = 0; i < m_AI.size(); i++) {
		sum += m_AI[i].rate * RANDOM_RATE;
		if (sum > res) {
			skill = m_AI[i].skillNo;
			target = m_AI[i].target;
			break;
		}
	}
}

void AIBase::RateCalc()
{
	float sum = 0.0f;

	//�g�p���̍��v�����߂�B
	for (auto& act : m_AI)
	{
		sum += act.rate;
	}

	//�O�̂���0�������B
	if (sum < 0.002)
	{
		sum = 1.0f;
	}

	//�m���ɒ����B
	for (auto&act : m_AI)
	{
		act.rate /= sum;
	}
}
