#include "stdafx.h"
#include "StatusManager.h"
#include "StatusUI.h"

bool StatusManager::AddATB()
{
	//死亡時は処理を中断する。
	if (m_stateAI == en_state_Death) return false;

	const float addTime = g_gameTime.GetFrameDeltaTime();
	//アクティブタイムを進める。
	m_activeTime += static_cast<float>(m_status.DEX) * addTime * 2.0f;
	//バフの効果時間減少。
	BuffDebuffTime(addTime);

	//アクティブタイムゲージ。
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
		ClearATB();
		m_UI->SetScaling(0.0f);
	}
	//UIに反映。
	if (m_UI->IsDead()) { return; }	//死亡時は処理しない。
	m_UI->SetHPScaling(nowHP);
}
