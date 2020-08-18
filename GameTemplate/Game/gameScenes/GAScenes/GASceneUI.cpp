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
}

bool GASceneUI::Start()
{
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
	swprintf(generationText, L"第%2d世代戦闘中...", m_currentGenerationNum + 1);
	m_fontGeneration->SetText(generationText);

	wchar_t winRateText[64];
	swprintf(winRateText, L"現在の勝率\n最高勝率%3d％ : 平均勝率%3.2f％", m_maxWinRate, m_aveWinRate);
	m_fontWinRate->SetText(winRateText);

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
}

void GASceneUI::EndWinRate(int maxR, float aveR)
{
	//値コピー。
	m_maxWinRate = maxR;
	m_aveWinRate = aveR;
	//終了表示。
	wchar_t generationText[64];
	swprintf(generationText, L"終了しました。\nAボタンで戻ります。");
	m_fontGeneration->SetText(generationText);
	//勝率表示。
	wchar_t winRateText[64];
	swprintf(winRateText, L"現在の勝率\n最高勝率%3d％ : 平均勝率%3.2f％", m_maxWinRate, m_aveWinRate);
	m_fontWinRate->SetText(winRateText);
}
