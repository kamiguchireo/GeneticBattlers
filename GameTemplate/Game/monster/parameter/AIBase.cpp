#include "stdafx.h"
#include "AIBase.h"

namespace
{
	const int RANDOM_RATE = 10000;		//0.01%ごとに判定。
}

AIBase::AIBase()
{
}

AIBase::~AIBase()
{
}

void AIBase::ActionDicide(int & skill, int & target)
{
	int res = g_random.GetRandomInt() % RANDOM_RATE;	//適当な乱数。
	float sum = 0;

	//行動テーブルをもとに行動させる。
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
