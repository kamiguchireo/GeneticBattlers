#include "stdafx.h"
#include "GAScenes.h"
#include "../BattleScenes/AIResouce.h"

const float GAScenes::RATE_CHANGE = 0.01f;	//初期遺伝子生成のための確率変動率。
const int GAScenes::CHANGE_NUM = 5;	//確率変動で作る数。

GAScenes::GAScenes()
{
	//データ読み込み。
	LoadAIData("Assets/AIData/Attacker.bin", m_myAI[en_Attacker]);
	LoadAIData("Assets/AIData/Healer.bin", m_myAI[en_Healer]);
	LoadAIData("Assets/AIData/Supporter.bin", m_myAI[en_Supporter]);

	auto aiResouce = AIResouce::GetInstance();
	if (aiResouce != nullptr)
	{
		m_enemyAI[en_Attacker] = aiResouce->GetAttacker();
		m_enemyAI[en_Healer] = aiResouce->GetHealer();
		m_enemyAI[en_Supporter] = aiResouce->GetSupporter();
		DeleteGO(aiResouce);
	}
}

GAScenes::~GAScenes()
{
}

bool GAScenes::Start()
{
	//行動の数を記録。
	m_actionNum = 0;
	for (auto& ai : m_myAI)
	{
		m_actionNum += ai.size();
	}
	//初期遺伝子をたくさん作成。
	FirstGenesCreate();

	return true;
}

void GAScenes::Update()
{
}

void GAScenes::LoadAIData(const char * filePath, AITable & ai)
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
		ai.push_back(hoge);
	}

	fclose(fp);
}

void GAScenes::FirstGenesCreate()
{
	//初期AIをコピー
	AITableList tables;
	tables.resize(en_JobNum);
	tables[en_Attacker] = m_myAI[en_Attacker];
	tables[en_Healer] = m_myAI[en_Healer];
	tables[en_Supporter] = m_myAI[en_Supporter];

	//確率変動のないデータを記録。
	m_currentGenetics.push_back(tables);
	//遺伝子の数を行動の数±5%の数まで増やす。
	for (auto& job: tables)		//ジョブ事に回す。
	{
		for (int i = 0; i < job.size(); i++)
		{
			//変動させる元の確率を取っておく。
			float rate = job[i].rate;

			for (int j = 0; j < CHANGE_NUM; j++)
			{
				//確率を+に変動させる。
				job[i].rate = rate + RATE_CHANGE * (j + 1);

				//現行遺伝子に記録する。
				m_currentGenetics.push_back(tables);

				//確率を-に変動させる。
				job[i].rate = rate - RATE_CHANGE * (j + 1);
				//確率が0を下回ってなければ。+変動はよほどのことがない限り1超えないかなぁ多分
				if (job[i].rate > 0.0f)
				{
					//現行遺伝子に記録する。
					m_currentGenetics.push_back(tables);
				}
			}

			//変動を元に戻しておく。
			job[i].rate = rate;
		}
	}
}


