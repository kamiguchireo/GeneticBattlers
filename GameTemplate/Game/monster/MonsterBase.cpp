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
	Status hoge;
	hoge.HP = hp;
	//hoge.MP = mp;
	hoge.ATK = atk;
	hoge.DEF = def;
	hoge.MAT = mat;
	hoge.MDF = mdf;
	hoge.DEX = dex;
	//設定。
	m_status.SetStatus(hoge);
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

int MonsterBase::Monster_Buff(StatusBuff status, float pow, float time)
{
	//エフェクトの再生。
	auto ef = NewGO<prefab::CEffect>(0);
	ef->Play(L"Assets/effect/buff.efk");
	ef->SetPosition(m_position + CVector3::AxisY()*20.0f);
	ef->SetScale(CVector3::One()*80.0f);

	return m_status.Monster_Buff(status,pow,time);
}

void MonsterBase::SelectUseSkill(const std::vector<MonsterBase*>& e_team, const std::vector<MonsterBase*>& m_team)
{
	SkillList* skillList = SkillList::GetInstance();

	auto ene_list = e_team;	//ソートするためにリストをコピー。
	auto list = m_team;

	//現在HPの低い方から順番にソート。
	for (int i = 0; i < list.size(); i++) {
		for (int j = i; j < list.size(); j++) {
			if (list[i]->GetStatusManager().GetStatus().HP > list[j]->GetStatusManager().GetStatus().HP) {
				auto hoge = list[i];
				list[i] = list[j];
				list[j] = hoge;
			}
		}
	}
	for (int i = 0; i < ene_list.size(); i++) {
		for (int j = i; j < ene_list.size(); j++) {
			if (ene_list[i]->GetStatusManager().GetStatus().HP > ene_list[j]->GetStatusManager().GetStatus().HP) {
				auto hoge = ene_list[i];
				ene_list[i] = ene_list[j];
				ene_list[j] = hoge;
			}
		}
	}
	//HPが0のやつは後ろに回す。
	for (int i = list.size() - 1; i >= 0; i--) {
		for (int j = i; j < list.size(); j++) {
			if (list[i]->GetStatusManager().GetStatus().HP <= 0) {
				auto hoge = list[i];
				list[i] = list[j];
				list[j] = hoge;
			}
		}
	}
	for (int i = ene_list.size() - 1; i >= 0; i--) {
		for (int j = i; j < ene_list.size(); j++) {
			if (ene_list[i]->GetStatusManager().GetStatus().HP <= 0) {
				auto hoge = ene_list[i];
				ene_list[i] = ene_list[j];
				ene_list[j] = hoge;
			}
		}
	}

	//選ばれる行動の数。
	int AINum = m_AI.size();

	//突然変異的な
	int pMutation = rand() % 100;
	//100分の１の確率。
	if (pMutation == 0) {
		while (m_target == nullptr)
		{
			//ランダムに数字を入れる。
			int actNum = rand() % AINum;
			int skillTable = (int)(m_AI[actNum].skillNo / 100);
			int skillNo = m_AI[actNum].skillNo % 100;
			int targetNo = m_AI[actNum].target;
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
		}
		//関数を抜ける。
		return;
	}

	//ターゲットが定まるまで回す。
	while (m_target == nullptr) {
		int res = rand() % 100;	//適当な乱数。
		int sum = 0;

		//行動テーブルをもとに行動させる。
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

void MonsterBase::Init(const char * filePath)
{
	strcpy(m_AIPath, filePath);
	FILE* fp = fopen(filePath, "rb");
	if (fp == nullptr) {
		//ファイルが存在しないならデフォルト。
		MakeData();

		return;
	}

	//読み込んでいく。
	AIData hoge;
	while (fread(&hoge, sizeof(AIData), 1, fp) == 1) {
		m_AI.push_back(hoge);
	}

	fclose(fp);
}

void MonsterBase::Save(const char * filePath)
{
	GIUpdate();

	FILE* fp = fopen(m_AIPath, "wb");

	if (fp == nullptr) {
		return;
	}

	//データを書き込んでいく。
	while (m_AI.size() != 0) {
		AIData hoge = m_AI.front();
		m_AI.erase(m_AI.begin());
		fwrite(&hoge, sizeof(AIData), 1, fp);
	}

	fclose(fp);
}

void MonsterBase::GIUpdate()
{
	//GIを用いて行動AIの確率の更新。?
	const int listSize = m_actResList.size();
	int AISize = m_AI.size();
	std::vector<float> AIscoreList(AISize, 0.0f);		//行動ごとのスコア。
	float sum = 0.0f;
	//スコアを合計する。
	for (auto res : m_actResList) {
		//評価されていない。
		if (!res.score)	continue;
		//スコアを合計する。
		int i = 0;
		for (i = 0; i < AISize; i++) {
			//既存の行動テーブルに存在する。
			if (res.skillNo == m_AI[i].skillNo
				&&res.target == m_AI[i].target) {
				AIscoreList[i] += res.damage;
				sum += res.damage;
				break;
			}
		}
		//存在しない。
		if (i == AISize) {
			//行動に追加。
			AIData hoge;
			hoge.skillNo = res.skillNo;
			hoge.target = res.target;
			hoge.rate = 3.0f;		//最初からある程度の確率を持たせておく。
			//配列に積む。
			m_AI.push_back(hoge);
			AIscoreList.push_back(res.damage);
			AISize++;		//サイズが増えた。
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
