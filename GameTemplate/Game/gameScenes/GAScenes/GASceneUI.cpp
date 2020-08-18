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
	//�w�i�摜�B
	m_sprite = NewGO<prefab::SpriteRender>(0);
	m_sprite->Init(
		L"Assets/sprite/BackWindow.dds",
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);
	//�t�H���g�B
	m_fontGeneration = NewGO<prefab::FontRender>(0);
	m_fontGeneration->SetPivot({ 0.5f,0.5f });
	m_fontGeneration->SetPosition({ 0.0f,200.0f });
	m_fontWinRate = NewGO<prefab::FontRender>(0);
	m_fontWinRate->SetPivot({ 0.5f,0.5f });
	m_fontWinRate->SetPosition({ 0.0f,-200.0f });
	wchar_t generationText[64];
	swprintf(generationText, L"��%2d����퓬��...", m_currentGenerationNum + 1);
	m_fontGeneration->SetText(generationText);

	wchar_t winRateText[64];
	swprintf(winRateText, L"���݂̏���\n�ō�����%3d�� : ���Ϗ���%3.2f��", m_maxWinRate, m_aveWinRate);
	m_fontWinRate->SetText(winRateText);

	return true;
}

void GASceneUI::Update()
{

}

void GASceneUI::SetWinRate(int generation, int maxR, float aveR)
{
	//�l���R�s�[���Ă����B
	m_currentGenerationNum = generation;
	m_maxWinRate = maxR;
	m_aveWinRate = aveR;
	//���s����\���B
	wchar_t generationText[64];
	swprintf(generationText, L"��%2d����퓬��...", m_currentGenerationNum + 1);
	m_fontGeneration->SetText(generationText);
	//�����\���B
	wchar_t winRateText[64];
	swprintf(winRateText, L"���݂̏���\n�ō�����%3d�� : ���Ϗ���%3.2f��", m_maxWinRate, m_aveWinRate);
	m_fontWinRate->SetText(winRateText);
}

void GASceneUI::EndWinRate(int maxR, float aveR)
{
	//�l�R�s�[�B
	m_maxWinRate = maxR;
	m_aveWinRate = aveR;
	//�I���\���B
	wchar_t generationText[64];
	swprintf(generationText, L"�I�����܂����B\nA�{�^���Ŗ߂�܂��B");
	m_fontGeneration->SetText(generationText);
	//�����\���B
	wchar_t winRateText[64];
	swprintf(winRateText, L"���݂̏���\n�ō�����%3d�� : ���Ϗ���%3.2f��", m_maxWinRate, m_aveWinRate);
	m_fontWinRate->SetText(winRateText);
}
