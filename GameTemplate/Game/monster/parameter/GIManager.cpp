#include "stdafx.h"
#include "GIManager.h"

GIManager::GIManager()
{
}

GIManager::~GIManager()
{
}

bool GIManager::Load(const char * filePath)
{
	//ファイルパスをコピーしておく。
	strcpy(m_AIPath, filePath);
	FILE* fp = fopen(filePath, "rb");
	if (fp == nullptr) {
		//読み込み失敗。
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

void GIManager::LoadDefault(const char * filePath)
{
	FILE* fp = fopen(filePath, "rb");
	if (fp == nullptr) {
		return;
	}

	//読み込んでいく。
	AIData hoge;
	while (fread(&hoge, sizeof(AIData), 1, fp) == 1) {
		m_AI.push_back(hoge);
	}

	fclose(fp);
}

void GIManager::Save()
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

void GIManager::GIUpdate()
{
	//GIを用いて行動AIの確率の更新。?
	const int listSize = m_actResList.size();
	int AISize = m_AI.size();
	std::vector<float> AIscoreList(AISize, 0.0f);		//行動ごとのスコア。
	float sum = 0.0f;
	//スコアを合計する。
	for (auto res : m_actResList) {
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

void GIManager::ActionDicide(int * skill, int * target)
{
	//突然変異的な
	int pMutation = rand() % 100;
	//100分の１の確率。
	if (pMutation == 0) {
		//ランダムに数字を入れる。
		int actNum = rand() % m_AI.size();
		*skill = m_AI[actNum].skillNo;
		*target = m_AI[actNum].target;//突然変異的な
		int pMutation = rand() % 100;

		//関数を抜ける。
		return;
	}
	int res = rand() % 100;	//適当な乱数。
	int sum = 0;

	//行動テーブルをもとに行動させる。
	for (int i = 0; i < m_AI.size(); i++) {
		sum += (int)(m_AI[i].rate * 100);
		if (sum > res) {
			*skill = m_AI[i].skillNo;
			*target = m_AI[i].target;
			break;
		}
	}
}
