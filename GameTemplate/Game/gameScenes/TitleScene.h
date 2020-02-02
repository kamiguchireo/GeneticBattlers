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
		enState_inTitle,	//!<�^�C�g���V�[���B
		enState_idle,		//!<���͎�t��ԁB
		enState_inGame,		//!<�C���Q�[���B
	};

	State m_state = enState_inTitle;		//��ԁB
	Fade* m_fade = nullptr;					//�t�F�[�h�̃|�C���^�B
	prefab::SpriteRender* m_sprite = nullptr;	//�X�v���C�g�����_�[�B
	//CVector4 m_color = CVector4::White();		//���������Ȃ��Ȃ������H
};

