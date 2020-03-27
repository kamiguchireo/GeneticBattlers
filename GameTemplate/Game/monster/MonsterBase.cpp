#include "stdafx.h"
#include "MonsterBase.h"
#include "Skill/SkillList.h"


MonsterBase::MonsterBase()
{
}


MonsterBase::~MonsterBase()
{
}

void MonsterBase::SetStatus(int hp, int mp, int atk, int def, int mat, int mdf, int dex)
{
	//基礎ステータスを設定。
	m_statusBase.HP = hp;
	//m_statusBase.MP = mp;
	m_statusBase.ATK = atk;
	m_statusBase.DEF = def;
	m_statusBase.MAT = mat;
	m_statusBase.MDF = mdf;
	m_statusBase.DEX = dex;
	//ステータスに代入。
	m_status = m_statusBase;
}

void MonsterBase::Draw()
{
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	//描画処理。
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

bool MonsterBase::AddATB()
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

//行動の評価。
bool MonsterBase::ACTScoring()
{
	//評価の選択の処理。
	if (g_pad[0].IsTrigger(enButtonRight)) {		
		m_scoringFlag = 1;
	}
	if (g_pad[0].IsTrigger(enButtonLeft)) {
		m_scoringFlag = 0;
	}
	switch (m_scoringFlag)
	{
	case 0:
		m_UI->SetGood();
		break;
	case 1:
		m_UI->SetBad();
		break;
	default:
		break;
	}
	//評価の決定の処理。
	if (g_pad[0].IsTrigger(enButtonA)) {
		switch (m_scoringFlag)
		{
		case 0:
			m_actRes.score = true;
			break;
		case 1:
			m_actRes.score = false;
			break;
		default:
			break;
		}
		m_actResList.push_back(m_actRes);	//リストに積み上げる。
		m_UI->ScoreReset();
		m_scoringFlag = 0;
		return true;
	}

	return false;
}

int MonsterBase::Healing(int healing)
{
	int res = healing;
	m_status.HP += healing;
	//最大HPを超えた。
	if (m_status.HP > m_statusBase.HP) {
		int diff = m_status.HP - m_statusBase.HP;
		res -= diff;		//超えた分だけ引く。

		m_status.HP = min(m_status.HP, m_statusBase.HP);
	}

	//エフェクトの再生。
	auto ef = NewGO<prefab::CEffect>(0);
	ef->Play(L"Assets/effect/heal.efk");
	ef->SetPosition(m_position + CVector3::AxisY()*20.0f);
	ef->SetScale(CVector3::One()*80.0f);

	return res;
}

int MonsterBase::Monster_Buff(StatusBuff status, float pow, float time)
{
	////バフの効果が続いているなら中断。
	//if (buffTimeList[status] >= 0.0f) {
	//	return;
	//}
	
	//エフェクトの再生。
	auto ef = NewGO<prefab::CEffect>(0);
	ef->Play(L"Assets/effect/buff.efk");
	ef->SetPosition(m_position + CVector3::AxisY()*20.0f);
	ef->SetScale(CVector3::One()*80.0f);

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

void MonsterBase::ResetBuff(int i)
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

void MonsterBase::SelectUseSkill(const std::vector<MonsterBase*>& e_team, const std::vector<MonsterBase*>& m_team)
{
	SkillList* skillList = SkillList::GetInstance();

	auto ene_list = e_team;	//ソートするためにリストをコピー。
	auto list = m_team;

	//現在HPの低い方から順番にソート。
	for (int i = 0; i < list.size(); i++) {
		for (int j = i; j < list.size(); j++) {
			if (list[i]->GetStatus().HP > list[j]->GetStatus().HP) {
				auto hoge = list[i];
				list[i] = list[j];
				list[j] = hoge;
			}
		}
	}
	for (int i = 0; i < ene_list.size(); i++) {
		for (int j = i; j < ene_list.size(); j++) {
			if (ene_list[i]->GetStatus().HP > ene_list[j]->GetStatus().HP) {
				auto hoge = ene_list[i];
				ene_list[i] = ene_list[j];
				ene_list[j] = hoge;
			}
		}
	}

	//ターゲットが定まるまで回す。
	while (m_target == nullptr) {
		int res = rand() % 100;	//適当な乱数。
		int sum = 0;

		//行動テーブルをもとに行動させる。
		int AINum = sizeof(m_AI) / sizeof(*m_AI);
		for (int i = 0; i < AINum; i++) {
			sum += (int)(m_AI[i].rate * 100);
			if (sum > res) {
				int skillTable = (int)(m_AI[i].skillNo / 100);
				int skillNo = m_AI[i].skillNo % 100;
				int targetNo = m_AI[i].target;
				m_useSkill = skillList->GetSkillData(skillTable, skillNo);

				//敵か味方のどちらに攻撃するか。
				if (!m_useSkill->GetIsAttack()) {
					//ターゲットが死亡していなければ。
					if (!list[targetNo]->IsDeath()) {
						m_target = list[targetNo];
					}
				}
				else if (m_useSkill->GetIsAttack()) {
					//ターゲットが死亡していなければ。
					if (!ene_list[targetNo]->IsDeath()) {
						m_target = ene_list[targetNo];
					}
				}

				break;
			}
		}
	}
}

void MonsterBase::StateUpdate()
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
	float res = m_activeTime / m_coolTime;
	res = min(1.0f, res);
	m_UI->SetScaling(res);
	m_UI->SetHPScaling(nowHP);
}

bool MonsterBase::Action()
{
	bool flag = false;
	//残りHPに応じて行動を決める。
	switch (m_stateAI)
	{
	case en_state_Good:
		flag = Action_good();
		break;
	
	case en_state_Usually:
		flag = Action_usually();
		break;
	
	case en_state_Bad:
		flag = Action_bad();
		break;
	
	case en_state_Death:
		return true;
		break;
	}
	return flag;
}

void MonsterBase::GIUpdate()
{
	//GIを用いて行動AIの確率の更新。
	const int listSize = m_actResList.size();
	const int AISize = sizeof(m_AI) / sizeof(*m_AI);
	std::vector<float> AIscoreList(AISize, 0.0f);
	float sum = 0.0f;
	for (auto res : m_actResList) {
		//評価されていない。
		if (!res.score)	continue;
		//スコアを合計する。
		for (int i = 0; i < AISize; i++) {
			if (res.skillNo == m_AI[i].skillNo
				&&res.target == m_AI[i].target) {
				AIscoreList[i] += res.damage;
				sum += res.damage;
				break;
			}
		}
	}
	//0割り回避。
	sum = max(sum, 1.0f);
	//比率計算。
	for (int i = 0; i < AISize; i++) {
		AIscoreList[i] /= sum;
	}

	sum = 0.0f;
	for (int i = 0; i < AISize; i++) {
		m_AI[i].rate = m_AI[i].rate * 10.0f + AIscoreList[i];
		sum += m_AI[i].rate;
	}

	for (int i = 0; i < AISize; i++) {
		m_AI[i].rate /= sum;
	}
}
