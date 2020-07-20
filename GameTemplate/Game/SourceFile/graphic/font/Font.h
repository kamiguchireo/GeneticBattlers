#pragma once
#include "SourceFile/Noncopyable.h"

namespace Engine
{
	class Font:Engine::Noncopyable
	{
	public:
		Font();
		~Font();

		//フォントを設定
		//デフォルトのフォントから変更したい場合は
		//DirectX::SpriteFontを使用して、フォントをロードして差し替えて下さい
		void SetFont(DirectX::SpriteFont* font)
		{
			m_spriteFont = font;
		}

		//描画開始
		void Begin();
		//描画終了
		void End();

		//描画
		//text		表示したいテキスト
		//trans		平行移動
		//color		カラー
		//rot		回転
		//sacle		拡大
		//pivot		起点
		//		0.5,0.5で画像の中心が起点
		//		0.0,0.0で画像の左下
		//		1.0,1.0で画像の右上
		void Draw
			(
			wchar_t const* text,
			const CVector2& position,
			const CVector4& color = CVector4::White(),
			float rotation = 0.0f,
			float scale = 1.0f,
			CVector2 pivot = { 0.5f, 0.5f }
		);

	private:
		DirectX::SpriteBatch* m_spriteBatch = nullptr;		//スプライトバッチ
		DirectX::SpriteFont* m_spriteFont = nullptr;		//スプライトフォント
		CMatrix m_scaleMat = CMatrix::Identity();
		float kaizoudo[2] = { 1280.0f,720.0f };
	};
}