#include "stdafx.h"
#include "BattleManager.h"
#include "monster/MonsterBase.h"

void BattleManager::ActiveTimeUpdate()
{
	//行動中なら中断。
	if (m_monsterACTList.size() != 0)return;

	//全員のタイムゲージを加算していく。
	for (int i = 0; i < m_monsterTeam.size(); i++)
	{
		bool is_action = m_monsterTeam[i]->AddATB();

		//ゲージが溜まり切ったらポインタを取得する。　
		if (is_action) {
			m_monsterACTList.push_back(m_monsterEnemy[i]);
			m_monsterTeam[i]->SelectUseSkill(m_monsterEnemy, m_monsterTeam);
			//ステートを変更。
			m_battleState = enState_ACT;
		}
	}
	for (int i = 0; i < m_monsterEnemy.size(); i++)
	{
		bool is_action = m_monsterEnemy[i]->AddATB();

		//ゲージが溜まり切ったらポインタを取得する。　
		if (is_action) {
			m_monsterACTList.push_back(m_monsterEnemy[i]);
			m_monsterEnemy[i]->SelectUseSkill(m_monsterTeam, m_monsterEnemy);
			//ステートを変更。
			m_battleState = enState_ACT;
		}
	}
}

void BattleManager::MonsterAction()
{
	m_monsterACT = m_monsterACTList.front();

	//行動が終わるまで行動をさせる。
	bool is_playAction = m_monsterACT->BattleAction();

	if (is_playAction) {
		//残りHPに応じてステートを更新。
		for (int i = 0; i < m_monsterTeam.size(); i++) {
			m_monsterTeam[i]->StateUpdate();
		}
		for (int i = 0; i < m_monsterEnemy.size(); i++) {
			m_monsterEnemy[i]->StateUpdate();
		}

		m_battleState = enState_Scoring;
	}
}

void BattleManager::MonsterScoring()
{
	bool flag = m_monsterACT->ACTScoring();

	if (flag) {
		//行動が終わったらポインタにnullを入れる。
		m_monsterACTList.erase(m_monsterACTList.begin());
		m_monsterACT = nullptr;


		int myDeath = 0;
		int eneDeath = 0;

		//デス数をカウントする。
		for (int i = 0; i < m_monsterTeam.size(); i++) {
			if (m_monsterTeam[i]->IsDeath())myDeath++;
		}
		for (int i = 0; i < m_monsterEnemy.size(); i++) {
			if (m_monsterEnemy[i]->IsDeath())eneDeath++;
		}
		//どちらかが全滅すればリザルトへ
		if (myDeath == m_monsterTeam.size()) {
			//バトルシーンに対してステートの変化と勝敗判定を渡す
			return;
		}
		else if (eneDeath == m_monsterEnemy.size()) {
			return;
		}

		//誰も行動していないなら
		if (m_monsterACTList.size() == 0) {
			m_battleState = enState_ATB;
		}
		else {
			m_battleState = enState_ACT;
		}

	}
}
