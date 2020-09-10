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
	CVector3 m_color = CVector3::One();					//フォントの色。

};

