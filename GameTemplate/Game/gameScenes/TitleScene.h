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
	void SelectMenu();		//メニュー選択。
	void DrawMenu();		//メニューのα値の描画。
	void SoundCursor();		//カーソル音を単発再生する。
private:
	//フェード切り替え。
	enum State {
		enState_inTitle,	//!<タイトルシーン。
		enState_idle,		//!<入力受付状態。
		enState_inGame,		//!<インゲーム。
	};
	//メニュー切り替え。
	enum MenuList {
		enMenu_Single,		//!<一人プレイ。
		enMenu_Net,			//!<通信プレイ。
		enMenu_Num			//!<メニューの数。
	};

	State m_state = enState_inTitle;		//状態。
	int m_menuNum = enMenu_Single;			//メニュー選択番号。
	Fade* m_fade = nullptr;					//フェードのポインタ。
	prefab::SpriteRender* m_sprite = nullptr;	//スプライトレンダー。
	prefab::CSoundSource* m_bgm = nullptr;		//サウンドソース。

	prefab::SpriteRender* m_menuSprite[enMenu_Num] = { nullptr };	//選択肢用のスプライト。
	const static CVector3 m_colorGray;					//グレー色。
	float m_bgmVol = 0.0f;
	const float SOUND_VOL = 0.6f;
};

