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
	//死亡時は処理を中断する。
	if (m_stateAI == en_state_Death) return false;
	//加算時間。
	const float addTime = 2.0f;
	//アクティブタイムを進める。
	m_activeTime += static_cast<float>(m_status.DEX) * addTime;
	//バフの効果時間減少。
	BuffDebuffTime(addTime);

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
