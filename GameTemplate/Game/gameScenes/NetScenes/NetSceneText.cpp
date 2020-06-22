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
	//�t�H���g�f�[�^�̃��[�h�B
	m_spFont = std::make_unique<DirectX::SpriteFont>(
		g_graphicsEngine->GetD3DDevice(),
		L"Assets/font/myfile.spritefont"
		);

	//�t�H���g�����_�[�̏������B
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
		m_fontRender->SetText(L"�ҋ@���B");
		break;
	case enState_SendGI:
		m_fontRender->SetText(L"GI�f�[�^�̒ʐM���B");
		break;
	case enState_SendStatus:
		m_fontRender->SetText(L"�X�e�[�^�X�f�[�^�̒ʐM���B");
		break;
	case enState_Exit:
		m_fontRender->SetText(L"�ʐM���������܂����B");
		break;
	case enState_Error:
		m_fontRender->SetText(L"�ʐM�Ɏ��s���܂����B");
		break;
	default:
		break;
	}
}
