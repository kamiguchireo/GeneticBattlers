#include "stdafx.h"
#include "NetScenes.h"
#include "Fade.h"

NetScenes::NetScenes()
{
}

NetScenes::~NetScenes()
{
	DeleteGO(m_fontRender);
}

bool NetScenes::Start()
{
	//�t�H���g�f�[�^�̃��[�h�B
	m_spFont = std::make_unique<DirectX::SpriteFont>(
		g_graphicsEngine->GetD3DDevice(),
		L"Assets/font/myfile.spritefont"
		);

	//�t�H���g�����_�[�̏������B
	m_fontRender = NewGO<prefab::FontRender>(3);
	m_fontRender->SetFont(m_spFont.get());
	m_fontRender->SetPivot({ 0.0f,0.0f });
	m_fontRender->SetText(L"�e�X�gTest1234");

	//�t�F�[�h�̏����B
	m_fade = Fade::GetInstance();
	m_fade->StartFadeIn();

	return true;
}

void NetScenes::Update()
{
	if (g_pad[0].IsPress(enButtonA)) {
		m_color -= CVector3::One() * 0.01f;
		m_color.Max(CVector3::Zero());
		m_fontRender->SetColor(m_color);
		m_fontRender->SetText(L"����������I");
	}
	else if (g_pad[0].IsPress(enButtonB)) {
		m_color += CVector3::One() * 0.01f;
		m_color.Min(CVector3::One());
		m_fontRender->SetColor(m_color);
	}
	else if (g_pad[0].IsTrigger(enButtonX)) {
		m_fontRender->SetColor({ 1.0f,0.0f,0.0f });
		m_fontRender->SetPivot({ 1.0f,1.0f });
	}
	else if (g_pad[0].IsTrigger(enButtonY)) {
		m_fontRender->SetColor({ 0.0f,1.0f,0.0f });
		m_fontRender->SetPivot({ 0.0f,0.0f });
	}
}
