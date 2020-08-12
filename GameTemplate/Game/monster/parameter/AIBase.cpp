#include "stdafx.h"
#include "AIBase.h"

AIBase::AIBase()
{
}

AIBase::~AIBase()
{
}

void AIBase::ActionDicide(int & skill, int & target)
{
	////突然変異的な
	//int pMutation = g_random.GetRandomInt() % 100;
	////100分の１の確率。
	//if (pMutation == 0) {
	//	//ランダムに数字を入れる。
	//	//int actNum = rand() % m_AI.size();
	//	int actNum = g_random.GetRandomInt() % m_AI.size();
	//	skill = m_AI[actNum].skillNo;
	//	target = m_AI[actNum].target;
	//	//関数を抜ける。
	//	return;
	//}

	int res = g_random.GetRandomInt() % 100;	//適当な乱数。
	float sum = 0;

	//行動テーブルをもとに行動させる。
	for (int i = 0; i < m_AI.size(); i++) {
		sum += m_AI[i].rate * 100;
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
