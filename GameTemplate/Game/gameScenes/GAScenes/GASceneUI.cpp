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
	//�܂���O���t�폜�B
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
	//�w�i�摜�B
	m_sprite = NewGO<prefab::SpriteRender>(0);
	m_sprite->Init(
		L"Assets/sprite/BackWindow.dds",
		FRAME_BUFFER_W + 46.0f,
		FRAME_BUFFER_H + 46.0f
	);
	//�O���t��\���B
	m_graph = NewGO<prefab::SpriteRender>(1);
	m_graph->Init(
		L"Assets/sprite/Graph.dds",
		GRAPH_W + 15.0f,		//�O�g���ǉ��B
		GRAPH_H + 15.0f			//����B
	);
	//�t�H���g�B
	m_fontGeneration = NewGO<prefab::FontRender>(0);
	m_fontGeneration->SetPivot({ 0.5f,0.5f });
	m_fontGeneration->SetPosition({ 0.0f,280.0f });	//�e�L�X�g�̍��W�B
	m_fontWinRate = NewGO<prefab::FontRender>(0);
	m_fontWinRate->SetPivot({ 0.5f,0.5f });
	m_fontWinRate->SetPosition({ 0.0f,-240.0f });	//�e�L�X�g�̍��W�B
	wchar_t generationText[64];
	swprintf(generationText, L"��%2d����퓬��...", m_currentGenerationNum + 1);
	m_fontGeneration->SetText(generationText);

	wchar_t winRateText[64];
	swprintf(winRateText, L"���݂̏���\n�ō�����%3d�� : ���Ϗ���%.2f��", m_maxWinRate, m_aveWinRate);
	m_fontWinRate->SetText(winRateText);

	//1���ゲ�Ƃ̉������L�^�B
	m_wideRange = GRAPH_W / m_endGenerationNum;

	return true;
}

void GASceneUI::Update()
{

}

void GASceneUI::SetWinRate(int generation, int maxR, float aveR)
{
	if (m_isError)return;
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
	swprintf(winRateText, L"���݂̏���\n�ō�����%3d�� : ���Ϗ���%.2f��", m_maxWinRate, m_aveWinRate);
	m_fontWinRate->SetText(winRateText);
	//�O���t��ǉ�����B
	AddGraphLine();
}

void GASceneUI::EndWinRate(int maxR, float aveR)
{
	if (m_isError)return;
	//�l�R�s�[�B
	m_maxWinRate = maxR;
	m_aveWinRate = aveR;
	//�I���\���B
	wchar_t generationText[64];
	swprintf(generationText, L"  �I�����܂����B\nA�{�^���Ŗ߂�܂��B");
	m_fontGeneration->SetText(generationText);
	//�����\���B
	wchar_t winRateText[64];
	swprintf(winRateText, L"���݂̏���\n�ō�����%3d�� : ���Ϗ���%.2f��", m_maxWinRate, m_aveWinRate);
	m_fontWinRate->SetText(winRateText);
	//���s������Z�B
	m_currentGenerationNum++;
	//�O���t��ǉ�����B
	AddGraphLine();
}

void GASceneUI::SetErrorMasage()
{
	//�I���\���B
	wchar_t generationText[64];
	swprintf(generationText, L"�G���[���������܂����B\nA�{�^���Ŗ߂�܂��B");
	m_fontGeneration->SetText(generationText);
	//�����\���B
	wchar_t winRateText[64];
	swprintf(winRateText, L"���݂̏���\n�ō�����%3d�� : ���Ϗ���%.2f��", m_maxWinRate, m_aveWinRate);
	m_fontWinRate->SetText(winRateText);
	m_isError = true;
}

void GASceneUI::AddGraphLine()
{
	//�O���t��x���W���v�Z�B
	const float graphX = (m_wideRange * (m_currentGenerationNum)) - ((GRAPH_W + m_wideRange) / 2.0f);
	//�ő叟���B
	m_maxWinLine = NewGO<prefab::SpriteRender>(2);
	m_maxWinLine->Init(
		L"Assets/sprite/MaxWinRatePixel.dds",
		1.0f,
		1.0f
	);
	m_maxWinLine->SetScale({ PIXEL_SIZE, PIXEL_SIZE, 1.0f });		//�傫�������B
	m_maxWinLine->SetPivot(LINE_PIVOT);
	m_maxWinLineList.push_back(m_maxWinLine);
	//�O���t��y���W�̌v�Z�B
	const float graphY_max = (m_maxWinRate / 100.0f * GRAPH_H) - (GRAPH_H / 2.0f);
	m_maxWinLine->SetPosition({ graphX ,graphY_max , 5.0f });
	//���Ϗ����B
	m_aveWinLine = NewGO<prefab::SpriteRender>(2);
	m_aveWinLine->Init(
		L"Assets/sprite/AveWinRatePixel.dds",
		1.0f,
		1.0f
	);
	m_aveWinLine->SetScale({ PIXEL_SIZE, PIXEL_SIZE, 1.0f });		//�傫�������B
	m_aveWinLine->SetPivot(LINE_PIVOT);
	m_aveWinLineList.push_back(m_aveWinLine);
	//�O���t��y���W�̌v�Z�B
	const float graphY_ave = (m_aveWinRate / 100.0f * GRAPH_H) - (GRAPH_H / 2.0f);
	m_aveWinLine->SetPosition({ graphX ,graphY_ave , 5.0f });
	//���C���������B
	DrawLine(m_maxWinLineList);
	DrawLine(m_aveWinLineList);
}

void GASceneUI::DrawLine(LineList& lineList)
{
	//���������Ȃ��B
	if(lineList.size() < 2)return;
	auto endPoint = lineList.end();		//���C���̏I���_�B
	endPoint--;
	auto startPoint = endPoint;					//���C���̊J�n�_�B
	startPoint--;	//�I���_�̈��O�̓_�B

	CVector3 diff = (*endPoint)->GetPosition() -(*startPoint)->GetPosition();		//�x�N�g�������߂�B
	float len = diff.Length();		//�����擾�B
	diff.Normalize();
	//�p�x�����߂�B
	float dotRes = diff.Dot(CVector3::AxisX());
	dotRes = min(1.0f, max(-1.0f, dotRes));
	float angle = acosf(dotRes);
	//��]�̌����B
	float dir = diff.Dot(CVector3::AxisY());
	if (dir < 0) {
		angle *= -1.0f;
	}
	//�N�I�[�^�j�I�����쐬�B
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisZ(), angle);

	(*startPoint)->SetRotation(qRot);
	//���C����L�΂��B
	CVector3 lineScale = (*startPoint)->GetScale();
	lineScale.x = len;
	(*startPoint)->SetScale(lineScale);
}
