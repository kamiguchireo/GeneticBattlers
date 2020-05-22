#pragma once
#include "SourceFile/graphic/font/FontRender.h"

class NetSceneText : public IGameObject
{
public:
	NetSceneText();
	~NetSceneText();
	bool Start();
	void Update();

private:
	prefab::FontRender* m_font = nullptr;

	prefab::FontRender* m_fontRender = nullptr;			//フォントレンダー。
	std::unique_ptr<DirectX::SpriteFont> m_spFont;		//スプライトフォントデータ。
	CVector3 m_color = CVector3::One();					//フォントの色。

};

