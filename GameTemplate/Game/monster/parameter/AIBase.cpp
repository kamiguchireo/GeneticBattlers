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

	//使用率の合計を求める。
	for (auto& act : m_AI)
	{
		sum += act.rate;
	}

	//念のため0割り回避。
	if (sum < 0.002)
	{
		sum = 1.0f;
	}

	//確率に直す。
	for (auto&act : m_AI)
	{
		act.rate /= sum;
	}
}
