#include "stdafx.h"
#include "Font.h"


namespace Engine
{

	Font::Font()
	{
		m_spriteBatch = g_graphicsEngine->GetSpriteBatch();
		m_spriteFont = g_graphicsEngine->GetSpriteFont();

	};

	Font::~Font()
	{

	}

	void Font::Begin()
	{
		m_spriteBatch->Begin
		(
			DirectX::SpriteSortMode_Deferred,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			m_scaleMat
		);
	}

	void Font::End()
	{
		auto D3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();

		m_spriteBatch->End();
		D3dDeviceContext->OMSetBlendState(g_graphicsEngine->GetBlendState(), 0, 0xFFFFFFFF);
		D3dDeviceContext->RSSetState(g_graphicsEngine->GetRasterizerState());
	}

	void Font::Draw
	(
		wchar_t const* text,
		const CVector2& position,
		const CVector4& color,
		float rotation,
		float scale,
		CVector2 pivot
	)
	{
		if (text == nullptr)
		{
			return;
		}
		pivot.y = 1.0f - pivot.y;

		//座標系をスプライトと合わせる
		CVector2 pos = position;
		float frameBufferHalfWidth = kaizoudo[0] * 0.5f;
		float frameBufferHalfHeight = kaizoudo[1] * 0.5f;

		pos.x += frameBufferHalfWidth;
		pos.y = -pos.y + frameBufferHalfHeight;

		m_spriteFont->DrawString(
			m_spriteBatch,
			text,
			pos.vec,
			color,
			rotation,
			DirectX::XMFLOAT2(pivot.x,pivot.y),
			scale
		);
	}
}