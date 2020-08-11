#include "stdafx.h"
#include "StatusManager.h"
#include "StatusUI.h"

bool StatusManager::AddATB()
{
	const float addTime = g_gameTime.GetFrameDeltaTime() * 2.0f;
	//���S���͏����𒆒f����B
	if (m_stateAI == en_state_Death) return false;
	//�o�t�̌��ʎ��Ԍ����B
	m_activeTime += (float)m_status.DEX * addTime;
	for (int i = 0; i < en_buff_num; i++) {
		if (m_buffTimeList[i] == 0.0f) continue;

		m_buffTimeList[i] -= addTime;
		if (m_buffTimeList[i] < 0.0f) {
			ResetBuff(i);
		}
	}
	//�f�o�t�̌��ʎ��Ԍ����B
	for (int i = 0; i < en_buff_num; i++) {
		if (m_debuffTimeList[i] == 0.0f) continue;

		m_debuffTimeList[i] -= addTime;
		if (m_debuffTimeList[i] < 0.0f) {
			ResetDebuff(i);
		}
	}

	//�A�N�e�B�u�^�C���Q�[�W�B
	float res = m_activeTime / m_coolTime;
	res = min(1.0f, res);
	m_UI->SetScaling(res);

	if (m_activeTime > m_coolTime) {
		return true;
	}
	return false;
}

void StatusManager::StateUpdate()
{
	//����HP/�ő�HP�̊�������X�e�[�g��ω�������B
	float nowHP = (float)m_status.HP / (float)m_statusBase.HP;
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
		ClearATB();
		m_UI->SetScaling(0.0f);
	}
	//UI�ɔ��f�B
	if (m_UI->IsDead()) { return; }	//���S���͏������Ȃ��B
	m_UI->SetHPScaling(nowHP);
}
