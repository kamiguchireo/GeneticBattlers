#include "stdafx.h"
#include "AIBase.h"

AIBase::AIBase()
{
}

AIBase::~AIBase()
{
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
