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
	const float addTime = 1.0f;
	//死亡時は処理を中断する。
	if (m_stateAI == en_state_Death) return false;
	//バフの効果時間減少。
	m_activeTime += static_cast<float>(m_status.DEX) * addTime;
	for (int i = 0; i < en_buff_num; i++) {
		if (m_buffTimeList[i] == 0.0f) continue;

		m_buffTimeList[i] -= addTime;
		if (m_buffTimeList[i] < 0.0f) {
			ResetBuff(i);
		}
	}
	//デバフの効果時間減少。
	for (int i = 0; i < en_buff_num; i++) {
		if (m_debuffTimeList[i] == 0.0f) continue;

		m_debuffTimeList[i] -= addTime;
		if (m_debuffTimeList[i] < 0.0f) {
			ResetDebuff(i);
		}
	}

	if (m_activeTime > m_coolTime) {
		m_activeTime -= m_coolTime;
		return true;
	}
	return false;
}

void StatusSimpleManager::StateUpdate()
{
	//現在HP/最大HPの割合からステートを変化させる。
	float nowHP = static_cast<float>(m_status.HP) / static_cast<float>(m_statusBase.HP);
	//ステートの変更。
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
