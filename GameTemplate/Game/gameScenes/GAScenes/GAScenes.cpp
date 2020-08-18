#include "stdafx.h"
#include "GAScenes.h"
#include "../BattleScenes/AIResouce.h"
#include "EvaluationCalculator.h"
#include "Fade.h"
#include "../TitleScene.h"

using namespace GA;

const int GAScenes::END_GENERATION = 100;	//何世代まで続けるか。
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
	m_evaluationCalc = NewGO<EvaluationCalculator>(0);
	//敵のAIを設定しておく。
	m_evaluationCalc->SetEnemyAI(m_enemyAI[en_Attacker], en_Attacker);
	m_evaluationCalc->SetEnemyAI(m_enemyAI[en_Healer], en_Healer);
	m_evaluationCalc->SetEnemyAI(m_enemyAI[en_Supporter], en_Supporter);
}

GAScenes::~GAScenes()
{
	if (m_evaluationCalc != nullptr)
	{
		DeleteGO(m_evaluationCalc);
	}
	DeleteGO(m_sprite);
	DeleteGO(m_fontGeneration);
}

bool GAScenes::Start()
{
	//行動の数を記録。
	m_geneSize = 0;
	for (auto& ai : m_myAI)
	{
		m_geneSize += static_cast<int>(ai.size());
	}
	//初期遺伝子をたくさん作成。
	FirstGenesCreate();
	//評価値を計算する。
	CalcWinRate();
	//評価値でソート。
	SortGenes();
	//背景画像。
	m_sprite = NewGO<prefab::SpriteRender>(0);
	m_sprite->Init(
		L"Assets/sprite/BackWindow.dds",
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);
	//フォント。
	m_fontGeneration = NewGO<prefab::FontRender>(0);
	m_fontGeneration->SetPivot({ 0.5f,0.5f });
	m_fontGeneration->SetPosition({ 0.0f,200.0f });
	m_fontWinRate = NewGO<prefab::FontRender>(0);
	m_fontWinRate->SetPivot({ 0.5f,0.5f });
	m_fontWinRate->SetPosition({ 0.0f,-200.0f });
	wchar_t generationText[64];
	swprintf(generationText, L"第%3d世代", m_currentGenerationNum);
	m_fontGeneration->SetText(generationText);

	wchar_t winRateText[64];
	swprintf(winRateText, L"最高勝率%3d%", m_maxWinRate);
	m_fontWinRate->SetText(winRateText);

	m_fade = Fade::GetInstance();
	m_fade->StartFadeIn();
	m_sceneState = en_FadeIn;

	return true;
}

void GAScenes::Update()
{
	switch (m_sceneState)
	{
	case GAScenes::en_FadeIn:
		if (!m_fade->IsFade())
		{
			m_sceneState = en_GA;
		}
		break;
	case GAScenes::en_GA:
		if (m_currentGenerationNum <= MAX_GENERATION)
		{
			GeneSelection();	//淘汰。
			GenesCrossover();	//交叉。
			//突然変異。
			CalcWinRate();		//評価。クソ遅い。
			SortGenes();		//ソート。
			wchar_t generationText[64];
			swprintf(generationText, L"第%3d世代", m_currentGenerationNum);
			m_fontGeneration->SetText(generationText);

			wchar_t winRateText[64];
			swprintf(winRateText, L"最高勝率%3d%", m_maxWinRate);
			m_fontWinRate->SetText(winRateText);
		}
		else
		{
			m_sceneState = en_End;
		}
		break;
	case GAScenes::en_End:
		if (g_pad[0].IsTrigger(enButtonA))
		{
			m_sceneState = en_FadeOut;
			m_fade->StartFadeOut();
		}
		break;
	case GAScenes::en_FadeOut:
		if (!m_fade->IsFade())	//フェードアウトが終わった。
		{
			DeleteGO(this);
			NewGO<TitleScene>(0, nullptr);
		}
		break;
	default:
		break;
	}
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
	m_currentGenetics.push_back({ tables,0 });
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
				m_currentGenetics.push_back({ tables,0 });

				//確率を-に変動させる。
				job[i].rate = rate - RATE_CHANGE * (j + 1);
				//確率が0を下回ってなければ。+変動はよほどのことがない限り1超えないかなぁ多分
				if (job[i].rate > 0.0f)
				{
					//現行遺伝子に記録する。
					m_currentGenetics.push_back({ tables,0 });
				}
			}

			//変動を元に戻しておく。
			job[i].rate = rate;
		}
	}
}

void GAScenes::CalcWinRate()
{
	//遺伝子の数。
	int genesSize = m_currentGenetics.size();

	//遺伝子毎の勝率計算。
	for (int i = 0; i < genesSize; i++)
	{
		m_currentGenetics[i].winRate  = m_evaluationCalc->Calculation(m_currentGenetics[i].genetic);
	}
}

void GAScenes::SortGenes()
{
	//現行遺伝子のソートを行う。
	std::sort(m_currentGenetics.begin(), m_currentGenetics.end(),
		[](const Genetic& a, const Genetic& b) {return a.winRate < b.winRate; });

	//一番優秀な遺伝子の勝率を記録。
	m_maxWinRate = (*m_currentGenetics.begin()).winRate;
	//世代数+1
	m_currentGenerationNum++;
}

void GAScenes::GeneSelection()
{
	//遺伝子の数を記録
	int eliteSize = static_cast<int>(m_currentGenetics.size());
	//残す数との比較。
	eliteSize = min(eliteSize, SELECT_ELETE);

	//エリート遺伝子のリスト初期化
	m_eliteGenetics.resize(eliteSize);
	//エリートをコピー。
	for (int i = 0; i < eliteSize; i++)
	{
		m_eliteGenetics[i] = m_currentGenetics[i];
	}
	//現行世代を空にしておく。
	m_currentGenetics.clear();
}

void GAScenes::GenesCrossover()
{
	//交叉のためにエリートをコピー。
	GeneticsList crossGenes1 = m_eliteGenetics;
	GeneticsList crossGenes2 = m_eliteGenetics;

	int crossSize = static_cast<int>(m_eliteGenetics.size());

	//交叉。
	for (int i = 0; i < crossSize; i++)
	{
		//職業ごとに行う。
		for (int j = 0; j < GA::en_JobNum; j++)
		{
			GeneSwap(
				crossGenes1[i].genetic[j],						//i番目の遺伝子
				crossGenes2[(i + 1) % crossSize].genetic[j]		//i+1番目の遺伝子
			);
		}
	}

	//現行世代に記録していく。評価値は0に戻しておく。
	for (auto&elite : m_eliteGenetics)
	{
		m_currentGenetics.push_back({ elite.genetic,0 });
	}
	for (auto&cross1 : crossGenes1)
	{
		m_currentGenetics.push_back({ cross1.genetic,0 });
	}
	for (auto&cross2 : crossGenes2)
	{
		m_currentGenetics.push_back({ cross2.genetic,0 });
	}
	//データをクリア。
	m_eliteGenetics.clear();
	crossGenes1.clear();
	crossGenes2.clear();
}

void GAScenes::GeneSwap(AITable & _t1, AITable & _t2)
{
	//サイズが違う。
	if (_t1.size() != _t2.size()) return;
	////配列のサイズ。
	int maxSize = _t1.size();
	//交叉する場所を決める。
	int pMax = g_random.GetRandomInt() % maxSize;
	pMax = min(pMax + 5, (maxSize-1));	//ある程度数値を持たせておく。0割り回避も含む。
	int pMin = g_random.GetRandomInt() % pMax;
	//交叉。
	for (int i = pMin; i <= pMax; i++)
	{
		//確率を交換。
		std::swap(_t1[i].rate, _t2[i].rate);
	}

}


