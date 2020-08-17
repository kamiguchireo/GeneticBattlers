#include "stdafx.h"
#include "AISimpleManager.h"

AISimpleManager::AISimpleManager()
{
}

AISimpleManager::~AISimpleManager()
{
}

void AISimpleManager::SetAIData(std::vector<AIData>& copy)
{
	m_AI = copy;
	//確率に戻す。
	RateCalc();
	//元データにも確率に戻したものを代入。
	copy = m_AI;
}
