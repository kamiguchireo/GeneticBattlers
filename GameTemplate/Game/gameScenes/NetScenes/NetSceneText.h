#pragma once

enum NetState;

class NetSceneText : public IGameObject
{
public:
	NetSceneText();
	~NetSceneText();
	bool Start();
	void Update();

	void SetText(const wchar_t* text);
	void SetState(NetState state);

private:
	NetState m_state;	//ステート。

	prefab::FontRender* m_font = nullptr;

	prefab::FontRender* m_fontRender = nullptr;			//フォントレンダー。
	std::unique_ptr<DirectX::SpriteFont> m_spFont;		//スプライトフォントデータ。
	CVector3 m_color = CVector3::One();					//フォントの色。

};

