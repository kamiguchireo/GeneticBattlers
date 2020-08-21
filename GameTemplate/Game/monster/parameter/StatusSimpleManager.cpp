#include "stdafx.h"
#include "StatusSimpleManager.h"

StatusSimpleManager::StatusSimpleManager()
{
}

StatusSimpleManager::~StatusSimpleManager()
{
}

bool StatusSimpleManager::AddATB()
{
	//���S���͏����𒆒f����B
	if (m_stateAI == en_state_Death) return false;
	//���Z���ԁB
	const float addTime = 2.0f;
	//�A�N�e�B�u�^�C����i�߂�B
	m_activeTime += static_cast<float>(m_status.DEX) * addTime;
	//�o�t�̌��ʎ��Ԍ����B
	BuffDebuffTime(addTime);

	if (m_activeTime > m_coolTime) {
		m_activeTime -= m_coolTime;
		return true;
	}
	return false;
}

void StatusSimpleManager::StateUpdate()
{
	//����HP/�ő�HP�̊�������X�e�[�g��ω�������B
	float nowHP = static_cast<float>(m_status.HP) / static_cast<float>(m_statusBase.HP);
	//�X�e�[�g�̕ύX�B
	if (2.0f / 3.0f < nowHP) {
		m_stateAI = en_state_Good;
	}
	else if (1.0f / 3.0f < nowHP
		&& 2.0f / 3.0f >= nowHP) {
		m_stateAI = en_state_Usually;
	}
	else if (0 < m_status.HP
		&& 1.0f / 3.0f >= nowHP) {
		m_stateAI = en_state_Bad;
	}
	else if (m_status.HP == 0) {
		m_stateAI = en_state_Death;
		m_IsDeath = true;
		ClearATB();
	}
}
