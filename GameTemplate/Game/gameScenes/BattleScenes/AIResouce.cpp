#include "stdafx.h"
#include "AIResouce.h"

AIResouce* AIResouce::m_instance = nullptr;

//�V���O���g���p�^�[���B
AIResouce::AIResouce()
{
	if (m_instance == nullptr)
	{
		m_instance = this;
	}
	else
	{
		DeleteGO(this);
	}
}

AIResouce::~AIResouce()
{
	if (m_instance == this)
	{
		m_instance = nullptr;
	}
}

//�f�[�^���N���A�B
void AIResouce::ClearData()
{
	m_attacker.clear();
	m_healer.clear();
	m_supporter.clear();
}
