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
	case enState_Idle:
		m_fontRender->SetText(L"待機中。");
		break;
	case enState_SendGI:
		m_fontRender->SetText(L"GIデータの通信中。");
		break;
	case enState_SendStatus:
		m_fontRender->SetText(L"ステータスデータの通信中。");
		break;
	case enState_Exit:
		m_fontRender->SetText(L"通信が完了しました。");
		break;
	case enState_Error:
		m_fontRender->SetText(L"通信に失敗しました。");
		break;
	default:
		break;
	}
}
