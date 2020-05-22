#include "stdafx.h"
#include "NetSceneText.h"
#include "NetScenes.h"

NetSceneText::NetSceneText()
{
	m_state = enState_Idle;
}

NetSceneText::~NetSceneText()
{
	DeleteGO(m_fontRender);
}

bool NetSceneText::Start()
{
	//フォントデータのロード。
	m_spFont = std::make_unique<DirectX::SpriteFont>(
		g_graphicsEngine->GetD3DDevice(),
		L"Assets/font/myfile.spritefont"
		);

	//フォントレンダーの初期化。
	m_fontRender = NewGO<prefab::FontRender>(3);
	m_fontRender->SetFont(m_spFont.get());
	m_fontRender->SetPivot({ 0.5f,0.5f });

	return true;
}

void NetSceneText::Update()
{
	switch (m_state)
	{
	case enState_Init:
		break;
	case enState_Idle:
		break;
	case enState_Send:
		if (g_pad[0].IsPress(enButtonA)) {
			m_color -= CVector3::One() * 0.01f;
			m_color.Max(CVector3::Zero());
			m_fontRender->SetColor(m_color);
			m_fontRender->SetText(L"送信");
		}
		else if (g_pad[0].IsPress(enButtonB)) {
			m_color += CVector3::One() * 0.01f;
			m_color.Min(CVector3::One());
			m_fontRender->SetColor(m_color);
		}
		else if (g_pad[0].IsTrigger(enButtonX)) {
			//m_fontRender->SetColor({ 1.0f,0.0f,0.0f });
			m_fontRender->SetPivot({ 1.0f,1.0f });
		}
		else if (g_pad[0].IsTrigger(enButtonY)) {
			//m_fontRender->SetColor({ 0.0f,1.0f,0.0f });
			m_fontRender->SetPivot({ 0.0f,0.0f });
		}
		break;
	case enState_Exit:
		break;
	default:
		break;
	}
}

void NetSceneText::SetText(const wchar_t * text)
{
	m_fontRender->SetText(text);
}

void NetSceneText::SetState(NetState state)
{
	m_state = state;
	switch (m_state)
	{
	case enState_Init:

		break;
	case enState_Idle:
		m_fontRender->SetText(L"待機中。");
		break;
	case enState_Send:
		m_fontRender->SetText(L"A(Jキー)ボタンでデータ送信");
		break;
	case enState_Exit:

		break;
	default:
		break;
	}
}
