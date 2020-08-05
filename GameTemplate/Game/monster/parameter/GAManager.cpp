#include "stdafx.h"
#include "GAManager.h"
#include "Skill/SkillDataLoad.h"

const float GAManager::SKILL_NEW_RATE = 0.3f;		//追加スキルの初期使用比率。
const float GAManager::FIRST_RATE = 0.15f;			//新規行動の初期比率。
const int GAManager::MAX_TARGET_COUNT = 3;			//ターゲットの最大数。

struct SkillRate
{
	int skillNo = 0;
	float rate = 0.0f;
};

GAManager::GAManager()
{
}

GAManager::~GAManager()
{
}

bool GAManager::Load(const char * filePath)
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

void GAManager::LoadDefault(const char * filePath)
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

void GAManager::Save()
{
	GAUpdate();
	AddNewSkill();

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

void GAManager::GAUpdate()
{
	//GAを用いて行動AIの確率の更新。?
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

	sum = 0.0f;
	//行動の評価を反映する。
	for (int i = 0; i < AISize; i++) {
		m_AI[i].rate = m_AI[i].rate * 10.0f + AIscoreList[i];
		sum += m_AI[i].rate;
	}
	//確率に戻す。
	for (int i = 0; i < AISize; i++) {
		m_AI[i].rate /= sum;
	}
}

void GAManager::AddNewSkill()
{
	//スキルごとの使用率を計算。
	std::vector<SkillRate> rateList;

	for (auto& ai : m_AI)
	{
		int i = 0;
		for (i = 0; i < rateList.size(); i++) {
			//リストに存在する。
			if (ai.skillNo == rateList[i].skillNo) {
				rateList[i].rate += ai.rate;
				break;
			}
		}
		//存在しない。
		if (i == rateList.size()) {
			//リストに追加。
			SkillRate hoge;
			hoge.skillNo = ai.skillNo;
			hoge.rate = ai.rate;
			//配列に積む。
			rateList.push_back(hoge);
		}
	}

	//スキルごとの使用率が一定を超えているか？
	std::vector<int> skillList;

	for (auto& sr : rateList)
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

		int NextSkillSize = static_cast<int>(data.NextSkillNo.size());

		//次のスキルはない。
		if (NextSkillSize == 0) continue;

		AIData newData;

		//次のスキル探査。
		//乱数。
		int r = rand() % NextSkillSize;
		newData.skillNo = data.NextSkillNo[r];

		int i = 0;
		for (i = 0; i < m_AI.size(); i++)
		{
			//同じスキルがすでにある。
			if (newData.skillNo == m_AI[i].skillNo)	 break;
		}
		//中断。
		if (i != m_AI.size()) continue;


		//ターゲット決める。
		newData.target = rand() % MAX_TARGET_COUNT;
		//使用率を適当に持たせておく。
		newData.rate = FIRST_RATE;		//半分くらいがちょうどいいかなぁ？
		//行動リストに積む。
		m_AI.push_back(newData);
	}

	//確率に戻す。
	float sum = 0.0f;
	for (auto&ai : m_AI)
	{
		sum += ai.rate;
	}
	sum = max(1.0f, sum);		//ゼロ割発生しないと思うけど回避。
	for (auto&ai : m_AI)
	{
		ai.rate /= sum;
	}
}

void GAManager::ActionDicide(int& skill, int& target)
{
	//突然変異的な
	int pMutation = rand() % 100;
	//100分の１の確率。
	if (pMutation == 0) {
		//ランダムに数字を入れる。
		int actNum = rand() % m_AI.size();
		skill = m_AI[actNum].skillNo;
		target = m_AI[actNum].target;

		//関数を抜ける。
		return;
	}
	int res = rand() % 100;	//適当な乱数。
	float sum = 0;

	//行動テーブルをもとに行動させる。
	for (int i = 0; i < m_AI.size(); i++) {
		sum += m_AI[i].rate * 100;
		if (sum > res) {
			skill = m_AI[i].skillNo;
			target = m_AI[i].target;
			break;
		}
	}
}
