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
	NetState m_state;	//�X�e�[�g�B

	prefab::FontRender* m_font = nullptr;

	prefab::FontRender* m_fontRender = nullptr;			//�t�H���g�����_�[�B
	std::unique_ptr<DirectX::SpriteFont> m_spFont;		//�X�v���C�g�t�H���g�f�[�^�B
	CVector3 m_color = CVector3::One();					//�t�H���g�̐F�B

};

