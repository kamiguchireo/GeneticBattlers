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
	void SelectMenu();		//���j���[�I���B
	void DrawMenu();		//���j���[�̃��l�̕`��B
	void SoundCursor();		//�J�[�\������P���Đ�����B
private:
	//�t�F�[�h�؂�ւ��B
	enum State {
		enState_inTitle,	//!<�^�C�g���V�[���B
		enState_idle,		//!<���͎�t��ԁB
		enState_inGame,		//!<�C���Q�[���B
	};
	//���j���[�؂�ւ��B
	enum MenuList {
		enMenu_Single,		//!<��l�v���C�B
		enMenu_Net,			//!<�ʐM�v���C�B
		enMenu_Num			//!<���j���[�̐��B
	};

	State m_state = enState_inTitle;		//��ԁB
	int m_menuNum = enMenu_Single;			//���j���[�I��ԍ��B
	Fade* m_fade = nullptr;					//�t�F�[�h�̃|�C���^�B
	prefab::SpriteRender* m_sprite = nullptr;	//�X�v���C�g�����_�[�B
	prefab::CSoundSource* m_bgm = nullptr;		//�T�E���h�\�[�X�B

	prefab::SpriteRender* m_menuSprite[enMenu_Num] = { nullptr };	//�I�����p�̃X�v���C�g�B
	const static CVector3 m_colorGray;					//�O���[�F�B
	float m_bgmVol = 0.0f;
	const float SOUND_VOL = 0.6f;
};

