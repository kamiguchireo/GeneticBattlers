#include "stdafx.h"
#include "StatusManager.h"
#include "StatusUI.h"

int StatusManager::Healing(int healing)
{
	int res = healing;
	m_status.HP += healing;
	//最大HPを超えた。
	if (m_status.HP > m_statusBase.HP) {
		int diff = m_status.HP - m_statusBase.HP;
		res -= diff;		//超えた分だけ引く。

		m_status.HP = min(m_status.HP, m_statusBase.HP);
	}

	return res;
}

int StatusManager::Monster_Buff(StatusBuff status, float pow, float time)
{
	int res = 0;

	//バフをかける。
	switch (status)
	{
	case en_buff_ATK:
		m_status.ATK = m_statusBase.ATK * pow;
		res = m_status.ATK - m_statusBase.ATK;	//上昇値の計算。

		break;
	case en_buff_DEF:
		m_status.DEF = m_statusBase.DEF * pow;
		res = m_status.DEF - m_statusBase.DEF;	//上昇値の計算。

		break;
	case en_buff_MAT:
		m_status.MAT = m_statusBase.MAT * pow;
		res = m_status.MAT - m_statusBase.MAT;	//上昇値の計算。

		break;
	case en_buff_MDF:
		m_status.MDF = m_statusBase.MDF * pow;
		res = m_status.MDF - m_statusBase.MDF;	//上昇値の計算。

		break;
	case en_buff_DEX:
		m_status.DEX = m_statusBase.DEX * pow;
		res = m_status.DEX - m_statusBase.DEX;	//上昇値の計算。

		break;
	}
	buffTimeList[status] = time;

	return res;
}

void StatusManager::ResetBuff(int i)
{
	////効果時間があるなら中断。
	//if (buffTimeList[i] > 0.0f) {
	//	return;
	//}
	//ステータスを元のステータスに戻す。
	switch (i)
	{
	case en_buff_ATK:
		m_status.ATK = m_statusBase.ATK;
		break;
	case en_buff_DEF:
		m_status.DEF = m_statusBase.DEF;
		break;
	case en_buff_MAT:
		m_status.MAT = m_statusBase.MAT;
		break;
	case en_buff_MDF:
		m_status.MDF = m_statusBase.MDF;
		break;
	case en_buff_DEX:
		m_status.DEX = m_statusBase.DEX;
		break;
	default:
		return;
	}
	//
	buffTimeList[i] = 0.0f;
}

bool StatusManager::AddATB()
{
	//死亡時は処理を中断する。
	if (m_stateAI == en_state_Death) return false;

	m_activeTime += (float)m_status.DEX * addTime;
	for (int i = 0; i < en_buff_num; i++) {
		if (buffTimeList[i] >= 0.0f) continue;

		buffTimeList[i] -= addTime;
		if (buffTimeList[i] < 0.0f) {
			ResetBuff(i);
		}
	}

	//アクティブタイムゲージ。
	float res = m_activeTime / m_coolTime;
	res = min(1.0f, res);
	m_UI->SetScaling(res);

	if (m_activeTime > m_coolTime) {
		m_activeTime = 0.0f;
		return true;
	}
	return false;
}

void StatusManager::StateUpdate()
{
	//現在HP/最大HPの割合からステートを変化させる。
	float nowHP = (float)m_status.HP / (float)m_statusBase.HP;
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
		m_activeTime = 0.0f;
	}
	//UIに反映。
	if (m_UI == nullptr) { return; }	//nullだったら処理をしない。
	float res = m_activeTime / m_coolTime;
	res = min(1.0f, res);
	m_UI->SetScaling(res);
	m_UI->SetHPScaling(nowHP);
}
