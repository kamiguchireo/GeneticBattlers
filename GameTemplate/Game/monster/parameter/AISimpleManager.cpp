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
	//�m���ɖ߂��B
	RateCalc();
	//���f�[�^�ɂ��m���ɖ߂������̂����B
	copy = m_AI;
}
