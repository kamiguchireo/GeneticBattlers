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
	////�ˑR�ψٓI��
	//int pMutation = g_random.GetRandomInt() % 100;
	////100���̂P�̊m���B
	//if (pMutation == 0) {
	//	//�����_���ɐ���������B
	//	//int actNum = rand() % m_AI.size();
	//	int actNum = g_random.GetRandomInt() % m_AI.size();
	//	skill = m_AI[actNum].skillNo;
	//	target = m_AI[actNum].target;
	//	//�֐��𔲂���B
	//	return;
	//}

	int res = g_random.GetRandomInt() % 100;	//�K���ȗ����B
	float sum = 0;

	//�s���e�[�u�������Ƃɍs��������B
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
