#include "stdafx.h"
#include "GASceneUI.h"

GASceneUI::GASceneUI()
{
}

GASceneUI::~GASceneUI()
{
	DeleteGO(m_sprite);
	DeleteGO(m_fontGeneration);
	DeleteGO(m_fontWinRate);
	DeleteGO(m_graph);
	//折れ線グラフ削除。
	for (auto line : m_maxWinLineList)
	{
		DeleteGO(line);
	}
	for (auto line : m_aveWinLineList)
	{
		DeleteGO(line);
	}
}

bool GASceneUI::Start()
{
	//背景画像。
	m_sprite = NewGO<prefab::SpriteRender>(0);
	m_sprite->Init(
		L"Assets/sprite/BackWindow.dds",
		FRAME_BUFFER_W + 46.0f,
		FRAME_BUFFER_H + 46.0f
	);
	//グラフを表示。
	m_graph = NewGO<prefab::SpriteRender>(1);
	m_graph->Init(
		L"Assets/sprite/Graph.dds",
		GRAPH_W + 15.0f,		//外枠分追加。
		GRAPH_H + 15.0f			//同上。
	);
	//フォント。
	m_fontGeneration = NewGO<prefab::FontRender>(0);
	m_fontGeneration->SetPivot({ 0.5f,0.5f });
	m_fontGeneration->SetPosition({ 0.0f,280.0f });	//テキストの座標。
	m_fontWinRate = NewGO<prefab::FontRender>(0);
	m_fontWinRate->SetPivot({ 0.5f,0.5f });
	m_fontWinRate->SetPosition({ 0.0f,-240.0f });	//テキストの座標。
	wchar_t generationText[64];
	swprintf(generationText, L"第%2d世代戦闘中...", m_currentGenerationNum + 1);
	m_fontGeneration->SetText(generationText);

	wchar_t winRateText[64];
	swprintf(winRateText, L"現在の勝率\n最高勝率%3d％ : 平均勝率%3.2f％", m_maxWinRate, m_aveWinRate);
	m_fontWinRate->SetText(winRateText);

	//1世代ごとの横幅を記録。
	m_wideRange = GRAPH_W / m_endGenerationNum;

	return true;
}

void GASceneUI::Update()
{

}

void GASceneUI::SetWinRate(int generation, int maxR, float aveR)
{
	//値をコピーしておく。
	m_currentGenerationNum = generation;
	m_maxWinRate = maxR;
	m_aveWinRate = aveR;
	//現行世代表示。
	wchar_t generationText[64];
	swprintf(generationText, L"第%2d世代戦闘中...", m_currentGenerationNum + 1);
	m_fontGeneration->SetText(generationText);
	//勝率表示。
	wchar_t winRateText[64];
	swprintf(winRateText, L"現在の勝率\n最高勝率%3d％ : 平均勝率%3.2f％", m_maxWinRate, m_aveWinRate);
	m_fontWinRate->SetText(winRateText);

	//グラフのx座標を計算。
	const float graphX = (m_wideRange * m_currentGenerationNum) - (GRAPH_W / 2.0f);
	//最大勝率。
	m_maxWinLine = NewGO<prefab::SpriteRender>(2);
	m_maxWinLine->Init(
		L"Assets/sprite/MaxWinRatePixel.dds",
		5.0f,
		5.0f
	);
	m_maxWinLineList.push_back(m_maxWinLine);
	//グラフのy座標の計算。
	const float graphY_max = (m_maxWinRate / 100.0f * GRAPH_H) - (GRAPH_H / 2.0f);
	m_maxWinLine->SetPosition({ graphX ,graphY_max , 5.0f });
	//平均勝率。
	m_aveWinLine = NewGO<prefab::SpriteRender>(2);
	m_aveWinLine->Init(
		L"Assets/sprite/AveWinRatePixel.dds",
		5.0f,
		5.0f
	);
	m_aveWinLineList.push_back(m_aveWinLine);
	//グラフのy座標の計算。
	const float graphY_ave = (m_aveWinRate / 100.0f * GRAPH_H) - (GRAPH_H / 2.0f);
	m_aveWinLine->SetPosition({ graphX ,graphY_ave , 5.0f });
}

void GASceneUI::EndWinRate(int maxR, float aveR)
{
	//値コピー。
	m_maxWinRate = maxR;
	m_aveWinRate = aveR;
	//終了表示。
	wchar_t generationText[64];
	swprintf(generationText, L"  終了しました。\nAボタンで戻ります。");
	m_fontGeneration->SetText(generationText);
	//勝率表示。
	wchar_t winRateText[64];
	swprintf(winRateText, L"現在の勝率\n最高勝率%3d％ : 平均勝率%3.2f％", m_maxWinRate, m_aveWinRate);
	m_fontWinRate->SetText(winRateText);
}
