#include "stdafx.h"
#include "TitleScene.h"
#include "Fade.h"
#include "BattleScenes/BattleScenes.h"
#include "NetScenes/NetScenes.h"

const CVector3 TitleScene::m_colorGray = { 0.4f ,0.4f ,0.4f };		//�O���[�̐ݒ�B

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
	//�^�C�g���̃X�v���C�g�B
	m_sprite = NewGO<prefab::SpriteRender>(1);
	m_sprite->Init(L"Assets/sprite/PreTitle.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);

	//���j���[�̃X�v���C�g�B
	m_menuSprite[enMenu_Single] = NewGO<prefab::SpriteRender>(2);	//��l�v���C�B
	m_menuSprite[enMenu_Single]->Init(L"Assets/sprite/CPUBattle.dds", 400, 100);
	m_menuSprite[enMenu_Single]->SetPosition({ 0.0f,-100.0f,4.0f });

	m_menuSprite[enMenu_Net] = NewGO<prefab::SpriteRender>(2);		//�ʐM�v���C�B
	m_menuSprite[enMenu_Net]->Init(L"Assets/sprite/MultiBattle.dds", 400, 100);
	m_menuSprite[enMenu_Net]->SetPosition({ 0.0f,-200.0f,4.0f });

	m_bgm = NewGO<prefab::CSoundSource>(0);
	m_bgm->Init(L"Assets/sound/bgm/bgm_title.wav");
	m_bgm->Play(true);
	m_bgm->SetVolume(m_bgmVol);

	//���j���[�̏�Z�J���[�������B
	for (int i = 0; i < enMenu_Num; i++)
	{
		if (i == m_menuNum) {
			m_menuSprite[i]->SetMulColor(CVector3::One());
		}
		else {
			m_menuSprite[i]->SetMulColor(m_colorGray);
		}
	}

	//�t�F�[�h�̏����B
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
			m_state = enState_idle;		//�t�F�[�h�C�����I���΃X�e�[�g��؂�ւ���B
		break;
	case enState_idle:
		SelectMenu();	//���j���[�I���B
		DrawMenu();		//���j���[�̕`��B

		//A�{�^���ŃV�[���؂�ւ��B
		if (g_pad[0].IsTrigger(enButtonA))
		{
			//���艹��P���Đ��B
			auto sound = NewGO<prefab::CSoundSource>(0, "cursor");
			sound->Init(L"Assets/sound/cursor/decision17.wav");
			sound->Play(false);
			sound->SetVolume(SOUND_VOL);

			m_fade->StartFadeOut();
			m_state = enState_inGame;	//A�{�^���������ꂽ��X�e�[�g��؂�ւ���B
		}
		break;
	case enState_inGame:
		if (m_bgmVol > 0.0f); {
			m_bgmVol -= g_gameTime.GetFrameDeltaTime();
			m_bgmVol = max(0.0f, m_bgmVol);
		}
		if (!m_fade->IsFade())
		{
			//�Q�[���J�ځB
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
	//���j���[�̑I���B
	if (g_pad[0].IsTrigger(enButtonDown))
	{
		SoundCursor();

		m_menuNum++;
		//�ő�܂ōs�����猳�ɖ߂�B
		m_menuNum %= enMenu_Num;
	}
	else if (g_pad[0].IsTrigger(enButtonUp))
	{
		SoundCursor();

		m_menuNum--;
		//�ŏ��܂ōs������ő��
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
	//�J�[�\������P���Đ��B
	auto sound = NewGO<prefab::CSoundSource>(0, "cursor");
	sound->Init(L"Assets/sound/cursor/cursor2.wav");
	sound->Play(false);
	sound->SetVolume(SOUND_VOL);
}
