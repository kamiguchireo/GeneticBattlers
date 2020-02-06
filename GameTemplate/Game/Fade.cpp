#include "stdafx.h"
#include "Fade.h"

Fade* Fade::m_instance = nullptr;

Fade::Fade()
{
	if (m_instance != nullptr)
	{
		std::abort();
	}
	m_instance = this;
}

Fade::~Fade()
{
	m_instance = nullptr;
}

bool Fade::Start()
{
	m_texture.CreateFromDDSTextureFromFile(L"Assets/sprite/fade.dds");
	m_sprite.Init(m_texture.GetBody(), FRAME_BUFFER_W, FRAME_BUFFER_H);
	m_sprite.Update({ 0.0f,0.0f,1.0f }, CQuaternion::Identity(), CVector3::One());

	return true;
}

void Fade::Update()
{
	switch (m_state)
	{
	case enState_fadeIn:
		m_currentAlpha -= 2.0f * 1.0f / 144.0f;
		if (m_currentAlpha <= 0.0f) {
			m_currentAlpha = 0.0f;
			m_state = enState_idle;
		}
		break;
	case enState_fadeOut:
		m_currentAlpha += 2.0f * 1.0f / 144.0f;
		if (m_currentAlpha >= 1.0f) {
			m_currentAlpha = 1.0f;
			m_state = enState_idle;
		}
		break;
	case enState_idle:
		break;
	}
}

void Fade::PostRender(RenderContext & renderContext)
{
	if (m_currentAlpha > 0.0f) {
		m_sprite.SetMulColor({ 1.0,1.0,1.0,m_currentAlpha });
		m_sprite.Draw(
			g_camera2D.GetViewMatrix(),
			g_camera2D.GetProjectionMatrix()
		);
	}
}
