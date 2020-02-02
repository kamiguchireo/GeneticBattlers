#pragma once
class Fade;

class TitleScene : public IGameObject
{
public:
	TitleScene();
	~TitleScene();

	bool Start();
	void Update();

private:
	enum State {
		enState_inTitle,	//!<タイトルシーン。
		enState_idle,		//!<入力受付状態。
		enState_inGame,		//!<インゲーム。
	};

	State m_state = enState_inTitle;		//状態。
	Fade* m_fade = nullptr;					//フェードのポインタ。
	prefab::SpriteRender* m_sprite = nullptr;	//スプライトレンダー。
	//CVector4 m_color = CVector4::White();		//これもいらなくなったか？
};

