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
	swprintf(winRateText, L"現在の勝率\n最高勝率%3d％ : 平均勝率%.2f％", m_maxWinRate, m_aveWinRate);
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
	if (m_isError)return;
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
	swprintf(winRateText, L"現在の勝率\n最高勝率%3d％ : 平均勝率%.2f％", m_maxWinRate, m_aveWinRate);
	m_fontWinRate->SetText(winRateText);
	//グラフを追加する。
	AddGraphLine();
}

void GASceneUI::EndWinRate(int maxR, float aveR)
{
	if (m_isError)return;
	//値コピー。
	m_maxWinRate = maxR;
	m_aveWinRate = aveR;
	//終了表示。
	wchar_t generationText[64];
	swprintf(generationText, L"  終了しました。\nAボタンで戻ります。");
	m_fontGeneration->SetText(generationText);
	//勝率表示。
	wchar_t winRateText[64];
	swprintf(winRateText, L"現在の勝率\n最高勝率%3d％ : 平均勝率%.2f％", m_maxWinRate, m_aveWinRate);
	m_fontWinRate->SetText(winRateText);
	//現行世代加算。
	m_currentGenerationNum++;
	//グラフを追加する。
	AddGraphLine();
}

void GASceneUI::SetErrorMasage()
{
	//終了表示。
	wchar_t generationText[64];
	swprintf(generationText, L"エラーが発生しました。\nAボタンで戻ります。");
	m_fontGeneration->SetText(generationText);
	//勝率表示。
	wchar_t winRateText[64];
	swprintf(winRateText, L"現在の勝率\n最高勝率%3d％ : 平均勝率%.2f％", m_maxWinRate, m_aveWinRate);
	m_fontWinRate->SetText(winRateText);
	m_isError = true;
}

void GASceneUI::AddGraphLine()
{
	//グラフのx座標を計算。
	const float graphX = (m_wideRange * (m_currentGenerationNum)) - ((GRAPH_W + m_wideRange) / 2.0f);
	//最大勝率。
	m_maxWinLine = NewGO<prefab::SpriteRender>(2);
	m_maxWinLine->Init(
		L"Assets/sprite/MaxWinRatePixel.dds",
		1.0f,
		1.0f
	);
	m_maxWinLine->SetScale({ PIXEL_SIZE, PIXEL_SIZE, 1.0f });		//大きさ調整。
	m_maxWinLine->SetPivot(LINE_PIVOT);
	m_maxWinLineList.push_back(m_maxWinLine);
	//グラフのy座標の計算。
	const float graphY_max = (m_maxWinRate / 100.0f * GRAPH_H) - (GRAPH_H / 2.0f);
	m_maxWinLine->SetPosition({ graphX ,graphY_max , 5.0f });
	//平均勝率。
	m_aveWinLine = NewGO<prefab::SpriteRender>(2);
	m_aveWinLine->Init(
		L"Assets/sprite/AveWinRatePixel.dds",
		1.0f,
		1.0f
	);
	m_aveWinLine->SetScale({ PIXEL_SIZE, PIXEL_SIZE, 1.0f });		//大きさ調整。
	m_aveWinLine->SetPivot(LINE_PIVOT);
	m_aveWinLineList.push_back(m_aveWinLine);
	//グラフのy座標の計算。
	const float graphY_ave = (m_aveWinRate / 100.0f * GRAPH_H) - (GRAPH_H / 2.0f);
	m_aveWinLine->SetPosition({ graphX ,graphY_ave , 5.0f });
	//ラインを引く。
	DrawLine(m_maxWinLineList);
	DrawLine(m_aveWinLineList);
}

void GASceneUI::DrawLine(LineList& lineList)
{
	//線を引けない。
	if(lineList.size() < 2)return;
	auto endPoint = lineList.end();		//ラインの終了点。
	endPoint--;
	auto startPoint = endPoint;					//ラインの開始点。
	startPoint--;	//終了点の一つ手前の点。

	CVector3 diff = (*endPoint)->GetPosition() -(*startPoint)->GetPosition();		//ベクトルを求める。
	float len = diff.Length();		//長さ取得。
	diff.Normalize();
	//角度を求める。
	float dotRes = diff.Dot(CVector3::AxisX());
	dotRes = min(1.0f, max(-1.0f, dotRes));
	float angle = acosf(dotRes);
	//回転の向き。
	float dir = diff.Dot(CVector3::AxisY());
	if (dir < 0) {
		angle *= -1.0f;
	}
	//クオータニオンを作成。
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisZ(), angle);

	(*startPoint)->SetRotation(qRot);
	//ラインを伸ばす。
	CVector3 lineScale = (*startPoint)->GetScale();
	lineScale.x = len;
	(*startPoint)->SetScale(lineScale);
}
