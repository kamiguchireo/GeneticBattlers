#include "stdafx.h"
#include "AIManager.h"
#include "Skill/SkillDataLoad.h"

const float AIManager::SKILL_NEW_RATE = 0.4f;		//スキル追加のために必要な使用頻度。
const float AIManager::FIRST_RATE = 0.05f;			//新規行動の初期比率。
const int AIManager::NEW_SKILL_PLOB_WEIGHT[] = {	//スキル進化の確率重み(%)
	60,30,10
};
const int AIManager::MAX_TARGET_COUNT = 3;			//ターゲットの最大数。


AIManager::AIManager()
{
}

AIManager::~AIManager()
{
}

bool AIManager::Load(const char * filePath)
{
	//ファイルパスをコピーしておく。
	strcpy(m_AIPath, filePath);
	FILE* fp = fopen(filePath, "rb");
	if (fp == nullptr) {
		//読み込み失敗。
#ifdef _DEBUG
		char message[256];
		sprintf(message, "binデータの読み込みに失敗しました。%s\n", filePath);
		OutputDebugStringA(message);
#endif
		return false;
	}

	//読み込んでいく。
	AIData hoge;
	while (fread(&hoge, sizeof(AIData), 1, fp) == 1) {
		m_AI.push_back(hoge);
	}

	fclose(fp);

	//読み込み成功。
	return true;
}

void AIManager::LoadDefault(const char * filePath)
{
	FILE* fp = fopen(filePath, "rb");
	if (fp == nullptr) {
		//読み込み失敗。
#ifdef _DEBUG
		char message[256];
		sprintf(message, "binデータの読み込みに失敗しました。%s\n", filePath);
		OutputDebugStringA(message);
#endif
		return;
	}

	//読み込んでいく。
	AIData hoge;
	while (fread(&hoge, sizeof(AIData), 1, fp) == 1) {
		m_AI.push_back(hoge);
	}

	fclose(fp);
}

void AIManager::Save()
{
	AIUpdate();
	AddNewSkill();
	DeleteSkill();

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

void AIManager::AIUpdate()
{
	//行動評価による行動AIの確率の更新。
	const int listSize = static_cast<const int>(m_actResList.size());
	int AISize = static_cast<int>(m_AI.size());
	std::vector<float> AIscoreList(AISize, 0.0f);		//行動ごとのスコア。
	float sum = 0.0f;
	//スコアを合計する。
	for (auto& res : m_actResList) {
		////評価されていない。
		//if (!res.score)	continue;
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
			hoge.rate = FIRST_RATE;		//最初からある程度の確率を持たせておく。
			//配列に積む。
			m_AI.push_back(hoge);
			AIscoreList.push_back(static_cast<float>(res.damage));
			AISize++;		//サイズが増えた。
		}
	}
	//0割り回避。
	sum = max(sum, 1.0f);
	//比率計算。
	for (int i = 0; i < AISize; i++) {
		AIscoreList[i] /= sum;
	}

	//行動の評価を反映する。
	for (int i = 0; i < AISize; i++) {
		m_AI[i].rate = m_AI[i].rate * 10.0f + AIscoreList[i];
	}
	//使用率を確率に直す。
	RateCalc();
}

void AIManager::AddNewSkill()
{
	//スキルごとの使用率を計算。
	SkillRateCalc();

	//スキルごとの使用率が一定を超えているか？
	std::vector<int> skillList;

	for (auto& sr : m_skillRateList)
	{
		if (sr.rate > SKILL_NEW_RATE)
		{
			skillList.push_back(sr.skillNo);
		}
	}
	//超えているものがない。中断。
	if (skillList.size() == 0) return;

	//スキルのデータを取得。
	auto skillData = SkillDataLoad::GetInstance();
	if (skillData == nullptr) return;

	//追加するスキルを決める。
	for (auto& No : skillList)
	{
		//スキルデータ取得。
		SkillData data = skillData->GetSkillData(No);
		//次のスキルはない。
		if (data.NextSkillNo.size() == 0) continue;

		AIData newData;

		//次のスキル探査。
		int newSkillNo = DisideNewSkill(data);
		newData.skillNo = newSkillNo;

		int i = 0;
		for (i = 0; i < m_skillRateList.size(); i++)
		{
			//同じスキルがすでにある。
			if (newData.skillNo == m_skillRateList[i].skillNo)	 break;
		}
		//中断。
		if (i != m_skillRateList.size()) continue;

		//スキルが存在しない。
		for (int j = 0; j < MAX_TARGET_COUNT; j++)
		{
			//ターゲット決める。
			newData.target = j;
			//使用率を適当に持たせておく。
			newData.rate = FIRST_RATE / MAX_TARGET_COUNT;		//半分くらいがちょうどいいかなぁ？
			//行動リストに積む。
			m_AI.push_back(newData);
		}
	}

	//確率に戻す。
	RateCalc();
}

int AIManager::DisideNewSkill(const SkillData & data)
{
	int ret = 0;
	//サイズ取得。
	const int noSize = static_cast<const int>(data.NextSkillNo.size());

	int r = g_random.GetRandomInt() % 100;		//乱数 0 ～　99
	int prob = 0;
	for (int i = 0;i < noSize;i++)
	{
		prob += NEW_SKILL_PLOB_WEIGHT[i];
		//決定。
		if (r < prob)
		{
			ret = data.NextSkillNo[i];
			break;
		}
	}

	return ret;
}

void AIManager::DeleteSkill()
{
	//スキルごとの使用確率計算。
	SkillRateCalc();

	std::vector<int> deleteSkillNo;		//削除リスト。

	for (auto& s : m_skillRateList)
	{
		//使用確率が低い。
		if (s.rate < 0.02f)
		{
			//記録しておく。
			deleteSkillNo.push_back(s.skillNo);
		}
	}
	
	//削除するものがないならリターン。
	if (deleteSkillNo.size() == 0)return;

	//配列の中から探して削除。
	for (auto itr = m_AI.begin(); itr != m_AI.end();itr++)
	{
		//削除していく。
		for (auto no : deleteSkillNo)
		{
			//削除する。
			if ((*itr).skillNo == no)
			{
				itr = m_AI.erase(itr);
				//イテレータの位置調整。
				itr--;
				break;
			}
		}
	}

	//確率に戻す。
	RateCalc();
}

void AIManager::SkillRateCalc()
{
	//リストを空にしておく。
	m_skillRateList.clear();

	//スキルごとの使用率を計算。
	for (auto& ai : m_AI)
	{
		int i = 0;
		for (i = 0; i < m_skillRateList.size(); i++) {
			//リストに存在する。
			if (ai.skillNo == m_skillRateList[i].skillNo) {
				m_skillRateList[i].rate += ai.rate;
				break;
			}
		}
		//存在しない。
		if (i == m_skillRateList.size()) {
			//リストに追加。
			SkillRate hoge;
			hoge.skillNo = ai.skillNo;
			hoge.rate = ai.rate;
			//配列に積む。
			m_skillRateList.push_back(hoge);
		}
	}
}
