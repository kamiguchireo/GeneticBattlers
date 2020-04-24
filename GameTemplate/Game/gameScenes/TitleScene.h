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
	void SelectMenu();
private:
	enum State {
		enState_inTitle,	//!<�^�C�g���V�[���B
		enState_idle,		//!<���͎�t��ԁB
		enState_inGame,		//!<�C���Q�[���B
	};
	enum MenuList {
		enMenu_Single,
		enMenu_Net,
		enMenu_Num
	};

	State m_state = enState_inTitle;		//��ԁB
	int m_menu = enMenu_Single;		//���j���[�I���B
	Fade* m_fade = nullptr;					//�t�F�[�h�̃|�C���^�B
	prefab::SpriteRender* m_sprite = nullptr;	//�X�v���C�g�����_�[�B
	//CVector4 m_color = CVector4::White();		//���������Ȃ��Ȃ������H
};

