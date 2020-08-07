#include "stdafx.h"
#include "TitleScene.h"
#include "Fade.h"
#include "BattleScenes/BattleScenes.h"
#include "NetScenes/NetScenes.h"

const CVector3 TitleScene::m_colorGray = { 0.4f ,0.4f ,0.4f };		//グレーの設定。

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	DeleteGO(m_sprite);
	DeleteGO(m_bgm);
	for (auto sp : m_menuSprite) {
		DeleteGO(sp);
	}

}

bool TitleScene::Start()
{
	//タイトルのスプライト。
	m_sprite = NewGO<prefab::SpriteRender>(1);
	m_sprite->Init(L"Assets/sprite/PreTitle.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);

	//メニューのスプライト。
	m_menuSprite[enMenu_Single] = NewGO<prefab::SpriteRender>(2);	//一人プレイ。
	m_menuSprite[enMenu_Single]->Init(L"Assets/sprite/CPUBattle.dds", 400, 100);
	m_menuSprite[enMenu_Single]->SetPosition({ 0.0f,-100.0f,4.0f });

	m_menuSprite[enMenu_Net] = NewGO<prefab::SpriteRender>(2);		//通信プレイ。
	m_menuSprite[enMenu_Net]->Init(L"Assets/sprite/MultiBattle.dds", 400, 100);
	m_menuSprite[enMenu_Net]->SetPosition({ 0.0f,-200.0f,4.0f });

	m_bgm = NewGO<prefab::CSoundSource>(0);
	m_bgm->Init(L"Assets/sound/bgm/bgm_title.wav");
	m_bgm->Play(true);
	m_bgm->SetVolume(m_bgmVol);

	//メニューの乗算カラー初期化。
	for (int i = 0; i < enMenu_Num; i++)
	{
		if (i == m_menuNum) {
			m_menuSprite[i]->SetMulColor(CVector3::One());
		}
		else {
			m_menuSprite[i]->SetMulColor(m_colorGray);
		}
	}

	//フェードの処理。
	m_fade = Fade::GetInstance();
	m_fade->StartFadeIn();

	return true;
}

void TitleScene::Update()
{
	//rand();
	switch (m_state)
	{
	case enState_inTitle:
		if (m_bgmVol < 1.0f); {
			m_bgmVol += g_gameTime.GetFrameDeltaTime();
			m_bgmVol = min(1.0f, m_bgmVol);
		}
		if (!m_fade->IsFade())
			m_state = enState_idle;		//フェードインが終わればステートを切り替える。
		break;
	case enState_idle:
		SelectMenu();	//メニュー選択。
		DrawMenu();		//メニューの描画。

		//Aボタンでシーン切り替え。
		if (g_pad[0].IsTrigger(enButtonA))
		{
			//決定音を単発再生。
			auto sound = NewGO<prefab::CSoundSource>(0, "cursor");
			sound->Init(L"Assets/sound/cursor/decision17.wav");
			sound->Play(false);
			sound->SetVolume(SOUND_VOL);

			m_fade->StartFadeOut();
			m_state = enState_inGame;	//Aボタンが押されたらステートを切り替える。
		}
		break;
	case enState_inGame:
		if (m_bgmVol > 0.0f); {
			m_bgmVol -= g_gameTime.GetFrameDeltaTime();
			m_bgmVol = max(0.0f, m_bgmVol);
		}
		if (!m_fade->IsFade())
		{
			//ゲーム遷移。
			switch (m_menuNum)
			{
			case enMenu_Single:
				NewGO<BattleScenes>(0);
				break;
			case enMenu_Net:
				NewGO<NetScenes>(0,"NetScenes");
				break;
			}
			DeleteGO(this);
		}
	}
	m_bgm->SetVolume(m_bgmVol * SOUND_VOL);
}

void TitleScene::SelectMenu()
{
	//メニューの選択。
	if (g_pad[0].IsTrigger(enButtonDown))
	{
		SoundCursor();

		m_menuNum++;
		//最大まで行ったら元に戻る。
		m_menuNum %= enMenu_Num;
	}
	else if (g_pad[0].IsTrigger(enButtonUp))
	{
		SoundCursor();

		m_menuNum--;
		//最小まで行ったら最大に
		m_menuNum += enMenu_Num;
		m_menuNum %= enMenu_Num;
	}
}

void TitleScene::DrawMenu()
{
	for(int i = 0;i<enMenu_Num;i++)
	{
		if (i == m_menuNum) {
			m_menuSprite[i]->SetMulColor(CVector3::One());
		}
		else {
			m_menuSprite[i]->SetMulColor(m_colorGray);
		}
	}
}

void TitleScene::SoundCursor()
{
	//カーソル音を単発再生。
	auto sound = NewGO<prefab::CSoundSource>(0, "cursor");
	sound->Init(L"Assets/sound/cursor/cursor2.wav");
	sound->Play(false);
	sound->SetVolume(SOUND_VOL);
}
